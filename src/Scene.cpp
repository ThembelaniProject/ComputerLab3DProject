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
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Scene::Scene()
    : keyboardTexture("C:/Users/Thembelani/source/repos/ThembelaniProject/ComputerLab3DProject/Resources/Textures/keyboard.png"),
    pcFrontTexture("C:/Users/Thembelani/source/repos/ThembelaniProject/ComputerLab3DProject/Resources/Textures/pc.png"),
    airconTexture("C:/Users/Thembelani/source/repos/ThembelaniProject/ComputerLab3DProject/Resources/Textures/aircon.png")
{
    room = new Room();
    desk = new Desk();
    chair = new Chair();
    monitor = new Monitor();
    door = new Door();
    window = new Window();
    ceiling = new Ceiling();
}
// ============================================================
// UPDATE
// ============================================================

void Scene::Update(float deltaTime)
{
    if (window)
    {
        window->Update(deltaTime);
    }
    if (door)
    {
        door->Update(deltaTime);
    }

    // ------------------------------------------------------------
   // DAYLIGHT -> EVENING TRANSITION
   // ------------------------------------------------------------

    if (eveningMode)
    {
        daylightIntensity -= transitionSpeed * deltaTime;

        if (daylightIntensity <= 0.0f)
        {
            daylightIntensity = 0.0f;
        }
    }
    else
    {
        daylightIntensity += transitionSpeed * deltaTime;

        if (daylightIntensity >= 1.0f)
        {
            daylightIntensity = 1.0f;
        }
    }
}


// ============================================================
// WINDOW CONTROLS
// ============================================================

void Scene::ToggleWindow()
{
    if (window)
    {
        window->Toggle();
    }
}


void Scene::OpenWindow()
{
    if (window)
    {
        window->Open();
    }
}


void Scene::CloseWindow()
{
    if (window)
    {
        window->Close();
    }
}

// ============================================================
// DOOR CONTROLS
// ============================================================

void Scene::ToggleDoor()
{
    if (door)
    {
        door->Toggle();
    }
}

void Scene::OpenDoor()
{
    if (door)
    {
        door->SetAngle(90.0f);
    }
}

void Scene::CloseDoor()
{
    if (door)
    {
        door->SetAngle(0.0f);
    }
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

    // Draw floor plan only when toggled on
    if (showFloorPlan)
    {
        DrawFloorPlan(shader, cube);
    }

    // ===== NEW SAFETY FEATURES =====
    DrawFireExtinguishers(shader, cube);   // CO₂ extinguishers
    DrawUnderFloorTrunking(shader, cube);  // Power + data under floor
    glm::mat4 roomModel(1.0f);

    door->Draw(
        shader,
        cube,
        roomModel);

    window->Draw(
        shader,
        cube,
        roomModel);

    // ============================================================
 // CEILING
 // ============================================================
 // Hide ceiling in floor-plan mode so it does not block
 // the top-down view of the laboratory.

    if (!showFloorPlan)
    {
        ceiling->Draw(
            shader,
            cube,
            roomModel
        );
    }

    // ============================================================
 // CEILING LIGHTS
 // ============================================================
 // Hide overhead lights in floor-plan mode.

    if (!showFloorPlan)
    {
        DrawCeilingLights(
            shader,
            cube
        );
    }
}

void Scene::ToggleFloorPlan()
{
    showFloorPlan = !showFloorPlan;
}

