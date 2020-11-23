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
	enabled_extensions(), available_extensions(supported_vulkan_extensions())
    {
      std::cerr << "Available extensions: ";
      std::copy(available_extensions.begin(), available_extensions.end(),
		std::ostream_iterator<std::string>(std::cerr, ", "));
      std::cerr << std::endl;
    }

    instance_builder& with_extension(const std::string& extension_name);

    std::shared_ptr<instance> build() const;
    
  private:
    static std::set<std::string> supported_vulkan_extensions();

  private:
    const std::string application_name;
    const std::string engine_name;

    std::set<std::string> enabled_extensions;
    std::set<std::string> available_extensions;
  };
}

#endif /* INSTANCE_BUILDER_H */
