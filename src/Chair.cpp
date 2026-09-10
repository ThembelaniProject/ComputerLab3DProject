
#include "Chair.h"
#include "Cube.h"
#include "Shader.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <vector>
#include <algorithm>

// ============================================================
// ROUNDED CHAIR GEOMETRY SETTINGS
// ============================================================
//
// The original chair used Cube::Draw() for the cushion and
// backrest. A normal cube always has sharp 90-degree corners.
//
// This small mesh creates a proper rounded/beveled rectangular
// box while keeping the same model transforms used by the chair.
//
// Increase ROUNDED_BEVEL for more rounded corners.
// Increase ROUNDED_SEGMENTS for smoother corners.
//
// IMPORTANT:
// The mesh is generated as a unit cube (-0.5 to +0.5), so all
// existing Chair.cpp scale values continue to work.
// ============================================================

namespace
{
    constexpr float ROUNDED_BEVEL = 0.16f;
    constexpr int ROUNDED_SEGMENTS = 6;

    struct RoundedVertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
    };

    class RoundedBoxMesh
    {
    public:

        RoundedBoxMesh()
            : VAO(0),
            VBO(0),
            EBO(0),
            indexCount(0)
        {
            Build();
        }

        void Draw() const
        {
            glBindVertexArray(VAO);
            glDrawElements(
                GL_TRIANGLES,
                indexCount,
                GL_UNSIGNED_INT,
                nullptr
            );
            glBindVertexArray(0);
        }

    private:

        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
        GLsizei indexCount;

        // ----------------------------------------------------
        // Convert a point on the normal unit cube to a rounded
        // box surface.
        // ----------------------------------------------------
        glm::vec3 RoundPoint(
            const glm::vec3& p,
            glm::vec3& outNormal) const
        {
            const glm::vec3 halfSize(0.5f);

            const float b =
                std::min(
                    ROUNDED_BEVEL,
                    0.49f
                );

            const glm::vec3 inner =
                halfSize - glm::vec3(b);

            glm::vec3 clampedPoint;

            clampedPoint.x =
                std::clamp(p.x, -inner.x, inner.x);

            clampedPoint.y =
                std::clamp(p.y, -inner.y, inner.y);

            clampedPoint.z =
                std::clamp(p.z, -inner.z, inner.z);

            glm::vec3 offset =
                p - clampedPoint;

            float length =
                glm::length(offset);

            if (length > 0.00001f)
            {
                outNormal =
                    glm::normalize(offset);

                return
                    clampedPoint +
                    outNormal * b;
            }

            // We are on the flat portion of a face.
            // Pick the closest face normal.
            float dx =
                halfSize.x - std::abs(p.x);

            float dy =
                halfSize.y - std::abs(p.y);

            float dz =
                halfSize.z - std::abs(p.z);

            if (dx <= dy && dx <= dz)
            {
                outNormal =
                    glm::vec3(
                        p.x >= 0.0f ? 1.0f : -1.0f,
                        0.0f,
                        0.0f
                    );
            }
            else if (dy <= dx && dy <= dz)
            {
                outNormal =
                    glm::vec3(
                        0.0f,
                        p.y >= 0.0f ? 1.0f : -1.0f,
                        0.0f
                    );
            }
            else
            {
                outNormal =
                    glm::vec3(
                        0.0f,
                        0.0f,
                        p.z >= 0.0f ? 1.0f : -1.0f
                    );
            }

            return clampedPoint;
        }

        // ----------------------------------------------------
        // Add one rounded face grid.
        // ----------------------------------------------------
        void AddFace(
            std::vector<RoundedVertex>& vertices,
            std::vector<unsigned int>& indices,
            int face,
            int segments)
        {
            const int start =
                static_cast<int>(vertices.size());

            const int rowCount =
                segments + 1;

            for (int y = 0; y <= segments; ++y)
            {
                float v =
                    static_cast<float>(y) /
                    static_cast<float>(segments);

                float fy =
                    -0.5f + v;

                for (int x = 0; x <= segments; ++x)
                {
                    float u =
                        static_cast<float>(x) /
                        static_cast<float>(segments);

                    float fx =
                        -0.5f + u;

                    glm::vec3 p;

                    switch (face)
                    {
                        // +X
                    case 0:
                        p = glm::vec3(
                            0.5f,
                            fy,
                            fx
                        );
                        break;

                        // -X
                    case 1:
                        p = glm::vec3(
                            -0.5f,
                            fy,
                            -fx
                        );
                        break;

                        // +Y
                    case 2:
                        p = glm::vec3(
                            fx,
                            0.5f,
                            -fy
                        );
                        break;

                        // -Y
                    case 3:
                        p = glm::vec3(
                            fx,
                            -0.5f,
                            fy
                        );
                        break;

                        // +Z
                    case 4:
                        p = glm::vec3(
                            fx,
                            fy,
                            0.5f
                        );
                        break;

                        // -Z
                    default:
                        p = glm::vec3(
                            -fx,
                            fy,
                            -0.5f
                        );
                        break;
                    }

                    glm::vec3 normal;

                    glm::vec3 rounded =
                        RoundPoint(p, normal);

                    RoundedVertex vertex;

                    vertex.position = rounded;
                    vertex.normal = normal;
                    vertex.texCoord =
                        glm::vec2(u, v);

                    vertices.push_back(vertex);
                }
            }

            // ------------------------------------------------
            // Build triangles.
            // ------------------------------------------------
            for (int y = 0; y < segments; ++y)
            {
                for (int x = 0; x < segments; ++x)
                {
                    unsigned int i0 =
                        start +
                        y * rowCount +
                        x;

                    unsigned int i1 =
                        start +
                        y * rowCount +
                        x + 1;

                    unsigned int i2 =
                        start +
                        (y + 1) * rowCount +
                        x;

                    unsigned int i3 =
                        start +
                        (y + 1) * rowCount +
                        x + 1;

                    // The winding order is adjusted per face.
                    if (face == 0 ||
                        face == 2 ||
                        face == 4)
                    {
                        indices.push_back(i0);
                        indices.push_back(i2);
                        indices.push_back(i1);

                        indices.push_back(i1);
                        indices.push_back(i2);
                        indices.push_back(i3);
                    }
                    else
                    {
                        indices.push_back(i0);
                        indices.push_back(i1);
                        indices.push_back(i2);

                        indices.push_back(i1);
                        indices.push_back(i3);
                        indices.push_back(i2);
                    }
                }
            }
        }

        void Build()
        {
            std::vector<RoundedVertex> vertices;
            std::vector<unsigned int> indices;

            vertices.reserve(
                6 *
                (ROUNDED_SEGMENTS + 1) *
                (ROUNDED_SEGMENTS + 1)
            );

            indices.reserve(
                6 *
                ROUNDED_SEGMENTS *
                ROUNDED_SEGMENTS *
                6
            );

            // Six sides of the rounded box.
            for (int face = 0; face < 6; ++face)
            {
                AddFace(
                    vertices,
                    indices,
                    face,
                    ROUNDED_SEGMENTS
                );
            }

            indexCount =
                static_cast<GLsizei>(indices.size());

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(
                GL_ARRAY_BUFFER,
                VBO
            );

            glBufferData(
                GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(
                    vertices.size() *
                    sizeof(RoundedVertex)
                    ),
                vertices.data(),
                GL_STATIC_DRAW
            );

            glBindBuffer(
                GL_ELEMENT_ARRAY_BUFFER,
                EBO
            );

            glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(
                    indices.size() *
                    sizeof(unsigned int)
                    ),
                indices.data(),
                GL_STATIC_DRAW
            );

            // Position
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(RoundedVertex),
                reinterpret_cast<void*>(0)
            );

            // Normal
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(
                1,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(RoundedVertex),
                reinterpret_cast<void*>(
                    offsetof(RoundedVertex, normal)
                    )
            );

            // Texture coordinates
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(
                2,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(RoundedVertex),
                reinterpret_cast<void*>(
                    offsetof(RoundedVertex, texCoord)
                    )
            );

            glBindVertexArray(0);
        }
    };

    // --------------------------------------------------------
    // Create the rounded mesh only once.
    //
    // We intentionally keep this object alive for the lifetime
    // of the OpenGL application so that its OpenGL resources
    // remain valid while the context is active.
    // --------------------------------------------------------
    RoundedBoxMesh& GetRoundedBox()
    {
        static RoundedBoxMesh* roundedBox =
            new RoundedBoxMesh();

        return *roundedBox;
    }

    // --------------------------------------------------------
    // Draw rounded box helper.
    // --------------------------------------------------------
    void DrawRoundedBox(
        Shader& shader,
        const glm::mat4& model)
    {
        // The rounded cushion is a closed mesh, but some of the
        // generated bevel triangles can have reversed winding.
        // Temporarily disable back-face culling while drawing it.
        GLboolean cullEnabled = GL_FALSE;

        glGetBooleanv(
            GL_CULL_FACE,
            &cullEnabled
        );

        glDisable(GL_CULL_FACE);

        shader.setMat4(
            "model",
            model
        );

        GetRoundedBox().Draw();

        // Restore the renderer's previous culling state.
        if (cullEnabled)
            glEnable(GL_CULL_FACE);
    }
}


