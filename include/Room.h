#pragma once

#include <glm/glm.hpp>

class Cube;
class Shader;


class Room
{

public:

    Room();


    void Draw(
        Shader& shader,
        const Cube& cube
    ) const;


private:


    void DrawFloor(
        Shader& shader,
        const Cube& cube
    ) const;


    void DrawCeiling(
        Shader& shader,
        const Cube& cube
    ) const;


    void DrawWalls(
        Shader& shader,
        const Cube& cube
    ) const;



    glm::vec3 roomSize;

};