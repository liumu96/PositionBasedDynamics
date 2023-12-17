#include "Common/Common.h"

#include "Simulation/SimulationModel.h"

#include "Demos/Common/DemoBase.h"

#include <iostream>

// Enable memory leak detection
#if defined(_DEBUG) && !defined(EIGEN_ALIGN)
#define new DEBUG_NEW
#endif

using namespace PBD;

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

    std::cout << "Cloth Demo" << std::endl;
}