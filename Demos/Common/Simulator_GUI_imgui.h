#pragma once

#include "Common/Common.h"

struct ImFont;
struct ImGuiContext;
struct ImGuiSettingsHandler;
struct ImGuiTextBuffer;

namespace PBD
{
    struct UserSettings
    {
        int scaleIndex;
        int win_x, win_y;
        int win_width, win_height;
        bool vsync;
        bool show_log_window;
        bool maximized;
        int log_filter;

        UserSettings()
        {
            win_x = 0;
            win_y = 0;
            win_width = 1280;
            win_height = 960;
            scaleIndex = 0;
            vsync = false;
            maximized = false;
            log_filter = 1;
        }
    };

    class LogWindow;
    class DemoBase;

    class Simulator_GUI_imgui
    {
    public:
        Simulator_GUI_imgui(DemoBase *base);
        virtual ~Simulator_GUI_imgui();

    protected:
        DemoBase *m_base;

        unsigned int m_currentScaleIndex;
        bool m_vsync;
        bool m_showLogWindow;

        ImGuiContext *m_context;

        UserSettings m_userSettings;

        bool m_iniFound;

        LogWindow *m_logWindow;

        static void writeIni(ImGuiContext *ctx, ImGuiSettingsHandler *handler, ImGuiTextBuffer *out_buf);
        static void readIni(ImGuiContext *ctx, ImGuiSettingsHandler *handler, void *entry, const char *line);
        static void *readOpenIni(ImGuiContext *ctx, ImGuiSettingsHandler *handler, const char *name);
        static void applySettings(ImGuiContext *ctx, ImGuiSettingsHandler *handler);

    public:
        void init();

        bool getVSync() { return m_userSettings.vsync; }
        bool getMaximized() { return m_userSettings.maximized; }
    };
}