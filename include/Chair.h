#pragma once

#include <glm/glm.hpp>

class Shader;
class Cube;

class Chair
{
public:
    Chair();

    void Draw(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

private:

    void DrawSeat(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model) const;

    void DrawBack(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model) const;

    void DrawArmrests(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model) const;

    void DrawCylinder(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model) const;

    void DrawBase(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model) const;

    void DrawWheel(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model,
        float x,
        float z) const;
};