// ============================================================
// CHAIR
// ============================================================

Chair::Chair()
    : seatHeightOffset(0.0f),
    armrestFlipAngle(0.0f),
    armrestWidthOffset(0.0f),
    wheelsLocked(true),
    transferHandles(true),
    wheelchairMode(false)
{
}


// ============================================================
// SETTINGS
// ============================================================

void Chair::SetSeatHeightOffset(float offset)
{
    // Clamp to realistic pneumatic lift adjustment range
    // [-0.05m to +0.12m]
    if (offset < -0.05f)
        offset = -0.05f;

    if (offset > 0.12f)
        offset = 0.12f;

    seatHeightOffset = offset;
}


void Chair::SetArmrestFlipAngle(float degrees)
{
    // 0 = standard horizontal down
    // 90 = flipped up for lateral wheelchair transfer

    if (degrees < 0.0f)
        degrees = 0.0f;

    if (degrees > 90.0f)
        degrees = 90.0f;

    armrestFlipAngle = degrees;
}


void Chair::SetArmrestWidthOffset(float offset)
{
    // Width expansion range
    // [0.0m to 0.08m]

    if (offset < 0.0f)
        offset = 0.0f;

    if (offset > 0.08f)
        offset = 0.08f;

    armrestWidthOffset = offset;
}


void Chair::SetWheelsLocked(bool locked)
{
    wheelsLocked = locked;
}


void Chair::SetTransferHandles(bool enabled)
{
    transferHandles = enabled;
}


void Chair::SetWheelchairAccessibleMode(bool enabled)
{
    wheelchairMode = enabled;

    if (enabled)
    {
        // Preset optimal wheelchair lateral transfer
        // configuration.

        // Armrests flipped 90 degrees.
        armrestFlipAngle = 90.0f;

        // Armrests widened.
        armrestWidthOffset = 0.035f;

        // Seat elevated.
        seatHeightOffset = 0.05f;

        // Casters locked.
        wheelsLocked = true;
    }
    else
    {
        // Standard seating configuration.
        armrestFlipAngle = 0.0f;
        armrestWidthOffset = 0.0f;
        seatHeightOffset = 0.0f;
        wheelsLocked = false;
    }
}


void Chair::ToggleWheelchairAccessibleMode()
{
    SetWheelchairAccessibleMode(
        !wheelchairMode
    );
}


// ============================================================
// GETTERS
// ============================================================

float Chair::GetSeatHeightOffset() const
{
    return seatHeightOffset;
}


float Chair::GetArmrestFlipAngle() const
{
    return armrestFlipAngle;
}


float Chair::GetArmrestWidthOffset() const
{
    return armrestWidthOffset;
}


bool Chair::AreWheelsLocked() const
{
    return wheelsLocked;
}


bool Chair::HasTransferHandles() const
{
    return transferHandles;
}


bool Chair::IsWheelchairAccessibleMode() const
{
    return wheelchairMode;
}


// ============================================================
// DRAW
// ============================================================

void Chair::Draw(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel) const
{
    Draw(
        shader,
        cube,
        parentModel,
        seatHeightOffset,
        armrestFlipAngle,
        wheelsLocked
    );
}


void Chair::Draw(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    float customHeightOffset,
    float customArmrestFlip,
    bool customWheelsLocked) const
{
    DrawSeat(
        shader,
        cube,
        parentModel,
        customHeightOffset,
        armrestWidthOffset
    );

    DrawBack(
        shader,
        cube,
        parentModel,
        customHeightOffset
    );

    DrawArmrests(
        shader,
        cube,
        parentModel,
        customHeightOffset,
        armrestWidthOffset,
        customArmrestFlip
    );

    DrawCylinder(
        shader,
        cube,
        parentModel,
        customHeightOffset
    );

    DrawBase(
        shader,
        cube,
        parentModel,
        customWheelsLocked
    );

    if (transferHandles)
    {
        DrawTransferHandles(
            shader,
            cube,
            parentModel,
            customHeightOffset
        );
    }
}


// ============================================================
// SEAT
// ============================================================

