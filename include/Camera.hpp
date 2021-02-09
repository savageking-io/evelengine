#ifndef __EVEL_ENGINE_CAMERA_HPP__
#define __EVEL_ENGINE_CAMERA_HPP__

#include "Velocity.hpp"
#include "Geometry.hpp"

namespace EvelEngine {
    class Camera 
    {
        public:
            //! Constructor
            Camera(int w, int h);

            //! Destructor
            ~Camera();

            //! Update position of the camera in a game world
            void setPosition(int x, int y);

            //! Returns current position of the camera in a game world
            Vector2D getPosition();

            //! Returns X coordinate of the camera (relative to game world)
            int x();

            //! Returns Y coordinate of the camera (relative to game world)
            int y();

            void tick(double delta);

	    Velocity* velocity();
        private:
            int _x; ///< X Position of the camera
            int _y; ///< Y Position of the camera
            int _w; ///< Width of the screen
            int _h; ///< Height of the screen
	    Velocity _velocity;
    };

}

#endif
