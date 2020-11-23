LDFLAGS = -lglfw -lvulkan -ldl -lpthread
CXXFLAGS = --std=c++17 -g
CXX = clang++
LD = clang++

.PHONY: test clean

main: main.o application.o vk/instance.o vk/instance_builder.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

vk/instance.o: vk/instance.cpp vk/instance.hpp
vk/instance_builder.o: vk/instance_builder.cpp vk/instance_builder.hpp vk/instance.hpp
application.o: application.cpp application.hpp vk/instance.hpp vk/instance_builder.hpp
main.cpp: application.hpp vk/instance.hpp vk/instance_builder.hpp string_builder.hpp

test: main
	./main
clean:
	find . -name "*.o" -delete


