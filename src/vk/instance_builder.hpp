#ifndef INSTANCE_BUILDER_H
#define INSTANCE_BUILDER_H

#include <memory>
#include <string>

namespace thh::vk
{
  class instance;
  
  class instance_builder
  {
  public:
    instance_builder(const std::string& application_name, const std::string& engine_name)
      : application_name(application_name), engine_name(engine_name)
    {}

    std::shared_ptr<instance> build() const;
    
  private:
    const std::string application_name;
    const std::string engine_name;
  };
}

#endif /* INSTANCE_BUILDER_H */
