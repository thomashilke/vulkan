#include <cstdlib>
#include <iostream>

#include "application.hpp"
#include "vk/api_call_error.hpp"

int main()
{
    thh::application app;

    try
    {
	app.run();
    }
    catch (const thh::vk::api_call_error& e)
    {
      std::cerr << "Vulkan API call exception: "
		<< e.what()
		<< std::endl;
      
      return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
	std::cerr << e.what() << std::endl;
	return EXIT_FAILURE;
    }
  
    return EXIT_SUCCESS;
}
