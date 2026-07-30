#pragma once

#include <glm/glm.hpp>

class Cube;
class Shader;

class Window
{
public:
    Window();

    void Draw(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

private:

    void DrawFrame(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

    void DrawGlass(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;
};