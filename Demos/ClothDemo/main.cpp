#include "Common/Common.h"

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

void buildModel();
void createMesh();

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

    std::cout << "Cloth Demo" << std::endl;
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
    // todo
}