void Chair::DrawSeat(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    float heightOffset,
    float armrestWidth) const
{
    float yOff = heightOffset;

    // --------------------------------------------------------
    // 1. Under-seat Mechanism & Mounting Base Plate
    // --------------------------------------------------------

    glm::mat4 basePan = parentModel;

    basePan = glm::translate(
        basePan,
        glm::vec3(
            0.0f,
            0.445f + yOff,
            0.0f
        )
    );

    basePan = glm::scale(
        basePan,
        glm::vec3(
            0.58f,
            0.025f,
            0.54f
        )
    );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.14f
    );

    shader.setMat4("model", basePan);
    cube.Draw();


    // --------------------------------------------------------
    // Central tilt mechanism housing
    // --------------------------------------------------------

    glm::mat4 mechBox = parentModel;

    mechBox = glm::translate(
        mechBox,
        glm::vec3(
            0.0f,
            0.415f + yOff,
            -0.02f
        )
    );

    mechBox = glm::scale(
        mechBox,
        glm::vec3(
            0.28f,
            0.055f,
            0.28f
        )
    );

    shader.setVec3(
        "objectColor",
        0.14f,
        0.14f,
        0.16f
    );

    shader.setMat4("model", mechBox);
    cube.Draw();


    // --------------------------------------------------------
    // Tilt tension knob
    // --------------------------------------------------------

    glm::mat4 knob = parentModel;

    knob = glm::translate(
        knob,
        glm::vec3(
            0.0f,
            0.365f + yOff,
            0.06f
        )
    );

    knob = glm::scale(
        knob,
        glm::vec3(
            0.08f,
            0.070f,
            0.08f
        )
    );

    shader.setVec3(
        "objectColor",
        0.10f,
        0.10f,
        0.12f
    );

    shader.setMat4("model", knob);
    cube.Draw();


    // --------------------------------------------------------
    // Height adjustment lever
    // --------------------------------------------------------

    glm::mat4 lever = parentModel;

    lever = glm::translate(
        lever,
        glm::vec3(
            0.22f,
            0.420f + yOff,
            -0.02f
        )
    );

    lever = glm::scale(
        lever,
        glm::vec3(
            0.20f,
            0.016f,
            0.016f
        )
    );

    shader.setVec3(
        "objectColor",
        0.18f,
        0.18f,
        0.20f
    );

    shader.setMat4("model", lever);
    cube.Draw();


    // --------------------------------------------------------
    // Paddle handle
    // --------------------------------------------------------

    glm::mat4 paddle = parentModel;

    paddle = glm::translate(
        paddle,
        glm::vec3(
            0.32f,
            0.420f + yOff,
            -0.02f
        )
    );

    paddle = glm::scale(
        paddle,
        glm::vec3(
            0.065f,
            0.014f,
            0.060f
        )
    );

    shader.setVec3(
        "objectColor",
        0.08f,
        0.08f,
        0.10f
    );

    shader.setMat4("model", paddle);
    cube.Draw();


    // --------------------------------------------------------
    // Armrest width adjustment sleeves
    // --------------------------------------------------------

    for (int s = -1; s <= 1; s += 2)
    {
        float sign =
            static_cast<float>(s);

        glm::mat4 slideSleeve =
            parentModel;

        slideSleeve =
            glm::translate(
                slideSleeve,
                glm::vec3(
                    sign *
                    (0.24f +
                        armrestWidth * 0.5f),
                    0.435f + yOff,
                    -0.04f
                )
            );

        slideSleeve =
            glm::scale(
                slideSleeve,
                glm::vec3(
                    0.12f + armrestWidth,
                    0.028f,
                    0.055f
                )
            );

        shader.setVec3(
            "objectColor",
            0.18f,
            0.18f,
            0.20f
        );

        shader.setMat4(
            "model",
            slideSleeve
        );

        cube.Draw();


        // Clamp screw knob

        glm::mat4 clampKnob =
            parentModel;

        clampKnob =
            glm::translate(
                clampKnob,
                glm::vec3(
                    sign * 0.20f,
                    0.418f + yOff,
                    -0.04f
                )
            );

        clampKnob =
            glm::scale(
                clampKnob,
                glm::vec3(
                    0.035f,
                    0.022f,
                    0.035f
                )
            );

        shader.setVec3(
            "objectColor",
            0.10f,
            0.10f,
            0.12f
        );

        shader.setMat4(
            "model",
            clampKnob
        );

        cube.Draw();
    }


    // ========================================================
    // 2. MAIN SEAT CUSHION
    // ========================================================
    //
    // THIS IS NOW A REAL ROUNDED BOX.
    //
    // Original:
    //     cube.Draw();
    //
    // New:
    //     DrawRoundedBox();
    //
    // The dimensions are intentionally kept identical to your
    // original cushion so that it stays in the same position.
    // ========================================================

    glm::mat4 cushion =
        parentModel;

    cushion =
        glm::translate(
            cushion,
            glm::vec3(
                0.0f,
                0.495f + yOff,
                0.01f
            )
        );

    cushion =
        glm::scale(
            cushion,
            glm::vec3(
                0.68f,
                0.085f,
                0.62f
            )
        );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.58f,
        0.62f
    );

    DrawRoundedBox(
        shader,
        cushion
    );


    // ========================================================
    // Soft rounded top seating layer
    // ========================================================

    glm::mat4 softTop =
        parentModel;

    softTop =
        glm::translate(
            softTop,
            glm::vec3(
                0.0f,
                0.545f + yOff,
                0.01f
            )
        );

    softTop =
        glm::scale(
            softTop,
            glm::vec3(
                0.60f,
                0.032f,
                0.56f
            )
        );

    shader.setVec3(
        "objectColor",
        0.16f,
        0.65f,
        0.69f
    );

    DrawRoundedBox(
        shader,
        softTop
    );


    // ========================================================
    // Waterfall front edge
    // ========================================================

    glm::mat4 frontRoll =
        parentModel;

    frontRoll =
        glm::translate(
            frontRoll,
            glm::vec3(
                0.0f,
                0.490f + yOff,
                0.31f
            )
        );

    frontRoll =
        glm::scale(
            frontRoll,
            glm::vec3(
                0.60f,
                0.075f,
                0.09f
            )
        );

    shader.setVec3(
        "objectColor",
        0.13f,
        0.58f,
        0.62f
    );

    DrawRoundedBox(
        shader,
        frontRoll
    );


    // Front bevel

    glm::mat4 frontBevel =
        parentModel;

    frontBevel =
        glm::translate(
            frontBevel,
            glm::vec3(
                0.0f,
                0.530f + yOff,
                0.27f
            )
        );

    frontBevel =
        glm::scale(
            frontBevel,
            glm::vec3(
                0.56f,
                0.025f,
                0.08f
            )
        );

    shader.setVec3(
        "objectColor",
        0.15f,
        0.63f,
        0.67f
    );

    DrawRoundedBox(
        shader,
        frontBevel
    );


    // --------------------------------------------------------
    // 3. Purple Side Bolsters
    // --------------------------------------------------------

    for (int s = -1; s <= 1; s += 2)
    {
        float sign =
            static_cast<float>(s);

        glm::mat4 bolster =
            parentModel;

        bolster =
            glm::translate(
                bolster,
                glm::vec3(
                    sign * 0.325f,
                    0.520f + yOff,
                    -0.05f
                )
            );

        bolster =
            glm::scale(
                bolster,
                glm::vec3(
                    0.065f,
                    0.075f,
                    0.46f
                )
            );

        shader.setVec3(
            "objectColor",
            0.50f,
            0.16f,
            0.66f
        );

        DrawRoundedBox(
            shader,
            bolster
        );


        glm::mat4 bolsterEdge =
            parentModel;

        bolsterEdge =
            glm::translate(
                bolsterEdge,
                glm::vec3(
                    sign * 0.325f,
                    0.560f + yOff,
                    -0.05f
                )
            );

        bolsterEdge =
            glm::scale(
                bolsterEdge,
                glm::vec3(
                    0.050f,
                    0.020f,
                    0.42f
                )
            );

        shader.setVec3(
            "objectColor",
            0.56f,
            0.20f,
            0.72f
        );

        DrawRoundedBox(
            shader,
            bolsterEdge
        );
    }
}


