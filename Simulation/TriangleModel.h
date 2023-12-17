#pragma once

#include "Common/Common.h"

#include "Utils/IndexedFaceMesh.h"
#include "Simulation/ParticleData.h"

namespace PBD
{
    class TriangleModel
    {
    public:
        typedef Utilities::IndexedFaceMesh ParticleMesh;

    protected:
        /** offset which must be added to get the correct index in the particles array */
        unsigned int m_indexOffset;

        /** Face mesh of particles which represents the simulation model */
        ParticleMesh m_particleMesh;

    public:
        ParticleMesh &getParticleMesh() { return m_particleMesh; }
        const ParticleMesh &getParticleMesh() const { return m_particleMesh; }

        unsigned int getIndexOffset() const;

        void initMesh(const unsigned int nPoints, const unsigned int nFaces, const unsigned int indexOffset, unsigned int *indices, const ParticleMesh::UVIndices &uvIndices, const ParticleMesh::UVs &uvs);
        void updateMeshNormals(const ParticleData &pd);
    };
}