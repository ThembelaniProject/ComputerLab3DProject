#include "Door.h"

#include "Cube.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Door::Door()
    : openAngle(0.0f)
{
}

void Door::SetAngle(float angle)
{
    openAngle = angle;
}

void Door::Draw(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    // Door position relative to the room
    model = glm::translate(
        model,
        glm::vec3(-7.5f, 1.0f, 5.95f));

    // Move pivot to hinge
    model = glm::translate(
        model,
        glm::vec3(-0.45f, 0.0f, 0.0f));

    // Rotate around hinge
    model = glm::rotate(
        model,
        glm::radians(openAngle),
        glm::vec3(0.0f, 1.0f, 0.0f));

    // Move back
    model = glm::translate(
        model,
        glm::vec3(0.45f, 0.0f, 0.0f));

    // Door size
    model = glm::scale(
        model,
        glm::vec3(0.9f, 2.0f, 0.08f));

    shader.setMat4("model", model);
    shader.setVec3(
        "objectColor",
        0.55f,
        0.32f,
        0.12f);
    cube.Draw();
}