// ============================================================
// BACKREST
// ============================================================

void Chair::DrawBack(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    float heightOffset) const
{
    float yOff = heightOffset;


    // --------------------------------------------------------
    // 1. Black Spine & Rear Structural Frame
    // --------------------------------------------------------

    glm::mat4 lowerArm =
        parentModel;

    lowerArm =
        glm::translate(
            lowerArm,
            glm::vec3(
                0.0f,
                0.450f + yOff,
                -0.22f
            )
        );

    lowerArm =
        glm::scale(
            lowerArm,
            glm::vec3(
                0.12f,
                0.040f,
                0.20f
            )
        );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.14f
    );

    shader.setMat4("model", lowerArm);
    cube.Draw();


    // Upright curve connector

    glm::mat4 uprightCurve =
        parentModel;

    uprightCurve =
        glm::translate(
            uprightCurve,
            glm::vec3(
                0.0f,
                0.540f + yOff,
                -0.32f
            )
        );

    uprightCurve =
        glm::scale(
            uprightCurve,
            glm::vec3(
                0.10f,
                0.160f,
                0.06f
            )
        );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.14f
    );

    shader.setMat4(
        "model",
        uprightCurve
    );

    cube.Draw();


    // Heavy-duty vertical spine

    glm::mat4 spine =
        parentModel;

    spine =
        glm::translate(
            spine,
            glm::vec3(
                0.0f,
                1.050f + yOff,
                -0.345f
            )
        );

    spine =
        glm::scale(
            spine,
            glm::vec3(
                0.09f,
                0.860f,
                0.045f
            )
        );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.14f
    );

    shader.setMat4(
        "model",
        spine
    );

    cube.Draw();


    // Shoulder cross brace

    glm::mat4 crossBrace =
        parentModel;

    crossBrace =
        glm::translate(
            crossBrace,
            glm::vec3(
                0.0f,
                1.250f + yOff,
                -0.335f
            )
        );

    crossBrace =
        glm::scale(
            crossBrace,
            glm::vec3(
                0.38f,
                0.060f,
                0.035f
            )
        );

    shader.setVec3(
        "objectColor",
        0.14f,
        0.14f,
        0.16f
    );

    shader.setMat4(
        "model",
        crossBrace
    );

    cube.Draw();


    // Accessibility badge

    glm::mat4 accessBadge =
        parentModel;

    accessBadge =
        glm::translate(
            accessBadge,
            glm::vec3(
                0.0f,
                1.350f + yOff,
                -0.370f
            )
        );

    accessBadge =
        glm::scale(
            accessBadge,
            glm::vec3(
                0.075f,
                0.075f,
                0.008f
            )
        );

    shader.setVec3(
        "objectColor",
        0.05f,
        0.40f,
        0.85f
    );

    shader.setMat4(
        "model",
        accessBadge
    );

    cube.Draw();


    glm::mat4 accessGlyph =
        parentModel;

    accessGlyph =
        glm::translate(
            accessGlyph,
            glm::vec3(
                0.0f,
                1.350f + yOff,
                -0.375f
            )
        );

    accessGlyph =
        glm::scale(
            accessGlyph,
            glm::vec3(
                0.046f,
                0.046f,
                0.008f
            )
        );

    shader.setVec3(
        "objectColor",
        0.96f,
        0.96f,
        0.96f
    );

    shader.setMat4(
        "model",
        accessGlyph
    );

    cube.Draw();


    // Neck bracket

    glm::mat4 headNeck =
        parentModel;

    headNeck =
        glm::translate(
            headNeck,
            glm::vec3(
                0.0f,
                1.540f + yOff,
                -0.310f
            )
        );

    headNeck =
        glm::scale(
            headNeck,
            glm::vec3(
                0.07f,
                0.200f,
                0.040f
            )
        );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.14f
    );

    shader.setMat4(
        "model",
        headNeck
    );

    cube.Draw();


    // ========================================================
    // 2. MAIN ROUNDED BACKREST
    // ========================================================
    //
    // This replaces the old sharp Cube backrest.
    //
    // Original dimensions:
    //     0.64 x 0.860 x 0.080
    //
    // The exact same dimensions are retained.
    // ========================================================

    glm::mat4 back =
        parentModel;

    back =
        glm::translate(
            back,
            glm::vec3(
                0.0f,
                1.100f + yOff,
                -0.295f
            )
        );

    back =
        glm::scale(
            back,
            glm::vec3(
                0.64f,
                0.860f,
                0.080f
            )
        );

    shader.setVec3(
        "objectColor",
        0.16f,
        0.62f,
        0.25f
    );

    DrawRoundedBox(
        shader,
        back
    );


    // ========================================================
    // Rounded shoulder contour
    // ========================================================

    glm::mat4 shoulders =
        parentModel;

    shoulders =
        glm::translate(
            shoulders,
            glm::vec3(
                0.0f,
                1.380f + yOff,
                -0.295f
            )
        );

    shoulders =
        glm::scale(
            shoulders,
            glm::vec3(
                0.68f,
                0.260f,
                0.075f
            )
        );

    shader.setVec3(
        "objectColor",
        0.16f,
        0.62f,
        0.25f
    );

    DrawRoundedBox(
        shader,
        shoulders
    );


    // ========================================================
    // Soft front padding
    // ========================================================

    glm::mat4 frontPad =
        parentModel;

    frontPad =
        glm::translate(
            frontPad,
            glm::vec3(
                0.0f,
                1.120f + yOff,
                -0.250f
            )
        );

    frontPad =
        glm::scale(
            frontPad,
            glm::vec3(
                0.56f,
                0.760f,
                0.032f
            )
        );

    shader.setVec3(
        "objectColor",
        0.24f,
        0.72f,
        0.32f
    );

    DrawRoundedBox(
        shader,
        frontPad
    );


    // ========================================================
    // Ergonomic rounded side wings
    // ========================================================

    for (int s = -1; s <= 1; s += 2)
    {
        float sign =
            static_cast<float>(s);

        glm::mat4 wing =
            parentModel;

        wing =
            glm::translate(
                wing,
                glm::vec3(
                    sign * 0.285f,
                    1.120f + yOff,
                    -0.260f
                )
            );

        wing =
            glm::scale(
                wing,
                glm::vec3(
                    0.055f,
                    0.740f,
                    0.045f
                )
            );

        shader.setVec3(
            "objectColor",
            0.18f,
            0.64f,
            0.27f
        );

        DrawRoundedBox(
            shader,
            wing
        );
    }


    // ========================================================
    // 3. Crimson Red Lumbar Support
    // ========================================================

    glm::mat4 lumbar =
        parentModel;

    lumbar =
        glm::translate(
            lumbar,
            glm::vec3(
                0.0f,
                0.690f + yOff,
                -0.225f
            )
        );

    lumbar =
        glm::scale(
            lumbar,
            glm::vec3(
                0.52f,
                0.165f,
                0.055f
            )
        );

    shader.setVec3(
        "objectColor",
        0.85f,
        0.12f,
        0.16f
    );

    DrawRoundedBox(
        shader,
        lumbar
    );


    // Lumbar front

    glm::mat4 lumbarFront =
        parentModel;

    lumbarFront =
        glm::translate(
            lumbarFront,
            glm::vec3(
                0.0f,
                0.690f + yOff,
                -0.195f
            )
        );

    lumbarFront =
        glm::scale(
            lumbarFront,
            glm::vec3(
                0.46f,
                0.135f,
                0.020f
            )
        );

    shader.setVec3(
        "objectColor",
        0.92f,
        0.18f,
        0.22f
    );

    DrawRoundedBox(
        shader,
        lumbarFront
    );


    // Lumbar curved sides

    for (int s = -1; s <= 1; s += 2)
    {
        float sign =
            static_cast<float>(s);

        glm::mat4 lumbarSide =
            parentModel;

        lumbarSide =
            glm::translate(
                lumbarSide,
                glm::vec3(
                    sign * 0.245f,
                    0.690f + yOff,
                    -0.235f
                )
            );

        lumbarSide =
            glm::scale(
                lumbarSide,
                glm::vec3(
                    0.045f,
                    0.145f,
                    0.045f
                )
            );

        shader.setVec3(
            "objectColor",
            0.80f,
            0.10f,
            0.14f
        );

        DrawRoundedBox(
            shader,
            lumbarSide
        );
    }


    // ========================================================
    // 4. Ergonomic Headrest
    // ========================================================

    glm::mat4 headShell =
        parentModel;

    headShell =
        glm::translate(
            headShell,
            glm::vec3(
                0.0f,
                1.660f + yOff,
                -0.275f
            )
        );

    headShell =
        glm::scale(
            headShell,
            glm::vec3(
                0.48f,
                0.185f,
                0.075f
            )
        );

    shader.setVec3(
        "objectColor",
        0.50f,
        0.16f,
        0.66f
    );

    DrawRoundedBox(
        shader,
        headShell
    );


    // Headrest collars

    for (int s = -1; s <= 1; s += 2)
    {
        float sign =
            static_cast<float>(s);

        glm::mat4 headCollar =
            parentModel;

        headCollar =
            glm::translate(
                headCollar,
                glm::vec3(
                    sign * 0.230f,
                    1.660f + yOff,
                    -0.250f
                )
            );

        headCollar =
            glm::scale(
                headCollar,
                glm::vec3(
                    0.042f,
                    0.170f,
                    0.090f
                )
            );

        shader.setVec3(
            "objectColor",
            0.50f,
            0.16f,
            0.66f
        );

        DrawRoundedBox(
            shader,
            headCollar
        );
    }


    // Main blue headrest cushion

    glm::mat4 headBlue =
        parentModel;

    headBlue =
        glm::translate(
            headBlue,
            glm::vec3(
                0.0f,
                1.660f + yOff,
                -0.245f
            )
        );

    headBlue =
        glm::scale(
            headBlue,
            glm::vec3(
                0.42f,
                0.165f,
                0.085f
            )
        );

    shader.setVec3(
        "objectColor",
        0.10f,
        0.28f,
        0.86f
    );

    DrawRoundedBox(
        shader,
        headBlue
    );


    // Soft blue front face

    glm::mat4 headBlueFront =
        parentModel;

    headBlueFront =
        glm::translate(
            headBlueFront,
            glm::vec3(
                0.0f,
                1.660f + yOff,
                -0.200f
            )
        );

    headBlueFront =
        glm::scale(
            headBlueFront,
            glm::vec3(
                0.36f,
                0.135f,
                0.025f
            )
        );

    shader.setVec3(
        "objectColor",
        0.14f,
        0.35f,
        0.94f
    );

    DrawRoundedBox(
        shader,
        headBlueFront
    );
}


