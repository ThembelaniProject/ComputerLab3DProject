#pragma once

#include "Mesh.h"

class Cube
{
public:
    Cube();

    void Draw() const;

private:
    Mesh mesh;

    static Mesh createCubeMesh();
};