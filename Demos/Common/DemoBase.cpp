#include "DemoBase.h"
#include "Demos/Visualization/MiniGL.h"
#include "Utils/SceneLoader.h"
#include "Utils/FileSystem.h"

#include "NumericParameter.h"
#include "Utils/Logger.h"

#include "Utils/Version.h"
#include "Utils/SystemInfo.h"

INIT_LOGGING

using namespace PBD;
using namespace std;
using namespace GenParam;

using namespace Utilities;

int DemoBase::PAUSE = -1;
int DemoBase::PAUSE_AT = -1;
int DemoBase::NUM_STEPS_PER_RENDER = -1;
int DemoBase::RENDER_TETS = -1;
int DemoBase::RENDER_TETS0 = -1;
int DemoBase::RENDER_CONTACTS = -1;
int DemoBase::RENDER_AABB = -1;
int DemoBase::RENDER_SDF = -1;
int DemoBase::RENDER_BVH = -1;
int DemoBase::RENDER_BVH_TETS = -1;
int DemoBase::EXPORT_OBJ = -1;
int DemoBase::EXPORT_PLY = -1;
int DemoBase::EXPORT_FPS = -1;

DemoBase::DemoBase()
{
    Utilities::logger.addSink(unique_ptr<Utilities::ConsoleSink>(new Utilities::ConsoleSink(Utilities::LogLevel::INFO)));
    Utilities::logger.addSink(shared_ptr<Utilities::BufferSink>(new Utilities::BufferSink(Utilities::LogLevel::DEBUG)));

    m_sceneLoader = nullptr;
    m_numberOfStepsPerRenderUpdate = 8;
    m_renderContacts = false;
    m_renderAABB = false;
    m_renderSDF = false;
    m_renderBVHDepth = -1;
    m_renderBVHDepthTets = -1;
    m_renderRefTets = false;
    m_renderTets = false;
    m_sceneFile = "";
    m_sceneName = "";
    m_doPause = true;
    m_pauseAt = -1.0;
    m_useCache = true;
    m_oldMousePos.setZero();
    m_enableExportOBJ = false;
    m_enableExportPLY = false;
    m_exportFPS = 25;
    m_nextFrameTime = 0.0;
    m_frameCounter = 1;

    m_gui = new Simulator_GUI_imgui(this);
}

DemoBase::~DemoBase()
{
    delete m_sceneLoader;
    delete m_gui;
}

void DemoBase::initParameters()
{
    ParameterObject::initParameters();

    PAUSE = createBoolParameter("pause", "Pause", &m_doPause);
    setGroup(PAUSE, "Simulation|General");
    setDescription(PAUSE, "Pause simulation.");
    setHotKey(PAUSE, "space");

    PAUSE_AT = createNumericParameter("pauseAt", "Pause simulation at", &m_pauseAt);
    setGroup(PAUSE_AT, "Simulation|General");
    setDescription(PAUSE_AT, "Pause simulation at the given time. When the value is negative, the simulation is not paused.");

    NUM_STEPS_PER_RENDER = createNumericParameter("numberOfStepsPerRenderUpdate", "# time steps / update", &m_numberOfStepsPerRenderUpdate);
    setGroup(NUM_STEPS_PER_RENDER, "Visualization|General");
    setDescription(NUM_STEPS_PER_RENDER, "Pause simulation at the given time. When the value is negative, the simulation is not paused.");
    static_cast<NumericParameter<unsigned int> *>(getParameter(NUM_STEPS_PER_RENDER))->setMinValue(1);

    RENDER_TETS = createBoolParameter("renderTets", "Render tet model", &m_renderTets);
    setGroup(RENDER_TETS, "Visualization|Solids");
    setDescription(RENDER_TETS, "Render tet model.");

    RENDER_TETS0 = createBoolParameter("renderTets0", "Render ref. tet model", &m_renderRefTets);
    setGroup(RENDER_TETS0, "Visualization|Solids");
    setDescription(RENDER_TETS0, "Render ref. tet model.");

    RENDER_CONTACTS = createBoolParameter("renderContacts", "Render contacts", &m_renderContacts);
    setGroup(RENDER_CONTACTS, "Visualization|Contact");
    setDescription(RENDER_CONTACTS, "Render contact points and normals.");

    RENDER_AABB = createBoolParameter("renderAABB", "Render AABBs", &m_renderAABB);
    setGroup(RENDER_AABB, "Visualization|Contact");
    setDescription(RENDER_AABB, "Render AABBs.");

    RENDER_SDF = createBoolParameter("renderSDF", "Render SDFs", &m_renderSDF);
    setGroup(RENDER_SDF, "Visualization|Contact");
    setDescription(RENDER_SDF, "Render SDFs.");

    RENDER_BVH = createNumericParameter("renderBVHDepth", "Render BVH depth", &m_renderBVHDepth);
    setGroup(RENDER_BVH, "Visualization|Contact");
    setDescription(RENDER_BVH, "Render BVH until given depth.");
    static_cast<NumericParameter<int> *>(getParameter(RENDER_BVH))->setMinValue(-1);

    RENDER_BVH_TETS = createNumericParameter("renderBVHDepthTets", "Render BVH depth (tets)", &m_renderBVHDepthTets);
    setGroup(RENDER_BVH_TETS, "Visualization|Contact");
    setDescription(RENDER_BVH_TETS, "Render BVH (tets) until given depth.");
    static_cast<NumericParameter<int> *>(getParameter(RENDER_BVH_TETS))->setMinValue(-1);

    EXPORT_OBJ = createBoolParameter("exportOBJ", "Export OBJ", &m_enableExportOBJ);
    setGroup(EXPORT_OBJ, "Simulation|Export");
    setDescription(EXPORT_OBJ, "Export meshes in OBJ files.");

    EXPORT_PLY = createBoolParameter("exportPLY", "Export PLY", &m_enableExportPLY);
    setGroup(EXPORT_PLY, "Simulation|Export");
    setDescription(EXPORT_PLY, "Export meshes in PLY files.");

    EXPORT_FPS = createNumericParameter("exportFPS", "Export FPS", &m_exportFPS);
    setGroup(EXPORT_FPS, "Simulation|Export");
    setDescription(EXPORT_FPS, "Frame rate for export.");
    static_cast<NumericParameter<int> *>(getParameter(EXPORT_FPS))->setMinValue(0);
}

