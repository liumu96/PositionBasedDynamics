#pragma once

#include "Common.h"

namespace PBD
{
    class PositionBasedDynamics
    {
    public:
        // standard PBD

        /**
         * Determin the position corrections for a distance constraint between two particles
         */
        static bool solve_DistanceConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Real restLength,
            const Real stiffness,
            Vector3r &corr0, Vector3r &corr1);

        /**
         * Determine the position corrections for a dihedral bending constraint
         */
        static bool solve_DihedralConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Vector3r &p3, Real invMass3,
            const Real restAngle,
            const Real stiffness,
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);

        /**
         * Determine the position correction for a constraint that conserves the volume
         * of single tetrahedron.
         */
        static bool solve_VolumeConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Vector3r &p3, Real invMass3,
            const Real restVolume,
            const Real stiffness,
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);

        /**
         * Determine the position corrections for a constraint that preserves a
         * rest distance between a point and an edge.
         */
        static bool solve_EdgePointDistanceConstraint(
            const Vector3r &p, Real invMass,
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Real restDist,
            const Real compressionStiffness,
            const Real stretchStiffness,
            Vector3r &corr, Vector3r &corr0, Vector3r &corr1);

        /**
         * Determine the position corrections for a constraint that preserves a
         * rest distance between a point and a triangle.
         */
        static bool solve_TrianglePointDistanceConstraint(
            const Vector3r &p, Real invMass,
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Real restDist,
            const Real compressionStiffness,
            const Real stretchStiffness,
            Vector3r &corr, Vector3r &corr0, Vector3r &corr1, Vector3r &corr2);

        /**
         * Determine the position corrections for a constraint that preserves a
         * rest distance between two edges.
         */
        static bool solve_EdgeEdgeDistanceConstraint(
            const Vector3r &p0, Real invMass0,
            const Vector3r &p1, Real invMass1,
            const Vector3r &p2, Real invMass2,
            const Vector3r &p3, Real invMass3,
            const Real restDist,
            const Real compressionStiffness,
            const Real stretchStiffness,
            Vector3r &corr0, Vector3r &corr1, Vector3r &corr2, Vector3r &corr3);
    };

};