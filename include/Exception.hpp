#ifndef __EVEL_ENGINE_EXCEPTION_HPP__
#define __EVEL_ENGINE_EXCEPTION_HPP__

#include <exception>
#include <string>

namespace EvelEngine 
{
  class Exception : public std::exception 
  {
    public:
    Exception(int code) noexcept;
    Exception(const std::string& msg, int code) noexcept;
    ~Exception();

    virtual const char* name() const throw();
    virtual const char* className() const throw();
    virtual const char* what() const throw();

    const std::string& message() const;
    int code() const;

    std::string displayText() const;

    private:
    std::string _msg; 
    int _code;
  };

  inline const std::string& Exception::message() const { return _msg; }
  inline int Exception::code() const { return _code; }
}

#endif
