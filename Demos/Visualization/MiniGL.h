#pragma once

#include <Eigen/Geometry>
#include <vector>

#ifdef USE_DOUBLE
#define glNormal3v glNormal3dv
#define glVertex3v glVertex3dv
#define glVertex3 glVertex3d
#define glMultMatrix glMultMatrixd
#define glGetRealv glGetDoublev
#define glLoadMatrix glLoadMatrixd
#define glTranslate glTranslated
#define GL_REAL GL_DOUBLE
#define TW_TYPE_REAL TW_TYPE_DOUBLE
#define TW_TYPE_DIR3R TW_TYPE_DIR3D
#else
#define glNormal3v glNormal3fv
#define glVertex3v glVertex3fv
#define glVertex3 glVertex3f
#define glMultMatrix glMultMatrixf
#define glGetRealv glGetFloatv
#define glLoadMatrix glLoadMatrixf
#define glTranslate glTranslatef
#define GL_REAL GL_FLOAT
#define TW_TYPE_REAL TW_TYPE_FLOAT
#define TW_TYPE_DIR3R TW_TYPE_DIR3F
#endif

struct GLFWwindow;

namespace PBD
{
    class MiniGL
    {
    private:
        typedef std::function<void()> SceneFct;
        typedef std::function<void()> IdleFct;
        typedef std::function<void()> DestroyFct;
        typedef std::function<void(int, int)> ReshapeFct;
        typedef std::function<bool(int, int, int, int)> KeyboardFct;
        typedef std::function<bool(int, int)> CharFct;
        typedef std::function<bool(int, int, int)> MousePressFct;
        typedef std::function<bool(int, int)> MouseMoveFct;
        typedef std::function<bool(int, double, double)> MouseWheelFct;

        static float fovy;
        static float znear;
        static float zfar;

        static SceneFct scenefunc;

        static int m_width;
        static int m_height;

        static GLFWwindow *m_glfw_window;
        static bool m_vsync;

    public:
        static void init(int argc, char **argv, const int width, const int height, const char *name, const bool vsync, const bool maximized = false);

        static void getWindowPos(int &x, int &y);
        static void getWindowSize(int &w, int &h);

        static bool getWindowMaximized();
    };
}