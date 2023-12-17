#include "Constraints.h"
#include "SimulationModel.h"

#include "Simulation/IDFactory.h"

using namespace PBD;

int RigidBodyContactConstraint::TYPE_ID = IDFactory::getId();
int ParticleRigidBodyContactConstraint::TYPE_ID = IDFactory::getId();
int ParticleTetContactConstraint::TYPE_ID = IDFactory::getId();