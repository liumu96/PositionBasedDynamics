#include "TimeManager.h"

using namespace PBD;

TimeManager *TimeManager::current = 0;

TimeManager::TimeManager()
{
    time = 0;
    h = static_cast<Real>(0.005);
}

TimeManager::~TimeManager()
{
    current = 0;
}

TimeManager *TimeManager::getCurrent()
{
    if (current == 0)
    {
        current = new TimeManager();
    }
    return current;
}

void TimeManager::setTimeStepSize(Real tss)
{
    h = tss;
}