// ============================================================
// ARMRESTS
// ============================================================

void Chair::DrawArmrests(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    float heightOffset,
    float armrestWidth,
    float flipAngle) const
{
    float yOff = heightOffset;

    for (int s = -1; s <= 1; s += 2)
    {
        float sign =
            static_cast<float>(s);

        float armX =
            sign *
            (0.365f + armrestWidth);


        // ----------------------------------------------------
        // Horizontal mounting bracket
        // ----------------------------------------------------

        glm::mat4 bracket =
            parentModel;

        bracket =
            glm::translate(
                bracket,
                glm::vec3(
                    sign *
                    (0.280f +
                        armrestWidth * 0.5f),
                    0.440f + yOff,
                    -0.040f
                )
            );

        bracket =
            glm::scale(
                bracket,
                glm::vec3(
                    0.18f + armrestWidth,
                    0.035f,
                    0.065f
                )
            );

        shader.setVec3(
            "objectColor",
            0.14f,
            0.14f,
            0.16f
        );

        shader.setMat4(
            "model",
            bracket
        );

        cube.Draw();


        // ----------------------------------------------------
        // Vertical post
        // ----------------------------------------------------

        glm::mat4 post =
            parentModel;

        post =
            glm::translate(
                post,
                glm::vec3(
                    armX,
                    0.610f + yOff,
                    -0.040f
                )
            );

        post =
            glm::scale(
                post,
                glm::vec3(
                    0.042f,
                    0.300f,
                    0.055f
                )
            );

        shader.setVec3(
            "objectColor",
            0.14f,
            0.14f,
            0.16f
        );

        shader.setMat4(
            "model",
            post
        );

        cube.Draw();


        // ----------------------------------------------------
        // Height collar
        // ----------------------------------------------------

        glm::mat4 collar =
            parentModel;

        collar =
            glm::translate(
                collar,
                glm::vec3(
                    armX,
                    0.670f + yOff,
                    -0.040f
                )
            );

        collar =
            glm::scale(
                collar,
                glm::vec3(
                    0.052f,
                    0.065f,
                    0.065f
                )
            );

        shader.setVec3(
            "objectColor",
            0.20f,
            0.20f,
            0.23f
        );

        shader.setMat4(
            "model",
            collar
        );

        cube.Draw();


        // ----------------------------------------------------
        // Flip hinge
        // ----------------------------------------------------

        glm::mat4 hingeKnuckle =
            parentModel;

        hingeKnuckle =
            glm::translate(
                hingeKnuckle,
                glm::vec3(
                    armX,
                    0.775f + yOff,
                    -0.150f
                )
            );

        hingeKnuckle =
            glm::scale(
                hingeKnuckle,
                glm::vec3(
                    0.050f,
                    0.040f,
                    0.045f
                )
            );

        shader.setVec3(
            "objectColor",
            0.22f,
            0.22f,
            0.25f
        );

        shader.setMat4(
            "model",
            hingeKnuckle
        );

        cube.Draw();


        // Release button

        glm::mat4 releaseBtn =
            parentModel;

        releaseBtn =
            glm::translate(
                releaseBtn,
                glm::vec3(
                    sign *
                    (0.395f +
                        armrestWidth),
                    0.775f + yOff,
                    -0.150f
                )
            );

        releaseBtn =
            glm::scale(
                releaseBtn,
                glm::vec3(
                    0.015f,
                    0.022f,
                    0.022f
                )
            );

        shader.setVec3(
            "objectColor",
            0.95f,
            0.65f,
            0.10f
        );

        shader.setMat4(
            "model",
            releaseBtn
        );

        cube.Draw();


        // ====================================================
        // Flip-up arm pad
        // ====================================================

        glm::mat4 padBase =
            parentModel;

        padBase =
            glm::translate(
                padBase,
                glm::vec3(
                    armX,
                    0.775f + yOff,
                    -0.150f
                )
            );

        padBase =
            glm::rotate(
                padBase,
                glm::radians(-flipAngle),
                glm::vec3(
                    1.0f,
                    0.0f,
                    0.0f
                )
            );

        padBase =
            glm::translate(
                padBase,
                glm::vec3(
                    0.0f,
                    0.030f,
                    0.170f
                )
            );


        // Main arm pad - rounded

        glm::mat4 pad =
            padBase;

        pad =
            glm::scale(
                pad,
                glm::vec3(
                    0.092f,
                    0.038f,
                    0.500f
                )
            );

        shader.setVec3(
            "objectColor",
            0.50f,
            0.16f,
            0.66f
        );

        DrawRoundedBox(
            shader,
            pad
        );


        // Soft top

        glm::mat4 padTop =
            padBase;

        padTop =
            glm::translate(
                padTop,
                glm::vec3(
                    0.0f,
                    0.021f,
                    0.0f
                )
            );

        padTop =
            glm::scale(
                padTop,
                glm::vec3(
                    0.080f,
                    0.016f,
                    0.460f
                )
            );

        shader.setVec3(
            "objectColor",
            0.56f,
            0.20f,
            0.72f
        );

        DrawRoundedBox(
            shader,
            padTop
        );


        // Front rounded tip

        glm::mat4 frontTip =
            padBase;

        frontTip =
            glm::translate(
                frontTip,
                glm::vec3(
                    0.0f,
                    0.0f,
                    0.240f
                )
            );

        frontTip =
            glm::scale(
                frontTip,
                glm::vec3(
                    0.080f,
                    0.030f,
                    0.040f
                )
            );

        shader.setVec3(
            "objectColor",
            0.48f,
            0.15f,
            0.64f
        );

        DrawRoundedBox(
            shader,
            frontTip
        );


        // Rear rounded tip

        glm::mat4 rearTip =
            padBase;

        rearTip =
            glm::translate(
                rearTip,
                glm::vec3(
                    0.0f,
                    0.0f,
                    -0.240f
                )
            );

        rearTip =
            glm::scale(
                rearTip,
                glm::vec3(
                    0.080f,
                    0.030f,
                    0.040f
                )
            );

        shader.setVec3(
            "objectColor",
            0.48f,
            0.15f,
            0.64f
        );

        DrawRoundedBox(
            shader,
            rearTip
        );
    }
}


