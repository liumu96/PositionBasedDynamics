#pragma once

namespace PBD
{
    class DemoBase
    {
    protected:
        unsigned int m_numberOfStepsPerRenderUpdate;

    public:
        DemoBase();
        virtual ~DemoBase();

        void init(int argc, char **argv, const char *demoName);

        void render();
        void cleanup();
    };
};