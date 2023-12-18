#pragma once

#include "Common/Common.h"

namespace PBD
{
    class PositionBasedDynamics
    {
    public:
        static bool init_ParticleTetContactConstraint(
            const Real invMass0,    // inverse mass is zero if particle is static
            const Vector3r &x0,     // particle which collides with tet
            const Vector3r &v0,     // velocity of particle
            const Real invMass[],   // inverse masses of tet particles
            const Vector3r x[],     // positions of tet particles
            const Vector3r v[],     // velocities of tet particles
            const Vector3r &bary,   // barycentric coordinates of contact point in tet
            const Vector3r &normal, // contact normal in body 1
            Eigen::Matrix<Real, 3, 3, Eigen::DontAlign> &constraintInfo);
    };
}