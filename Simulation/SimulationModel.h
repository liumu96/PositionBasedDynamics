#pragma once

#include "Common/Common.h"

#include "Simulation/RigidBody.h"
#include "Simulation/ParticleData.h"
#include "TriangleModel.h"
#include "TetModel.h"

#include "ParameterObject.h"
#include "Constraints.h"

namespace PBD
{
    class Constraint;
    // class RigidBodyContactConstraint;
    // class ParticleRigidBodyContactConstraint;
    // class ParticleTetContactConstraint;

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

        typedef std::vector<RigidBody *> RigidBodyVector;
        typedef std::vector<TriangleModel *> TriangleModelVector;
        typedef std::vector<TetModel *> TetModelVector;

    protected:
        RigidBodyVector m_rigidBodies;
        TriangleModelVector m_triangleModels;
        TetModelVector m_tetModels;
        ParticleData m_particles;

        ConstraintVector m_constraints;
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

        RigidBodyVector &getRigidBodies();
        ParticleData &getParticles();

        TriangleModelVector &getTriangleModels();
        TetModelVector &getTetModels();

        ConstraintVector &getConstraints();
        RigidBodyContactConstraintVector &getRigidBodyContactConstraints();
        ParticleRigidBodyContactConstraintVector &getParticleRigidBodyContactConstraints();

        bool m_groupsInitialized;

        void addTriangleModel(
            const unsigned int nPoints,
            const unsigned int nFaces,
            Vector3r *points,
            unsigned int *indices,
            const TriangleModel::ParticleMesh::UVIndices &uvIndices,
            const TriangleModel::ParticleMesh::UVs &uvs);

        void addRegularTriangleModel(const int width, const int height,
                                     const Vector3r &translation = Vector3r::Zero(),
                                     const Matrix3r &rotation = Matrix3r::Identity(),
                                     const Vector2r &scale = Vector2r::Ones());

        bool addRigidBodyContactConstraint(const unsigned int rbIndex1, const unsigned int rbIndex2,
                                           const Vector3r &cp1, const Vector3r &cp2,
                                           const Vector3r &normal, const Real dist,
                                           const Real restitutionCoeff, const Real frictionCoeff);
        bool addParticleRigidBodyContactConstraint(const unsigned int particleIndex, const unsigned int rbIndex,
                                                   const Vector3r &cp1, const Vector3r &cp2,
                                                   const Vector3r &normal, const Real dist,
                                                   const Real restitutionCoeff, const Real frictionCoeff);

        bool addParticleSolidContactConstraint(const unsigned int particleIndex, const unsigned int solidIndex,
                                               const unsigned int tetIndex, const Vector3r &bary,
                                               const Vector3r &cp1, const Vector3r &cp2,
                                               const Vector3r &normal, const Real dist,
                                               const Real restitutionCoeff, const Real frictionCoeff);
    };
}