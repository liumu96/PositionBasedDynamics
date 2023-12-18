#include "TetModel.h"

using namespace PBD;
using namespace Utilities;

TetModel::SurfaceMesh &TetModel::getSurfaceMesh()
{
    return m_surfaceMesh;
}

VertexData &TetModel::getVisVertices()
{
    return m_visVertices;
}

TetModel::SurfaceMesh &TetModel::getVisMesh()
{
    return m_visMesh;
}

unsigned int TetModel::getIndexOffset() const
{
    return m_indexOffset;
}
