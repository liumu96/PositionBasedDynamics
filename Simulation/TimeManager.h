#pragma once

#include "Common/Common.h"

namespace PBD
{
    class TimeManager
    {

    private:
        Real time;
        static TimeManager *current;
        Real h;

    public:
        TimeManager();
        ~TimeManager();

        // Singleton
        static TimeManager *getCurrent();

        void setTimeStepSize(Real tss);
    };
}