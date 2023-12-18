#pragma once

#include "Common/Common.h"

// ------------------------------------------------------------------------------------
namespace PBD
{
    class PositionBasedRigidBodyDynamics
    {
        // -------------- Position Based Rigid Body Dynamics  -----------------------------------------------------
    private:
        static void computeMatrixK(
            const Vector3r &connector,
            const Real invMass,
            const Vector3r &x,
            const Matrix3r &inertiaInverseW,
            Matrix3r &K);

        static void computeMatrixK(
            const Vector3r &connector0,
            const Vector3r &connector1,
            const Real invMass,
            const Vector3r &x,
            const Matrix3r &inertiaInverseW,
            Matrix3r &K);

    public:
        static bool init_RigidBodyContactConstraint(
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
            Eigen::Matrix<Real, 3, 5, Eigen::DontAlign> &constraintInfo);

        static bool init_ParticleRigidBodyContactConstraint(
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
            Eigen::Matrix<Real, 3, 5, Eigen::DontAlign> &constraintInfo);
    };
}