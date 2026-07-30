#include "Camera.h"


const float SPEED = 4.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;



Camera::Camera(
    glm::vec3 position,
    glm::vec3 up,
    float yaw,
    float pitch)
{

    Position = position;

    WorldUp = up;

    Yaw = yaw;

    Pitch = pitch;



    Front = glm::vec3(
        0.0f,
        0.0f,
        -1.0f
    );



    MovementSpeed = SPEED;

    MouseSensitivity = SENSITIVITY;

    Zoom = ZOOM;



    updateCameraVectors();

}




glm::mat4 Camera::GetViewMatrix()
{

    return glm::lookAt(
        Position,
        Position + Front,
        Up
    );

}




void Camera::ProcessKeyboard(
    Camera_Movement direction,
    float deltaTime)
{

    float velocity =
        MovementSpeed * deltaTime;



    if (direction == FORWARD)
    {
        Position += Front * velocity;
    }



    if (direction == BACKWARD)
    {
        Position -= Front * velocity;
    }



    if (direction == LEFT)
    {
        Position -= Right * velocity;
    }



    if (direction == RIGHT)
    {
        Position += Right * velocity;
    }



    KeepInsideRoom();

}





void Camera::ProcessMouseMovement(
    float xoffset,
    float yoffset,
    bool constrainPitch)
{

    xoffset *= MouseSensitivity;

    yoffset *= MouseSensitivity;



    Yaw += xoffset;

    Pitch += yoffset;




    if (constrainPitch)
    {

        if (Pitch > 89.0f)
        {
            Pitch = 89.0f;
        }


        if (Pitch < -89.0f)
        {
            Pitch = -89.0f;
        }

    }



    updateCameraVectors();

}





void Camera::KeepInsideRoom()
{

    /*
       Computer Laboratory Size:

       Width  = 16 metres
       Length = 12 metres

       Camera limits:
       X : -7.5 -> 7.5
       Z : -5.5 -> 5.5

       Eye height:
       1.7 metres
    */


    if (Position.x > 7.5f)
    {
        Position.x = 7.5f;
    }


    if (Position.x < -7.5f)
    {
        Position.x = -7.5f;
    }




    if (Position.z > 5.5f)
    {
        Position.z = 5.5f;
    }


    if (Position.z < -5.5f)
    {
        Position.z = -5.5f;
    }



    // Human eye height

    Position.y = 1.7f;

}





void Camera::updateCameraVectors()
{

    glm::vec3 front;



    front.x =
        cos(glm::radians(Yaw))
        *
        cos(glm::radians(Pitch));



    front.y =
        sin(glm::radians(Pitch));



    front.z =
        sin(glm::radians(Yaw))
        *
        cos(glm::radians(Pitch));



    Front =
        glm::normalize(front);



    Right =
        glm::normalize(
            glm::cross(
                Front,
                WorldUp
            )
        );



    Up =
        glm::normalize(
            glm::cross(
                Right,
                Front
            )
        );

}