#include "MiniGL.h"

#ifdef WIN32
#include "windows.h"
#else
#include <cstdio>
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

using namespace PBD;

float MiniGL::fovy = 45;
float MiniGL::znear = 0.5f;
float MiniGL::zfar = 1000;

MiniGL::SceneFct MiniGL::scenefunc = nullptr;

int MiniGL::m_width = 0;
int MiniGL::m_height = 0;

GLFWwindow *MiniGL::m_glfw_window = nullptr;

bool MiniGL::m_vsync = false;

void MiniGL::init(int argc, char **argv, const int width, const int height, const char *name, const bool vsync, const bool maximized)
{
    fovy = 60;
    znear = 0.5f;
    zfar = 1000;

    m_width = width;
    m_height = height;
    m_vsync = vsync;

    scenefunc = nullptr;

    // glfwSetErrorCallback(error_callback);

    // if (!glfwInit())
    //     exit(EXIT_FAILURE);

    // glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
    // // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // if (maximized)
    //     glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // if (m_vsync)
    //     glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    // else
    //     glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);

    // m_glfw_window = glfwCreateWindow(width, height, name, NULL, NULL);
    // if (!m_glfw_window)
    // {
    //     glfwTerminate();
    //     exit(EXIT_FAILURE);
    // }

    // glfwMakeContextCurrent(m_glfw_window);
    // gladLoadGL(glfwGetProcAddress);
    // glfwSwapInterval(0);

    // glfwSetFramebufferSizeCallback(m_glfw_window, reshape);

    // getOpenGLVersion(m_context_major_version, m_context_minor_version);
    // glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &m_context_profile);

    // LOG_INFO << "OpenGL version " << m_context_major_version << "." << m_context_minor_version;
    // LOG_INFO << "Vendor: " << glGetString(GL_VENDOR);
    // LOG_INFO << "Renderer: " << glGetString(GL_RENDERER);
    // LOG_INFO << "Version: " << glGetString(GL_VERSION);

    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_NORMALIZE);
    // glShadeModel(GL_SMOOTH);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    // glfwSetKeyCallback(m_glfw_window, keyboard);
    // glfwSetCharCallback(m_glfw_window, char_callback);
    // glfwSetMouseButtonCallback(m_glfw_window, mousePress);
    // glfwSetCursorPosCallback(m_glfw_window, mouseMove);
    // glfwSetScrollCallback(m_glfw_window, mouseWheel);

    // int w, h;
    // glfwGetWindowSize(m_glfw_window, &w, &h);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // m_lastTime = glfwGetTime();
}

void MiniGL::getWindowPos(int &x, int &y)
{
    glfwGetWindowPos(m_glfw_window, &x, &y);
}

void MiniGL::getWindowSize(int &w, int &h)
{
    glfwGetWindowSize(m_glfw_window, &w, &h);
}

bool MiniGL::getWindowMaximized()
{
    return glfwGetWindowAttrib(m_glfw_window, GLFW_MAXIMIZED);
}