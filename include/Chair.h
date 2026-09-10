#pragma once

#include <glm/glm.hpp>

class Shader;
class Cube;

class Chair
{
public:
    Chair();

    // Standard Draw using internal adjustment settings
    void Draw(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel
    ) const;

    // Overload for drawing with custom wheelchair accessibility adjustments
    void Draw(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& parentModel,
        float customHeightOffset,
        float customArmrestFlip,
        bool customWheelsLocked
    ) const;

    // ------------------------------------------------------------------------
    // Wheelchair Accessibility & Ergonomic Adjusters
    // ------------------------------------------------------------------------
    void SetSeatHeightOffset(float offset);
    void SetArmrestFlipAngle(float degrees);
    void SetArmrestWidthOffset(float offset);
    void SetWheelsLocked(bool locked);
    void SetTransferHandles(bool enabled);
    void SetWheelchairAccessibleMode(bool enabled);
    void ToggleWheelchairAccessibleMode();

    float GetSeatHeightOffset() const;
    float GetArmrestFlipAngle() const;
    float GetArmrestWidthOffset() const;
    bool  AreWheelsLocked() const;
    bool  HasTransferHandles() const;
    bool  IsWheelchairAccessibleMode() const;

private:
    float seatHeightOffset;     // Vertical lift adjustment for level wheelchair transfer
    float armrestFlipAngle;     // 0 = standard down, 90 = flipped up for lateral slide transfer
    float armrestWidthOffset;   // Widens armrests outward for wheelchair clearance
    bool  wheelsLocked;         // Safety wheel lock brakes for transfer stability
    bool  transferHandles;      // Sturdy lateral grab rails for wheelchair transfer
    bool  wheelchairMode;       // Preset toggle flag

    void DrawSeat(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model,
        float heightOffset,
        float armrestWidth) const;

    void DrawBack(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model,
        float heightOffset) const;

    void DrawArmrests(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model,
        float heightOffset,
        float armrestWidth,
        float flipAngle) const;

    void DrawCylinder(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model,
        float heightOffset) const;

    void DrawBase(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model,
        bool locked) const;

    void DrawWheel(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model,
        float x,
        float z,
        bool locked) const;

    void DrawTransferHandles(
        Shader& shader,
        const Cube& cube,
        const glm::mat4& model,
        float heightOffset) const;
};