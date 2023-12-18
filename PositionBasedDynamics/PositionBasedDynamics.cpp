#include "PositionBasedDynamics.h"
#include "MathFunctions.h"
#include <cfloat>

const Real eps = static_cast<Real>(1e-6);

using namespace PBD;

// ----------------------------------------------------------------------------------------------
bool PositionBasedDynamics::init_ParticleTetContactConstraint(
    const Real invMass0,    // inverse mass is zero if particle is static
    const Vector3r &x0,     // particle which collides with tet
    const Vector3r &v0,     // velocity of particle
    const Real invMass[],   // inverse masses of tet particles
    const Vector3r x[],     // positions of tet particles
    const Vector3r v[],     // velocities of tet particles
    const Vector3r &bary,   // barycentric coordinates of contact point in tet
    const Vector3r &normal, // contact normal in body 1
    Eigen::Matrix<Real, 3, 3, Eigen::DontAlign> &constraintInfo)
{
    // constraintInfo contains
    // 0:	contact normal in body 1 (global)
    // 1:	contact tangent (global)
    // 0,1:  1.0 / normal^T * K * normal
    // 1,2: maximal impulse in tangent direction

    const Real bary0 = static_cast<Real>(1.0) - bary[0] - bary[1] - bary[2];

    // compute world space contact point in body 2
    const Vector3r v1 = bary0 * v[0] + bary[0] * v[1] + bary[1] * v[2] + bary[2] * v[3];

    // compute goal velocity in normal direction after collision
    const Vector3r u_rel = v0 - v1;
    const Real u_rel_n = normal.dot(u_rel);

    constraintInfo.col(0) = normal;

    // tangent direction
    Vector3r t = u_rel - u_rel_n * normal;
    Real tl2 = t.squaredNorm();
    if (tl2 > 1.0e-6)
        t *= static_cast<Real>(1.0) / sqrt(tl2);

    constraintInfo.col(1) = t;

    // determine 1/(J M^-1 J^T)
    const Real JMinvJT = invMass0 + bary0 * bary0 * invMass[0] + bary[0] * bary[0] * invMass[1] + bary[1] * bary[1] * invMass[2] + bary[2] * bary[2] * invMass[3];
    constraintInfo(0, 2) = static_cast<Real>(1.0) / JMinvJT;

    // maximal impulse in tangent direction
    constraintInfo(1, 2) = static_cast<Real>(1.0) / JMinvJT * u_rel.dot(t);

    return true;
}
