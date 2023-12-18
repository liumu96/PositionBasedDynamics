#include "PositionBasedRigidBodyDynamics.h"
#include "MathFunctions.h"
#include <cfloat>
#include <iostream>
#define _USE_MATH_DEFINES
#include "math.h"

using namespace PBD;

void PositionBasedRigidBodyDynamics::computeMatrixK(
    const Vector3r &connector,
    const Real invMass,
    const Vector3r &x,
    const Matrix3r &inertiaInverseW,
    Matrix3r &K)
{
    if (invMass != 0.0)
    {
        const Vector3r v = connector - x;
        const Real a = v[0];
        const Real b = v[1];
        const Real c = v[2];

        // J is symmetric
        const Real j11 = inertiaInverseW(0, 0);
        const Real j12 = inertiaInverseW(0, 1);
        const Real j13 = inertiaInverseW(0, 2);
        const Real j22 = inertiaInverseW(1, 1);
        const Real j23 = inertiaInverseW(1, 2);
        const Real j33 = inertiaInverseW(2, 2);

        K(0, 0) = c * c * j22 - b * c * (j23 + j23) + b * b * j33 + invMass;
        K(0, 1) = -(c * c * j12) + a * c * j23 + b * c * j13 - a * b * j33;
        K(0, 2) = b * c * j12 - a * c * j22 - b * b * j13 + a * b * j23;
        K(1, 0) = K(0, 1);
        K(1, 1) = c * c * j11 - a * c * (j13 + j13) + a * a * j33 + invMass;
        K(1, 2) = -(b * c * j11) + a * c * j12 + a * b * j13 - a * a * j23;
        K(2, 0) = K(0, 2);
        K(2, 1) = K(1, 2);
        K(2, 2) = b * b * j11 - a * b * (j12 + j12) + a * a * j22 + invMass;
    }
    else
        K.setZero();
}

// ----------------------------------------------------------------------------------------------
void PositionBasedRigidBodyDynamics::computeMatrixK(
    const Vector3r &connector0,
    const Vector3r &connector1,
    const Real invMass,
    const Vector3r &x,
    const Matrix3r &inertiaInverseW,
    Matrix3r &K)
{
    if (invMass != 0.0)
    {
        const Vector3r v0 = connector0 - x;
        const Real a = v0[0];
        const Real b = v0[1];
        const Real c = v0[2];

        const Vector3r v1 = connector1 - x;
        const Real d = v1[0];
        const Real e = v1[1];
        const Real f = v1[2];

        // J is symmetric
        const Real j11 = inertiaInverseW(0, 0);
        const Real j12 = inertiaInverseW(0, 1);
        const Real j13 = inertiaInverseW(0, 2);
        const Real j22 = inertiaInverseW(1, 1);
        const Real j23 = inertiaInverseW(1, 2);
        const Real j33 = inertiaInverseW(2, 2);

        K(0, 0) = c * f * j22 - c * e * j23 - b * f * j23 + b * e * j33 + invMass;
        K(0, 1) = -(c * f * j12) + c * d * j23 + b * f * j13 - b * d * j33;
        K(0, 2) = c * e * j12 - c * d * j22 - b * e * j13 + b * d * j23;
        K(1, 0) = -(c * f * j12) + c * e * j13 + a * f * j23 - a * e * j33;
        K(1, 1) = c * f * j11 - c * d * j13 - a * f * j13 + a * d * j33 + invMass;
        K(1, 2) = -(c * e * j11) + c * d * j12 + a * e * j13 - a * d * j23;
        K(2, 0) = b * f * j12 - b * e * j13 - a * f * j22 + a * e * j23;
        K(2, 1) = -(b * f * j11) + b * d * j13 + a * f * j12 - a * d * j23;
        K(2, 2) = b * e * j11 - b * d * j12 - a * e * j12 + a * d * j22 + invMass;
    }
    else
        K.setZero();
}

