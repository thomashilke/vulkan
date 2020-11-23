#ifndef API_CALL_ERROR_H
#define API_CALL_ERROR_H

#include <exception>
#include <string>

#include <vulkan/vulkan_core.h>

#include "../string_builder.hpp"

namespace thh::vk
{
  class api_call_error: public std::exception
  {
  public:
    api_call_error(const std::string& message, VkResult error_code)
      : std::exception(), message(string_builder(message)("(error code ")(static_cast<int>(error_code))(")").str())
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
