#pragma once

#include "Common/Common.h"

namespace PBD
{
    class XPBD
    {
        static bool solve_DistanceConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Real restLength,
            const Real stiffness,
            const Real dt,
            Real &lambda,
            Vector3r &corr0, Vector3r &corr1);

        static bool solve_VolumeConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Vector3r &p3, Real invMass3,
            const Real restVolume,
            const Real stiffness,
            const Real dt,
            Real &lambda,
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);

        static bool init_IsometricBendingConstraint(
            const Vector3r &p0,
            const Vector3r &p1,
            const Vector3r &p2,
            const Vector3r &p3,
            Matrix4r &Q);

        static bool solve_IsometricBendingConstraint(
            const Vector3r &p0, Real invMass0, // angle on (p2, p3) between triangles (p0, p2, p3) and (p1, p3, p2)
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Vector3r &p3, Real invMass3,
            const Matrix4r &Q,
            const Real stiffness,
            const Real dt,
            Real &lambda,
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);

        static bool solve_FEMTetraConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Vector3r &p3, Real invMass3,
            const Real restVolume,
            const Matrix3r &invRestMat,
            const Real youngsModulus,
            const Real poissonRatio,
            const bool handleInversion,
            const Real dt,
            Real &lambda,
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);
    };
}