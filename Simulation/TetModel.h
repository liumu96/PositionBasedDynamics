#pragma once

#include "Common/Common.h"
#include "Utils/IndexedFaceMesh.h"
#include "Utils/IndexedTetMesh.h"
#include "Simulation/ParticleData.h"
#include <vector>

namespace PBD
{
    class TetModel
    {
    public:
        typedef Utilities::IndexedFaceMesh SurfaceMesh;
        typedef Utilities::IndexedTetMesh ParticleMesh;

    protected:
        /** offset which must be added to get the correct index in the particles array */
        unsigned int m_indexOffset;
        /** Tet mesh of particles which represents the simulation model */
        ParticleMesh m_particleMesh;
        SurfaceMesh m_surfaceMesh;
        VertexData m_visVertices;
        SurfaceMesh m_visMesh;

    public:
        SurfaceMesh &getSurfaceMesh();
        VertexData &getVisVertices();
        SurfaceMesh &getVisMesh();
        ParticleMesh &getParticleMesh() { return m_particleMesh; }
        const ParticleMesh &getParticleMesh() const { return m_particleMesh; }

        unsigned int getIndexOffset() const;
    };
}