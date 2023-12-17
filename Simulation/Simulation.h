#pragma once

#include "Common/Common.h"
#include "SimulationModel.h"
#include "ParameterObject.h"

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

        void setModel(SimulationModel *model) { m_model = model; }
    };
}