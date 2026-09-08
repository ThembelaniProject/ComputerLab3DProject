#pragma once

#include <vector>

#include <glm/glm.hpp>
#include "Texture.h"
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

    void Draw(
        Shader& shader,
        const Cube& cube
    ) const;

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

    void DrawWorkstations(
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