void Scene::DrawFloorPlan(Shader& shader, const Cube& cube) const
{
    auto drawFloorRect = [&](float x, float z, float width, float depth, const glm::vec3& color)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(x, 0.015f, z));
            model = glm::scale(model, glm::vec3(width, 0.01f, depth));
            shader.setVec3("objectColor", color.x, color.y, color.z);
            shader.setMat4("model", model);
            cube.Draw();
        };

    glm::vec3 aisleColor(0.75f, 0.78f, 0.82f);
    glm::vec3 deskZoneColor(0.92f, 0.92f, 0.88f);
    glm::vec3 safetyColor(0.95f, 0.25f, 0.25f);
    glm::vec3 trunkColor(0.35f, 0.55f, 0.75f);
    glm::vec3 lecturerColor(0.85f, 0.80f, 0.70f);
    glm::vec3 cabinetZone(0.40f, 0.40f, 0.45f);
    glm::vec3 accessibleColor(0.40f, 0.75f, 0.45f);

    // Main circulation aisles
    drawFloorRect(0.0f, 0.0f, 1.4f, 14.0f, aisleColor);
    for (int row = 0; row < 5; row++)
    {
        float z = -4.25f + row * 2.5f;
        drawFloorRect(0.0f, z, 13.0f, 1.1f, aisleColor);
    }

    // Desk zones
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            float x = -5.5f + col * 3.2f;
            float z = -3.0f + row * 2.5f;
            drawFloorRect(x, z, 2.4f, 1.6f, deskZoneColor);
        }
    }

    // Lecturer zone
    drawFloorRect(-4.5f, -5.1f, 2.8f, 2.2f, lecturerColor);

    // Network cabinet zone
    drawFloorRect(7.35f, -5.2f, 1.6f, 1.6f, cabinetZone);

    // Under-floor trunking
    for (int row = 0; row < 4; row++)
    {
        float z = -3.0f + row * 2.5f;
        drawFloorRect(0.0f, z, 12.0f, 0.22f, trunkColor);
    }

    // Fire extinguisher markers
    drawFloorRect(7.4f, -5.5f, 0.55f, 0.55f, safetyColor);
    drawFloorRect(-7.4f, 4.0f, 0.55f, 0.55f, safetyColor);

    // Wheelchair accessible workstation
    drawFloorRect(-5.5f, -3.0f, 2.6f, 1.8f, accessibleColor);
}

void Scene::DrawFloorPlanButton(Shader& shader, const Cube& cube, int screenWidth, int screenHeight) const
{
    // Switch to 2D orthographic
    glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    // Button size and position (bottom-left corner)
    float btnWidth = 180.0f;
    float btnHeight = 45.0f;
    float btnX = 20.0f;
    float btnY = 20.0f;

    // Background of the button
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(btnX + btnWidth / 2, btnY + btnHeight / 2, 0.0f));
    model = glm::scale(model, glm::vec3(btnWidth, btnHeight, 1.0f));

    // Change colour when floor plan is active
    if (showFloorPlan)
        shader.setVec3("objectColor", 0.20f, 0.55f, 0.90f); // blue when ON
    else
        shader.setVec3("objectColor", 0.25f, 0.25f, 0.28f); // dark grey when OFF

    shader.setMat4("model", model);
    cube.Draw();

    // You can later add text with a font library.
    // For now the colour change shows the state.
}


bool Scene::IsFloorPlanVisible() const
{
    return showFloorPlan;
}

bool Scene::IsFloorPlanButtonClicked(double mouseX, double mouseY, int screenWidth, int screenHeight) const
{
    float glY = static_cast<float>(screenHeight) - static_cast<float>(mouseY);

    const float btnWidth = 180.0f;
    const float btnHeight = 45.0f;
    const float btnX = 20.0f;
    const float btnY = 20.0f;

    return (mouseX >= btnX && mouseX <= btnX + btnWidth &&
        glY >= btnY && glY <= btnY + btnHeight);
}

