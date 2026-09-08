cmake_minimum_required(VERSION 3.21)

project(ComputerLabOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------
# Dependencies
# ---------------------------------------------------------

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# ---------------------------------------------------------
# Source files
# ---------------------------------------------------------

add_executable(ComputerLabOpenGL

    # Main
    src/main.cpp

    # Core
    src/Shader.cpp
    src/Camera.cpp
    src/Mesh.cpp
    src/Cube.cpp
    src/Renderer.cpp

    # Room
    src/Room.cpp
    src/Ceiling.cpp

    # Furniture
    src/Desk.cpp
    src/Chair.cpp
    src/Cushion.cpp
    src/Monitor.cpp
    src/Cylinder.cpp

    # Environment
    src/Door.cpp
    src/Window.cpp

    # Lighting
    src/Lighting.cpp

    # Scene
    src/Scene.cpp

    # Textures
    src/Texture.cpp
    src/stb_image.cpp
 "include/Cylinder.h" "src/Cylinder.cpp")

# ---------------------------------------------------------
# Include directories
# ---------------------------------------------------------

target_include_directories(
    ComputerLabOpenGL
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# ---------------------------------------------------------
# Libraries
# ---------------------------------------------------------

target_link_libraries(
    ComputerLabOpenGL
    PRIVATE
        OpenGL::GL
        glfw
        glad::glad
        glm::glm
)

# ---------------------------------------------------------
# Copy assets after build
# ---------------------------------------------------------

add_custom_command(
    TARGET ComputerLabOpenGL
    POST_BUILD

    COMMAND ${CMAKE_COMMAND}
    -E copy_directory

    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:ComputerLabOpenGL>/assets
)