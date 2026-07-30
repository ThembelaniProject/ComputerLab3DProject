#pragma once

#include <glm/glm.hpp>

class Cube;
class Shader;

class Door
{
public:
    Door();

    void SetAngle(float angle);

    void Draw(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

private:
    float openAngle;
};