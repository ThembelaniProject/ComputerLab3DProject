#include "Desk.h"
#include "Texture.h"
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
    const Texture& keyboardTexture,
    const Texture& pcFrontTexture,
    const glm::mat4& parentModel) const

{
    DrawTop(shader, cube, parentModel);

    DrawLeftPanel(shader, cube, parentModel);
    DrawRightPanel(shader, cube, parentModel);
    DrawBackPanel(shader, cube, parentModel);
    DrawCpuShelf(shader, cube, pcFrontTexture, parentModel);

    DrawKeyboardTray(shader, cube, parentModel);

    DrawSupportBar(shader, cube, parentModel);
    DrawKeyboard(shader, cube, keyboardTexture, parentModel);
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
{/*
    glm::mat4 model = parentModel;

    model = glm::translate(
        model,
        glm::vec3(0.0f, 0.42f, 0.0f));

    model = glm::scale(
        model,
        glm::vec3(0.45f, 2.03f, 0.05f));
    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.12f);
    shader.setMat4("model", model);

    cube.Draw();*/
}
void Desk::DrawCpuShelf(
    Shader& shader,
    const Cube& cube,
    const Texture& frontTexture,
    const glm::mat4& parentModel) const
{
    // Position under the right side of the desk
    glm::mat4 base = parentModel;
    base = glm::translate(base, glm::vec3(0.58f, 0.0f, 0.05f));

    // ?????????????????????????????????????????????
    // 1. Main case body (dark plastic)
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(0.0f, 0.40f, 0.0f));
        model = glm::scale(model, glm::vec3(0.20f, 0.48f, 0.40f));
        shader.setVec3("objectColor", 0.10f, 0.10f, 0.11f);
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 2. Front panel WITH PNG TEXTURE
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(0.0f, 0.40f, 0.206f)); // slightly in front
        model = glm::scale(model, glm::vec3(0.200f, 0.54f, 0.0f));

        // Bind the front texture
        frontTexture.Bind(0);                     // texture unit 0
        shader.setInt("texture1", 0);             // make sure your shader has this uniform
        shader.setBool("useTexture", true);       // if your shader supports a flag

        shader.setMat4("model", model);
        cube.Draw();

        // Optional: unbind or reset flag
        shader.setBool("useTexture", false);
    }
    /*
    // ?????????????????????????????????????????????
    // 3. Power button (red LED) – drawn on top of texture
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(0.0f, 0.65f, 0.214f));
        model = glm::scale(model, glm::vec3(0.032f, 0.032f, 0.006f));
        shader.setVec3("objectColor", 0.95f, 0.18f, 0.12f);
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 4. Side ventilation panel
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(-0.103f, 0.40f, 0.0f));
        model = glm::scale(model, glm::vec3(0.006f, 0.65f, 0.32f));
        shader.setVec3("objectColor", 0.07f, 0.07f, 0.08f);
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 5. Rubber feet
    // ?????????????????????????????????????????????
    const float footY = 0.012f;
    const float footScale = 0.025f;

    auto drawFoot = [&](float x, float z) {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(x, footY, z));
        model = glm::scale(model, glm::vec3(footScale));
        shader.setVec3("objectColor", 0.04f, 0.04f, 0.04f);
        shader.setMat4("model", model);
        cube.Draw();
        };

    drawFoot(-0.07f, 0.14f);
    drawFoot(0.07f, 0.14f);
    drawFoot(-0.07f, -0.14f);
    drawFoot(0.07f, -0.14f);*/
}

