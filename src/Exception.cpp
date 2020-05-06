#include "Exception.hpp"

namespace EvelEngine 
{
  Exception::Exception(int code) noexcept : _code(code)
  {

  } 

  Exception::Exception(const std::string& msg, int code) noexcept : _msg(msg), _code(code)
  {

  }

  Exception::~Exception()
  {

  }

  const char* Exception::name() const throw()
  {
    return "AI Exception";
  }

  const char* Exception::className() const throw()
  {
    return typeid(*this).name();
  }

  const char* Exception::what() const throw()
  {
    return name();
  }

  std::string Exception::displayText() const 
  {
    std::string output = what();
    if (!_msg.empty()) 
    {
      output.append(": ");
      output.append(_msg);
    }
    return output;
  }

}
