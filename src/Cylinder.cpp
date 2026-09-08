#include "Cylinder.h"
#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Cylinder::Cylinder(int segments)
    : mesh(createCylinderMesh(segments))
{
}

void Cylinder::Draw() const
{
    mesh.Draw();
}

Mesh Cylinder::createCylinderMesh(int segments)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const float radius = 0.5f;
    const float height = 1.0f;

    // ---------- Side vertices ----------
    for (int i = 0; i <= segments; ++i)
    {
        float angle = (float)i / segments * 2.0f * (float)M_PI;
        float x = cos(angle) * radius;
        float z = sin(angle) * radius;
        float u = (float)i / segments;

        // Bottom
        vertices.push_back({ {x, -0.5f, z}, {x, 0.0f, z}, {u, 0.0f} });
        // Top
        vertices.push_back({ {x,  0.5f, z}, {x, 0.0f, z}, {u, 1.0f} });
    }

    // Side indices
    for (int i = 0; i < segments; ++i)
    {
        int bl = i * 2;
        int br = bl + 2;
        int tl = bl + 1;
        int tr = br + 1;

        indices.push_back(bl);
        indices.push_back(br);
        indices.push_back(tl);

        indices.push_back(tl);
        indices.push_back(br);
        indices.push_back(tr);
    }

    // ---------- Top & Bottom caps ----------
    int baseIndex = (int)vertices.size();

    // Center points
    vertices.push_back({ {0,  0.5f, 0}, {0, 1, 0}, {0.5f, 0.5f} }); // top center
    vertices.push_back({ {0, -0.5f, 0}, {0,-1, 0}, {0.5f, 0.5f} }); // bottom center

    int topCenter = baseIndex;
    int botCenter = baseIndex + 1;

    for (int i = 0; i <= segments; ++i)
    {
        float angle = (float)i / segments * 2.0f * (float)M_PI;
        float x = cos(angle) * radius;
        float z = sin(angle) * radius;
        float u = cos(angle) * 0.5f + 0.5f;
        float v = sin(angle) * 0.5f + 0.5f;

        vertices.push_back({ {x,  0.5f, z}, {0, 1, 0}, {u, v} }); // top ring
        vertices.push_back({ {x, -0.5f, z}, {0,-1, 0}, {u, v} }); // bottom ring
    }

    // Cap indices
    for (int i = 0; i < segments; ++i)
    {
        int t0 = baseIndex + 2 + i * 2;
        int t1 = baseIndex + 2 + (i + 1) * 2;
        int b0 = t0 + 1;
        int b1 = t1 + 1;

        // Top
        indices.push_back(topCenter);
        indices.push_back(t0);
        indices.push_back(t1);

        // Bottom
        indices.push_back(botCenter);
        indices.push_back(b1);
        indices.push_back(b0);
    }

    return Mesh(vertices, indices);
}