#include "Room.h"

#include "Cube.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>

Room::Room()
{
    // Width, Height, Length (1 OpenGL unit = 1 metre)
    roomSize = glm::vec3(16.0f, 3.0f, 12.0f);
}

void Room::Draw(Shader& shader, const Cube& cube) const
{
    DrawFloor(shader, cube);
    DrawWalls(shader, cube);
}

void Room::DrawFloor(Shader& shader, const Cube& cube) const
{
    const float tileSize = 1.0f;
    const float grout = 0.04f;

    int tilesX = static_cast<int>(roomSize.x);
    int tilesZ = static_cast<int>(roomSize.z);

    for (int x = 0; x < tilesX; x++)
    {
        for (int z = 0; z < tilesZ; z++)
        {
            //-------------------------
            // Floor tile
            //-------------------------

            glm::mat4 model(1.0f);

            float worldX =
                -roomSize.x * 0.5f +
                tileSize * 0.5f +
                x;

            float worldZ =
                -roomSize.z * 0.5f +
                tileSize * 0.5f +
                z;

            model = glm::translate(
                model,
                glm::vec3(worldX, -0.50f, worldZ));

            model = glm::scale(
                model,
                glm::vec3(
                    tileSize - grout,
                    0.04f,
                    tileSize - grout));

            // Real glossy grey ceramic tiles
            if ((x + z) % 2 == 0)
            {
                shader.setVec3(
                    "objectColor",
                    0.58f,
                    0.60f,
                    0.63f);
            }
            else
            {
                shader.setVec3(
                    "objectColor",
                    0.72f,
                    0.74f,
                    0.76f);
            }

            shader.setMat4("model", model);

            cube.Draw();

            //-------------------------
            // Grout lines
            //-------------------------

            shader.setVec3(
                "objectColor",
                0.18f,
                0.18f,
                0.18f);

            // Vertical grout
            glm::mat4 groutX(1.0f);

            groutX = glm::translate(
                groutX,
                glm::vec3(
                    worldX + 0.5f,
                    -0.499f,
                    worldZ));

            groutX = glm::scale(
                groutX,
                glm::vec3(
                    0.02f,
                    0.005f,
                    1.0f));

            shader.setMat4("model", groutX);

            cube.Draw();

            // Horizontal grout
            glm::mat4 groutZ(1.0f);

            groutZ = glm::translate(
                groutZ,
                glm::vec3(
                    worldX,
                    -0.499f,
                    worldZ + 0.5f));

            groutZ = glm::scale(
                groutZ,
                glm::vec3(
                    1.0f,
                    0.005f,
                    0.02f));

            shader.setMat4("model", groutZ);

            cube.Draw();
        }
    }
}

void Room::DrawCeiling(Shader& shader, const Cube& cube) const
{
    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(0.0f, roomSize.y, 0.0f)
    );

    model = glm::scale(
        model,
        glm::vec3(roomSize.x, 0.1f, roomSize.z)
    );

    shader.setMat4("model", model);
    shader.setVec3(
        "objectColor",
        0.95f,
        0.95f,
        0.95f);

    cube.Draw();
}
void Room::DrawWalls(
    Shader& shader,
    const Cube& cube) const
{
    glm::mat4 model;

    shader.setVec3(
        "objectColor",
        0.96f,
        0.96f,
        0.96f);

    //-------------------------------------------------
    // LEFT WALL (SOLID)
    //-------------------------------------------------

    model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            -roomSize.x / 2,
            roomSize.y / 2,
            0.0f));

    model = glm::scale(
        model,
        glm::vec3(
            0.10f,
            roomSize.y,
            roomSize.z));

    shader.setMat4("model", model);

    cube.Draw();

    //-------------------------------------------------
    // RIGHT WALL WITH WINDOW OPENING
    //-------------------------------------------------

    // Front section

    model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            roomSize.x / 2,
            roomSize.y / 2,
            4.5f));

    model = glm::scale(
        model,
        glm::vec3(
            0.10f,
            roomSize.y,
            3.0f));

    shader.setMat4("model", model);

    cube.Draw();

    // Rear section

    model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            roomSize.x / 2,
            roomSize.y / 2,
            -4.5f));

    model = glm::scale(
        model,
        glm::vec3(
            0.10f,
            roomSize.y,
            3.0f));

    shader.setMat4("model", model);

    cube.Draw();

    // Bottom section

    model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            roomSize.x / 2,
            0.45f,
            0.0f));

    model = glm::scale(
        model,
        glm::vec3(
            0.10f,
            0.90f,
            6.0f));

    shader.setMat4("model", model);

    cube.Draw();

    // Top section

    model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            roomSize.x / 2,
            2.75f,
            0.0f));

    model = glm::scale(
        model,
        glm::vec3(
            0.10f,
            0.50f,
            6.0f));

    shader.setMat4("model", model);

    cube.Draw();

    //-------------------------------------------------
    // FRONT WALL WITH DOOR
    //-------------------------------------------------

    // Left side

    model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            -5.0f,
            roomSize.y / 2,
            roomSize.z / 2));

    model = glm::scale(
        model,
        glm::vec3(
            6.0f,
            roomSize.y,
            0.10f));

    shader.setMat4("model", model);

    cube.Draw();

    // Right side

    model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            5.0f,
            roomSize.y / 2,
            roomSize.z / 2));

    model = glm::scale(
        model,
        glm::vec3(
            6.0f,
            roomSize.y,
            0.10f));

    shader.setMat4("model", model);

    cube.Draw();

    //-------------------------------------------------
    // BACK WALL (SOLID)
    //-------------------------------------------------

    model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            roomSize.y / 2,
            -roomSize.z / 2));

    model = glm::scale(
        model,
        glm::vec3(
            roomSize.x,
            roomSize.y,
            0.10f));

    shader.setMat4("model", model);

    cube.Draw();
}