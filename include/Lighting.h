#pragma once

#include <glm/glm.hpp>

class Shader;

class Lighting
{
public:
    Lighting();

    void Apply(Shader& shader) const;

    void SetViewPosition(const glm::vec3& position);

private:

    // Sun light
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // Six ceiling lights
    glm::vec3 lightPositions[6];

    glm::vec3 lightAmbient;
    glm::vec3 lightDiffuse;
    glm::vec3 lightSpecular;

    glm::vec3 viewPosition;
};