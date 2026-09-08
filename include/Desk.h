#pragma once

#include <glm/glm.hpp>

class Cube;
class Shader;
class Texture;

class Desk
{
public:
    Desk();

    void Draw(
        Shader& shader,
        const Cube& cube,
        const Texture& keyboardTexture,
        const Texture& pcFrontTexture,
        const glm::mat4& parentModel
    ) const;

private:

    void DrawTop(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

    void DrawLeg(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel,
        float x,
        float z
    ) const;

    void DrawLeftPanel(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

    void DrawRightPanel(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

    void DrawBackPanel(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

    void DrawCpuShelf(
        Shader& shader,
        const Cube& cube,
        const Texture& frontTexture,          // ? new parameter
        const glm::mat4& parentModel) const;
    void DrawKeyboardTray(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

    void DrawSupportBar(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

    void DrawKeyboard(
        Shader& shader,
        const Cube& cube,
        const Texture& keyboardTexture,
        const glm::mat4& parentModel
    ) const;

    void DrawMouse(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

    void DrawMousePad(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;
};