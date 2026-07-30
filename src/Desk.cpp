#include "Desk.h"

#include "Cube.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Desk::Desk()
{
}

void Desk::Draw(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    DrawTop(shader, cube, parentModel);

    DrawLeftPanel(shader, cube, parentModel);
    DrawRightPanel(shader, cube, parentModel);
    DrawBackPanel(shader, cube, parentModel);

    DrawCpuShelf(shader, cube, parentModel);

    DrawKeyboardTray(shader, cube, parentModel);

    DrawSupportBar(shader, cube, parentModel);
    DrawKeyboard(shader, cube, parentModel);
    DrawMouse(shader, cube, parentModel);

    DrawMousePad(shader, cube, parentModel);
  
}


void Desk::DrawTop(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.75f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(1.80f, 0.08f, 0.80f));

    shader.setVec3(
        "objectColor",
        0.56f,
        0.32f,
        0.12f);

    shader.setMat4("model", model);

    cube.Draw();
}

void Desk::DrawLeg(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    float x,
    float z) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(x, 0.35f, z));

    model = glm::scale(
        model,
        glm::vec3(0.07f, 0.70f, 0.07f));

    shader.setVec3(
        "objectColor",
        0.20f,
        0.20f,
        0.20f);

    shader.setMat4("model", model);

    cube.Draw();
}
void Desk::DrawLeftPanel(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(-0.82f, 0.34f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(0.05f, 0.68f, 0.78f));

    shader.setMat4("model", model);

    shader.setVec3(
        "objectColor",
        0.60f,
        0.36f,
        0.15f);

    cube.Draw();
}
void Desk::DrawRightPanel(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.82f, 0.34f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(0.05f, 0.68f, 0.78f));

    shader.setMat4("model", model);

    shader.setVec3(
        "objectColor",
        0.60f,
        0.36f,
        0.15f);

    cube.Draw();
}
void Desk::DrawBackPanel(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.35f, -0.36f));

    model = glm::scale(
        model,
        glm::vec3(1.55f, 0.55f, 0.04f));

    shader.setMat4("model", model);

    shader.setVec3(
        "objectColor",
        0.57f,
        0.34f,
        0.14f);

    cube.Draw();
}

void Desk::DrawKeyboardTray(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.63f, 0.15f));

    model = glm::scale(
        model,
        glm::vec3(0.70f, 0.03f, 0.25f));

    shader.setVec3(
        "objectColor",
        0.10f,
        0.10f,
        0.10f);

    shader.setMat4("model", model);

    cube.Draw();
}

void Desk::DrawSupportBar(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.42f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(1.45f, 0.03f, 0.05f));
    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.12f);
    shader.setMat4("model", model);

    cube.Draw();
}
void Desk::DrawCpuShelf(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    // CPU shelf under the desk
    model = glm::translate(
        model,
        glm::vec3(0.55f, 0.35f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(0.25f, 0.55f, 0.45f));

    shader.setMat4("model", model);

    // Dark grey
    shader.setVec3(
        "objectColor",
        0.08f,
        0.08f,
        0.08f);

    cube.Draw();
}

void Desk::DrawKeyboard(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.79f, 0.18f));

    model = glm::scale(
        model,
        glm::vec3(0.42f, 0.02f, 0.14f));

    shader.setVec3(
        "objectColor",
        0.08f,
        0.08f,
        0.08f);

    shader.setMat4("model", model);

    cube.Draw();
}

void Desk::DrawMouse(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.34f, 0.79f, 0.16f));

    model = glm::scale(
        model,
        glm::vec3(0.05f, 0.025f, 0.08f));

    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.12f);

    shader.setMat4("model", model);

    cube.Draw();
}
void Desk::DrawMousePad(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    // Right side of the keyboard
    model = glm::translate(
        model,
        glm::vec3(0.42f, 0.78f, 0.08f));

    // Very thin pad
    model = glm::scale(
        model,
        glm::vec3(0.18f, 0.01f, 0.22f));

    shader.setVec3(
        "objectColor",
        0.05f,
        0.05f,
        0.05f);

    shader.setMat4("model", model);

    cube.Draw();
}

