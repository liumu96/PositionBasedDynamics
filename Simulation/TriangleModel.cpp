#include "TriangleModel.h"

using namespace PBD;

unsigned int TriangleModel::getIndexOffset() const
{
    return m_indexOffset;
}

void TriangleModel::updateMeshNormals(const ParticleData &pd)
{
    m_particleMesh.updateNormals(pd, m_indexOffset);
    m_particleMesh.updateVertexNormals(pd);
}

void TriangleModel::initMesh(const unsigned int nPoints, const unsigned int nFaces, const unsigned int indexOffset, unsigned int *indices, const ParticleMesh::UVIndices &uvIndices, const ParticleMesh::UVs &uvs)
{
    m_indexOffset = indexOffset;
    m_particleMesh.release();

    m_particleMesh.initMesh(nPoints, nFaces * 2, nFaces);

    for (unsigned int i = 0; i < nFaces; i++)
    {
        m_particleMesh.addFace(&indices[3 * i]);
    }
    m_particleMesh.copyUVs(uvIndices, uvs);
    m_particleMesh.buildNeighbors();
}