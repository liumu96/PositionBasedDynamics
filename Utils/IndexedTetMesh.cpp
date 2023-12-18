#include "IndexedTetMesh.h"

using namespace Utilities;

IndexedTetMesh::IndexedTetMesh()
{
}

IndexedTetMesh::~IndexedTetMesh()
{
    release();
}

void IndexedTetMesh::release()
{
    m_faceIndices.clear();
    m_tetIndices.clear();
    m_edges.clear();
    m_tets.clear();
    m_faces.clear();
    m_verticesTets.clear();
    m_verticesFaces.clear();
    m_verticesEdges.clear();
}