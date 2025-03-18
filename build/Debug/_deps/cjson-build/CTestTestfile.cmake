# CMake generated Testfile for 
# Source directory: C:/Users/user/Documents/Projects/CGame/build/Debug/_deps/cjson-src
# Build directory: C:/Users/user/Documents/Projects/CGame/build/Debug/_deps/cjson-build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "C:/Users/user/Documents/Projects/CGame/build/Debug/_deps/cjson-build/cJSON_test")
set_tests_properties(cJSON_test PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/user/Documents/Projects/CGame/build/Debug/_deps/cjson-src/CMakeLists.txt;248;add_test;C:/Users/user/Documents/Projects/CGame/build/Debug/_deps/cjson-src/CMakeLists.txt;0;")
subdirs("tests")
subdirs("fuzzing")
