cmake_minimum_required(VERSION 3.21)

project(ComputerLabOpenGL)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)



add_executable(ComputerLabOpenGL

    src/main.cpp

    src/Shader.cpp
    src/Camera.cpp

    src/Mesh.cpp
    src/Cube.cpp

    src/Renderer.cpp

    src/Room.cpp
    src/Desk.cpp
    src/Chair.cpp
    src/Monitor.cpp

    src/Door.cpp
    src/Window.cpp

    src/Lighting.cpp
    
    src/Scene.cpp

  "include/Ceiling.h" "src/Ceiling.cpp" "include/Texture.h")



target_include_directories(
    ComputerLabOpenGL PRIVATE
    include
)



target_link_libraries(
    ComputerLabOpenGL PRIVATE

    OpenGL::GL

    glfw

    glad::glad

    glm::glm
)



# Copy assets folder after build

add_custom_command(
    TARGET ComputerLabOpenGL POST_BUILD

    COMMAND ${CMAKE_COMMAND}
    -E copy_directory

    ${CMAKE_SOURCE_DIR}/assets

    $<TARGET_FILE_DIR:ComputerLabOpenGL>/assets
)