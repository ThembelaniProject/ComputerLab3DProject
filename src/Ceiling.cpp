#include "Ceiling.h"

#include "Shader.h"
#include "Cube.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Ceiling::Ceiling()
{
}


void Ceiling::Draw(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    //----------------------------------------
    // Main Ceiling
    //----------------------------------------
    glm::mat4 ceiling = parentModel;

    ceiling = glm::translate(
        ceiling,
        glm::vec3(0.0f, 3.05f, 0.0f));

    ceiling = glm::scale(
        ceiling,
        glm::vec3(16.0f, 0.15f, 12.0f));

    shader.setVec3(
        "objectColor",
        0.97f,
        0.95f,
        0.88f);

    shader.setMat4("model", ceiling);
    cube.Draw();
  


    // ceiling Grid//
    

    shader.setVec3(
        "objectColor",
        1.00f,
        0.99f,
        0.92f); // Warm white LED

    for (float x = -5.0f; x <= 5.0f; x += 5.0f)
    {
        for (float z = -3.5f; z <= 3.5f; z += 3.5f)
        {
            glm::mat4 light = parentModel;

            light = glm::translate(
                light,
                glm::vec3(x, 2.97f, z));

            light = glm::scale(
                light,
                glm::vec3(1.2f, 0.02f, 1.2f));

            shader.setMat4("model", light);
            cube.Draw();
        }
    }

    // Long beams
    for (float z = -5.5f; z <= 5.5f; z += 1.5f)
    {
        glm::mat4 beam = parentModel;

        beam = glm::translate(
            beam,
            glm::vec3(0.0f, 2.95f, z));

        beam = glm::scale(
            beam,
            glm::vec3(16.0f, 0.03f, 0.05f));

        shader.setMat4("model", beam);
        cube.Draw();
    }

    // Cross beams
    for (float x = -7.5f; x <= 7.5f; x += 1.5f)
    {
        glm::mat4 beam = parentModel;

        beam = glm::translate(
            beam,
            glm::vec3(x, 2.95f, 0.0f));

        beam = glm::scale(
            beam,
            glm::vec3(0.05f, 0.03f, 12.0f));

        shader.setMat4("model", beam);
        cube.Draw();
    }
    
    shader.setVec3("objectColor", 0.70f, 0.70f, 0.70f);

    // Long beams
    for (float z = -5.5f; z <= 5.5f; z += 1.5f)
    {
        glm::mat4 beam = parentModel;

        beam = glm::translate(
            beam,
            glm::vec3(0.0f, 2.95f, z));

        beam = glm::scale(
            beam,
            glm::vec3(16.0f, 0.03f, 0.05f));

        shader.setMat4("model", beam);
        cube.Draw();
    }

    // Cross beams
    for (float x = -7.5f; x <= 7.5f; x += 1.5f)
    {
        glm::mat4 beam = parentModel;

        beam = glm::translate(
            beam,
            glm::vec3(x, 2.95f, 0.0f));

        beam = glm::scale(
            beam,
            glm::vec3(0.05f, 0.03f, 12.0f));

        shader.setMat4("model", beam);
        cube.Draw();
    }

    glm::mat4 vent = parentModel;

    vent = glm::translate(
        vent,
        glm::vec3(-5.5f, 2.93f, -4.5f));

    vent = glm::scale(
        vent,
        glm::vec3(0.9f, 0.02f, 0.9f));
    shader.setVec3(
        "objectColor",
        0.78f,
        0.78f,
        0.76f);

    shader.setMat4("model", vent);
    cube.Draw();



    //------------------------------------------------------
 // PREMIUM AI CCTV CAMERA  (v3 – highly detailed)
 //------------------------------------------------------
    glm::mat4 model;
    const float camX = -7.60f;
    const float camY = 2.68f;
    const float camZ = -5.38f;
    const float tilt = 22.0f;

    //======================================================
    // Ceiling Mount Plate
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, 2.98f, -5.60f));
    model = glm::scale(model, glm::vec3(0.28f, 0.032f, 0.28f));
    shader.setVec3("objectColor", 0.91f, 0.91f, 0.93f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Mount Stem
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, 2.91f, -5.60f));
    model = glm::scale(model, glm::vec3(0.052f, 0.13f, 0.052f));
    shader.setVec3("objectColor", 0.68f, 0.68f, 0.70f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Ball Joint
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, 2.84f, -5.60f));
    model = glm::scale(model, glm::vec3(0.095f, 0.095f, 0.095f));
    shader.setVec3("objectColor", 0.48f, 0.48f, 0.52f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Neck
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, 2.77f, -5.54f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.058f, 0.058f, 0.20f));
    shader.setVec3("objectColor", 0.40f, 0.40f, 0.43f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Main Body
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, camY, camZ));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.195f, 0.155f, 0.46f));
    shader.setVec3("objectColor", 0.955f, 0.955f, 0.965f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Side Rails (premium accent)
    //======================================================
    for (float s : {-1.0f, 1.0f}) {
        model = parentModel;
        model = glm::translate(model, glm::vec3(camX + s * 0.102f, camY, camZ));
        model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
        model = glm::scale(model, glm::vec3(0.011f, 0.135f, 0.40f));
        shader.setVec3("objectColor", 0.22f, 0.22f, 0.25f);
        shader.setMat4("model", model);
        cube.Draw();
    }

    //======================================================
    // Top Heat-sink / Vent
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, camY + 0.085f, camZ));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.13f, 0.010f, 0.32f));
    shader.setVec3("objectColor", 0.28f, 0.28f, 0.30f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Rear Cable Boot
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, camY + 0.02f, camZ - 0.25f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.08f));
    shader.setVec3("objectColor", 0.18f, 0.18f, 0.20f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Front Bezel
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, camY, -5.13f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.180f, 0.140f, 0.035f));
    shader.setVec3("objectColor", 0.07f, 0.07f, 0.08f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Sun Shield / Hood
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, camY + 0.055f, -5.06f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.195f, 0.045f, 0.12f));
    shader.setVec3("objectColor", 0.12f, 0.12f, 0.14f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Lens Outer Ring
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, camY, -5.095f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.105f, 0.105f, 0.022f));
    shader.setVec3("objectColor", 0.14f, 0.14f, 0.16f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Lens Glass
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, camY, -5.075f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.078f, 0.078f, 0.018f));
    shader.setVec3("objectColor", 0.04f, 0.11f, 0.26f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Lens Reflection Spot
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX - 0.015f, camY + 0.015f, -5.062f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.028f, 0.028f, 0.010f));
    shader.setVec3("objectColor", 0.35f, 0.55f, 0.85f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // IR LED Array (8 LEDs – realistic pattern)
    //======================================================
    float ledPos[][2] = {
        {-0.058f, -0.040f}, {-0.020f, -0.040f}, {0.020f, -0.040f}, {0.058f, -0.040f},
        {-0.058f,  0.018f}, {-0.020f,  0.018f}, {0.020f,  0.018f}, {0.058f,  0.018f}
    };
    for (auto& p : ledPos) {
        model = parentModel;
        model = glm::translate(model, glm::vec3(camX + p[0], camY + p[1], -5.085f));
        model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
        model = glm::scale(model, glm::vec3(0.013f, 0.013f, 0.013f));
        shader.setVec3("objectColor", 0.93f, 0.93f, 0.95f);
        shader.setMat4("model", model);
        cube.Draw();
    }

    //======================================================
    // AI Status LED (bright green)
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX + 0.085f, camY + 0.055f, -5.20f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.015f));
    shader.setVec3("objectColor", 0.05f, 0.98f, 0.40f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Recording LED (red)
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX - 0.085f, camY + 0.055f, -5.20f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.013f));
    shader.setVec3("objectColor", 0.95f, 0.12f, 0.10f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Brand Strip
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX, camY + 0.055f, -5.30f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.145f, 0.011f, 0.18f));
    shader.setVec3("objectColor", 0.16f, 0.16f, 0.18f);
    shader.setMat4("model", model);
    cube.Draw();

    //======================================================
    // Tiny Antenna (AI / wireless)
    //======================================================
    model = parentModel;
    model = glm::translate(model, glm::vec3(camX + 0.07f, camY + 0.09f, camZ - 0.12f));
    model = glm::rotate(model, glm::radians(tilt), glm::vec3(1, 0, 0));
    model = glm::scale(model, glm::vec3(0.012f, 0.012f, 0.09f));
    shader.setVec3("objectColor", 0.25f, 0.25f, 0.28f);
    shader.setMat4("model", model);
    cube.Draw();
    glm::mat4 sprinkler = parentModel;

    sprinkler = glm::translate(
        sprinkler,
        glm::vec3(5.5f, 2.94f, -5.2f));

    sprinkler = glm::scale(
        sprinkler,
        glm::vec3(0.08f, 0.08f, 0.08f));
    shader.setVec3(
        "objectColor",
        0.85f,
        0.84f,
        0.82f);
    shader.setMat4("model", sprinkler);
    cube.Draw();
   

}