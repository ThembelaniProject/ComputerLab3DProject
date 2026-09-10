#pragma once

#include <vector>

#include <glm/glm.hpp>
#include "Texture.h"
#include "Window.h"
class Shader;
class Cube;
class Room;
class Desk;
class Chair;
class Monitor;
class Door;
class Window;
class Ceiling;


    

class Scene
{
public:
    Scene();

    Chair* GetChair() const { return chair; }

    void Draw(
        Shader& shader,
        const Cube& cube
    ) const;

    // Animation/update
    void Update(float deltaTime);

    // Window controls
    void ToggleWindow();
    void OpenWindow();
    void CloseWindow();

    // Door controls
    void ToggleDoor();
    void OpenDoor();
    void CloseDoor();

private:

    Room* room;
    Desk* desk;
    Chair* chair;
    Monitor* monitor;
    Door* door;
    Window* window;
    Ceiling* ceiling;

    Texture keyboardTexture;
    Texture pcFrontTexture;
    Texture airconTexture;

    // Daylight / evening transition
    float daylightIntensity;
    float transitionSpeed;
    bool eveningMode;


    void DrawWorkstations(
        Shader& shader,
        const Cube& cube
    ) const;
    void DrawWindows(
        Shader& shader,
        const Cube& cube
    ) const;

    
    void DrawLecturerStation(
        Shader& shader,
        const Cube& cube
    ) const;

    void DrawNetworkCabinet(
        Shader& shader,
        const Cube& cube
    ) const;

    void DrawAirConditioner(
        Shader& shader,
        const Cube& cube
    ) const;

    void DrawProjectionScreen(
        Shader& shader,
        const Cube& cube
    ) const;
    void DrawCeilingLights(
        Shader& shader,
        const Cube& cube
    ) const;
    void DrawProjector(
        Shader& shader,
        const Cube& cube
    ) const;
   void DrawWhiteboard(
        Shader& shader,
        const Cube& cube
    ) const;

};