// ============================================================
// CYLINDER / HEIGHT MECHANISM
// ============================================================

void Chair::DrawCylinder(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    float heightOffset) const
{
    float yOff = heightOffset;


    glm::mat4 baseCollar =
        parentModel;

    baseCollar =
        glm::translate(
            baseCollar,
            glm::vec3(
                0.0f,
                0.085f,
                0.0f
            )
        );

    baseCollar =
        glm::scale(
            baseCollar,
            glm::vec3(
                0.090f,
                0.040f,
                0.090f
            )
        );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.14f
    );

    shader.setMat4(
        "model",
        baseCollar
    );

    cube.Draw();


    glm::mat4 sleeve =
        parentModel;

    sleeve =
        glm::translate(
            sleeve,
            glm::vec3(
                0.0f,
                0.200f,
                0.0f
            )
        );

    sleeve =
        glm::scale(
            sleeve,
            glm::vec3(
                0.075f,
                0.200f,
                0.075f
            )
        );

    shader.setVec3(
        "objectColor",
        0.14f,
        0.14f,
        0.16f
    );

    shader.setMat4(
        "model",
        sleeve
    );

    cube.Draw();


    glm::mat4 ring =
        parentModel;

    ring =
        glm::translate(
            ring,
            glm::vec3(
                0.0f,
                0.285f,
                0.0f
            )
        );

    ring =
        glm::scale(
            ring,
            glm::vec3(
                0.082f,
                0.030f,
                0.082f
            )
        );

    shader.setVec3(
        "objectColor",
        0.20f,
        0.20f,
        0.22f
    );

    shader.setMat4(
        "model",
        ring
    );

    cube.Draw();


    glm::mat4 piston =
        parentModel;

    piston =
        glm::translate(
            piston,
            glm::vec3(
                0.0f,
                0.350f +
                yOff * 0.5f,
                0.0f
            )
        );

    piston =
        glm::scale(
            piston,
            glm::vec3(
                0.052f,
                0.150f + yOff,
                0.052f
            )
        );

    shader.setVec3(
        "objectColor",
        0.70f,
        0.70f,
        0.73f
    );

    shader.setMat4(
        "model",
        piston
    );

    cube.Draw();


    glm::mat4 topMount =
        parentModel;

    topMount =
        glm::translate(
            topMount,
            glm::vec3(
                0.0f,
                0.415f + yOff,
                0.0f
            )
        );

    topMount =
        glm::scale(
            topMount,
            glm::vec3(
                0.100f,
                0.030f,
                0.100f
            )
        );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.14f
    );

    shader.setMat4(
        "model",
        topMount
    );

    cube.Draw();
}


