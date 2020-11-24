#ifndef INSTANCE_H
#define INSTANCE_H

#include <stdexcept>

#include <vulkan/vulkan_core.h>

#include "instance_builder.hpp"

namespace thh::vk
{
  class instance
  {
    friend class instance_builder;
        
  public:
    using builder = instance_builder;
    
    instance(const instance&) = delete;
    instance(instance&&) = delete;
    instance& operator=(const instance&) = delete;
    instance& operator=(instance&&) = delete;

    ~instance()
    {
      vkDestroyInstance(vulkan_instance, nullptr);
    }

    const VkInstance& handle() const
    {
      return vulkan_instance;
    }
      
  private:
    instance(VkInstance vulkan_instance): vulkan_instance(vulkan_instance)
    {
      if (vulkan_instance == VK_NULL_HANDLE)
      {
	throw std::invalid_argument("The vulkan instance cannot be null.");
      }
    }

  private:
    VkInstance vulkan_instance;
  };
}

#endif /* INSTANCE_H */
