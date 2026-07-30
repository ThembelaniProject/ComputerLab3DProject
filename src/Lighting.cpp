#include "Lighting.h"
#include "Shader.h"

Lighting::Lighting()
{
    //-----------------------------
    // Daylight
    //-----------------------------

    direction = glm::vec3(-1.0f, -1.0f, -0.5f);
    ambient = glm::vec3(0.08f);
    diffuse = glm::vec3(0.40f);
    specular = glm::vec3(1.0f);

    //-----------------------------
    // Ceiling Lights
    //-----------------------------

    lightPositions[0] = glm::vec3(-5.5f, 2.85f, -4.5f);
    lightPositions[1] = glm::vec3(0.0f, 2.85f, -4.5f);
    lightPositions[2] = glm::vec3(5.5f, 2.85f, -4.5f);

    lightPositions[3] = glm::vec3(-5.5f, 2.85f, 3.0f);
    lightPositions[4] = glm::vec3(0.0f, 2.85f, 3.0f);
    lightPositions[5] = glm::vec3(5.5f, 2.85f, 3.0f);

    lightAmbient = glm::vec3(0.04f);
    lightDiffuse = glm::vec3(0.55f);

    lightSpecular = glm::vec3(1.0f);

    viewPosition = glm::vec3(0.0f);
}

void Lighting::SetViewPosition(const glm::vec3& position)
{
    viewPosition = position;
}

void Lighting::Apply(Shader& shader) const
{
    shader.setVec3("viewPos", viewPosition);

    //-----------------------------
    // Directional Light
    //-----------------------------

    shader.setVec3("dirLight.direction", direction);
    shader.setVec3("dirLight.ambient", ambient);
    shader.setVec3("dirLight.diffuse", diffuse);
    shader.setVec3("dirLight.specular", specular);

    //-----------------------------
    // Six Point Lights
    //-----------------------------

    for (int i = 0; i < 6; i++)
    {
        std::string index = "pointLights[" + std::to_string(i) + "]";

        shader.setVec3(index + ".position", lightPositions[i]);

        shader.setVec3(index + ".ambient", lightAmbient);

        shader.setVec3(index + ".diffuse", lightDiffuse);

        shader.setVec3(index + ".specular", lightSpecular);

        shader.setFloat(index + ".constant", 1.0f);

        shader.setFloat(index + ".linear", 0.09f);

        shader.setFloat(index + ".quadratic", 0.032f);
    }
}