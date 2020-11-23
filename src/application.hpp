#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdexcept>

#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "vk/instance.hpp"

namespace thh
{
  class application
  {
  public:
    void run()
    {

    }

  private:
    void init_vulkan()
    {
    
    }

    void main_loop()
    {

    }

    void cleanup()
    {

    }

    void create_instance()
    {
      instance = vk::instance::builder("application", "application engine").build();
    }

    std::shared_ptr<vk::instance> instance;
  };
}

#endif /* APPLICATION_H */
