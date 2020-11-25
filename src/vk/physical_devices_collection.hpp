#ifndef PHYSICAL_DEVICES_COLLECTION_H
#define PHYSICAL_DEVICES_COLLECTION_H

#include <algorithm>
#include <iterator>
#include <map>

#include <vulkan/vulkan_core.h>

#include "api_call.hpp"
#include "instance.hpp"

namespace thh::vk
{
  class physical_devices_collection
  {
  public:
    static physical_devices_collection from_instance(instance& vulkan_instance)
    {
      uint32_t physical_devices_count{0};
      call(vkEnumeratePhysicalDevices, vulkan_instance.handle(), &physical_devices_count, nullptr);
      
      std::vector<VkPhysicalDevice> physical_devices(physical_devices_count, VK_NULL_HANDLE);
      call(vkEnumeratePhysicalDevices, vulkan_instance.handle(), &physical_devices_count, physical_devices.data());


      physical_device_properties_t physical_device_properties;
      std::transform(physical_devices.begin(), physical_devices.end(),
		     std::inserter<physical_device_properties_t>(
		       physical_device_properties, physical_device_properties.begin()),
		     [](const VkPhysicalDevice& physical_device)
		     {
		       VkPhysicalDeviceProperties properties;
		       vkGetPhysicalDeviceProperties(physical_device, &properties);
		       return std::make_pair(physical_device, properties);
		     });

      return physical_devices_collection((physical_device_properties));
    }

  private:
    using physical_device_properties_t = std::map<VkPhysicalDevice, VkPhysicalDeviceProperties>;
    
    explicit physical_devices_collection(const physical_device_properties_t& physical_device_properties)
      : physical_device_properties(physical_device_properties)
    {
      std::cerr << "Physical devices: ";
      std::transform(physical_device_properties.begin(), physical_device_properties.end(),
		     std::ostream_iterator<const char*>(std::cerr, ", "),
		     [](const std::pair<const VkPhysicalDevice, VkPhysicalDeviceProperties>& p)
		     {
		       return p.second.deviceName;
		     });
    }

  private:
    physical_device_properties_t physical_device_properties;
  };
}

#endif /* PHYSICAL_DEVICES_COLLECTION_H */
