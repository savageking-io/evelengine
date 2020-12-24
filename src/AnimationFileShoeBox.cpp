#include "AnimationFileShoeBox.hpp"

#include <fstream>

#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/SAX/SAXException.h"
#include "Poco/NumberParser.h"
#include "Poco/Path.h"

#include "Log.hpp"

namespace EvelEngine {
    AnimationFileShoeBox::AnimationFileShoeBox(const std::string& xmlfile) : AnimationFileBase(xmlfile)
    {
        _log = Engine::get()->log();
    }

    AnimationFileShoeBox::~AnimationFileShoeBox()
    {

    }

    std::vector<Frame> AnimationFileShoeBox::unmarshal()
    {
        _log->info("Reading ShoeBox animation file from {0}", _filename); 

        try {
            // TODO: Check if file exists
            std::ifstream fs(_filename);
            Poco::XML::InputSource src(fs);

            Poco::XML::DOMParser parser;
            Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&src);

            Poco::XML::NodeIterator it(pDoc, Poco::XML::NodeFilter::SHOW_ELEMENT);
            auto root = it.root();
            _log->debug("Root element: {0}", root->nodeName());
            Poco::XML::Node* pNode = it.nextNode();

            std::string spriteFile = "";

            int frameIndex = 0;
            while (pNode) {    
                if (pNode->nodeName() == "TextureAtlas") {
                    auto attr = pNode->attributes();
                    spriteFile = attr->getNamedItem("imagePath")->nodeValue();
                    _log->debug("Associated sprite file: {0}", spriteFile);
                    addSpriteFile(spriteFile);
                    attr->release();
                    pNode = it.nextNode();
                    continue;
                } 
                if (pNode->nodeName() != "SubTexture") {
                    pNode = it.nextNode();   
                    continue;
                }
                
                auto attr = pNode->attributes();
                std::string name = attr->getNamedItem("name")->nodeValue();

                if (isTagHasNumbers(name)) {
                    _log->debug("Item with name {0} has a digit - probably it's a sequence", name);
                    if (isExistingTag(name)) {
                        addIndexToTag(name, frameIndex);
                    } else {
                        createNewTag(name, frameIndex);
                    }
                } else {
                    createNewTag(name, frameIndex);
                }

                int x = Poco::NumberParser::parse(attr->getNamedItem("x")->nodeValue());
                int y = Poco::NumberParser::parse(attr->getNamedItem("y")->nodeValue());
                int w = Poco::NumberParser::parse(attr->getNamedItem("width")->nodeValue());
                int h = Poco::NumberParser::parse(attr->getNamedItem("height")->nodeValue());

                appendFrame(frameIndex, x, y, w, h);
                attr->release();
                pNode = it.nextNode();
                frameIndex++;
            }
        } catch (Poco::XML::SAXParseException& e) {
            _log->error("Failed to parse ShoeBox XML file: {0}", e.message());
            return std::vector<Frame>();
        }

        return std::vector<Frame>();
    }

    std::string AnimationFileShoeBox::marshal()
    {
        return "";
    }

    bool AnimationFileShoeBox::isExistingTag(const std::string& tag) const
    {
        _log->debug("Checking if tag {0} exists", tag);
        for (const auto& t : _tags) {
            if (tag.substr(0, t.tag.size()) == t.tag) {
                _log->debug("Tag {0} exists: {1}", tag, tag.substr(0, t.tag.size()));
                return true;
            }
        }
        _log->debug("Tag {0} wasn't found", tag);
        return false;
    }

    void AnimationFileShoeBox::addIndexToTag(const std::string& tag, int index)
    {
        auto puretag = purifyTag(tag);
        for (auto it = _tags.begin(); it != _tags.end(); it++)
        {
            if (it->tag == puretag) {
                it->end = index;
                it->frames += 1;
                break;
            }
        }
    }

    void AnimationFileShoeBox::createNewTag(const std::string& tag, int index)
    {
        std::string puretag = purifyTag(tag);
        _log->debug("Creating new tag: {0}", puretag);
        if (puretag.size() == 0) return;

        FrameRange r;
        r.direction = 1;
        r.tag = puretag;
        r.start = index;
        r.end = index;
        r.frames = 1;
        _tags.push_back(r);
        _log->debug("New tag {0} has been saved", puretag);
    }

    const std::string AnimationFileShoeBox::purifyTag(const std::string& tag) const
    {
        _log->debug("Purifying tag {0}", tag);
        if (isTagHasNumbers(tag)) {
            _log->debug("Tag {0} has digits. Removing", tag);
            std::string puretag = tag.substr(0, tag.size() - 1);
            return puretag;
        }
        return tag;
    }

    bool AnimationFileShoeBox::isTagHasNumbers(const std::string& tag) const
    {
        return std::any_of(tag.begin(), tag.end(), ::isdigit);
    }

    void AnimationFileShoeBox::appendFrame(int index, int x, int y, int w, int h)
    {
        _log->debug("Adding new frame {0}: {1}-{2} {3} {4}", index, x, y, w, h);
        Frame f;
        f.index = index;
        f.x = x;
        f.y = y;
        f.w = w;
        f.h = h;
        _frames.push_back(f);
    }

    void AnimationFileShoeBox::addSpriteFile(const std::string& spritefile)
    {
        // Extract path from xml file
        Poco::Path f(spritefile);
        Poco::Path p(_filename);
        Poco::Path dirname = p.makeDirectory().popDirectory();
        _log->debug("Extracted dirname from filename {0}: {1}", _filename, dirname.toString());

        _texture = dirname.append(f).toString();
    }
}