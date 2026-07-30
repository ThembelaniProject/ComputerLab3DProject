#include "Window.h"

#include "Cube.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>

Window::Window()
{
}

void Window::Draw(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    const float wallX = 7.95f;

    //----------------------------------------
    // LEFT FRAME
    //----------------------------------------

    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(wallX, 1.80f, -3.25f));

    model = glm::scale(
        model,
        glm::vec3(0.08f, 2.10f, 0.08f));

    shader.setVec3("objectColor",
        0.82f,
        0.82f,
        0.82f);

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------------
    // RIGHT FRAME
    //----------------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(wallX, 1.80f, 3.25f));

    model = glm::scale(
        model,
        glm::vec3(0.08f, 2.10f, 0.08f));

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------------
    // TOP FRAME
    //----------------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(wallX, 2.82f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(0.08f, 0.08f, 6.60f));

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------------
    // BOTTOM FRAME
    //----------------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(wallX, 0.78f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(0.08f, 0.08f, 6.60f));

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------------
    // GLASS
    //----------------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(7.90f, 1.80f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(0.02f, 1.95f, 6.35f));

    shader.setVec3(
        "objectColor",
        0.65f,
        0.85f,
        0.98f);

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------------
    // VERTICAL DIVIDERS
    //----------------------------------------

    for (float z = -2.1f; z <= 2.1f; z += 2.1f)
    {
        model = parentModel;

        model = glm::translate(
            model,
            glm::vec3(7.91f, 1.80f, z));

        model = glm::scale(
            model,
            glm::vec3(0.03f, 1.95f, 0.05f));

        shader.setVec3(
            "objectColor",
            0.72f,
            0.72f,
            0.72f);

        shader.setMat4("model", model);

        cube.Draw();
    }

    //----------------------------------------
    // HORIZONTAL DIVIDER
    //----------------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(7.91f, 1.80f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(0.03f, 0.05f, 6.35f));

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------------
    // ROLLER BLIND
    //----------------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(7.86f, 2.95f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(0.12f, 0.18f, 6.55f));

    shader.setVec3(
        "objectColor",
        0.96f,
        0.96f,
        0.96f);

    shader.setMat4("model", model);

    cube.Draw();
}