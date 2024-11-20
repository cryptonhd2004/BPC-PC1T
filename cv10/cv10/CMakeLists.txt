# CMakeList.txt : CMake project for cv10, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (cv10 "cv10.cpp" "cv10.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cv10 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
