cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(bomberman)

set(CMAKE_CXX_STANDARD 17)
if (UNIX)
    set(CMAKE_CXX_FLAGS "-Og")
endif()

# Set this to the minimal version you want to support
find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/3.7.0.tar.gz
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

# Fixing assets bug on windows

if (WIN32) 
    file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/..)
endif()

# Adding extra compilation flags for UNIX

# if (UNIX)
#     add_compile_options(-Wall -Wextra)
# endif()

# Debug Mode

if (UNIX)
    SET(CMAKE_BUILD_TYPE DEBUG)
endif()
if (WIN32)
    SET(CMAKE_BUILD_TYPE RELEASE)
    file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../Release)
endif()

set(EXECUTABLE_OUTPUT_PATH ..)

# -I

#include_directories(include)
#include_directories(include/raylib)
#include_directories(include/entityComponent)

# File to compile

add_executable(${PROJECT_NAME}
src/raylib/Window.cpp
src/raylib/Color.cpp
src/raylib/RenderTexture.cpp
src/raylib/Font.cpp
src/raylib/Image.cpp
src/raylib/Vector.cpp
src/raylib/Texture.cpp
src/raylib/Sound.cpp
src/raylib/Music.cpp
src/raylib/Model.cpp
src/raylib/BoundingBox.cpp
src/raylib/Ray.cpp
src/raylib/Shader.cpp
src/raylib/Mesh.cpp
src/raylib/Rectangle.cpp
src/raylib/Camera.cpp
src/entityComponent/Manager.cpp
src/entityComponent/object/Cube.cpp
src/entityComponent/object/Wall.cpp
src/entityComponent/object/Floor.cpp
src/entityComponent/object/Preview.cpp
src/entityComponent/object/Player.cpp
src/entityComponent/object/Box.cpp
src/entityComponent/object/PowerUp.cpp
src/entityComponent/object/Skybox.cpp
src/entityComponent/object/Btn.cpp
src/entityComponent/object/Input.cpp
src/entityComponent/object/MImage.cpp
src/entityComponent/object/Slider.cpp
src/entityComponent/object/PlayerAI.cpp
src/entityComponent/object/List.cpp
src/entityComponent/object/Bomb.cpp
src/entityComponent/object/Particle.cpp
src/entityComponent/object/MusicManager.cpp
src/entityComponent/object/EscManager.cpp
src/entityComponent/object/Text.cpp
src/entityComponent/Object.cpp
src/entityComponent/ByteObject.cpp
src/entityComponent/object/GameOpt.cpp
src/functionalities/BtnFuncs.cpp
src/functionalities/Control.cpp
src/Bomberman.cpp
src/main.cpp
)

target_link_libraries(${PROJECT_NAME} raylib)

set(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
