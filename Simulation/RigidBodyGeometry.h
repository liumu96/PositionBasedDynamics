#pragma once

#include "Common/Common.h"
#include "Utils/IndexedFaceMesh.h"
#include "Simulation/ParticleData.h"

namespace PBD
{
    class RigidBodyGeometry
    {
    public:
        typedef Utilities::IndexedFaceMesh Mesh;

    protected:
        Mesh m_mesh;
        VertexData m_vertexData_local;
        VertexData m_vertexData;

    public:
        Mesh &getMesh();
        VertexData &getVertexData();
        const VertexData &getVertexData() const;
    };
}