// ----------------------------------------------------------------------------------------------
bool PositionBasedRigidBodyDynamics::init_ParticleRigidBodyContactConstraint(
    const Real invMass0,              // inverse mass is zero if body is static
    const Vector3r &x0,               // center of mass of body 0
    const Vector3r &v0,               // velocity of body 0
    const Real invMass1,              // inverse mass is zero if body is static
    const Vector3r &x1,               // center of mass of body 1
    const Vector3r &v1,               // velocity of body 1
    const Matrix3r &inertiaInverseW1, // inverse inertia tensor (world space) of body 1
    const Quaternionr &q1,            // rotation of body 1
    const Vector3r &omega1,           // angular velocity of body 1
    const Vector3r &cp0,              // contact point of body 0
    const Vector3r &cp1,              // contact point of body 1
    const Vector3r &normal,           // contact normal in body 1
    const Real restitutionCoeff,      // coefficient of restitution
    Eigen::Matrix<Real, 3, 5, Eigen::DontAlign> &constraintInfo)
{
    // constraintInfo contains
    // 0:	contact point in body 0 (global)
    // 1:	contact point in body 1 (global)
    // 2:	contact normal in body 1 (global)
    // 3:	contact tangent (global)
    // 0,4:  1.0 / normal^T * K * normal
    // 1,4: maximal impulse in tangent direction
    // 2,4: goal velocity in normal direction after collision

    // compute goal velocity in normal direction after collision
    const Vector3r r1 = cp1 - x1;

    const Vector3r u1 = v1 + omega1.cross(r1);
    const Vector3r u_rel = v0 - u1;
    const Real u_rel_n = normal.dot(u_rel);

    constraintInfo.col(0) = cp0;
    constraintInfo.col(1) = cp1;
    constraintInfo.col(2) = normal;

    // tangent direction
    Vector3r t = u_rel - u_rel_n * normal;
    Real tl2 = t.squaredNorm();
    if (tl2 > 1.0e-6)
        t *= static_cast<Real>(1.0) / sqrt(tl2);

    constraintInfo.col(3) = t;

    // determine K matrix
    Matrix3r K;
    computeMatrixK(cp1, invMass1, x1, inertiaInverseW1, K);
    if (invMass0 != 0.0)
    {
        K(0, 0) += invMass0;
        K(1, 1) += invMass0;
        K(2, 2) += invMass0;
    }

    constraintInfo(0, 4) = static_cast<Real>(1.0) / (normal.dot(K * normal));

    // maximal impulse in tangent direction
    constraintInfo(1, 4) = static_cast<Real>(1.0) / (t.dot(K * t)) * u_rel.dot(t);

    // goal velocity in normal direction after collision
    constraintInfo(2, 4) = 0.0;
    if (u_rel_n < 0.0)
        constraintInfo(2, 4) = -restitutionCoeff * u_rel_n;

    return true;
}

// ----------------------------------------------------------------------------------------------
bool PositionBasedRigidBodyDynamics::init_RigidBodyContactConstraint(
    const Real invMass0,              // inverse mass is zero if body is static
    const Vector3r &x0,               // center of mass of body 0
    const Vector3r &v0,               // velocity of body 0
    const Matrix3r &inertiaInverseW0, // inverse inertia tensor (world space) of body 0
    const Quaternionr &q0,            // rotation of body 0
    const Vector3r &omega0,           // angular velocity of body 0
    const Real invMass1,              // inverse mass is zero if body is static
    const Vector3r &x1,               // center of mass of body 1
    const Vector3r &v1,               // velocity of body 1
    const Matrix3r &inertiaInverseW1, // inverse inertia tensor (world space) of body 1
    const Quaternionr &q1,            // rotation of body 1
    const Vector3r &omega1,           // angular velocity of body 1
    const Vector3r &cp0,              // contact point of body 0
    const Vector3r &cp1,              // contact point of body 1
    const Vector3r &normal,           // contact normal in body 1
    const Real restitutionCoeff,      // coefficient of restitution
    Eigen::Matrix<Real, 3, 5, Eigen::DontAlign> &constraintInfo)
{
    // constraintInfo contains
    // 0:	contact point in body 0 (global)
    // 1:	contact point in body 1 (global)
    // 2:	contact normal in body 1 (global)
    // 3:	contact tangent (global)
    // 0,4:  1.0 / normal^T * K * normal
    // 1,4: maximal impulse in tangent direction
    // 2,4: goal velocity in normal direction after collision

    // compute goal velocity in normal direction after collision
    const Vector3r r0 = cp0 - x0;
    const Vector3r r1 = cp1 - x1;

    const Vector3r u0 = v0 + omega0.cross(r0);
    const Vector3r u1 = v1 + omega1.cross(r1);
    const Vector3r u_rel = u0 - u1;
    const Real u_rel_n = normal.dot(u_rel);

    constraintInfo.col(0) = cp0;
    constraintInfo.col(1) = cp1;
    constraintInfo.col(2) = normal;

    // tangent direction
    Vector3r t = u_rel - u_rel_n * normal;
    Real tl2 = t.squaredNorm();
    if (tl2 > 1.0e-6)
        t *= static_cast<Real>(1.0) / sqrt(tl2);

    constraintInfo.col(3) = t;

    // determine K matrix
    Matrix3r K1, K2;
    computeMatrixK(cp0, invMass0, x0, inertiaInverseW0, K1);
    computeMatrixK(cp1, invMass1, x1, inertiaInverseW1, K2);
    Matrix3r K = K1 + K2;

    constraintInfo(0, 4) = static_cast<Real>(1.0) / (normal.dot(K * normal));

    // maximal impulse in tangent direction
    constraintInfo(1, 4) = static_cast<Real>(1.0) / (t.dot(K * t)) * u_rel.dot(t);

    // goal velocity in normal direction after collision
    constraintInfo(2, 4) = 0.0;
    if (u_rel_n < 0.0)
        constraintInfo(2, 4) = -restitutionCoeff * u_rel_n;

    return true;
}
