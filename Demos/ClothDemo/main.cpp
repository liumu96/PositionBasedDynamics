#include "Common/Common.h"
#include "Demos/Visualization/MiniGL.h"

#include "Simulation/TimeManager.h"

#include "Simulation/SimulationModel.h"

#include "Demos/Common/DemoBase.h"
#include "Simulation/Simulation.h"

#include <iostream>

// Enable memory leak detection
#if defined(_DEBUG) && !defined(EIGEN_ALIGN)
#define new DEBUG_NEW
#endif

using namespace PBD;

void timeStep();
void buildModel();
void createMesh();
void render();
void reset();

const int nRows = 50;
const int nCols = 50;
const Real width = 10.0;
const Real height = 10.0;

DemoBase *base;

int main(int argc, char **argv)
{
    REPORT_MEMORY_LEAKS

    base = new DemoBase();
    base->init(argc, argv, "Cloth demo");

    SimulationModel *model = new SimulationModel();
    model->init();

    Simulation::getCurrent()->setModel(model);

    buildModel();

    // OpenGL
    MiniGL::setClientIdleFunc(timeStep);
    MiniGL::addKeyFunc('r', reset);
    MiniGL::setClientSceneFunc(render);
    MiniGL::setViewport(40.0f, 0.1f, 500.0f, Vector3r(5.0, 10.0, 30.0), Vector3r(5.0, 0.0, 0.0));

    MiniGL::mainLoop();

    std::cout << "Cloth Demo3" << std::endl;
}

void reset()
{
    // todo
}

void timeStep()
{
    // todo
}

void render()
{
    // todo
    base->render();
}

void buildModel()
{
    TimeManager::getCurrent()->setTimeStepSize(static_cast<Real>(0.005));

    createMesh();
}

/**
 * Create a particle model mesh
 */
void createMesh()
{
    SimulationModel *model = Simulation::getCurrent()->getModel();
    model->addRegularTriangleModel(nCols, nRows,
                                   Vector3r(0, 1, 0), AngleAxisr(M_PI * 0.5, Vector3r(1, 0, 0)).matrix(), Vector2r(width, height));

    // Set mass of points to zero => make it static
    ParticleData &pd = model->getParticles();
    pd.setMass(0, 0.0);
    pd.setMass(nRows - 1, 0.0);

    // todo init constraints
}
