#include "Simulator_GUI_imgui.h"
#include "Demos/Visualization/MiniGL.h"
#include "DemoBase.h"

#include "LogWindow.h"

#include "imgui.h"
#include "imgui_internal.h"

using namespace PBD;

Simulator_GUI_imgui::Simulator_GUI_imgui(DemoBase *base)
{
    m_base = base;
    m_currentScaleIndex = 0;
    m_vsync = false;
    m_iniFound = false;
    m_showLogWindow = true;
}

Simulator_GUI_imgui::~Simulator_GUI_imgui(void)
{
    // todo
}

void Simulator_GUI_imgui::init()
{
    m_logWindow = new LogWindow();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    m_context = ImGui::CreateContext();

    // Add .ini handle for UserData type
    ImGuiSettingsHandler ini_handler;
    ini_handler.TypeName = "PBDSimulator";
    ini_handler.TypeHash = ImHashStr("PBDSimulator");
    ini_handler.ReadOpenFn = readOpenIni;
    ini_handler.ReadLineFn = readIni;
    ini_handler.WriteAllFn = writeIni;
    ini_handler.ApplyAllFn = applySettings;
    ini_handler.UserData = this;
    m_context->SettingsHandlers.push_back(ini_handler);

    // load ini file before window is created
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    ImGui::LoadIniSettingsFromDisk(io.IniFilename);
}

void *Simulator_GUI_imgui::readOpenIni(ImGuiContext *ctx, ImGuiSettingsHandler *handler, const char *name)
{
    Simulator_GUI_imgui *gui = (Simulator_GUI_imgui *)handler->UserData;
    return &gui->m_userSettings;
}

void Simulator_GUI_imgui::readIni(ImGuiContext *ctx, ImGuiSettingsHandler *handler, void *entry, const char *line)
{
    Simulator_GUI_imgui *gui = (Simulator_GUI_imgui *)handler->UserData;
    UserSettings *settings = (UserSettings *)entry;
    int x, y, w, h;
    int i;
    if (sscanf(line, "pos=%d,%d", &x, &y) == 2)
    {
        settings->win_x = x;
        settings->win_y = y;
    }
    else if (sscanf(line, "size=%d,%d", &w, &h) == 2)
    {
        settings->win_width = w;
        settings->win_height = h;
    }
    else if (sscanf(line, "scale=%d", &i) == 1)
    {
        settings->scaleIndex = i;
    }
    else if (sscanf(line, "maximized=%d", &i) == 1)
    {
        settings->maximized = (i != 0);
    }
    else if (sscanf(line, "vsync=%d", &i) == 1)
    {
        settings->vsync = (i != 0);
    }
    else if (sscanf(line, "show_log_window=%d", &i) == 1)
    {
        settings->show_log_window = (i != 0);
    }
    else if (sscanf(line, "log_filter=%d", &i) == 1)
    {
        settings->log_filter = i;
    }
}

void Simulator_GUI_imgui::writeIni(ImGuiContext *ctx, ImGuiSettingsHandler *handler, ImGuiTextBuffer *out_buf)
{
    Simulator_GUI_imgui *gui = (Simulator_GUI_imgui *)handler->UserData;
    out_buf->reserve(out_buf->size() + 200);
    out_buf->appendf("[%s][%s]\n", handler->TypeName, "Settings");
    out_buf->appendf("scale=%d\n", gui->m_currentScaleIndex);

    int x, y;
    MiniGL::getWindowPos(x, y);
    out_buf->appendf("pos=%d,%d\n", x, y);

    int w, h;
    MiniGL::getWindowSize(w, h);
    out_buf->appendf("size=%d,%d\n", w, h);
    out_buf->appendf("maximized=%d\n", MiniGL::getWindowMaximized());

    out_buf->appendf("vsync=%d\n", gui->m_vsync);
    out_buf->appendf("show_log_window=%d\n", gui->m_showLogWindow);
    out_buf->appendf("log_filter=%d\n", gui->m_logWindow->getSelectedFilter());
}

void Simulator_GUI_imgui::applySettings(ImGuiContext *ctx, ImGuiSettingsHandler *handler)
{
    Simulator_GUI_imgui *gui = (Simulator_GUI_imgui *)handler->UserData;
    UserSettings *settings = (UserSettings *)&gui->m_userSettings;
    gui->m_currentScaleIndex = settings->scaleIndex;
    gui->m_vsync = settings->vsync;
    gui->m_showLogWindow = settings->show_log_window;
    gui->m_iniFound = true;
    gui->m_logWindow->setSelectedFilter(settings->log_filter);
}
