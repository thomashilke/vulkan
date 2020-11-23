#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <sstream>

namespace thh
{
  class string_builder
  {
  public:
    template<typename T>
    explicit string_builder(T&& v)
    {
      stream << v;
    }

    template<typename T>
    string_builder& operator()(T&& v)
    {
      stream << v;
      return *this;
    }

    std::string str() const
    {
      return stream.str();
    }

  private:
    std::ostringstream stream;
  };
}

#endif /* STRING_BUILDER_H */
