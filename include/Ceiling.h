#pragma once

#include <glm/glm.hpp>

class Shader;
class Cube;

class Ceiling
{
public:
    Ceiling();

    void Draw(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;
};