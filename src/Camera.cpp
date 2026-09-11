#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


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

// ============================================================
// TOP-DOWN FLOOR PLAN VIEW
// ============================================================
//
// Camera position:
//     X = 0
//     Y = 12
//     Z = 0
//
// Looking directly down at the centre of the laboratory.
//
// ============================================================

glm::mat4 Camera::GetFloorPlanView() const
{
    glm::vec3 cameraPosition(
        0.0f,
        12.0f,
        0.0f
    );

    glm::vec3 target(
        0.0f,
        0.0f,
        0.0f
    );

    // Keeps the floor-plan orientation stable.
    //
    // Because the camera is looking straight down,
    // the normal Y-up vector cannot be used.
    //
    glm::vec3 up(
        0.0f,
        0.0f,
        -1.0f
    );

    return glm::lookAt(
        cameraPosition,
        target,
        up
    );
}


// ============================================================
// TOP-DOWN ORTHOGRAPHIC PROJECTION
// ============================================================
//
// Laboratory dimensions:
//
// X = -7.5 -> +7.5  = 15 metres
// Z = -6.5 -> +6.5  = 13 metres
//
// Extra margin is added so the walls are not touching
// the edge of the screen.
//
// ============================================================

glm::mat4 Camera::GetFloorPlanProjection(
    float screenWidth,
    float screenHeight) const
{
    float aspect =
        screenWidth / screenHeight;

    const float roomWidth = 15.0f;
    const float roomDepth = 13.0f;

    const float margin = 1.5f;

    float halfWidth =
        (roomWidth * 0.5f) + margin;

    float halfHeight =
        (roomDepth * 0.5f) + margin;


    // Maintain the correct room proportions
    // regardless of window aspect ratio.

    if (aspect >= 1.0f)
    {
        halfWidth *= aspect;
    }
    else
    {
        halfHeight /= aspect;
    }


    return glm::ortho(
        -halfWidth,
        halfWidth,

        -halfHeight,
        halfHeight,

        0.1f,
        50.0f
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