#include "Constraints.h"
#include "SimulationModel.h"

#include "PositionBasedDynamics/PositionBasedRigidBodyDynamics.h"

#include "PositionBasedDynamics/PositionBasedDynamics.h"

#include "Simulation/IDFactory.h"

using namespace PBD;

int BallJoint::TYPE_ID = IDFactory::getId();
int BallOnLineJoint::TYPE_ID = IDFactory::getId();
int HingeJoint::TYPE_ID = IDFactory::getId();
int UniversalJoint::TYPE_ID = IDFactory::getId();
int RigidBodyParticleBallJoint::TYPE_ID = IDFactory::getId();
int RigidBodySpring::TYPE_ID = IDFactory::getId();
int DistanceJoint::TYPE_ID = IDFactory::getId();
// int DistanceConstraint::TYPE_ID = IDFactory::getId();
// int DistanceConstraint_XPBD::TYPE_ID = IDFactory::getId();
// int DihedralConstraint::TYPE_ID = IDFactory::getId();
// int IsometricBendingConstraint::TYPE_ID = IDFactory::getId();
// int IsometricBendingConstraint_XPBD::TYPE_ID = IDFactory::getId();
// int FEMTriangleConstraint::TYPE_ID = IDFactory::getId();
// int StrainTriangleConstraint::TYPE_ID = IDFactory::getId();
// int VolumeConstraint::TYPE_ID = IDFactory::getId();
// int VolumeConstraint_XPBD::TYPE_ID = IDFactory::getId();
// int FEMTetConstraint::TYPE_ID = IDFactory::getId();
// int XPBD_FEMTetConstraint::TYPE_ID = IDFactory::getId();
// int StrainTetConstraint::TYPE_ID = IDFactory::getId();
// int ShapeMatchingConstraint::TYPE_ID = IDFactory::getId();
int TargetAngleMotorHingeJoint::TYPE_ID = IDFactory::getId();
int TargetVelocityMotorHingeJoint::TYPE_ID = IDFactory::getId();
int SliderJoint::TYPE_ID = IDFactory::getId();
int TargetPositionMotorSliderJoint::TYPE_ID = IDFactory::getId();
int TargetVelocityMotorSliderJoint::TYPE_ID = IDFactory::getId();
int DamperJoint::TYPE_ID = IDFactory::getId();
int RigidBodyContactConstraint::TYPE_ID = IDFactory::getId();
int ParticleRigidBodyContactConstraint::TYPE_ID = IDFactory::getId();
int ParticleTetContactConstraint::TYPE_ID = IDFactory::getId();
// int StretchShearConstraint::TYPE_ID = IDFactory::getId();
// int BendTwistConstraint::TYPE_ID = IDFactory::getId();
// int StretchBendingTwistingConstraint::TYPE_ID = IDFactory::getId();
// int DirectPositionBasedSolverForStiffRodsConstraint::TYPE_ID = IDFactory::getId();

//////////////////////////////////////////////////////////////////////////
// RigidBodyContactConstraint
//////////////////////////////////////////////////////////////////////////
bool RigidBodyContactConstraint::initConstraint(SimulationModel &model, const unsigned int rbIndex1, const unsigned int rbIndex2,
                                                const Vector3r &cp1, const Vector3r &cp2,
                                                const Vector3r &normal, const Real dist,
                                                const Real restitutionCoeff, const Real stiffness, const Real frictionCoeff)
{
    m_stiffness = stiffness;
    m_frictionCoeff = frictionCoeff;

    m_bodies[0] = rbIndex1;
    m_bodies[1] = rbIndex2;
    SimulationModel::RigidBodyVector &rb = model.getRigidBodies();
    RigidBody &rb1 = *rb[m_bodies[0]];
    RigidBody &rb2 = *rb[m_bodies[1]];

    m_sum_impulses = 0.0;

    return PositionBasedRigidBodyDynamics::init_RigidBodyContactConstraint(
        rb1.getInvMass(),
        rb1.getPosition(),
        rb1.getVelocity(),
        rb1.getInertiaTensorInverseW(),
        rb1.getRotation(),
        rb1.getAngularVelocity(),
        rb2.getInvMass(),
        rb2.getPosition(),
        rb2.getVelocity(),
        rb2.getInertiaTensorInverseW(),
        rb2.getRotation(),
        rb2.getAngularVelocity(),
        cp1, cp2, normal, restitutionCoeff,
        m_constraintInfo);
}

