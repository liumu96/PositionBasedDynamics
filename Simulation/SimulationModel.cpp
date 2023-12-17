#include "SimulationModel.h"

#include "Constraints.h"

using namespace PBD;
using namespace GenParam;

SimulationModel::SimulationModel()
{
    m_contactStiffnessRigidBody = 1.0;
    m_contactStiffnessParticleRigidBody = 100.0;

    m_clothSimulationMethod = 2;
    m_clothBendingMethod = 2;
    m_cloth_stiffness = static_cast<Real>(1.0);
    m_cloth_bendingStiffness = static_cast<Real>(0.01);
    m_cloth_xxStiffness = static_cast<Real>(1.0);
    m_cloth_yyStiffness = static_cast<Real>(1.0);
    m_cloth_xyStiffness = static_cast<Real>(1.0);
    m_cloth_xyPoissonRatio = static_cast<Real>(0.3);
    m_cloth_yxPoissonRatio = static_cast<Real>(0.3);
    m_cloth_normalizeShear = false;
    m_cloth_normalizeStretch = false;

    m_solidSimulationMethod = 2;
    m_solid_stiffness = static_cast<Real>(1.0);
    m_solid_poissonRatio = static_cast<Real>(0.3);
    m_solid_volumeStiffness = static_cast<Real>(1.0);
    m_solid_normalizeShear = false;
    m_solid_normalizeStretch = false;

    m_rod_stretchingStiffness = static_cast<Real>(1.0);
    m_rod_shearingStiffnessX = static_cast<Real>(1.0);
    m_rod_shearingStiffnessY = static_cast<Real>(1.0);
    m_rod_bendingStiffnessX = static_cast<Real>(0.5);
    m_rod_bendingStiffnessY = static_cast<Real>(0.5);
    m_rod_twistingStiffness = static_cast<Real>(0.5);

    m_groupsInitialized = false;

    m_rigidBodyContactConstraints.reserve(10000);
    m_particleRigidBodyContactConstraints.reserve(10000);
    m_particleSolidContactConstraints.reserve(10000);

    m_clothSimMethodChanged = nullptr;
    m_solidSimMethodChanged = nullptr;
}

SimulationModel::~SimulationModel(void)
{
    cleanup();
}

void SimulationModel::init()
{
    initParameters();
}

void SimulationModel::cleanup()
{
    // todo
}

void SimulationModel::initParameters()
{
    ParameterObject::initParameters();

    // todo
}