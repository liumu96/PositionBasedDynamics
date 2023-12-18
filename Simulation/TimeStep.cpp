#include "TimeStep.h"

using namespace PBD;
using namespace GenParam;

TimeStep::TimeStep()
{
    m_collisionDetection = new CollisionDetection();
}

TimeStep::~TimeStep(void)
{
}

void TimeStep::initParameters()
{
    ParameterObject::initParameters();
}

void TimeStep::setCollisionDetection(SimulationModel &model, CollisionDetection *cd)
{
    m_collisionDetection = cd;
    m_collisionDetection->setContactCallback(contactCallbackFunction, &model);
    m_collisionDetection->setSolidContactCallback(solidContactCallbackFunction, &model);
}

CollisionDetection *TimeStep::getCollisionDetection()
{
    return m_collisionDetection;
}

void TimeStep::contactCallbackFunction(const unsigned int contactType, const unsigned int bodyIndex1, const unsigned int bodyIndex2,
                                       const Vector3r &cp1, const Vector3r &cp2,
                                       const Vector3r &normal, const Real dist,
                                       const Real restitutionCoeff, const Real frictionCoeff, void *userData)
{
    SimulationModel *model = (SimulationModel *)userData;
    if (contactType == CollisionDetection::RigidBodyContactType)
        model->addRigidBodyContactConstraint(bodyIndex1, bodyIndex2, cp1, cp2, normal, dist, restitutionCoeff, frictionCoeff);
    else if (contactType == CollisionDetection::ParticleRigidBodyContactType)
        model->addParticleRigidBodyContactConstraint(bodyIndex1, bodyIndex2, cp1, cp2, normal, dist, restitutionCoeff, frictionCoeff);
}

void TimeStep::solidContactCallbackFunction(const unsigned int contactType, const unsigned int bodyIndex1, const unsigned int bodyIndex2,
                                            const unsigned int tetIndex, const Vector3r &bary,
                                            const Vector3r &cp1, const Vector3r &cp2,
                                            const Vector3r &normal, const Real dist,
                                            const Real restitutionCoeff, const Real frictionCoeff, void *userData)
{
    SimulationModel *model = (SimulationModel *)userData;
    if (contactType == CollisionDetection::ParticleSolidContactType)
        model->addParticleSolidContactConstraint(bodyIndex1, bodyIndex2, tetIndex, bary, cp1, cp2, normal, dist, restitutionCoeff, frictionCoeff);
}