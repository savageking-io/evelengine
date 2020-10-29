#ifndef __EVEL_ENGINE_ANIMATED_OBJECT_HPP__
#define __EVEL_ENGINE_ANIMATED_OBJECT_HPP__

#include "Object.hpp"
#include "ResourceManager.hpp"
#include "Log.hpp"
#include "Timer.hpp"

#include "AnimationFileBase.hpp"
#include "AnimationFileJSON.hpp"

#define FPS 1000.0f / 30

namespace EvelEngine {

    ///
    /// \class AnimatedObject
    /// \brief Game Object that can play animation
    /// 
    /// Animated object can have animation data and play during the render
    /// with specified animation speed
    /// \sa Object
    class AnimatedObject : public Object {
        public:

            //! Constructor
            /*!
             * Initializes Animated Object
             * It's recommended to use NewAnimatedObject() function to create
             * new animated objects
             *
             * \param id - Unique identified of the object
             * \param manager - reference to ResourceManager
             * \param renderer - reference to SDL_Renderer
             * \param filename - path to animation data file
             * \param log - reference to Log object
             * \sa NewAnimatedObject()
             */
            AnimatedObject(const std::string& id, ResourceManager* manager, SDL_Renderer* renderer, const std::string& filename, Log* log);

            //! Destructor
            ~AnimatedObject();

            //! Load animation from provided animation data file
            /*!
             * This method will request animation data file from ResourceManager
             * If manager was able to load and provide file (meaning unmarshaling went well)
             * Method will request texture file and will load it like a normal object
             *
             * \return bool whether load was successful or not
             * \sa AnimationFileBase AnimationFileJSON
             */
            bool load();

            //! Render object's texture with animation
            void render(Camera* camera, double delta);

            //! Set current animation tag
            /*!
             * \param tag - name of the animation
             * \return bool whether specified animation tag exists or not
             */
            bool animation(const std::string& tag);

            //! Returns current animation tag
            /*!
             * \return animation tag
             */
            const FrameRange* animation() const;

            //! Returns a list of tags
            /*!
             * \return vector of tags
             */
            std::vector<FrameRange> tagsList();
        private:
            // std::string _animation;                     ///< Current animation
            std::vector<std::string> _animations;       ///< List of animations
            std::vector<Frame> _frames;                 ///< All frames
            std::map<std::string, FrameRange> _tags;    ///< Animation tags
            int _frame;                                 ///< Current frame
            Uint32 _fd;
            FrameRange* _animation;
            Uint32 _lastTick;
            Timer* _timer;
    };

    //! Create New Animated Object
    /*!
     * This function will create and initialize new AnimatedObject and return it
     * as a shared pointer
     *
     * \return shared_ptr<AnimatedObject> new object or nullptr if object creation failed
     * \sa AnimatedObject
     */
    std::shared_ptr<AnimatedObject> NewAnimatedObject(const std::string& id, const std::string& filename);
}

#endif
