#pragma once

#include "Common/Common.h"
#include "SimulationModel.h"
#include "CollisionDetection.h"
#include "ParameterObject.h"

namespace PBD
{
    /**
     * Base class for the simulation methods.
     */
    class TimeStep : public GenParam::ParameterObject
    {
    protected:
        CollisionDetection *m_collisionDetection;

        virtual void initParameters();

        static void contactCallbackFunction(const unsigned int contactType,
                                            const unsigned int bodyIndex1, const unsigned int bodyIndex2,
                                            const Vector3r &cp1, const Vector3r &cp2,
                                            const Vector3r &normal, const Real dist,
                                            const Real restitutionCoeff, const Real frictionCoeff, void *userData);

        static void solidContactCallbackFunction(const unsigned int contactType,
                                                 const unsigned int bodyIndex1, const unsigned int bodyIndex2,
                                                 const unsigned int tetIndex, const Vector3r &bary,
                                                 const Vector3r &cp1, const Vector3r &cp2,
                                                 const Vector3r &normal, const Real dist,
                                                 const Real restitutionCoeff, const Real frictionCoeff, void *userData);

    public:
        TimeStep();
        virtual ~TimeStep(void);

        void setCollisionDetection(SimulationModel &model, CollisionDetection *cd);
        CollisionDetection *getCollisionDetection();
    };
}