// ============================================================
// BASE
// ============================================================

void Chair::DrawBase(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    bool locked) const
{
    // Central hub

    glm::mat4 hub =
        parentModel;

    hub =
        glm::translate(
            hub,
            glm::vec3(
                0.0f,
                0.065f,
                0.0f
            )
        );

    hub =
        glm::scale(
            hub,
            glm::vec3(
                0.140f,
                0.065f,
                0.140f
            )
        );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.14f
    );

    shader.setMat4(
        "model",
        hub
    );

    cube.Draw();


    glm::mat4 hubTop =
        parentModel;

    hubTop =
        glm::translate(
            hubTop,
            glm::vec3(
                0.0f,
                0.095f,
                0.0f
            )
        );

    hubTop =
        glm::scale(
            hubTop,
            glm::vec3(
                0.110f,
                0.015f,
                0.110f
            )
        );

    shader.setVec3(
        "objectColor",
        0.16f,
        0.16f,
        0.18f
    );

    shader.setMat4(
        "model",
        hubTop
    );

    cube.Draw();


    // --------------------------------------------------------
    // Five legs
    // --------------------------------------------------------

    const float legRadius =
        0.36f;

    for (int i = 0; i < 5; ++i)
    {
        float angle =
            glm::radians(
                static_cast<float>(i) *
                72.0f
            );

        glm::mat4 armBase =
            parentModel;

        armBase =
            glm::rotate(
                armBase,
                angle,
                glm::vec3(
                    0.0f,
                    1.0f,
                    0.0f
                )
            );


        glm::mat4 armInner =
            armBase;

        armInner =
            glm::translate(
                armInner,
                glm::vec3(
                    0.120f,
                    0.058f,
                    0.0f
                )
            );

        armInner =
            glm::scale(
                armInner,
                glm::vec3(
                    0.160f,
                    0.038f,
                    0.052f
                )
            );

        shader.setVec3(
            "objectColor",
            0.12f,
            0.12f,
            0.14f
        );

        shader.setMat4(
            "model",
            armInner
        );

        cube.Draw();


        glm::mat4 armOuter =
            armBase;

        armOuter =
            glm::translate(
                armOuter,
                glm::vec3(
                    0.245f,
                    0.040f,
                    0.0f
                )
            );

        armOuter =
            glm::scale(
                armOuter,
                glm::vec3(
                    0.170f,
                    0.030f,
                    0.044f
                )
            );

        shader.setVec3(
            "objectColor",
            0.12f,
            0.12f,
            0.14f
        );

        shader.setMat4(
            "model",
            armOuter
        );

        cube.Draw();


        glm::mat4 armRib =
            armBase;

        armRib =
            glm::translate(
                armRib,
                glm::vec3(
                    0.170f,
                    0.068f,
                    0.0f
                )
            );

        armRib =
            glm::scale(
                armRib,
                glm::vec3(
                    0.240f,
                    0.012f,
                    0.026f
                )
            );

        shader.setVec3(
            "objectColor",
            0.18f,
            0.18f,
            0.20f
        );

        shader.setMat4(
            "model",
            armRib
        );

        cube.Draw();


        glm::mat4 armSocket =
            armBase;

        armSocket =
            glm::translate(
                armSocket,
                glm::vec3(
                    legRadius,
                    0.042f,
                    0.0f
                )
            );

        armSocket =
            glm::scale(
                armSocket,
                glm::vec3(
                    0.058f,
                    0.052f,
                    0.058f
                )
            );

        shader.setVec3(
            "objectColor",
            0.10f,
            0.10f,
            0.12f
        );

        shader.setMat4(
            "model",
            armSocket
        );

        cube.Draw();


        // Wheel

        DrawWheel(
            shader,
            cube,
            parentModel,
            std::cos(angle) *
            legRadius,
            std::sin(angle) *
            legRadius,
            locked
        );
    }
}


// ============================================================
// WHEEL
// ============================================================

