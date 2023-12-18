#pragma once

#include "Common/Common.h"
#include "Utils/SceneLoader.h"
#include "Demos/Visualization/Shader.h"

#include "Simulation/SimulationModel.h"
#include "ParameterObject.h"
#include "Simulator_GUI_imgui.h"

namespace PBD
{
    class DemoBase : public GenParam::ParameterObject
    {
    protected:
        unsigned int m_numberOfStepsPerRenderUpdate;

        std::string m_outputPath;
        std::string m_exePath;

        std::string m_sceneFile;
        std::string m_sceneName;

        bool m_useCache;

        GLint m_context_major_version;
        GLint m_context_minor_version;

        Shader m_shader;
        Shader m_shaderFlat;
        Shader m_shaderTex;

        void shaderTexBegin(const float *col);
        void shaderTexEnd();

        bool m_doPause;
        Real m_pauseAt;

        bool m_renderTets;
        bool m_renderRefTets;
        bool m_renderContacts;
        bool m_renderAABB;
        bool m_renderSDF;
        int m_renderBVHDepth;
        int m_renderBVHDepthTets;

        Vector3r m_oldMousePos;

        std::vector<unsigned int> m_selectedBodies;
        Utilities::SceneLoader *m_sceneLoader;

        float m_jointColor[4] = {0.0f, 0.6f, 0.2f, 1};
        Simulator_GUI_imgui *m_gui;

        bool m_enableExportOBJ;
        bool m_enableExportPLY;
        unsigned int m_exportFPS;

        Real m_nextFrameTime;
        unsigned int m_frameCounter;

        virtual void initParameters();

        void initShaders();

        void renderTriangleModels();
        void renderTetModels();
        void renderBallJoint(BallJoint &bj);
        void renderRigidBodyParticleBallJoint(RigidBodyParticleBallJoint &bj);
        void renderBallOnLineJoint(BallOnLineJoint &bj);
        void renderHingeJoint(HingeJoint &hj);
        void renderUniversalJoint(UniversalJoint &uj);
        void renderSliderJoint(SliderJoint &joint);
        void renderTargetPositionMotorSliderJoint(TargetPositionMotorSliderJoint &joint);
        void renderTargetVelocityMotorSliderJoint(TargetVelocityMotorSliderJoint &joint);
        void renderTargetAngleMotorHingeJoint(TargetAngleMotorHingeJoint &hj);
        void renderTargetVelocityMotorHingeJoint(TargetVelocityMotorHingeJoint &hj);
        void renderRigidBodyContact(RigidBodyContactConstraint &cc);
        void renderParticleRigidBodyContact(ParticleRigidBodyContactConstraint &cc);
        void renderSpring(RigidBodySpring &s);
        void renderDistanceJoint(DistanceJoint &j);
        void renderDamperJoint(DamperJoint &j);

    public:
        static int PAUSE;
        static int PAUSE_AT;
        static int NUM_STEPS_PER_RENDER;
        static int RENDER_TETS;
        static int RENDER_TETS0;
        static int RENDER_CONTACTS;
        static int RENDER_AABB;
        static int RENDER_SDF;
        static int RENDER_BVH;
        static int RENDER_BVH_TETS;
        static int EXPORT_OBJ;
        static int EXPORT_PLY;
        static int EXPORT_FPS;

        DemoBase();
        virtual ~DemoBase();

        void init(int argc, char **argv, const char *demoName);

        void render();

        void reset();

        const std::string &getExePath() const { return m_exePath; }

        void shaderBegin(const float *col);
        void shaderEnd();
        void shaderFlatBegin(const float *col);
        void shaderFlatEnd();

        void setUseCache(bool val) { m_useCache = val; }
    };
}