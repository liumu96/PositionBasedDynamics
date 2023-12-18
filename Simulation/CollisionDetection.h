#pragma once

#include "Common/Common.h"

#include "AABB.h"
#include "ParameterObject.h"

namespace PBD
{
    class CollisionDetection : public GenParam::ParameterObject
    {
    public:
        static int CONTACT_TOLERANCE;

        static const unsigned int RigidBodyContactType;         // = 0;
        static const unsigned int ParticleContactType;          // = 1;
        static const unsigned int ParticleRigidBodyContactType; // = 2;
        static const unsigned int ParticleSolidContactType;     // = 3;

        typedef void (*ContactCallbackFunction)(const unsigned int contactType, const unsigned int bodyIndex1, const unsigned int bodyIndex2,
                                                const Vector3r &cp1, const Vector3r &cp2,
                                                const Vector3r &normal, const Real dist,
                                                const Real restitutionCoeff, const Real frictionCoeff, void *userData);

        typedef void (*SolidContactCallbackFunction)(const unsigned int contactType, const unsigned int bodyIndex1, const unsigned int bodyIndex2,
                                                     const unsigned int tetIndex, const Vector3r &bary,
                                                     const Vector3r &cp1, const Vector3r &cp2,
                                                     const Vector3r &normal, const Real dist,
                                                     const Real restitutionCoeff, const Real frictionCoeff, void *userData);

        struct CollisionObject
        {
            static const unsigned int RigidBodyCollisionObjectType;     // = 0;
            static const unsigned int TriangleModelCollisionObjectType; // = 1;
            static const unsigned int TetModelCollisionObjectType;      // = 2;

            AABB m_aabb;
            unsigned int m_bodyIndex;
            unsigned int m_bodyType;

            virtual ~CollisionObject() {}
            virtual int &getTypeId() const = 0;
        };

        struct CollisionObjectWithoutGeometry : public CollisionObject
        {
            static int TYPE_ID;
            virtual int &getTypeId() const { return TYPE_ID; }
            virtual ~CollisionObjectWithoutGeometry() {}
        };

    protected:
        Real m_tolerance;
        ContactCallbackFunction m_contactCB;
        SolidContactCallbackFunction m_solidContactCB;
        void *m_contactCBUserData;
        void *m_solidContactCBUserData;

        std::vector<CollisionObject *> m_collisionObjects;

        virtual void initParameters();

    public:
        CollisionDetection();
        virtual ~CollisionDetection();

        void setContactCallback(CollisionDetection::ContactCallbackFunction val, void *userData);
        void setSolidContactCallback(CollisionDetection::SolidContactCallbackFunction val, void *userData);

        void cleanup();
    };
}