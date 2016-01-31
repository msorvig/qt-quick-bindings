all:
	gcc main.cpp -o example_property_c++ -I../src -L../lib -lqmlbindings -std=c++11 -lstdc++
run:
	DYLD_LIBRARY_PATH=../lib ./example_property_c++
debug:
	DYLD_IMAGE_SUFFIX=_debug DYLD_LIBRARY_PATH=../lib lldb ./example_property_c++