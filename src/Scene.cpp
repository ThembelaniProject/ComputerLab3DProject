#include "Scene.h"

#include "Room.h"
#include "Desk.h"
#include "Chair.h"
#include "Monitor.h"
#include "Door.h"
#include "Window.h"
#include "Cube.h"
#include "Shader.h"
#include "Ceiling.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Scene::Scene()
{
    room = new Room();
    desk = new Desk();
    chair = new Chair();
    monitor = new Monitor();
    door = new Door();
    window = new Window();
    ceiling = new Ceiling();
}

void Scene::Draw(
    Shader& shader,
    const Cube& cube) const
{
    room->Draw(shader, cube);

    DrawWorkstations(shader, cube);

    DrawLecturerStation(shader, cube);

    DrawNetworkCabinet(shader, cube);

    DrawAirConditioner(shader, cube);

    DrawProjectionScreen(shader, cube);
    DrawProjector(shader, cube);
    DrawWhiteboard(shader, cube);

    glm::mat4 roomModel(1.0f);

    door->Draw(
        shader,
        cube,
        roomModel);

    window->Draw(
        shader,
        cube,
        roomModel);

    ceiling->Draw(
        shader,
        cube,
        roomModel);

    DrawCeilingLights(
        shader,
        cube);
}

void Scene::DrawWorkstations(
    Shader& shader,
    const Cube& cube) const
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            float x = -5.5f + col * 3.2f;
            float z = -3.0f + row * 2.5f;

            //---------------- Desk ----------------

            glm::mat4 deskModel =
                glm::translate(
                    glm::mat4(1.0f),
                    glm::vec3(x, 0.0f, z));

            desk->Draw(
                shader,
                cube,
                deskModel);

            //---------------- Chair ----------------

            glm::mat4 chairModel = glm::mat4(1.0f);

            chairModel = glm::translate(
                chairModel,
                glm::vec3(x, 0.0f, z + 1.0f));

            // Rotate chair to face the desk
            chairModel = glm::rotate(
                chairModel,
                glm::radians(180.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));

            chair->Draw(
                shader,
                cube,
                chairModel);

            //---------------- Monitor ----------------

            glm::mat4 monitorModel = glm::mat4(1.0f);

            monitorModel = glm::translate(
                glm::mat4(1.0f),
                glm::vec3(x, 0.82f, z));

            monitorModel = glm::rotate(
                monitorModel,
                glm::radians(0.0f),
                glm::vec3(0, 1, 0));

            monitor->Draw(shader, cube, monitorModel);
        }
    }
}

void Scene::DrawLecturerStation(
    Shader& shader,
    const Cube& cube) const
{
    //-----------------------------
    // Lecturer desk (left of projector)
    //-----------------------------

    glm::mat4 model =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(-4.5f, 0.0f, -5.0f));

    desk->Draw(
        shader,
        cube,
        model);

    //-----------------------------
    // Lecturer chair
    //-----------------------------

    glm::mat4 chairModel =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(-4.5f, 0.0f, -5.5f));

    chairModel =
        glm::rotate(
            chairModel,
            glm::radians(0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

    chair->Draw(
        shader,
        cube,
        chairModel);
    //-----------------------------
    // Lecturer monitor
    //-----------------------------

    glm::mat4 monitorModel =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(-4.5f, 0.82f, -5.0f));

    monitorModel = glm::rotate(
        monitorModel,
        glm::radians(180.0f),
        glm::vec3(0, 1, 0));

    monitor->Draw(shader, cube, monitorModel);
}
void Scene::DrawNetworkCabinet(
    Shader& shader,
    const Cube& cube) const
{
    glm::mat4 model =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(7.35f, 1.0f, -5.2f));

    model =
        glm::scale(
            model,
            glm::vec3(0.8f, 2.0f, 0.8f));

    shader.setMat4("model", model);

    cube.Draw();
}

void Scene::DrawAirConditioner(
    Shader& shader,
    const Cube& cube) const
{
    glm::mat4 model =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(7.35f, 2.65f, -5.8f));

    model =
        glm::scale(
            model,
            glm::vec3(1.2f, 0.5f, 0.4f));

    shader.setMat4("model", model);

    cube.Draw();
}

