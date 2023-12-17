#pragma once

namespace PBD
{
    class SimulationModel;

    class Constraint
    {
        // todo
    };

    class RigidBodyContactConstraint
    {

    public:
        static int TYPE_ID;
        // todo

        RigidBodyContactConstraint() {}
        ~RigidBodyContactConstraint() {}
    };

    class ParticleRigidBodyContactConstraint
    {

    public:
        static int TYPE_ID;
        // todo

        ParticleRigidBodyContactConstraint() {}
        ~ParticleRigidBodyContactConstraint() {}
    };

    class ParticleTetContactConstraint
    {
    public:
        static int TYPE_ID;
        // todo

        ParticleTetContactConstraint() {}
        ~ParticleTetContactConstraint() {}
    };

}