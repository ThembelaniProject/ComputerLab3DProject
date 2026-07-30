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
    // ==========================
    // Soft Cushion
    // ==========================
    glm::mat4 cushion = parentModel;

    cushion = glm::translate(
        cushion,
        glm::vec3(0.0f, 0.53f, 0.0f));

    cushion = glm::scale(
        cushion,
        glm::vec3(0.66f, 0.12f, 0.66f));

    shader.setVec3(
        "objectColor",
        0.12f,
        0.18f,
        0.80f);

    shader.setMat4("model", cushion);
    cube.Draw();

    // ==========================
    // Soft top layer
    // ==========================
    glm::mat4 top = parentModel;

    top = glm::translate(
        top,
        glm::vec3(0.0f, 0.60f, 0.0f));

    top = glm::scale(
        top,
        glm::vec3(0.58f, 0.04f, 0.58f));

    shader.setVec3(
        "objectColor",
        0.25f,
        0.45f,
        1.0f);

    shader.setMat4("model", top);
    cube.Draw();
}

void Chair::DrawBack(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    //-------------------------------
    // Thick Back Cushion
    //-------------------------------
    glm::mat4 back = parentModel;

    back = glm::translate(
        back,
        glm::vec3(0.0f, 1.02f, -0.28f));

    back = glm::scale(
        back,
        glm::vec3(0.66f, 0.82f, 0.12f));

    shader.setVec3(
        "objectColor",
        0.12f,
        0.18f,
        0.80f);

    shader.setMat4("model", back);
    cube.Draw();

    //-------------------------------
    // Soft Front Padding
    //-------------------------------
    glm::mat4 front = parentModel;

    front = glm::translate(
        front,
        glm::vec3(0.0f, 1.02f, -0.22f));

    front = glm::scale(
        front,
        glm::vec3(0.56f, 0.72f, 0.03f));

    shader.setVec3(
        "objectColor",
        0.30f,
        0.50f,
        1.0f);

    shader.setMat4("model", front);
    cube.Draw();

    //-------------------------------
    // Head Rest
    //-------------------------------
    glm::mat4 head = parentModel;

    head = glm::translate(
        head,
        glm::vec3(0.0f, 1.56f, -0.24f));

    head = glm::scale(
        head,
        glm::vec3(0.42f, 0.18f, 0.10f));

    shader.setVec3(
        "objectColor",
        0.18f,
        0.30f,
        0.95f);

    shader.setMat4("model", head);
    cube.Draw();
}

void Chair::DrawArmrests(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    for (int side = -1; side <= 1; side += 2)
    {
        // Vertical Support
        glm::mat4 support = parentModel;

        support = glm::translate(
            support,
            glm::vec3(side * 0.34f, 0.67f, 0.0f));

        support = glm::scale(
            support,
            glm::vec3(0.05f, 0.22f, 0.05f));

        shader.setVec3(
            "objectColor",
            0.15f,
            0.15f,
            0.15f);

        shader.setMat4("model", support);
        cube.Draw();

        // Soft Arm Pad
        glm::mat4 pad = parentModel;

        pad = glm::translate(
            pad,
            glm::vec3(side * 0.34f, 0.78f, 0.0f));

        pad = glm::scale(
            pad,
            glm::vec3(0.08f, 0.04f, 0.55f));

        shader.setVec3(
            "objectColor",
            0.10f,
            0.18f,
            0.75f);

        shader.setMat4("model", pad);
        cube.Draw();
    }
}

void Chair::DrawCylinder(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.24f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(0.08f, 0.48f, 0.08f));
    shader.setVec3(
        "objectColor",
        0.72f,
        0.72f,
        0.75f);
    

    shader.setMat4("model", model);

    cube.Draw();
}

void Chair::DrawBase(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    for (int i = 0; i < 5; i++)
    {
        float angle = glm::radians(i * 72.0f);

        glm::mat4 arm = parentModel;

        arm = glm::translate(
            arm,
            glm::vec3(0.0f, 0.05f, 0.0f));

        arm = glm::rotate(
            arm,
            angle,
            glm::vec3(0, 1, 0));

        arm = glm::translate(
            arm,
            glm::vec3(0.33f, 0.0f, 0.0f));

        arm = glm::scale(
            arm,
            glm::vec3(0.66f, 0.03f, 0.05f));

        shader.setVec3(
            "objectColor",
            0.25f,
            0.25f,
            0.28f);

        shader.setMat4("model", arm);

        cube.Draw();

        DrawWheel(
            shader,
            cube,
            parentModel,
            cos(angle) * 0.66f,
            sin(angle) * 0.66f);
    }
}

void Chair::DrawWheel(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    float x,
    float z) const
{
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(
            x,
            0.02f,
            z));

    model = glm::scale(
        model,
        glm::vec3(
            0.11f,
            0.06f,
            0.11f));
        

    shader.setVec3(
        "objectColor",
        0.03f,
        0.03f,
        0.03f);

    shader.setMat4("model", model);

    cube.Draw();
}