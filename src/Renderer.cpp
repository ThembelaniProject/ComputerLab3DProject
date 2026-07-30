#include "Renderer.h"

#include "Shader.h"
#include "Cube.h"

#include <glad/glad.h>

Renderer::Renderer()
{
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable back-face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Background colour
    glClearColor(
        0.15f,
        0.18f,
        0.25f,
        1.0f
    );
}

void Renderer::BeginFrame() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndFrame() const
{
    // Reserved for future rendering tasks.
}

void Renderer::DrawCube(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& model) const
{
    shader.setMat4("model", model);

    cube.Draw();
}