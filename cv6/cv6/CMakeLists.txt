# CMakeList.txt : CMake project for cv6, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (cv6 "cv6.cpp" "cv6.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cv6 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
