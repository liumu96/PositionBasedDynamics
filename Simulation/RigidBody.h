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
        /** center of mass */
        Vector3r m_x;

        /** Quaternion that describes the rotation of the body in world space */
        Quaternionr m_q;

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

        FORCE_INLINE Vector3r &getPosition()
        {
            return m_x;
        }

        FORCE_INLINE const Vector3r &getPosition() const
        {
            return m_x;
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