void DemoBase::init(int argc, char **argv, const char *demoName)
{
    initParameters();
    m_exePath = FileSystem::getProgramPath();

    m_sceneFile = "";
    setUseCache(true);
    for (int i = 1; i < argc; i++)
    {
        string argStr = argv[i];
        if (argStr == "--no-cache")
            setUseCache(false);
        else
        {
            m_sceneFile = string(argv[i]);
            if (FileSystem::isRelativePath(m_sceneFile))
                m_sceneFile = FileSystem::normalizePath(m_exePath + "/" + m_sceneFile);
        }
    }

    if (m_sceneFile != "")
        m_outputPath = FileSystem::normalizePath(getExePath() + "/output/" + FileSystem::getFileName(m_sceneFile));
    else
        m_outputPath = FileSystem::normalizePath(getExePath() + "/output/" + std::string(demoName));

#ifdef DL_OUTPUT
    std::string sceneFilePath = FileSystem::normalizePath(m_outputPath + "/scene");
    FileSystem::makeDirs(sceneFilePath);
    FileSystem::copyFile(m_sceneFile, sceneFilePath + "/" + FileSystem::getFileNameWithExt(m_sceneFile));

    std::string progFilePath = FileSystem::normalizePath(m_outputPath + "/program");
    FileSystem::makeDirs(progFilePath);
    FileSystem::copyFile(argv[0], progFilePath + "/" + FileSystem::getFileNameWithExt(argv[0]));
#endif

    std::string logPath = FileSystem::normalizePath(m_outputPath + "/log");
    FileSystem::makeDirs(logPath);
    Utilities::logger.addSink(unique_ptr<Utilities::FileSink>(new Utilities::FileSink(Utilities::LogLevel::DEBUG, logPath + "/PBD_log.txt")));

    LOG_DEBUG << "Git refspec: " << GIT_REFSPEC;
    LOG_DEBUG << "Git SHA1:    " << GIT_SHA1;
    LOG_DEBUG << "Git status:  " << GIT_LOCAL_STATUS;
    LOG_DEBUG << "Host name:   " << SystemInfo::getHostName();
    LOG_INFO << "PositionBasedDynamics " << PBD_VERSION;

    m_gui->init();

    // OpenGL
    MiniGL::init(argc, argv, 1280, 1024, demoName, m_gui->getVSync(), m_gui->getMaximized());
    // MiniGL::initLights();
    // MiniGL::initTexture();
    // MiniGL::getOpenGLVersion(m_context_major_version, m_context_minor_version);
    // MiniGL::setViewport(40.0, 0.1f, 500.0, Vector3r(0.0, 3.0, 8.0), Vector3r(0.0, 0.0, 0.0));
    // MiniGL::setSelectionFunc(selection, this);

    // if (MiniGL::checkOpenGLVersion(3, 3))
    //     initShaders();

    // m_gui->initImgui();
}