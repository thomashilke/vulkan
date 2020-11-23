#ifndef API_CALL_ERROR_H
#define API_CALL_ERROR_H

#include <exception>
#include <string>

namespace thh::vk
{
  class api_call_error: public std::exception
  {
  public:
    explicit api_call_error(const std::string& message)
      : std::exception(), message(message)
    {}

    virtual const char* what() const throw() override
    {
      return message.c_str();
    }
    
  private:
    const std::string message;
  };
}

#endif /* API_CALL_ERROR_H */