//////////////////////////////////////////////////////////////////////////
// ParticleRigidBodyContactConstraint
//////////////////////////////////////////////////////////////////////////
bool ParticleRigidBodyContactConstraint::initConstraint(SimulationModel &model,
                                                        const unsigned int particleIndex, const unsigned int rbIndex,
                                                        const Vector3r &cp1, const Vector3r &cp2,
                                                        const Vector3r &normal, const Real dist,
                                                        const Real restitutionCoeff, const Real stiffness, const Real frictionCoeff)
{
    m_stiffness = stiffness;
    m_frictionCoeff = frictionCoeff;

    m_bodies[0] = particleIndex;
    m_bodies[1] = rbIndex;
    SimulationModel::RigidBodyVector &rbs = model.getRigidBodies();
    ParticleData &pd = model.getParticles();

    RigidBody &rb = *rbs[m_bodies[1]];

    m_sum_impulses = 0.0;

    return PositionBasedRigidBodyDynamics::init_ParticleRigidBodyContactConstraint(
        pd.getInvMass(particleIndex),
        pd.getPosition(particleIndex),
        pd.getVelocity(particleIndex),
        rb.getInvMass(),
        rb.getPosition(),
        rb.getVelocity(),
        rb.getInertiaTensorInverseW(),
        rb.getRotation(),
        rb.getAngularVelocity(),
        cp1, cp2, normal, restitutionCoeff,
        m_constraintInfo);
}

//////////////////////////////////////////////////////////////////////////
// ParticleSolidContactConstraint
//////////////////////////////////////////////////////////////////////////
bool ParticleTetContactConstraint::initConstraint(SimulationModel &model,
                                                  const unsigned int particleIndex, const unsigned int solidIndex,
                                                  const unsigned int tetIndex, const Vector3r &bary,
                                                  const Vector3r &cp1, const Vector3r &cp2,
                                                  const Vector3r &normal, const Real dist,
                                                  const Real frictionCoeff)
{
    m_frictionCoeff = frictionCoeff;

    m_bodies[0] = particleIndex;
    m_bodies[1] = solidIndex;
    m_tetIndex = tetIndex;
    m_solidIndex = solidIndex;
    m_bary = bary;
    ParticleData &pd = model.getParticles();

    const SimulationModel::TetModelVector &tetModels = model.getTetModels();
    TetModel *tm = tetModels[solidIndex];
    const unsigned int offset = tm->getIndexOffset();
    const unsigned int *indices = tm->getParticleMesh().getTets().data();
    m_x[0] = pd.getPosition(indices[4 * tetIndex] + offset);
    m_x[1] = pd.getPosition(indices[4 * tetIndex + 1] + offset);
    m_x[2] = pd.getPosition(indices[4 * tetIndex + 2] + offset);
    m_x[3] = pd.getPosition(indices[4 * tetIndex + 3] + offset);
    m_v[0] = pd.getVelocity(indices[4 * tetIndex] + offset);
    m_v[1] = pd.getVelocity(indices[4 * tetIndex + 1] + offset);
    m_v[2] = pd.getVelocity(indices[4 * tetIndex + 2] + offset);
    m_v[3] = pd.getVelocity(indices[4 * tetIndex + 3] + offset);
    m_invMasses[0] = pd.getInvMass(indices[4 * tetIndex] + offset);
    m_invMasses[1] = pd.getInvMass(indices[4 * tetIndex + 1] + offset);
    m_invMasses[2] = pd.getInvMass(indices[4 * tetIndex + 2] + offset);
    m_invMasses[3] = pd.getInvMass(indices[4 * tetIndex + 3] + offset);

    return PositionBasedDynamics::init_ParticleTetContactConstraint(
        pd.getInvMass(particleIndex),
        pd.getPosition(particleIndex),
        pd.getVelocity(particleIndex),
        m_invMasses,
        m_x.data(),
        m_v.data(),
        bary, normal,
        m_constraintInfo);
}
