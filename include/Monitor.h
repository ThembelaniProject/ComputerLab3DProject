#pragma once

#include <glm/glm.hpp>

class Shader;
class Cube;

class Monitor
{
public:
    Monitor();

    void Draw(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;
};