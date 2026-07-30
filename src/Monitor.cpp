#include "Monitor.h"

#include "Cube.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Monitor::Monitor()
{
}

void Monitor::Draw(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model;

    //----------------------------------
    // Monitor Body (Thin Bezel)
    //----------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.35f, -0.03f));

    model = glm::rotate(
        model,
        glm::radians(-8.0f),
        glm::vec3(1, 0, 0));

    model = glm::scale(
        model,
        glm::vec3(0.82f, 0.48f, 0.025f));

    shader.setVec3(
        "objectColor",
        0.05f,
        0.05f,
        0.05f);

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------
    // Display
    //----------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.35f, -0.016f));

    model = glm::rotate(
        model,
        glm::radians(-8.0f),
        glm::vec3(1, 0, 0));

    model = glm::scale(
        model,
        glm::vec3(0.77f, 0.43f, 0.003f));

    shader.setVec3(
        "objectColor",
        0.07f,
        0.10f,
        0.14f);

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------
    // Bottom Bezel (Logo Area)
    //----------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.11f, -0.02f));

    model = glm::scale(
        model,
        glm::vec3(0.82f, 0.03f, 0.02f));

    shader.setVec3(
        "objectColor",
        0.10f,
        0.10f,
        0.10f);

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------
    // Webcam
    //----------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.60f, -0.02f));

    model = glm::scale(
        model,
        glm::vec3(0.025f, 0.025f, 0.025f));

    shader.setVec3(
        "objectColor",
        0.25f,
        0.25f,
        0.25f);

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------
    // Stand Neck
    //----------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.12f, -0.04f));

    model = glm::scale(
        model,
        glm::vec3(0.05f, 0.20f, 0.05f));

    shader.setVec3(
        "objectColor",
        0.35f,
        0.35f,
        0.35f);

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------
    // Stand Joint
    //----------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.24f, -0.04f));

    model = glm::scale(
        model,
        glm::vec3(0.08f, 0.04f, 0.08f));

    shader.setVec3(
        "objectColor",
        0.22f,
        0.22f,
        0.22f);

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------
    // Base
    //----------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.01f, -0.02f));

    model = glm::scale(
        model,
        glm::vec3(0.28f, 0.02f, 0.22f));

    shader.setVec3(
        "objectColor",
        0.18f,
        0.18f,
        0.18f);

    shader.setMat4("model", model);

    cube.Draw();

    //----------------------------------
    // Cable
    //----------------------------------

    model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.15f, -0.09f));

    model = glm::scale(
        model,
        glm::vec3(0.01f, 0.16f, 0.01f));

    shader.setVec3(
        "objectColor",
        0.03f,
        0.03f,
        0.03f);

    shader.setMat4("model", model);

    cube.Draw();
}