void Desk::DrawKeyboard(
    Shader& shader,
    const Cube& cube,
    const Texture& keyboardTexture,
    const glm::mat4& parentModel) const
{
    //--------------------------------------------------
    // Keyboard Base
    //--------------------------------------------------
    glm::mat4 base = parentModel;

    base = glm::translate(base, glm::vec3(0.0f, 0.79f, 0.18f));
    base = glm::scale(base, glm::vec3(0.42f, 0.02f, 0.14f));

    shader.setVec3("objectColor", 0.10f, 0.10f, 0.10f);
    shader.setMat4("model", base);
    cube.Draw();

    //--------------------------------------------------
    // Top Surface
    //--------------------------------------------------
    glm::mat4 top = parentModel;

    top = glm::translate(top, glm::vec3(0.0f, 0.80f, 0.18f));
    top = glm::scale(top, glm::vec3(0.42f, 0.02f, 0.14f));

    shader.use();

    keyboardTexture.Bind(0);

    shader.setInt(
        "texture1",
        0);

    shader.setBool(
        "useTexture",
        true);

    shader.setMat4(
        "model",
        top);

    cube.Draw();

   

    shader.setBool("useTexture", false);

  
}
void Desk::DrawMouse(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    // Base position of the mouse on the desk
    glm::mat4 base = parentModel;
    base = glm::translate(base, glm::vec3(0.34f, 0.79f, 0.16f));

    // ?????????????????????????????????????????????
    // 1. Main body (slightly tapered / ergonomic look)
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::scale(model, glm::vec3(0.068f, 0.028f, 0.105f));
        shader.setVec3("objectColor", 0.13f, 0.13f, 0.14f);   // dark charcoal
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 2. Slightly raised top shell (gives thickness)
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(0.0f, 0.018f, -0.008f));
        model = glm::scale(model, glm::vec3(0.062f, 0.012f, 0.092f));
        shader.setVec3("objectColor", 0.18f, 0.18f, 0.19f);
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 3. Left mouse button
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(-0.016f, 0.027f, 0.018f));
        model = glm::scale(model, glm::vec3(0.028f, 0.006f, 0.042f));
        shader.setVec3("objectColor", 0.22f, 0.22f, 0.23f);
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 4. Right mouse button
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(0.016f, 0.027f, 0.018f));
        model = glm::scale(model, glm::vec3(0.028f, 0.006f, 0.042f));
        shader.setVec3("objectColor", 0.22f, 0.22f, 0.23f);
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 5. Scroll wheel (thin cylinder approximation)
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(0.0f, 0.032f, 0.012f));
        model = glm::scale(model, glm::vec3(0.010f, 0.010f, 0.022f));
        shader.setVec3("objectColor", 0.08f, 0.08f, 0.09f);   // almost black
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 6. Scroll-wheel side grips / detail
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(0.0f, 0.031f, 0.012f));
        model = glm::scale(model, glm::vec3(0.014f, 0.004f, 0.018f));
        shader.setVec3("objectColor", 0.35f, 0.35f, 0.36f);
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 7. Logo / brand accent (small glossy rectangle)
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(0.0f, 0.029f, -0.032f));
        model = glm::scale(model, glm::vec3(0.018f, 0.003f, 0.012f));
        shader.setVec3("objectColor", 0.55f, 0.55f, 0.58f);   // silver-ish
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 8. Side buttons (left side of mouse)
    // ?????????????????????????????????????????????
    {
        // Forward button
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(-0.035f, 0.018f, 0.005f));
        model = glm::scale(model, glm::vec3(0.006f, 0.010f, 0.016f));
        shader.setVec3("objectColor", 0.20f, 0.20f, 0.21f);
        shader.setMat4("model", model);
        cube.Draw();
    }
    {
        // Back button
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(-0.035f, 0.018f, -0.015f));
        model = glm::scale(model, glm::vec3(0.006f, 0.010f, 0.016f));
        shader.setVec3("objectColor", 0.20f, 0.20f, 0.21f);
        shader.setMat4("model", model);
        cube.Draw();
    }

    // ?????????????????????????????????????????????
    // 9. Soft rubber side grip (visual only)
    // ?????????????????????????????????????????????
    {
        glm::mat4 model = base;
        model = glm::translate(model, glm::vec3(-0.034f, 0.010f, -0.005f));
        model = glm::scale(model, glm::vec3(0.004f, 0.018f, 0.070f));
        shader.setVec3("objectColor", 0.09f, 0.09f, 0.10f);
        shader.setMat4("model", model);
        cube.Draw();
    }
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