void Scene::DrawFireExtinguishers(Shader& shader, const Cube& cube) const
{
    // Helper that draws one CO₂ extinguisher
    // rotationY rotates the whole extinguisher so the bracket faces the wall
    auto drawExtinguisher = [&](const glm::vec3& pos, float rotationY = 0.0f)
        {
            glm::mat4 base = glm::mat4(1.0f);
            base = glm::translate(base, pos);
            base = glm::rotate(base, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));

            // ---- Main red cylinder body ----
            glm::mat4 model = base;
            model = glm::scale(model, glm::vec3(0.18f, 0.55f, 0.18f));
            shader.setVec3("objectColor", 0.85f, 0.05f, 0.05f); // Safety red
            shader.setMat4("model", model);
            cube.Draw();

            // ---- Black top / valve ----
            model = base;
            model = glm::translate(model, glm::vec3(0.0f, 0.32f, 0.0f));
            model = glm::scale(model, glm::vec3(0.12f, 0.08f, 0.12f));
            shader.setVec3("objectColor", 0.12f, 0.12f, 0.12f);
            shader.setMat4("model", model);
            cube.Draw();

            // ---- Nozzle / hose ----
            model = base;
            model = glm::translate(model, glm::vec3(0.12f, 0.28f, 0.0f));
            model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f, 0.04f, 0.04f));
            shader.setVec3("objectColor", 0.15f, 0.15f, 0.15f);
            shader.setMat4("model", model);
            cube.Draw();

            // ---- Wall bracket ----
            model = base;
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.12f));
            model = glm::scale(model, glm::vec3(0.10f, 0.08f, 0.04f));
            shader.setVec3("objectColor", 0.35f, 0.35f, 0.35f);
            shader.setMat4("model", model);
            cube.Draw();
        };

    // ============================================================
    // 1. Right wall – next to network cabinet (highest electrical risk)
    // ============================================================
    drawExtinguisher(glm::vec3(9.55f, 0.90f, -10.9f), 180.0f);

    // ============================================================
    // 2. Left wall – near the main exit / door
    // ============================================================
    drawExtinguisher(glm::vec3(-7.55f, 1.90f, 0.2f), -90.0f);
}

