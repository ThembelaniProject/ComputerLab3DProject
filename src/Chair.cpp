#include "Chair.h"
#include "Cube.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Chair::Chair()
{
}

void Chair::Draw(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    DrawSeat(shader, cube, parentModel);
    DrawBack(shader, cube, parentModel);
    DrawArmrests(shader, cube, parentModel);
    DrawCylinder(shader, cube, parentModel);
    DrawBase(shader, cube, parentModel);
}

void Chair::DrawSeat(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    // Main green cushion
    glm::mat4 cushion = parentModel;
    cushion = glm::translate(cushion, glm::vec3(0.0f, 0.50f, 0.02f));
    cushion = glm::scale(cushion, glm::vec3(0.70f, 0.105f, 0.64f));
    shader.setVec3("objectColor", 0.18f, 0.55f, 0.23f);
    shader.setMat4("model", cushion);
    cube.Draw();

    // Soft top
    glm::mat4 top = parentModel;
    top = glm::translate(top, glm::vec3(0.0f, 0.565f, 0.02f));
    top = glm::scale(top, glm::vec3(0.64f, 0.032f, 0.58f));
    shader.setVec3("objectColor", 0.26f, 0.66f, 0.30f);
    shader.setMat4("model", top);
    cube.Draw();

    // Teal front strip
    glm::mat4 front = parentModel;
    front = glm::translate(front, glm::vec3(0.0f, 0.50f, 0.30f));
    front = glm::scale(front, glm::vec3(0.60f, 0.085f, 0.085f));
    shader.setVec3("objectColor", 0.10f, 0.60f, 0.66f);
    shader.setMat4("model", front);
    cube.Draw();

    // Purple side bolsters
    for (int s = -1; s <= 1; s += 2)
    {
        glm::mat4 side = parentModel;
        side = glm::translate(side, glm::vec3(s * 0.34f, 0.50f, 0.0f));
        side = glm::scale(side, glm::vec3(0.048f, 0.085f, 0.52f));
        shader.setVec3("objectColor", 0.50f, 0.16f, 0.66f);
        shader.setMat4("model", side);
        cube.Draw();
    }
}

void Chair::DrawBack(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    // Main green back
    glm::mat4 back = parentModel;
    back = glm::translate(back, glm::vec3(0.0f, 1.12f, -0.295f));
    back = glm::scale(back, glm::vec3(0.64f, 0.90f, 0.085f));
    shader.setVec3("objectColor", 0.18f, 0.55f, 0.23f);
    shader.setMat4("model", back);
    cube.Draw();

    // Soft front padding
    glm::mat4 pad = parentModel;
    pad = glm::translate(pad, glm::vec3(0.0f, 1.12f, -0.245f));
    pad = glm::scale(pad, glm::vec3(0.55f, 0.80f, 0.032f));
    shader.setVec3("objectColor", 0.26f, 0.66f, 0.30f);
    shader.setMat4("model", pad);
    cube.Draw();

    // Red lumbar
    glm::mat4 lumbar = parentModel;
    lumbar = glm::translate(lumbar, glm::vec3(0.0f, 0.68f, -0.245f));
    lumbar = glm::scale(lumbar, glm::vec3(0.50f, 0.17f, 0.038f));
    shader.setVec3("objectColor", 0.80f, 0.12f, 0.16f);
    shader.setMat4("model", lumbar);
    cube.Draw();

    // Blue headrest
    glm::mat4 head = parentModel;
    head = glm::translate(head, glm::vec3(0.0f, 1.66f, -0.26f));
    head = glm::scale(head, glm::vec3(0.48f, 0.185f, 0.115f));
    shader.setVec3("objectColor", 0.10f, 0.30f, 0.90f);
    shader.setMat4("model", head);
    cube.Draw();
}

void Chair::DrawArmrests(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    for (int s = -1; s <= 1; s += 2)
    {
        // Support
        glm::mat4 support = parentModel;
        support = glm::translate(support, glm::vec3(s * 0.365f, 0.67f, -0.04f));
        support = glm::scale(support, glm::vec3(0.038f, 0.27f, 0.038f));
        shader.setVec3("objectColor", 0.14f, 0.14f, 0.16f);
        shader.setMat4("model", support);
        cube.Draw();

        // Purple arm pad
        glm::mat4 arm = parentModel;
        arm = glm::translate(arm, glm::vec3(s * 0.365f, 0.82f, 0.0f));
        arm = glm::scale(arm, glm::vec3(0.085f, 0.042f, 0.50f));
        shader.setVec3("objectColor", 0.48f, 0.15f, 0.64f);
        shader.setMat4("model", arm);
        cube.Draw();
    }
}

void Chair::DrawCylinder(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 column = parentModel;
    column = glm::translate(column, glm::vec3(0.0f, 0.23f, 0.0f));
    column = glm::scale(column, glm::vec3(0.068f, 0.46f, 0.068f));
    shader.setVec3("objectColor", 0.40f, 0.40f, 0.43f);
    shader.setMat4("model", column);
    cube.Draw();
}

void Chair::DrawBase(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    for (int i = 0; i < 5; ++i)
    {
        float angle = glm::radians(static_cast<float>(i) * 72.0f);

        glm::mat4 arm = parentModel;
        arm = glm::translate(arm, glm::vec3(0.0f, 0.032f, 0.0f));
        arm = glm::rotate(arm, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        arm = glm::translate(arm, glm::vec3(0.335f, 0.0f, 0.0f));
        arm = glm::scale(arm, glm::vec3(0.67f, 0.028f, 0.048f));
        shader.setVec3("objectColor", 0.11f, 0.11f, 0.13f);
        shader.setMat4("model", arm);
        cube.Draw();

        DrawWheel(shader, cube, parentModel,
            std::cos(angle) * 0.67f,
            std::sin(angle) * 0.67f);
    }
}

void Chair::DrawWheel(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    float x,
    float z) const
{
    glm::mat4 wheel = parentModel;
    wheel = glm::translate(wheel, glm::vec3(x, 0.022f, z));
    wheel = glm::scale(wheel, glm::vec3(0.115f, 0.048f, 0.115f));
    shader.setVec3("objectColor", 0.03f, 0.03f, 0.03f);
    shader.setMat4("model", wheel);
    cube.Draw();
}