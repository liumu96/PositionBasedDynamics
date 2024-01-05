#pragma once

#include "Common/Common.h"

namespace PBD
{
    class TimeIntegration
    {
        static void semiImplicitEuler(
            const Real h,
            const Real mass,
            Vector3r &position,
            Vector3r &velocity,
            const Vector3r &acceleration);

        static void semiImplicitEulerRotation(
            const Real h,
            const Real mass,
            const Matrix3r &invertiaW,
            const Matrix3r &invInertiaW,
            Quaternionr &rotation,
            Vector3r &angularVelocity,
            const Vector3r &torque);

        static void velocityUpdateFirstOrder(
            const Real h,
            const Real mass,
            const Vector3r &position,    // position after constraint projection	at time t+h
            const Vector3r &oldPosition, // position before constraint projection at time t
            Vector3r &velocity);

        static void angularVelocityUpdateFirstOrder(
            const Real h,
            const Real mass,
            const Quaternionr &rotation,    // rotation after constraint projection	at time t+h
            const Quaternionr &oldRotation, // rotation before constraint projection at time t
            Vector3r &angularVelocity);

        static void velocityUpdateSecondOrder(
            const Real h,
            const Real mass,
            const Vector3r &position,           // position after constraint projection	at time t+h
            const Vector3r &oldPosition,        // position before constraint projection at time t
            const Vector3r &positionOfLastStep, // position of last simulation step at time t-h
            Vector3r &velocity);

        static void angularVelocityUpdateSecondOrder(
            const Real h,
            const Real mass,
            const Quaternionr &rotation,           // rotation after constraint projection	at time t+h
            const Quaternionr &oldRotation,        // rotation before constraint projection at time t
            const Quaternionr &rotationOfLastStep, // rotation of last simulation step at time t-h
            Vector3r &angularVelocity);
    };
}