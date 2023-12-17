#include "Simulation.h"

using namespace PBD;

Simulation *Simulation::current = nullptr;

Simulation::Simulation()
{
    m_gravitation = Vector3r(0.0, -9.81, 0.0);

    // m_timeStep = nullptr;
    m_model = nullptr;
}

Simulation::~Simulation()
{
    // todo
    // delete m_timeStep;
    // delete TimeManager::getCurrent();

    current = nullptr;
}

Simulation *Simulation::getCurrent()
{
    if (current == nullptr)
    {
        current = new Simulation();
        current->init();
    }
    return current;
}

void Simulation::init()
{
    initParameters();
    // todo
    // m_timeStep = new TimeStepController();
    // m_timeStep->init();
    // TimeManager::getCurrent()->setTimeStepSize(static_cast<Real>(0.005));
}

void Simulation::initParameters()
{
    ParameterObject::initParameters();
    // todo
    // GRAVITATION = createVectorParameter("gravitation", "Gravitation", 3u, m_gravitation.data());
    // setGroup(GRAVITATION, "Simulation|General");
    // setDescription(GRAVITATION, "Vector to define the gravitational acceleration.");
}