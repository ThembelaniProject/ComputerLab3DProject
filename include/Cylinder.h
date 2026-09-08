#pragma once
#include "Mesh.h"
#include "Shader.h"

class Cylinder
{
public:
    Cylinder(int segments = 24);
    void Draw() const;

private:
    Mesh mesh;
    static Mesh createCylinderMesh(int segments);
};