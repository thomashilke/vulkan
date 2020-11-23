#include "instance_builder.hpp"

#include <algorithm>
#include <stdexcept>
#include <vulkan/vulkan_core.h>

#include "../string_builder.hpp"
#include "instance.hpp"
#include "api_call.hpp"

std::set<std::string> thh::vk::instance_builder::supported_vulkan_extensions()
{
  uint32_t count{0};
  call(vkEnumerateInstanceExtensionProperties, nullptr, &count, nullptr);

  std::vector<VkExtensionProperties> extension_properties(count);
  call(vkEnumerateInstanceExtensionProperties, nullptr, &count, extension_properties.data());

  std::set<std::string> extension_names;
  for (auto extension: extension_properties)
  {
    extension_names.insert(extension.extensionName);
  }
  
  return extension_names;
}

thh::vk::instance_builder& thh::vk::instance_builder::with_extension(const std::string& extension_name)
{
  if (available_extensions.find(extension_name) != available_extensions.end())
  {
    enabled_extensions.insert(extension_name);
  }
  else
  {
    throw std::runtime_error(thh::string_builder("Unknown extension name \"")(extension_name)("\"").str());
  }

  return *this;
}

std::shared_ptr<thh::vk::instance> thh::vk::instance_builder::build() const
{
  std::vector<const char*> extensions(enabled_extensions.size(), nullptr);
  std::transform(
    enabled_extensions.begin(), enabled_extensions.end(),
    extensions.begin(),
    [](const std::string& extension_name)
    {
      return extension_name.c_str();
    });

  VkApplicationInfo applicationInfo{};
  applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  applicationInfo.pApplicationName = "application";
  applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  applicationInfo.pEngineName = "application engine";
  applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  applicationInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo instanceCreateInfo{};
  instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instanceCreateInfo.pApplicationInfo = &applicationInfo;
  instanceCreateInfo.enabledExtensionCount = enabled_extensions.size();
  instanceCreateInfo.ppEnabledExtensionNames = enabled_extensions.size() > 0 ? extensions.data() : nullptr;
  instanceCreateInfo.enabledLayerCount = 0;
  instanceCreateInfo.ppEnabledLayerNames = nullptr;

  VkInstance vulkan_instance;
  call(vkCreateInstance, &instanceCreateInfo, nullptr, &vulkan_instance);
  
  return std::shared_ptr<thh::vk::instance>(new instance(vulkan_instance));
}
