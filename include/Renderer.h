#pragma once

#include <glm/glm.hpp>

class Shader;
class Cube;

class Renderer
{
public:
    Renderer();

    void BeginFrame() const;

    void EndFrame() const;

    void DrawCube(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model
    ) const;
};