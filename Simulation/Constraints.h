#pragma once

#include "Common/Common.h"

namespace PBD
{
    class SimulationModel;

    class Constraint
    {
    public:
        /** indices of the linked bodies */
        std::vector<unsigned int> m_bodies;

        Constraint(const unsigned int numberOfBodies)
        {
            m_bodies.resize(numberOfBodies);
        }

        unsigned int numberOfBodies() const { return static_cast<unsigned int>(m_bodies.size()); }
        virtual ~Constraint(){};
        virtual int &getTypeId() const = 0;

        virtual bool initConstraintBeforeProjection(SimulationModel &model) { return true; };
        virtual bool updateConstraint(SimulationModel &model) { return true; };
        virtual bool solvePositionConstraint(SimulationModel &model, const unsigned int iter) { return true; };
        virtual bool solveVelocityConstraint(SimulationModel &model, const unsigned int iter) { return true; };
    };

    class BallJoint : public Constraint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 3, 4, Eigen::DontAlign> m_jointInfo;

        BallJoint() : Constraint(2) {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class BallOnLineJoint : public Constraint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 3, 10, Eigen::DontAlign> m_jointInfo;

        BallOnLineJoint() : Constraint(2) {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class HingeJoint : public Constraint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 4, 7, Eigen::DontAlign> m_jointInfo;

        HingeJoint() : Constraint(2) {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class UniversalJoint : public Constraint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 3, 8, Eigen::DontAlign> m_jointInfo;

        UniversalJoint() : Constraint(2) {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class SliderJoint : public Constraint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 4, 6, Eigen::DontAlign> m_jointInfo;

        SliderJoint() : Constraint(2) {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class MotorJoint : public Constraint
    {
    public:
        Real m_target;
        std::vector<Real> m_targetSequence;
        MotorJoint() : Constraint(2) { m_target = 0.0; }

        virtual Real getTarget() const { return m_target; }
        virtual void setTarget(const Real val) { m_target = val; }

        virtual std::vector<Real> &getTargetSequence() { return m_targetSequence; }
        virtual void setTargetSequence(const std::vector<Real> &val) { m_targetSequence = val; }

        bool getRepeatSequence() const { return m_repeatSequence; }
        void setRepeatSequence(bool val) { m_repeatSequence = val; }

    private:
        bool m_repeatSequence;
    };

    class TargetPositionMotorSliderJoint : public MotorJoint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 4, 6, Eigen::DontAlign> m_jointInfo;

        TargetPositionMotorSliderJoint() : MotorJoint() {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class TargetVelocityMotorSliderJoint : public MotorJoint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 4, 6, Eigen::DontAlign> m_jointInfo;

        TargetVelocityMotorSliderJoint() : MotorJoint() {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class TargetAngleMotorHingeJoint : public MotorJoint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 4, 8, Eigen::DontAlign> m_jointInfo;
        TargetAngleMotorHingeJoint() : MotorJoint() {}
        virtual int &getTypeId() const { return TYPE_ID; }

        virtual void setTarget(const Real val)
        {
            const Real pi = (Real)M_PI;
            m_target = std::max(val, -pi);
            m_target = std::min(m_target, pi);
        }

    private:
        std::vector<Real> m_targetSequence;
    };

    class TargetVelocityMotorHingeJoint : public MotorJoint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 4, 8, Eigen::DontAlign> m_jointInfo;
        TargetVelocityMotorHingeJoint() : MotorJoint() {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class DamperJoint : public Constraint
    {
    public:
        static int TYPE_ID;
        Real m_stiffness;
        Eigen::Matrix<Real, 4, 6, Eigen::DontAlign> m_jointInfo;
        Real m_lambda;

        DamperJoint() : Constraint(2) {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class RigidBodyParticleBallJoint : public Constraint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 3, 2, Eigen::DontAlign> m_jointInfo;

        RigidBodyParticleBallJoint() : Constraint(2) {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class RigidBodySpring : public Constraint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 3, 4, Eigen::DontAlign> m_jointInfo;
        Real m_restLength;
        Real m_stiffness;
        Real m_lambda;

        RigidBodySpring() : Constraint(2) {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class DistanceJoint : public Constraint
    {
    public:
        static int TYPE_ID;
        Eigen::Matrix<Real, 3, 4, Eigen::DontAlign> m_jointInfo;
        Real m_restLength;

        DistanceJoint() : Constraint(2) {}
        virtual int &getTypeId() const { return TYPE_ID; }
    };

    class RigidBodyContactConstraint
    {

    public:
        static int TYPE_ID;
        /** indices of the linked bodies */
        std::array<unsigned int, 2> m_bodies;
        Real m_stiffness;
        Real m_frictionCoeff;
        Real m_sum_impulses;

        Eigen::Matrix<Real, 3, 5, Eigen::DontAlign> m_constraintInfo;

        RigidBodyContactConstraint() {}
        ~RigidBodyContactConstraint() {}
        virtual int &getTypeId() const { return TYPE_ID; }

        bool initConstraint(SimulationModel &model, const unsigned int rbIndex1, const unsigned int rbIndex2,
                            const Vector3r &cp1, const Vector3r &cp2,
                            const Vector3r &normal, const Real dist,
                            const Real restitutionCoeff, const Real stiffness, const Real frictionCoeff);
    };

    class ParticleRigidBodyContactConstraint
    {

    public:
        static int TYPE_ID;
        /** indices of the linked bodies */
        std::array<unsigned int, 2> m_bodies;
        Real m_stiffness;
        Real m_frictionCoeff;
        Real m_sum_impulses;
        Eigen::Matrix<Real, 3, 5, Eigen::DontAlign> m_constraintInfo;

        ParticleRigidBodyContactConstraint() {}
        ~ParticleRigidBodyContactConstraint() {}
        virtual int &getTypeId() const { return TYPE_ID; }

        bool initConstraint(SimulationModel &model, const unsigned int particleIndex, const unsigned int rbIndex,
                            const Vector3r &cp1, const Vector3r &cp2,
                            const Vector3r &normal, const Real dist,
                            const Real restitutionCoeff, const Real stiffness, const Real frictionCoeff);
    };

    class ParticleTetContactConstraint
    {
    public:
        static int TYPE_ID;
        /** indices of the linked bodies */
        std::array<unsigned int, 2> m_bodies;
        unsigned int m_solidIndex;
        unsigned int m_tetIndex;
        Vector3r m_bary;
        Real m_lambda;
        Real m_frictionCoeff;
        Eigen::Matrix<Real, 3, 3, Eigen::DontAlign> m_constraintInfo;
        Real m_invMasses[4];
        std::array<Vector3r, 4> m_x;
        std::array<Vector3r, 4> m_v;

        ParticleTetContactConstraint() {}
        ~ParticleTetContactConstraint() {}

        virtual int &getTypeId() const { return TYPE_ID; }

        bool initConstraint(SimulationModel &model, const unsigned int particleIndex, const unsigned int solidIndex,
                            const unsigned int tetindex, const Vector3r &bary,
                            const Vector3r &cp1, const Vector3r &cp2,
                            const Vector3r &normal, const Real dist,
                            const Real frictionCoeff);
    };

    struct Node;
    struct Interval;
    class SimulationModel;
    using Vector6r = Eigen::Matrix<Real, 6, 1, Eigen::DontAlign>;

}