void Scene::DrawProjectionScreen(
    Shader& shader,
    const Cube& cube) const
{
    glm::mat4 model =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(0.0f, 2.0f, -5.9f));

    model =
        glm::scale(
            model,
            glm::vec3(3.5f, 2.0f, 0.05f));

    shader.setMat4("model", model);

    cube.Draw();
}
void Scene::DrawCeilingLights(
    Shader& shader,
    const Cube& cube) const
{
    float xPos[3] =
    {
        -4.5f,
         0.0f,
         4.5f
    };

    float zPos[2] =
    {
        -3.5f,
         2.0f
    };

    for (int row = 0; row < 2; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            //-----------------------------
            // White LED panel
            //-----------------------------

            glm::mat4 panel = glm::mat4(1.0f);
            panel = glm::translate(
                panel,
                glm::vec3(
                    xPos[col],
                    2.985f,
                    zPos[row]));
           

            panel = glm::scale(
                panel,
                glm::vec3(
                    1.60f,
                    0.01f,
                    0.80f));

            shader.setVec3(
                "objectColor",
                0.98f,
                0.98f,
                0.96f);

            shader.setMat4(
                "model",
                panel);

            cube.Draw();

            //-----------------------------
            // Grey border
            //-----------------------------

            glm::mat4 border = glm::mat4(1.0f);

            border = glm::translate(
                border,
                glm::vec3(
                    xPos[col],
                    2.935f,
                    zPos[row]));

            border = glm::scale(
                border,
                glm::vec3(
                    1.68f,
                    0.015f,
                    0.88f));

            shader.setVec3(
                "objectColor",
                0.72f,
                0.72f,
                0.72f);

            shader.setMat4(
                "model",
                border);

            cube.Draw();
        }
    }
}
void Scene::DrawProjector(
    Shader& shader,
    const Cube& cube) const
{
    //-------------------------
    // Ceiling pole
    //-------------------------

    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            2.75f,
            -2.3f));

    model = glm::scale(
        model,
        glm::vec3(
            0.05f,
            0.35f,
            0.05f));

    shader.setVec3(
        "objectColor",
        0.35f,
        0.35f,
        0.35f);

    shader.setMat4(
        "model",
        model);

    cube.Draw();

    //-------------------------
    // Projector body
    //-------------------------

    model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            2.55f,
            -2.3f));

    model = glm::scale(
        model,
        glm::vec3(
            0.65f,
            0.22f,
            0.45f));

    shader.setVec3(
        "objectColor",
        0.92f,
        0.92f,
        0.92f);

    shader.setMat4(
        "model",
        model);

    cube.Draw();

    //-------------------------
    // Lens
    //-------------------------

    model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(
            0.0f,
            2.55f,
            -2.52f));

    model = glm::scale(
        model,
        glm::vec3(
            0.12f,
            0.12f,
            0.08f));

    shader.setVec3(
        "objectColor",
        0.10f,
        0.10f,
        0.20f);

    shader.setMat4(
        "model",
        model);

    cube.Draw();
}

    void Scene::DrawWhiteboard(
        Shader& shader,
        const Cube& cube) const
    {
        //-------------------------
        // Whiteboard
        //-------------------------

        glm::mat4 model(1.0f);
        model = glm::translate(
            model,
            glm::vec3(
                5.0f,
                2.0f,
                -5.88f));
        
        model = glm::scale(
            model,
            glm::vec3(
                2.8f,
                1.7f,
                0.05f));

        shader.setVec3(
            "objectColor",
            0.97f,
            0.97f,
            0.97f);

        shader.setMat4(
            "model",
            model);

        cube.Draw();

        //-------------------------
        // Aluminium frame
        //-------------------------

        shader.setVec3(
            "objectColor",
            0.65f,
            0.65f,
            0.65f);

        // Top
        model = glm::mat4(1.0f);
        model = glm::translate(
            model,

            glm::vec3(5.0f, 2.88f, -5.86f));
        model = glm::scale(
            model,
            glm::vec3(2.9f, 0.05f, 0.07f));
        shader.setMat4("model", model);
        cube.Draw();

        // Bottom
        model = glm::mat4(1.0f);
        model = glm::translate(
            model,
            glm::vec3(5.0f, 1.12f, -5.86f));
        model = glm::scale(
            model,
            glm::vec3(2.9f, 0.05f, 0.07f));
        shader.setMat4("model", model);
        cube.Draw();

        // Left
        model = glm::mat4(1.0f);
        model = glm::translate(
            model,
            glm::vec3(3.58f, 2.0f, -5.86f));
        model = glm::scale(
            model,
            glm::vec3(0.05f, 1.8f, 0.07f));
        shader.setMat4("model", model);
        cube.Draw();

        // Right
        model = glm::mat4(1.0f);
        model = glm::translate(
            model,
            glm::vec3(6.42f, 2.0f, -5.86f));
        model = glm::scale(
            model,
            glm::vec3(0.05f, 1.8f, 0.07f));
        shader.setMat4("model", model);
        cube.Draw();

        //-------------------------
        // Marker tray
        //-------------------------

        shader.setVec3(
            "objectColor",
            0.80f,
            0.80f,
            0.80f);

        model = glm::mat4(1.0f);

        model = glm::translate(
            model,
            glm::vec3(
                5.0f,
                1.0f,
                -5.75f));

        model = glm::scale(
            model,
            glm::vec3(
                1.6f,
                0.05f,
                0.18f));

        shader.setMat4(
            "model",
            model);

        cube.Draw();
        //------------------------------------------------------
        // MARKERS
        //------------------------------------------------------

        struct MarkerData
        {
            float x;
            float z;
            float angle;
            glm::vec3 capColor;
        };

        MarkerData markers[] =
        {
            {4.45f, -5.74f,  8.0f, glm::vec3(0.90f,0.05f,0.05f)}, // Red
            {4.80f, -5.73f, -5.0f, glm::vec3(0.05f,0.25f,0.95f)}, // Blue
            {5.15f, -5.75f,  6.0f, glm::vec3(0.05f,0.75f,0.15f)}, // Green
           
        };

        for (const auto& m : markers)
        {
            glm::mat4 marker = glm::mat4(1.0f);

            marker = glm::translate(
                marker,
                glm::vec3(m.x, 1.07f, m.z));

            marker = glm::rotate(
                marker,
                glm::radians(m.angle),
                glm::vec3(0, 1, 0));

            //--------------------------------------------------
            // White body
            //--------------------------------------------------

            shader.setVec3("objectColor",
                0.96f,
                0.96f,
                0.96f);

            glm::mat4 part = glm::translate(
                marker,
                glm::vec3(0.0f, 0.0f, 0.0f));

            part = glm::scale(
                part,
                glm::vec3(
                    0.22f,
                    0.025f,
                    0.025f));

            shader.setMat4("model", part);
            cube.Draw();

            //--------------------------------------------------
            // Grey ring
            //--------------------------------------------------

            shader.setVec3("objectColor",
                0.65f,
                0.65f,
                0.65f);

            part = glm::translate(
                marker,
                glm::vec3(
                    0.082f,
                    0.0f,
                    0.0f));

            part = glm::scale(
                part,
                glm::vec3(
                    0.012f,
                    0.030f,
                    0.030f));

            shader.setMat4("model", part);
            cube.Draw();

            //--------------------------------------------------
            // Coloured cap
            //--------------------------------------------------

            shader.setVec3(
                "objectColor",
                m.capColor.x,
                m.capColor.y,
                m.capColor.z);

            part = glm::translate(
                marker,
                glm::vec3(
                    0.110f,
                    0.0f,
                    0.0f));

            part = glm::scale(
                part,
                glm::vec3(
                    0.055f,
                    0.033f,
                    0.033f));

            shader.setMat4("model", part);
            cube.Draw();

            //--------------------------------------------------
            // Cap clip
            //--------------------------------------------------

            shader.setVec3(
                "objectColor",
                m.capColor.x * 0.9f,
                m.capColor.y * 0.9f,
                m.capColor.z * 0.9f);

            part = glm::translate(
                marker,
                glm::vec3(
                    0.115f,
                    0.022f,
                    0.0f));

            part = glm::scale(
                part,
                glm::vec3(
                    0.045f,
                    0.008f,
                    0.010f));

            shader.setMat4("model", part);
            cube.Draw();

            //--------------------------------------------------
            // Black tip
            //--------------------------------------------------

            shader.setVec3(
                "objectColor",
                0.05f,
                0.05f,
                0.05f);

            part = glm::translate(
                marker,
                glm::vec3(
                    -0.112f,
                    0.0f,
                    0.0f));

            part = glm::scale(
                part,
                glm::vec3(
                    0.020f,
                    0.018f,
                    0.018f));

            shader.setMat4("model", part);
            cube.Draw();

            //--------------------------------------------------
            // Felt nib
            //--------------------------------------------------

            shader.setVec3(
                "objectColor",
                0.18f,
                0.18f,
                0.18f);

            part = glm::translate(
                marker,
                glm::vec3(
                    -0.126f,
                    0.0f,
                    0.0f));

            part = glm::scale(
                part,
                glm::vec3(
                    0.010f,
                    0.010f,
                    0.010f));

            shader.setMat4("model", part);
            cube.Draw();

            //--------------------------------------------------
            // Back end
            //--------------------------------------------------

            shader.setVec3(
                "objectColor",
                0.90f,
                0.90f,
                0.90f);

            part = glm::translate(
                marker,
                glm::vec3(
                    0.145f,
                    0.0f,
                    0.0f));

            part = glm::scale(
                part,
                glm::vec3(
                    0.012f,
                    0.022f,
                    0.022f));

            shader.setMat4("model", part);
            cube.Draw();
        }
        //-------------------------
        // Duster (Eraser)
        //-------------------------

        // Wooden top
        shader.setVec3("objectColor", 0.45f, 0.28f, 0.12f);

        model = glm::mat4(1.0f);
        model = glm::translate(
            model,
            glm::vec3(
                5.65f,
                1.08f,
                -5.74f));

        model = glm::scale(
            model,
            glm::vec3(
                0.30f,
                0.05f,
                0.10f));

        shader.setMat4("model", model);
        cube.Draw();

        // Felt bottom
        shader.setVec3("objectColor", 0.18f, 0.18f, 0.18f);

        model = glm::mat4(1.0f);
        model = glm::translate(
            model,
            glm::vec3(
                5.65f,
                1.045f,
                -5.74f));

        model = glm::scale(
            model,
            glm::vec3(
                0.30f,
                0.02f,
                0.10f));

        shader.setMat4("model", model);
        cube.Draw();
    }