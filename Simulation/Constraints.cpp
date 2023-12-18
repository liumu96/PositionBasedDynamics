#include "Constraints.h"
#include "SimulationModel.h"

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