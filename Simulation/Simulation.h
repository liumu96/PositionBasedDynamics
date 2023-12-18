#pragma once

#include "Common/Common.h"
#include "SimulationModel.h"
#include "ParameterObject.h"
#include "TimeStep.h"

namespace PBD
{
    /**
     * Class to manage the current simulation time and the time step size.
     * This class is a singleton.
     */
    class Simulation : public GenParam::ParameterObject
    {
    public:
    protected:
        SimulationModel *m_model;
        TimeStep *m_timeStep;
        Vector3r m_gravitation;

        virtual void initParameters();

    private:
        static Simulation *current;

    public:
        Simulation();
        Simulation(const Simulation &) = delete;
        Simulation &operator=(const Simulation &) = delete;
        ~Simulation();
        static Simulation *getCurrent();

        void init();

        SimulationModel *getModel() { return m_model; }
        void setModel(SimulationModel *model) { m_model = model; }

        TimeStep *getTimeStep() { return m_timeStep; }
    };
}