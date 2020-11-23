#ifndef API_CALL_H
#define API_CALL_H

#include <utility>
#include <vulkan/vulkan_core.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "api_call_error.hpp"

namespace thh::vk
{
  template<class ...Ps, class ...As>
  void call(VkResult (*function)(Ps...), As&& ...as)
  {
    VkResult result{function(std::forward<As>(as)...)};

    switch (result)
    {
    case VK_ERROR_OUT_OF_HOST_MEMORY:
      throw api_call_error("VK_ERROR_OUT_OF_HOST_MEMORY");
      
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
      throw api_call_error("VK_ERROR_OUT_OF_DEVICE_MEMORY");
      
    case VK_ERROR_INITIALIZATION_FAILED:
      throw api_call_error("VK_ERROR_INITIALIZATION_FAILED");
      
    case VK_ERROR_LAYER_NOT_PRESENT:
      throw api_call_error("VK_ERROR_LAYER_NOT_PRESENT");
      
    case VK_ERROR_EXTENSION_NOT_PRESENT:
      throw api_call_error("VK_ERROR_EXTENSION_NOT_PRESENT");
      
    case VK_ERROR_INCOMPATIBLE_DRIVER:
      throw api_call_error("VK_ERROR_INCOMPATIBLE_DRIVER");

    default:
      throw api_call_error("Unknown error.");
    }
  }
}

#endif /* API_CALL_H */
