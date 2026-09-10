
#pragma once

#include <glm/glm.hpp>

class Cube;
class Shader;

class Door
{
public:
    Door();

    // Set the current door angle directly
    void SetAngle(float angle);

    // Toggle between closed and open
    void Toggle();

    // Smooth door animation
    void Update(float deltaTime);

    // Draw the complete door
    void Draw(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

private:
    float openAngle;
    float targetAngle;

    // Animation settings
    float openSpeed;
};

