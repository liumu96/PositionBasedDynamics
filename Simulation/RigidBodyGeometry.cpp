#include "RigidBodyGeometry.h"

using namespace PBD;

RigidBodyGeometry::Mesh &RigidBodyGeometry::getMesh()
{
    return m_mesh;
}

VertexData &RigidBodyGeometry::getVertexData()
{
    return m_vertexData;
}

const VertexData &RigidBodyGeometry::getVertexData() const
{
    return m_vertexData;
}