#pragma once

#include "Common/Common.h"

#include "ParameterObject.h"

namespace PBD
{
    class Constraint;
    class RigidBodyContactConstraint;
    class ParticleRigidBodyContactConstraint;
    class ParticleTetContactConstraint;

    class SimulationModel : public GenParam::ParameterObject
    {
    public:
        SimulationModel();
        SimulationModel(const SimulationModel &) = delete;
        SimulationModel &operator=(const SimulationModel &) = delete;
        virtual ~SimulationModel();

        void init();
        virtual void initParameters();

        typedef std::vector<Constraint *> ConstraintVector;
        typedef std::vector<RigidBodyContactConstraint> RigidBodyContactConstraintVector;
        typedef std::vector<ParticleRigidBodyContactConstraint> ParticleRigidBodyContactConstraintVector;
        typedef std::vector<ParticleTetContactConstraint> ParticleSolidContactConstraintVector;

    protected:
        RigidBodyContactConstraintVector m_rigidBodyContactConstraints;
        ParticleRigidBodyContactConstraintVector m_particleRigidBodyContactConstraints;
        ParticleSolidContactConstraintVector m_particleSolidContactConstraints;

        int m_clothSimulationMethod;
        int m_clothBendingMethod;
        Real m_cloth_stiffness;
        Real m_cloth_bendingStiffness;
        Real m_cloth_xxStiffness;
        Real m_cloth_yyStiffness;
        Real m_cloth_xyStiffness;
        Real m_cloth_xyPoissonRatio;
        Real m_cloth_yxPoissonRatio;
        bool m_cloth_normalizeStretch;
        bool m_cloth_normalizeShear;

        int m_solidSimulationMethod;
        Real m_solid_stiffness;
        Real m_solid_poissonRatio;
        Real m_solid_volumeStiffness;
        bool m_solid_normalizeStretch;
        bool m_solid_normalizeShear;

        Real m_rod_stretchingStiffness;
        Real m_rod_shearingStiffnessX;
        Real m_rod_shearingStiffnessY;
        Real m_rod_bendingStiffnessX;
        Real m_rod_bendingStiffnessY;
        Real m_rod_twistingStiffness;

        Real m_contactStiffnessRigidBody;
        Real m_contactStiffnessParticleRigidBody;

        std::function<void()> m_clothSimMethodChanged;
        std::function<void()> m_solidSimMethodChanged;

    public:
        virtual void cleanup();

        bool m_groupsInitialized;
    };
}