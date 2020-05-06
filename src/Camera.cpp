#include "Camera.hpp"

namespace EvelEngine {

  Camera::Camera(int w, int h) : _w(w), _h(h)
  {
    _x = 0;
    _y = 0;
  }

  Camera::~Camera()
  {

  }

  void Camera::setPosition(int x, int y)
  {
    _x = x;
    _y = y;
  }

  Vector2D Camera::getPosition() 
  {
    return Vector2D{_x, _y};
  }

  int Camera::x()
  {
    return _x;
  }

  int Camera::y()
  {
    return _y;
  }

}
