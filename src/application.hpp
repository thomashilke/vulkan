#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdexcept>

#include <vulkan/vulkan_core.h>

#include "vk/instance.hpp"
#include "vk/physical_devices_collection.hpp"

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
      instance =
	vk::instance::builder("My application", "My application engine")
	.with_extension("VK_KHR_surface")
	//.with_validation_layer("VK_LAYER_LUNARG_api_dump")
	.build();
      
      vk::physical_devices_collection::from_instance(*instance);
    }

    std::shared_ptr<vk::instance> instance;
  };
}

#endif /* APPLICATION_H */
