#pragma once

#include "Common/Common.h"
#include "RigidBodyGeometry.h"

namespace PBD
{
    /** This class encapsulates the state of a rigid body.
     */
    class RigidBody
    {
    private:
        /** mass */
        Real m_mass;
        /** inverse mass */
        Real m_invMass;
        /** center of mass */
        Vector3r m_x;

        /** center of mass velocity */
        Vector3r m_v;

        /** 3x3 matrix, inverse of the inertia tensor in world space */
        Matrix3r m_inertiaTensorInverseW;

        /** Quaternion that describes the rotation of the body in world space */
        Quaternionr m_q;

        /** Angular velocity, defines rotation axis and velocity (magnitude of the vector) */
        Vector3r m_omega;

        RigidBodyGeometry m_geometry;

        // transformation required to transform a point to local space or vice vera
        Matrix3r m_transformation_R;
        Vector3r m_transformation_v1;
        Vector3r m_transformation_v2;

    public:
        const Matrix3r &getTransformationR() { return m_transformation_R; }
        const Vector3r &getTransformationV1() { return m_transformation_v1; }
        const Vector3r &getTransformationV2() { return m_transformation_v2; }

        FORCE_INLINE Real &getMass()
        {
            return m_mass;
        }

        FORCE_INLINE const Real &getMass() const
        {
            return m_mass;
        }

        FORCE_INLINE const Real &getInvMass() const
        {
            return m_invMass;
        }

        FORCE_INLINE Vector3r &getPosition()
        {
            return m_x;
        }

        FORCE_INLINE const Vector3r &getPosition() const
        {
            return m_x;
        }

        FORCE_INLINE Vector3r &getVelocity()
        {
            return m_v;
        }

        FORCE_INLINE const Vector3r &getVelocity() const
        {
            return m_v;
        }

        FORCE_INLINE Matrix3r &getInertiaTensorInverseW()
        {
            return m_inertiaTensorInverseW;
        }

        FORCE_INLINE const Matrix3r &getInertiaTensorInverseW() const
        {
            return m_inertiaTensorInverseW;
        }

        FORCE_INLINE Vector3r &getAngularVelocity()
        {
            return m_omega;
        }

        FORCE_INLINE const Vector3r &getAngularVelocity() const
        {
            return m_omega;
        }

        FORCE_INLINE Quaternionr &getRotation()
        {
            return m_q;
        }

        FORCE_INLINE const Quaternionr &getRotation() const
        {
            return m_q;
        }

        RigidBodyGeometry &getGeometry()
        {
            return m_geometry;
        }
    };
}