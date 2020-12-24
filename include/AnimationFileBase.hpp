#ifndef __EVEL_ENGINE_ANIMATION_FILE_BASE_HPP__
#define __EVEL_ENGINE_ANIMATION_FILE_BASE_HPP__

#include <string>
#include <vector>

namespace EvelEngine {

    ///
    /// \struct Frame
    /// \brief Animation frame
    ///
    struct Frame
    {
        uint16_t index;     ///< Frame number
        uint16_t x;         ///< X Position of the frame on the texture
        uint16_t y;         ///< Y Position
        uint16_t w;         ///< Width of the frame
        uint16_t h;         ///< Height of the frame
    };

    ///
    /// \struct FrameRange
    /// \brief Set of animated frames (tag)
    ///
    struct FrameRange 
    {
        std::string tag;      ///< Name of the animation set
        uint8_t start;               ///< First frame of the animation set
        uint8_t end;                 ///< Last frame of the animation set
        uint8_t frames;             ///< Number of frames in this tag
        uint8_t direction;          ///< Direction of the animation
    };

    // Used to compare indeces of frames for sorting
    bool compare_index(const Frame &a, const Frame &b);

    ///
    /// \class AnimationFileBase
    /// \brief Base-class for all variants of animation files
    /// 
    /// AnimationFileBase is a base class for all different kinds of 
    /// animation files. 
    /// \sa AnimationFileJSON
    class AnimationFileBase {
        public:
            //! Constructor
            /*!
             * Creates Animation
             * 
             * \param filename - path to the animation specification
             */
            AnimationFileBase(const std::string& filename);
            //! Destructor
            ~AnimationFileBase();

            //! Returns name (path) of the animation specification file
            /*!
              \return path to file
             */
            const std::string& filename() const;

            //! Returns path to texture file extracted from animation specification file
            /*!
             * During unmarshaling of the specification file we can extract path to actual 
             * texture for the animation (tileset)
             * \return path to file
            */ 
            const std::string& texture() const;

            //! Unmarshal specified file
            /*!
             * Pure virtual - must be overriden
             */
            virtual std::vector<Frame> unmarshal() = 0;

            //! Marshal specified file
            /*!
             * Pure virtual - must be overriden
             */
            virtual std::string marshal() = 0;

            //! Returns full collection of frames after unmarshaling
            /*!
             * \return vector of Frame objects
             * \sa Frame
             */
            std::vector<Frame> get();

            //! Return extracted tags
            /*!
             * Return tags extracted from a file
             *
             * \return vector of FrameRange objects
             */
            std::vector<FrameRange> tags();

            //! Set frames to be marshaled
            void set(std::vector<Frame> frames);

        protected:
            std::string _filename;          ///< Filename of a data file
            std::string _texture;           ///< Filename of a texture
            std::vector<Frame> _frames;     ///< Frames extracted from data file
            std::vector<FrameRange> _tags;  ///< Frame tags
    };
}

#endif
