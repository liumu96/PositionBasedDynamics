#pragma once

#include "Common/Common.h"

namespace PBD
{
    class PositionBasedFluids
    {
    public:
        static bool computePBFDensity(
            const unsigned int particleIndex,     // current fluid particle
            const unsigned int numberOfParticles, // number of fluid particles
            const Vector3r x[],                   // array of all particle positions
            const Real mass[],                    // array of all particle masses
            const Vector3r boundaryX[],           // array of all boundary particles
            const Real boundaryPsi[],             // array of all boundary psi values (Akinci2012)
            const unsigned int numNeighbors,      // number of neighbors
            const unsigned int neighbors[],       // array with indices of all neighbors (indices larger than numberOfParticles are boundary particles)
            const Real density0,                  // rest density
            const bool boundaryHandling,          // perform boundary handling (Akinci2012)
            Real &density_err,                    // returns the clamped density error (can be used for enforcing a maximal global density error)
            Real &density);                       // return the density

        static bool computePBFLagrangeMultiplier(
            const unsigned int particleIndex,     // current fluid particle
            const unsigned int numberOfParticles, // number of fluid particles
            const Vector3r x[],                   // array of all particle positions
            const Real mass[],                    // array of all particle masses
            const Vector3r boundaryX[],           // array of all boundary particles
            const Real boundaryPsi[],             // array of all boundary psi values (Akinci2012)
            const Real density,                   // density of current fluid particle
            const unsigned int numNeighbors,      // number of neighbors
            const unsigned int neighbors[],       // array with indices of all neighbors
            const Real density0,                  // rest density
            const bool boundaryHandling,          // perform boundary handling (Akinci2012)
            Real &lambda);                        // returns the Lagrange multiplier

        static bool solveDensityConstraint(
            const unsigned int particleIndex,     // current fluid particle
            const unsigned int numberOfParticles, // number of fluid particles
            const Vector3r x[],                   // array of all particle positions
            const Real mass[],                    // array of all particle masses
            const Vector3r boundaryX[],           // array of all boundary particles
            const Real boundaryPsi[],             // array of all boundary psi values (Akinci2012)
            const unsigned int numNeighbors,      // number of neighbors
            const unsigned int neighbors[],       // array with indices of all neighbors
            const Real density0,                  // rest density
            const bool boundaryHandling,          // perform boundary handling (Akinci2012)
            const Real lambda[],                  // Lagrange multiplier
            Vector3r &corr);                      // returns the position correction for the current fluid particle
    };
}