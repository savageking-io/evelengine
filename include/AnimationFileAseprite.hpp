#ifndef __EVEL_ENGINE_ANIMATION_FILE_JSON_HPP__
#define __EVEL_ENGINE_ANIMATION_FILE_JSON_HPP__

#include <fstream>
#include <string>
#include <vector>

#include "json/json.h"

#include "AnimationFileBase.hpp"
#include "Engine.hpp"
#include "Log.hpp"

#define EXTRACT_ANIMATION_META false

namespace EvelEngine
{
    ///
    /// \class AnimationFileAseprite
    /// \brief Animation file in JSON format
    /// 
    /// Recognizes JSON file exported from Aseprite
    /// \sa AnimationFileBase
    class AnimationFileAseprite : public AnimationFileBase
    {
        public:
            //! Constructor
            /*!
             * Creates Animation
             * 
             * \param filename - path to the animation specification
             */
            AnimationFileAseprite(const std::string& jsonfile);

            //! Constructor
            /*!
             * Creates Animation
             * 
             * \param filename - path to the animation specification
             */
            ~AnimationFileAseprite();

            //! Unmarshal provided JSON file
            /*!
             * This method will read input file using istream.
             * Method will extract meta data if EXTRACT_ANIMATION_META set to true. 
             * Even this macros is set to false, path to texture file and 
             * animation breakdown will be extracted
             * 
             * \return vector of frames
             */
            std::vector<Frame> unmarshal();
            
            //! Marshal animation data into JSON
            std::string marshal();

            
        private:
            Log* _log;
    };
}

#endif
