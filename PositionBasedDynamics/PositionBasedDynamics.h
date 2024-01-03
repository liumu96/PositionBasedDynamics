#pragma once

#include "Common/Common.h"

namespace PBD
{
    class PositionBasedDynamics
    {
    public:
        // -------------- standard PBD -----------------------------------------------------
        static bool solve_DistanceConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Real restLength,
            const Real stiffness,
            Vector3r &corr0, Vector3r &corr1);

        static bool solve_DihedralConstraint(
            const Vector3r &p0, Real invMass0, // angle on (p2, p3) between triangles (p0, p2, p3) and (p1, p3, p2)
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Vector3r &p3, Real invMass3,
            const Real restAngle,
            const Real stiffness,
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);

        static bool solve_VolumeConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Vector3r &p3, Real invMass3,
            const Real restVolume,
            const Real stiffness,
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);

        static bool solve_EdgePointDistanceConstraint(
            const Vector3r &p, Real invMass,
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Real restDist,
            const Real compressionStiffness,
            const Real stretchStiffness,
            Vector3r &corr, Vector3r &corr0, Vector3r &corr1);

        static bool solve_TrianglePointDistanceConstraint(
            const Vector3r &p, Real invMass,
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Real restDist,
            const Real compressionStiffness,
            const Real stretchStiffness,
            Vector3r &corr, Vector3r &corr0, Vector3r &corr1, Vector3r &corr2);

        static bool solve_EdgeEdgeDistanceConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Vector3r &p3, Real invMass3,
            const Real restDist,
            const Real compressionStiffness,
            const Real stretchStiffness,
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);

        // -------------- Isometric bending -----------------------------------------------------
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
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);

        static bool init_ShapeMatchingConstraint(
            const Vector3r x0[], const Real invMasses[], const int numPoints,
            Vector3r &restCm);

        static bool solve_ShapeMatchingConstraint(
            const Vector3r x0[], const Vector3r x[], const Real invMasses[], const int numPoints,
            const Vector3r &restCm,
            const Real stiffness,
            const bool allowStretch, // default false
            Vector3r corr[], Matrix3r *rot = NULL);

        // -------------- Strain Based Dynamics  -----------------------------------------------------
        static bool init_StrainTriangleConstraint(
            const Vector3r &p0,
            const Vector3r &p1,
            const Vector3r &p2,
            Matrix2r &invRestMat);

        static bool solve_StrainTriangleConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Matrix2r &invRestMat,
            const Real xxStiffness,
            const Real yyStiffness,
            const Real xyStiffness,
            const bool normalizeStretch, // use false as default
            const bool normalizeShear,   // use false as default
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2);

        static bool init_StrainTetraConstraint(
            const Vector3r &p0,
            const Vector3r &p1,
            const Vector3r &p2,
            const Vector3r &p3,
            Matrix3r &invRestMat);

        static bool solve_StrainTetraConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Vector3r &p3, Real invMass3,
            const Matrix3r &invRestMat,
            const Vector3r &stretchStiffness, // xx, yy, zz
            const Vector3r &shearStiffness,   // xy, xz, yz
            const bool normalizeStretch,      // use false as default
            const bool normalizeShear,        // use false as default
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);

        // -------------- FEM Based PBD  -----------------------------------------------------
        static void computeGradCGreen(
            Real restVolume,
            const Matrix3r &invRestMat,
            const Matrix3r &sigma,
            Vector3r *J);

        static void computeGreenStrainAndPiolaStress(
            const Vector3r &x1, const Vector3r &x2, const Vector3r &x3, const Vector3r &x4,
            const Matrix3r &invRestMat,
            const Real restVolume,
            const Real mu, const Real lambda,
            Matrix3r &epsilon, Matrix3r &sigma, Real &energy);

        static void computeGreenStrainAndPiolaStressInversion(
            const Vector3r &x1, const Vector3r &x2, const Vector3r &x3, const Vector3r &x4,
            const Matrix3r &invRestMat,
            const Real restVolume,
            const Real mu, const Real lambda,
            Matrix3r &epsilon, Matrix3r &sigma, Real &energy);

    public:
        static bool init_FEMTriangleConstraint(
            const Vector3r &p0,
            const Vector3r &p1,
            const Vector3r &p2,
            Real &area,
            Matrix2r &invRestMat);

        static bool solve_FEMTriangleConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Real &area,
            const Matrix2r &invRestMat,
            const Real youngsModulusX,
            const Real youngsModulusY,
            const Real youngsModulusShear,
            const Real poissonRatioXY,
            const Real poissonRatioYX,
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2);

        static bool init_FEMTetraConstraint(
            const Vector3r &p0,
            const Vector3r &p1,
            const Vector3r &p2,
            const Vector3r &p3,
            Real &volume,
            Matrix3r &invRestMat);

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
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);

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

        static bool solve_ParticleTetContactConstraint(
            const Real invMass0,                                         // inverse mass is zero if particle is static
            const Vector3r &x0,                                          // particle which collides with tet
            const Real invMass[],                                        // inverse masses of tet particles
            const Vector3r x[],                                          // positions of tet particles
            const Vector3r &bary,                                        // barycentric coordinates of contact point in tet
            Eigen::Matrix<Real, 3, 3, Eigen::DontAlign> &constraintInfo, // precomputed contact info
            Real &lambda,
            Vector3r &corr0,
            Vector3r corr[]);

        static bool velocitySolve_ParticleTetContactConstraint(
            const Real invMass0,  // inverse mass is zero if particle is static
            const Vector3r &x0,   // particle which collides with tet
            const Vector3r &v0,   // velocity of particle
            const Real invMass[], // inverse masses of tet particles
            const Vector3r x[],   // positions of tet particles
            const Vector3r v[],   // velocities of tet particles
            const Vector3r &bary, // barycentric coordinates of contact point in tet
            const Real lambda,
            const Real frictionCoeff,                                    // friction coefficient
            Eigen::Matrix<Real, 3, 3, Eigen::DontAlign> &constraintInfo, // precomputed contact info
            Vector3r &corr_v0,
            Vector3r corr_v[]);
    };
}