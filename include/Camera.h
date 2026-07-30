#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};



class Camera
{

public:

    // Camera attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;


    // Euler angles
    float Yaw;
    float Pitch;


    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;



    Camera(
        glm::vec3 position = glm::vec3(0.0f, 1.7f, 5.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f
    );



    // Returns view matrix
    glm::mat4 GetViewMatrix();



    // Keyboard movement
    void ProcessKeyboard(
        Camera_Movement direction,
        float deltaTime
    );



    // Mouse movement
    void ProcessMouseMovement(
        float xoffset,
        float yoffset,
        bool constrainPitch = true
    );



private:

    // Update Front, Right, Up vectors
    void updateCameraVectors();


    // Keep player inside laboratory
    void KeepInsideRoom();

};