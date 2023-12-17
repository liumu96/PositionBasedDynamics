#pragma once

#include "Common/Common.h"
#include "Utils/SceneLoader.h"

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

        Utilities::SceneLoader *m_sceneLoader;

        Simulator_GUI_imgui *m_gui;

        bool m_enableExportOBJ;
        bool m_enableExportPLY;
        unsigned int m_exportFPS;

        Real m_nextFrameTime;
        unsigned int m_frameCounter;

        virtual void initParameters();

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

        const std::string &getExePath() const { return m_exePath; }

        void setUseCache(bool val) { m_useCache = val; }
    };
}