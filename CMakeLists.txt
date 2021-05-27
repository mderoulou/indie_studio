cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

# Set this to the minimal version you want to support
find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

# -I

include_directories(include)
include_directories(include/raylib)
include_directories(include/entityComponent)

# File to compile

add_executable(${PROJECT_NAME}
include/entityComponent/Object.hpp
include/raylib/Error.hpp
include/raylib/Color.hpp
include/raylib/Vector.hpp
include/raylib/Mesh.hpp
include/raylib/Image.hpp
include/raylib/Rectangle.hpp
include/raylib/RenderTexture.hpp
include/raylib/Model.hpp
include/raylib/Font.hpp
include/raylib/rayLib.hpp
include/raylib/Window.hpp 
include/raylib/Camera.hpp 
include/raylib/Sound.hpp 
include/raylib/Music.hpp 
include/raylib/Shader.hpp
include/Indie.hpp
src/raylib/Window.cpp
src/raylib/Color.cpp
src/raylib/RenderTexture.cpp
src/raylib/Font.cpp
src/raylib/Image.cpp
src/raylib/Vector.cpp
src/raylib/Sound.cpp
src/raylib/Music.cpp
src/raylib/Model.cpp
src/raylib/Shader.cpp
src/raylib/Mesh.cpp
src/raylib/Camera.cpp
src/raylib/Rectangle.cpp
src/main.cpp
)

target_link_libraries(${PROJECT_NAME} raylib)

set(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
