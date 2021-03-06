#include "instance_builder.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vulkan/vulkan_core.h>

#include "../string_builder.hpp"
#include "instance.hpp"
#include "api_call.hpp"

std::set<std::string> thh::vk::instance_builder::supported_vulkan_extensions()
{
  uint32_t count{0};
  call(vkEnumerateInstanceExtensionProperties, nullptr, &count, nullptr);

  std::vector<VkExtensionProperties> extensions_properties(count);
  call(vkEnumerateInstanceExtensionProperties, nullptr, &count,  extensions_properties.data());

  std::set<std::string> extensions_name;
  for (auto extension_properties : extensions_properties) {
    extensions_name.insert(extension_properties.extensionName);
  }

  return extensions_name;
}

std::set<std::string> thh::vk::instance_builder::supported_vulkan_validation_layers()
{
  uint32_t count{0};
  call(vkEnumerateInstanceLayerProperties, &count, nullptr);

  std::vector<VkLayerProperties> layers_properties(count);
  call(vkEnumerateInstanceLayerProperties, &count, layers_properties.data());

  std::set<std::string> layers_name;
  for (auto layer_properties : layers_properties)
  {
    layers_name.insert(layer_properties.layerName);
  }

  return layers_name;
}

thh::vk::instance_builder& thh::vk::instance_builder::with_extension(const std::string& extension_name)
{
  if (available_extensions.find(extension_name) != available_extensions.end())
  {
    enabled_extensions.insert(extension_name);
  }
  else
  {
    throw std::runtime_error(thh::string_builder("Unknown extension \"")(extension_name)("\"").str());
  }

  return *this;
}

thh::vk::instance_builder& thh::vk::instance_builder::with_validation_layer(const std::string& validation_layer_name)
{
  if (available_validation_layers.find(validation_layer_name) != available_validation_layers.end())
  {
    enabled_validation_layers.insert(validation_layer_name);
  }
  else
  {
    throw std::runtime_error(thh::string_builder("Unknown validation layer \"")(validation_layer_name)("\"").str());
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

  std::vector<const char*> validation_layers(enabled_validation_layers.size(), nullptr);
  std::transform(
    enabled_validation_layers.begin(), enabled_validation_layers.end(),
    validation_layers.begin(),
    [](const std::string& validation_layer_name)
    {
      return validation_layer_name.c_str();
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
  instanceCreateInfo.enabledLayerCount = enabled_validation_layers.size();
  instanceCreateInfo.ppEnabledLayerNames = enabled_validation_layers.size() > 0 ? validation_layers.data() : nullptr;

  VkInstance vulkan_instance{VK_NULL_HANDLE};
  call(vkCreateInstance, &instanceCreateInfo, nullptr, &vulkan_instance);

  return std::shared_ptr<thh::vk::instance>(new instance(vulkan_instance));
}
