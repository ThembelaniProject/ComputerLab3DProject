#pragma once

#include <glm/glm.hpp>

class Cube;
class Shader;

class Window
{
public:
    Window();

    // Update opening/closing animation
    void Update(float deltaTime);

    // Open / close controls
    void Open();
    void Close();
    void Toggle();

    // Draw complete window
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

    void DrawOutdoor(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

private:

    // 0.0 = completely closed
    // 1.0 = completely open
    float openAmount;

    // Desired state
    float targetOpenAmount;

    // Animation speed
    float animationSpeed;
};