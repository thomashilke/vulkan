#ifndef INSTANCE_BUILDER_H
#define INSTANCE_BUILDER_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace thh::vk
{
  class instance;
  
  class instance_builder
  {
  public:
    instance_builder(const std::string& application_name, const std::string& engine_name)
      : application_name(application_name), engine_name(engine_name),
	enabled_extensions(), available_extensions(supported_vulkan_extensions()),
	enabled_validation_layers(), available_validation_layers(supported_vulkan_validation_layers())
    {
      std::cerr << "Available extensions: ";
      std::copy(available_extensions.begin(), available_extensions.end(),
		std::ostream_iterator<std::string>(std::cerr, ", "));
      std::cerr << std::endl << std::endl;
      
      std::cerr << "Available validation layers: ";
      std::copy(available_validation_layers.begin(), available_validation_layers.end(),
		std::ostream_iterator<std::string>(std::cerr, ", "));
      std::cerr << std::endl;
    }

    instance_builder& with_extension(const std::string& extension_name);
    instance_builder& with_validation_layer(const std::string& validation_layer_name);

    std::shared_ptr<instance> build() const;
    
  private:
    static std::set<std::string> supported_vulkan_extensions();
    static std::set<std::string> supported_vulkan_validation_layers();
    
  private:
    const std::string application_name;
    const std::string engine_name;

    std::set<std::string> enabled_extensions;
    std::set<std::string> available_extensions;

    std::set<std::string> enabled_validation_layers;
    std::set<std::string> available_validation_layers;
  };
}

#endif /* INSTANCE_BUILDER_H */