void Scene::DrawUnderFloorTrunking(Shader& shader, const Cube& cube) const
{
    // Colour of the metal trunking
    glm::vec3 trunkColor(0.45f, 0.47f, 0.48f);
    glm::vec3 boxColor(0.55f, 0.55f, 0.55f);

    // -------------------------------------------------
    // Long under-floor ducts under each row of desks
    // -------------------------------------------------
    for (int row = 0; row < 4; row++)
    {
        float z = -3.0f + row * 2.5f;

        // Main horizontal trunking running under the whole row
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.02f, z)); // just above floor
        model = glm::scale(model, glm::vec3(12.5f, 0.04f, 0.18f));
        shader.setVec3("objectColor", trunkColor.x, trunkColor.y, trunkColor.z);
        shader.setMat4("model", model);
        cube.Draw();
    }

    // -------------------------------------------------
    // Vertical risers / floor boxes under every desk
    // -------------------------------------------------
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            float x = -5.5f + col * 3.2f;
            float z = -3.0f + row * 2.5f;

            // Small floor box under the desk
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(x, 0.04f, z + 0.15f));
            model = glm::scale(model, glm::vec3(0.35f, 0.06f, 0.25f));
            shader.setVec3("objectColor", boxColor.x, boxColor.y, boxColor.z);
            shader.setMat4("model", model);
            cube.Draw();
        }
    }

    // Also serve the lecturer station
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-4.5f, 0.04f, -4.6f));
        model = glm::scale(model, glm::vec3(0.40f, 0.06f, 0.30f));
        shader.setVec3("objectColor", boxColor.x, boxColor.y, boxColor.z);
        shader.setMat4("model", model);
        cube.Draw();
    }
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
                keyboardTexture,
                pcFrontTexture,   // ← pass it here
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

            if (row == 0 && col == 0)
            {
                // Designated Wheelchair-Accessible Workstation (Aisle Front Row)
                // Armrests flipped 90 degrees up for unobstructed lateral transfer,
                // elevated +0.05m to match wheelchair seat height, and caster safety brakes locked.
                chair->Draw(
                    shader,
                    cube,
                    chairModel,
                    0.05f,   // Elevated for level wheelchair cushion transfer
                    90.0f,   // Armrests flipped up 90 degrees
                    true     // Wheelchair transfer safety brakes locked
                );
            }
            else
            {
                chair->Draw(
                    shader,
                    cube,
                    chairModel);
            }

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
    // Lecturer desk
    //-----------------------------

    glm::mat4 model =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(-4.5f, 0.0f, -4.8f)
        );

    // Rotate the entire desk setup 180 degrees
    // so the keyboard and mouse face the monitor.
    model =
        glm::rotate(
            model,
            glm::radians(180.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

    desk->Draw(
        shader,
        cube,
        keyboardTexture,
        pcFrontTexture,
        model
    );


    //-----------------------------
    // Lecturer chair
    //-----------------------------

    glm::mat4 chairModel =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(-4.5f, 0.0f, -5.5f)
        );

    chairModel =
        glm::rotate(
            chairModel,
            glm::radians(0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

    chair->Draw(
        shader,
        cube,
        chairModel
    );


    //-----------------------------
    // Lecturer monitor
    //-----------------------------

    glm::mat4 monitorModel =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(-4.5f, 0.82f, -4.8f)
        );

    // Monitor faces the opposite direction
    monitorModel =
        glm::rotate(
            monitorModel,
            glm::radians(180.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

    monitor->Draw(
        shader,
        cube,
        monitorModel
    );
}
void Scene::DrawNetworkCabinet(
    Shader& shader,
    const Cube& cube) const
{
    // ---------------------------------------------------------
    // NETWORK CABINET POSITION
    // ---------------------------------------------------------
    glm::vec3 position(
        7.35f,
        1.0f,
        -5.2f
    );

    // Overall cabinet size
    glm::vec3 cabinetScale(
        0.8f,
        2.0f,
        0.8f
    );

    // ---------------------------------------------------------
    // Helper for drawing cabinet parts
    // ---------------------------------------------------------
    auto drawPart =
        [&](const glm::vec3& localPosition,
            const glm::vec3& localScale,
            const glm::vec3& color)
        {
            glm::mat4 model =
                glm::mat4(1.0f);

            model = glm::translate(
                model,
                position
            );

            // Rotate the COMPLETE network cabinet
            model = glm::rotate(
                model,
                glm::radians(180.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
            );

            model = glm::translate(
                model,
                localPosition
            );
            model =
                glm::scale(
                    model,
                    localScale
                );

            shader.setVec3(
                "objectColor",
                color.x,
                color.y,
                color.z
            );

            shader.setMat4(
                "model",
                model
            );

            cube.Draw();
        };

    // ---------------------------------------------------------
    // COLOURS
    // ---------------------------------------------------------
    glm::vec3 cabinetBlack(
        0.08f,
        0.09f,
        0.10f
    );

    glm::vec3 darkMetal(
        0.14f,
        0.15f,
        0.16f
    );

    glm::vec3 metal(
        0.30f,
        0.32f,
        0.34f
    );

    glm::vec3 glass(
        0.12f,
        0.20f,
        0.25f
    );

    glm::vec3 silver(
        0.55f,
        0.57f,
        0.58f
    );

    glm::vec3 serverBlack(
        0.05f,
        0.055f,
        0.06f
    );

    glm::vec3 blue(
        0.02f,
        0.35f,
        0.75f
    );

    glm::vec3 green(
        0.05f,
        0.80f,
        0.20f
    );

    glm::vec3 red(
        0.85f,
        0.05f,
        0.04f
    );

    // =========================================================
    // MAIN CABINET FRAME
    // =========================================================

    // Top
    drawPart(
        { 0.0f, 0.97f, 0.0f },
        { 0.82f, 0.08f, 0.82f },
        cabinetBlack
    );

    // Bottom
    drawPart(
        { 0.0f, -0.97f, 0.0f },
        { 0.82f, 0.08f, 0.82f },
        cabinetBlack
    );

    // Left vertical frame
    drawPart(
        { -0.36f, 0.0f, 0.0f },
        { 0.08f, 1.90f, 0.78f },
        darkMetal
    );

    // Right vertical frame
    drawPart(
        { 0.36f, 0.0f, 0.0f },
        { 0.08f, 1.90f, 0.78f },
        darkMetal
    );

    // Back panel
    drawPart(
        { 0.0f, 0.0f, 0.35f },
        { 0.68f, 1.85f, 0.06f },
        darkMetal
    );

    // =========================================================
    // FRONT DOOR
    // =========================================================

    // Outer door
    drawPart(
        { 0.0f, 0.0f, -0.43f },
        { 0.68f, 1.82f, 0.055f },
        cabinetBlack
    );

    // Glass window
    drawPart(
        { 0.0f, 0.20f, -0.465f },
        { 0.55f, 1.25f, 0.018f },
        glass
    );

    // Door top frame
    drawPart(
        { 0.0f, 0.86f, -0.47f },
        { 0.65f, 0.06f, 0.035f },
        metal
    );

    // Door bottom frame
    drawPart(
        { 0.0f, -0.84f, -0.47f },
        { 0.65f, 0.06f, 0.035f },
        metal
    );

    // Door left frame
    drawPart(
        { -0.31f, 0.0f, -0.47f },
        { 0.045f, 1.75f, 0.035f },
        metal
    );

    // Door right frame
    drawPart(
        { 0.31f, 0.0f, -0.47f },
        { 0.045f, 1.75f, 0.035f },
        metal
    );

    // =========================================================
    // DOOR HANDLE / LOCK
    // =========================================================

    drawPart(
        { 0.28f, 0.35f, -0.51f },
        { 0.035f, 0.22f, 0.035f },
        silver
    );

    drawPart(
        { 0.28f, 0.48f, -0.52f },
        { 0.06f, 0.06f, 0.025f },
        darkMetal
    );

    // =========================================================
    // RACK RAILS
    // =========================================================

    // Left rack rail
    drawPart(
        { -0.25f, 0.0f, -0.32f },
        { 0.035f, 1.65f, 0.035f },
        silver
    );

    // Right rack rail
    drawPart(
        { 0.25f, 0.0f, -0.32f },
        { 0.035f, 1.65f, 0.035f },
        silver
    );

    // =========================================================
    // SERVER UNITS
    // =========================================================

    for (int i = 0; i < 6; i++)
    {
        float y =
            0.62f - (i * 0.25f);

        // Server body
        drawPart(
            { 0.0f, y, -0.35f },
            { 0.48f, 0.18f, 0.28f },
            serverBlack
        );

        // Server front panel
        drawPart(
            { 0.0f, y, -0.50f },
            { 0.48f, 0.17f, 0.025f },
            darkMetal
        );

        // Server left indicator
        drawPart(
            { -0.17f, y, -0.53f },
            { 0.025f, 0.025f, 0.015f },
            green
        );

        // Server right indicator
        drawPart(
            { -0.11f, y, -0.53f },
            { 0.025f, 0.025f, 0.015f },
            blue
        );

        // Server ventilation
        for (int v = 0; v < 4; v++)
        {
            drawPart(
                {
                    0.05f + v * 0.06f,
                    y,
                    -0.53f
                },
                { 0.025f, 0.035f, 0.012f },
                cabinetBlack
            );
        }
    }

    // =========================================================
    // NETWORK SWITCH
    // =========================================================

    drawPart(
        { 0.0f, -0.72f, -0.35f },
        { 0.50f, 0.14f, 0.28f },
        darkMetal
    );

    drawPart(
        { 0.0f, -0.72f, -0.51f },
        { 0.50f, 0.10f, 0.025f },
        serverBlack
    );

    // Ethernet port lights
    for (int i = 0; i < 8; i++)
    {
        glm::vec3 lightColor =
            (i % 2 == 0) ? green : blue;

        drawPart(
            {
                -0.20f + i * 0.055f,
                -0.72f,
                -0.54f
            },
            { 0.025f, 0.035f, 0.012f },
            lightColor
        );
    }

    // =========================================================
    // TOP VENTILATION
    // =========================================================

    for (int i = 0; i < 7; i++)
    {
        drawPart(
            {
                -0.24f + i * 0.08f,
                0.91f,
                -0.05f
            },
            { 0.035f, 0.025f, 0.55f },
            cabinetBlack
        );
    }

    // =========================================================
    // RUBBER / METAL FEET
    // =========================================================

    drawPart(
        { -0.28f, -1.04f, -0.25f },
        { 0.15f, 0.08f, 0.15f },
        cabinetBlack
    );

    drawPart(
        { 0.28f, -1.04f, -0.25f },
        { 0.15f, 0.08f, 0.15f },
        cabinetBlack
    );

    drawPart(
        { -0.28f, -1.04f, 0.25f },
        { 0.15f, 0.08f, 0.15f },
        cabinetBlack
    );

    drawPart(
        { 0.28f, -1.04f, 0.25f },
        { 0.15f, 0.08f, 0.15f },
        cabinetBlack
    );
}
void Scene::DrawAirConditioner(
    Shader& shader,
    const Cube& cube) const
{
    // ============================================================
    // WALL-MOUNTED SPLIT AIR CONDITIONER
    // ============================================================
    //
    // The entire air conditioner is controlled as ONE assembly.
    //
    // position.x = move left / right
    // position.y = move up / down
    // position.z = move front / back
    //
    // Change ONLY position.x if you want to align it with
    // the network cabinet / wires.
    // ============================================================

    glm::vec3 position(
        7.0f,
        2.65f,
        5.92f
    );

    // Overall size of the COMPLETE air conditioner.
    // X is deliberately smaller so the AC is not too long.
    glm::vec3 acScale(
        0.80f,
        0.90f,
        0.90f
    );

    // ============================================================
    // HELPER FUNCTION
    // ============================================================
    //
    // Every component is positioned relative to the same
    // air-conditioner origin.
    //
    // This makes all parts move together as ONE unit.
    // ============================================================

    auto drawPart =
        [&](const glm::vec3& localPosition,
            const glm::vec3& localScale,
            const glm::vec3& color)
        {
            // Scale local position as part of the complete AC assembly
            glm::vec3 scaledLocalPosition(
                localPosition.x * acScale.x,
                localPosition.y * acScale.y,
                localPosition.z * acScale.z
            );

            glm::vec3 worldPosition =
                position + scaledLocalPosition;

            glm::mat4 model =
                glm::mat4(1.0f);

            // Move the COMPLETE AC into position
            model =
                glm::translate(
                    model,
                    position
                );

            // Rotate the COMPLETE AC to the opposite side
            model =
                glm::rotate(
                    model,
                    glm::radians(0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f)
                );

            // Move each component relative to the AC centre
            model =
                glm::translate(
                    model,
                    scaledLocalPosition
                );

            // Scale the individual component
            model =
                glm::scale(
                    model,
                    glm::vec3(
                        localScale.x * acScale.x,
                        localScale.y * acScale.y,
                        localScale.z * acScale.z
                    )
                );

            shader.setVec3(
                "objectColor",
                color.x,
                color.y,
                color.z
            );

            shader.setMat4(
                "model",
                model
            );

            cube.Draw();
        };


    // ============================================================
    // COLOURS
    // ============================================================

    glm::vec3 body(
        0.93f,
        0.94f,
        0.93f
    );

    glm::vec3 white(
        1.0f,
        1.0f,
        1.0f
    );

    glm::vec3 lightGrey(
        0.78f,
        0.80f,
        0.79f
    );

    glm::vec3 grey(
        0.55f,
        0.57f,
        0.56f
    );

    glm::vec3 darkGrey(
        0.10f,
        0.11f,
        0.12f
    );

    glm::vec3 grille(
        0.24f,
        0.25f,
        0.26f
    );

    glm::vec3 displayBlue(
        0.02f,
        0.55f,
        0.85f
    );

    glm::vec3 green(
        0.05f,
        0.85f,
        0.18f
    );


    // ============================================================
    // 1. MAIN AIR CONDITIONER BODY
    // ============================================================

    drawPart(
        glm::vec3(
            0.0f,
            0.0f,
            0.0f
        ),

        glm::vec3(
            1.65f,
            0.50f,
            0.40f
        ),

        body
    );


    // ============================================================
    // 2. TOP COVER
    // ============================================================

    drawPart(
        glm::vec3(
            0.0f,
            0.22f,
            -0.01f
        ),

        glm::vec3(
            1.58f,
            0.12f,
            0.38f
        ),

        white
    );


    // ============================================================
    // 3. TOP FRONT EDGE
    // ============================================================

    drawPart(
        glm::vec3(
            0.0f,
            0.30f,
            -0.04f
        ),

        glm::vec3(
            1.45f,
            0.055f,
            0.32f
        ),

        white
    );


    // ============================================================
    // 4. TOP AIR INTAKE
    // ============================================================

    drawPart(
        glm::vec3(
            0.0f,
            0.34f,
            -0.05f
        ),

        glm::vec3(
            1.30f,
            0.035f,
            0.20f
        ),

        darkGrey
    );


    // ============================================================
    // 5. TOP GRILLE
    // ============================================================

    for (int i = 0; i < 9; i++)
    {
        float x =
            -0.60f +
            (i * 0.15f);

        drawPart(
            glm::vec3(
                x,
                0.385f,
                -0.06f
            ),

            glm::vec3(
                0.025f,
                0.025f,
                0.17f
            ),

            grille
        );
    }


    // ============================================================
    // 6. FRONT PANEL
    // ============================================================

    drawPart(
        glm::vec3(
            0.0f,
            0.00f,
            -0.385f
        ),

        glm::vec3(
            1.58f,
            0.38f,
            0.055f
        ),

        white
    );


    // ============================================================
    // 7. FRONT PANEL UPPER SEAM
    // ============================================================

    drawPart(
        glm::vec3(
            0.0f,
            -0.145f,
            -0.415f
        ),

        glm::vec3(
            1.42f,
            0.025f,
            0.025f
        ),

        lightGrey
    );


    // ============================================================
    // 8. LOWER AIR OUTLET
    // ============================================================

    drawPart(
        glm::vec3(
            0.0f,
            -0.205f,
            -0.425f
        ),

        glm::vec3(
            1.30f,
            0.10f,
            0.045f
        ),

        darkGrey
    );


    // ============================================================
    // 9. AIR OUTLET INNER GRILLE
    // ============================================================

    drawPart(
        glm::vec3(
            0.0f,
            -0.205f,
            -0.450f
        ),

        glm::vec3(
            1.20f,
            0.025f,
            0.025f
        ),

        grille
    );


    // ============================================================
    // 10. MAIN AIRFLOW LOUVER
    // ============================================================

    drawPart(
        glm::vec3(
            0.0f,
            -3.285f,
            -0.455f
        ),

        glm::vec3(
            1.18f,
            0.025f,
            0.040f
        ),

        white
    );


    // ============================================================
    // 11. VERTICAL LOUVER SECTIONS
    // ============================================================

    for (int i = 0; i < 7; i++)
    {
        float x =
            -0.65f +
            (i * 0.216f);

        drawPart(
            glm::vec3(
                x,
                -0.25f,
                -0.49f
            ),

            glm::vec3(
                0.025f,
                0.07f,
                0.025f
            ),

            lightGrey
        );
    }


    // ============================================================
    // 12. LEFT SIDE CAP
    // ============================================================

    drawPart(
        glm::vec3(
            -0.82f,
            0.0f,
            0.0f
        ),

        glm::vec3(
            0.08f,
            0.43f,
            0.35f
        ),

        lightGrey
    );


    // ============================================================
    // 13. RIGHT SIDE CAP
    // ============================================================

    drawPart(
        glm::vec3(
            0.82f,
            0.0f,
            0.0f
        ),

        glm::vec3(
            0.08f,
            0.43f,
            0.35f
        ),

        lightGrey
    );


    // ============================================================
    // 14. LEFT SIDE VENT
    // ============================================================

    drawPart(
        glm::vec3(
            -0.86f,
            0.02f,
            -0.05f
        ),

        glm::vec3(
            0.025f,
            0.25f,
            0.18f
        ),

        darkGrey
    );


    // ============================================================
    // 15. RIGHT SIDE VENT
    // ============================================================

    drawPart(
        glm::vec3(
            0.86f,
            0.02f,
            -0.05f
        ),

        glm::vec3(
            0.025f,
            0.25f,
            0.18f
        ),

        darkGrey
    );


    // ============================================================
    // 16. DISPLAY PANEL
    // ============================================================

    drawPart(
        glm::vec3(
            0.53f,
            0.06f,
            -0.410f
        ),

        glm::vec3(
            0.24f,
            0.095f,
            0.035f
        ),

        darkGrey
    );


    // ============================================================
    // 17. DIGITAL DISPLAY
    // ============================================================

    drawPart(
        glm::vec3(
            0.53f,
            0.06f,
            -0.435f
        ),

        glm::vec3(
            0.17f,
            0.045f,
            0.020f
        ),

        displayBlue
    );


    // ============================================================
    // 18. TEMPERATURE SENSOR
    // ============================================================

    drawPart(
        glm::vec3(
            0.25f,
            0.05f,
            -0.425f
        ),

        glm::vec3(
            0.045f,
            0.045f,
            0.030f
        ),

        darkGrey
    );


    // ============================================================
    // 19. POWER LED
    // ============================================================

    drawPart(
        glm::vec3(
            0.12f,
            0.05f,
            -0.428f
        ),

        glm::vec3(
            0.025f,
            0.025f,
            0.02f
        ),

        green
    );


    // ============================================================
    // 20. BRAND PANEL
    // ============================================================

    drawPart(
        glm::vec3(
            -0.38f,
            0.07f,
            -0.445f
        ),

        glm::vec3(
            0.25f,
            0.055f,
            0.015f
        ),

        lightGrey
    );


    // ============================================================
    // 21. BRAND STRIP
    // ============================================================

    drawPart(
        glm::vec3(
            -0.38f,
            0.07f,
            -0.463f
        ),

        glm::vec3(
            0.18f,
            0.025f,
            0.010f
        ),

        darkGrey
    );


    // ============================================================
    // 22. LOWER BODY STRIP
    // ============================================================

    drawPart(
        glm::vec3(
            0.0f,
            -0.25f,
            -0.42f
        ),

        glm::vec3(
            1.45f,
            0.035f,
            0.025f
        ),

        lightGrey
    );


    // ============================================================
    // 23. LEFT LOWER END CAP
    // ============================================================

    drawPart(
        glm::vec3(
            -0.78f,
            -0.23f,
            -0.43f
        ),

        glm::vec3(
            0.06f,
            0.10f,
            0.025f
        ),

        grey
    );


    // ============================================================
    // 24. RIGHT LOWER END CAP
    // ============================================================

    drawPart(
        glm::vec3(
            0.78f,
            -0.23f,
            -0.43f
        ),

        glm::vec3(
            0.06f,
            0.10f,
            0.025f
        ),

        grey
    );


    // ============================================================
    // 25. WALL MOUNTING BRACKET
    // ============================================================

    // Back plate
    drawPart(
        glm::vec3(
            0.0f,
            0.0f,
            0.25f
        ),

        glm::vec3(
            1.35f,
            0.38f,
            0.06f
        ),

        lightGrey
    );


    // Left mounting support
    drawPart(
        glm::vec3(
            -0.58f,
            -0.05f,
            0.30f
        ),

        glm::vec3(
            0.08f,
            0.25f,
            0.12f
        ),

        grey
    );


    // Right mounting support
    drawPart(
        glm::vec3(
            0.58f,
            -0.05f,
            0.30f
        ),

        glm::vec3(
            0.08f,
            0.25f,
            0.12f
        ),

        grey
    );


    // ============================================================
    // 26. SMALL TOP SIDE DETAILS
    // ============================================================

    drawPart(
        glm::vec3(
            -0.72f,
            0.31f,
            -0.05f
        ),

        glm::vec3(
            0.10f,
            0.035f,
            0.18f
        ),

        lightGrey
    );


    drawPart(
        glm::vec3(
            0.72f,
            0.31f,
            -0.05f
        ),

        glm::vec3(
            0.10f,
            0.035f,
            0.18f
        ),

        lightGrey
    );
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