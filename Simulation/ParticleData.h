#pragma once

#include "Common/Common.h"

namespace PBD
{
    /**
     * This class encapsulates the state of all vertices.
     * All parameters are stored in individual arrays.
     */
    class VertexData
    {
    };

    /**
     * This class encapsulates the state of all particles of a particle model.
     * All parameters are stored in individual arrays.
     */

    class ParticleData
    {
    private:
        // Mass
        // If the mass is zero, the particle is static
        std::vector<Real> m_masses;
        std::vector<Real> m_invMasses;

        // Dynamic state
        std::vector<Vector3r> m_x0;
        std::vector<Vector3r> m_x;
        std::vector<Vector3r> m_v;
        std::vector<Vector3r> m_a;
        std::vector<Vector3r> m_oldX;
        std::vector<Vector3r> m_lastX;

    public:
        FORCE_INLINE void addVertex(const Vector3r &vertex)
        {
            m_x0.push_back(vertex);
            m_x.push_back(vertex);
            m_oldX.push_back(vertex);
            m_lastX.push_back(vertex);
            m_masses.push_back(1.0);
            m_invMasses.push_back(1.0);
            m_v.push_back(Vector3r(0.0, 0.0, 0.0));
            m_a.push_back(Vector3r(0.0, 0.0, 0.0));
        }

        FORCE_INLINE Vector3r &getPosition(const unsigned int i)
        {
            return m_x[i];
        }

        FORCE_INLINE const Vector3r &getPosition(const unsigned int i) const
        {
            return m_x[i];
        }

        FORCE_INLINE void setMass(const unsigned int i, const Real mass)
        {
            m_masses[i] = mass;
            if (mass != 0.0)
                m_invMasses[i] = static_cast<Real>(1.0) / mass;
            else
                m_invMasses[i] = 0.0;
        }

        /**
         * Reserve the array containing the particle data.
         */
        FORCE_INLINE void reserve(const unsigned int newSize)
        {
            m_masses.reserve(newSize);
            m_invMasses.reserve(newSize);
            m_x0.reserve(newSize);
            m_x.reserve(newSize);
            m_v.reserve(newSize);
            m_a.reserve(newSize);
            m_oldX.reserve(newSize);
            m_lastX.reserve(newSize);
        }

        /**
         * Release the array containing the particle data.
         */
        FORCE_INLINE unsigned int size() const
        {
            return (unsigned int)m_x.size();
        }
    };
}