void Chair::DrawWheel(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    float x,
    float z,
    bool locked) const
{
    // Stem

    glm::mat4 stem =
        parentModel;

    stem =
        glm::translate(
            stem,
            glm::vec3(
                x,
                0.050f,
                z
            )
        );

    stem =
        glm::scale(
            stem,
            glm::vec3(
                0.032f,
                0.035f,
                0.032f
            )
        );

    shader.setVec3(
        "objectColor",
        0.18f,
        0.18f,
        0.20f
    );

    shader.setMat4(
        "model",
        stem
    );

    cube.Draw();


    // Hood

    glm::mat4 hood =
        parentModel;

    hood =
        glm::translate(
            hood,
            glm::vec3(
                x,
                0.038f,
                z
            )
        );

    hood =
        glm::scale(
            hood,
            glm::vec3(
                0.065f,
                0.032f,
                0.065f
            )
        );

    shader.setVec3(
        "objectColor",
        0.10f,
        0.10f,
        0.12f
    );

    shader.setMat4(
        "model",
        hood
    );

    cube.Draw();


    // Axle

    glm::mat4 axle =
        parentModel;

    axle =
        glm::translate(
            axle,
            glm::vec3(
                x,
                0.024f,
                z
            )
        );

    axle =
        glm::scale(
            axle,
            glm::vec3(
                0.056f,
                0.012f,
                0.012f
            )
        );

    shader.setVec3(
        "objectColor",
        0.25f,
        0.25f,
        0.28f
    );

    shader.setMat4(
        "model",
        axle
    );

    cube.Draw();


    // Brake

    glm::mat4 brakeTab =
        parentModel;

    if (locked)
    {
        brakeTab =
            glm::translate(
                brakeTab,
                glm::vec3(
                    x,
                    0.032f,
                    z - 0.035f
                )
            );

        brakeTab =
            glm::scale(
                brakeTab,
                glm::vec3(
                    0.040f,
                    0.014f,
                    0.032f
                )
            );

        shader.setVec3(
            "objectColor",
            0.88f,
            0.14f,
            0.14f
        );

        shader.setMat4(
            "model",
            brakeTab
        );

        cube.Draw();


        glm::mat4 brakeShoe =
            parentModel;

        brakeShoe =
            glm::translate(
                brakeShoe,
                glm::vec3(
                    x,
                    0.022f,
                    z - 0.022f
                )
            );

        brakeShoe =
            glm::scale(
                brakeShoe,
                glm::vec3(
                    0.044f,
                    0.016f,
                    0.014f
                )
            );

        shader.setVec3(
            "objectColor",
            0.20f,
            0.20f,
            0.22f
        );

        shader.setMat4(
            "model",
            brakeShoe
        );

        cube.Draw();
    }
    else
    {
        brakeTab =
            glm::translate(
                brakeTab,
                glm::vec3(
                    x,
                    0.050f,
                    z - 0.038f
                )
            );

        brakeTab =
            glm::scale(
                brakeTab,
                glm::vec3(
                    0.040f,
                    0.014f,
                    0.030f
                )
            );

        shader.setVec3(
            "objectColor",
            0.35f,
            0.35f,
            0.38f
        );

        shader.setMat4(
            "model",
            brakeTab
        );

        cube.Draw();
    }


    // Twin wheels

    for (int side = -1;
        side <= 1;
        side += 2)
    {
        float wheelSide =
            static_cast<float>(side);

        glm::mat4 wheel =
            parentModel;

        wheel =
            glm::translate(
                wheel,
                glm::vec3(
                    x +
                    wheelSide *
                    0.022f,
                    0.024f,
                    z
                )
            );

        wheel =
            glm::scale(
                wheel,
                glm::vec3(
                    0.018f,
                    0.048f,
                    0.048f
                )
            );

        shader.setVec3(
            "objectColor",
            0.04f,
            0.04f,
            0.05f
        );

        shader.setMat4(
            "model",
            wheel
        );

        cube.Draw();


        glm::mat4 cap =
            parentModel;

        cap =
            glm::translate(
                cap,
                glm::vec3(
                    x +
                    wheelSide *
                    0.031f,
                    0.024f,
                    z
                )
            );

        cap =
            glm::scale(
                cap,
                glm::vec3(
                    0.006f,
                    0.022f,
                    0.022f
                )
            );

        shader.setVec3(
            "objectColor",
            0.12f,
            0.12f,
            0.14f
        );

        shader.setMat4(
            "model",
            cap
        );

        cube.Draw();
    }
}


// ============================================================
// TRANSFER HANDLES
// ============================================================

void Chair::DrawTransferHandles(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel,
    float heightOffset) const
{
    float yOff =
        heightOffset;

    for (int s = -1;
        s <= 1;
        s += 2)
    {
        float sign =
            static_cast<float>(s);


        // Mounting bracket

        glm::mat4 mount =
            parentModel;

        mount =
            glm::translate(
                mount,
                glm::vec3(
                    sign * 0.14f,
                    0.600f + yOff,
                    -0.320f
                )
            );

        mount =
            glm::scale(
                mount,
                glm::vec3(
                    0.045f,
                    0.040f,
                    0.075f
                )
            );

        shader.setVec3(
            "objectColor",
            0.12f,
            0.12f,
            0.14f
        );

        shader.setMat4(
            "model",
            mount
        );

        cube.Draw();


        // Side tube

        glm::mat4 outTube =
            parentModel;

        outTube =
            glm::translate(
                outTube,
                glm::vec3(
                    sign * 0.240f,
                    0.600f + yOff,
                    -0.280f
                )
            );

        outTube =
            glm::scale(
                outTube,
                glm::vec3(
                    0.160f,
                    0.030f,
                    0.035f
                )
            );

        shader.setVec3(
            "objectColor",
            0.16f,
            0.16f,
            0.18f
        );

        shader.setMat4(
            "model",
            outTube
        );

        cube.Draw();


        // Forward rail

        glm::mat4 fwdRail =
            parentModel;

        fwdRail =
            glm::translate(
                fwdRail,
                glm::vec3(
                    sign * 0.310f,
                    0.600f + yOff,
                    -0.190f
                )
            );

        fwdRail =
            glm::scale(
                fwdRail,
                glm::vec3(
                    0.030f,
                    0.030f,
                    0.150f
                )
            );

        shader.setVec3(
            "objectColor",
            0.16f,
            0.16f,
            0.18f
        );

        shader.setMat4(
            "model",
            fwdRail
        );

        cube.Draw();


        // Vertical grip bar

        glm::mat4 gripBar =
            parentModel;

        gripBar =
            glm::translate(
                gripBar,
                glm::vec3(
                    sign * 0.310f,
                    0.670f + yOff,
                    -0.120f
                )
            );

        gripBar =
            glm::scale(
                gripBar,
                glm::vec3(
                    0.030f,
                    0.140f,
                    0.030f
                )
            );

        shader.setVec3(
            "objectColor",
            0.14f,
            0.14f,
            0.16f
        );

        shader.setMat4(
            "model",
            gripBar
        );

        cube.Draw();


        // Rubber grip sleeve

        glm::mat4 gripSleeve =
            parentModel;

        gripSleeve =
            glm::translate(
                gripSleeve,
                glm::vec3(
                    sign * 0.310f,
                    0.670f + yOff,
                    -0.120f
                )
            );

        gripSleeve =
            glm::scale(
                gripSleeve,
                glm::vec3(
                    0.040f,
                    0.110f,
                    0.040f
                )
            );

        shader.setVec3(
            "objectColor",
            0.24f,
            0.24f,
            0.27f
        );

        shader.setMat4(
            "model",
            gripSleeve
        );

        cube.Draw();


        // Upper return rail

        glm::mat4 upperRail =
            parentModel;

        upperRail =
            glm::translate(
                upperRail,
                glm::vec3(
                    sign * 0.310f,
                    0.740f + yOff,
                    -0.190f
                )
            );

        upperRail =
            glm::scale(
                upperRail,
                glm::vec3(
                    0.030f,
                    0.030f,
                    0.150f
                )
            );

        shader.setVec3(
            "objectColor",
            0.16f,
            0.16f,
            0.18f
        );

        shader.setMat4(
            "model",
            upperRail
        );

        cube.Draw();
    }
}
