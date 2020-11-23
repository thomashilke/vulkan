#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdexcept>

#include <vulkan/vulkan_core.h>

#include "vk/instance.hpp"

namespace thh
{
  class application
  {
  public:
    application()
    {
      init_vulkan();
    }
    
    void run()
    {

    }

  private:
    void init_vulkan()
    {
      create_instance();
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
