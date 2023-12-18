#include "MiniGL.h"

#ifdef WIN32
#include "windows.h"
#else
#include <cstdio>
#endif

#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
#else
#include "GL/gl.h"
#include "GL/glu.h"
#endif

#include "Utils/Logger.h"

using namespace PBD;

float MiniGL::fovy = 45;
float MiniGL::znear = 0.5f;
float MiniGL::zfar = 1000;

MiniGL::SceneFct MiniGL::scenefunc = nullptr;
MiniGL::IdleFct MiniGL::idlefunc = nullptr;
MiniGL::DestroyFct MiniGL::destroyfunc = nullptr;

int MiniGL::m_width = 0;
int MiniGL::m_height = 0;
Quaternionr MiniGL::m_rotation;
Real MiniGL::m_zoom = 1.0;
Vector3r MiniGL::m_translation;

std::vector<MiniGL::KeyFunction> MiniGL::keyfunc;
int MiniGL::drawMode = GL_FILL;
unsigned char MiniGL::texData[IMAGE_ROWS][IMAGE_COLS][3];
unsigned int MiniGL::m_texId = 0;

GLint MiniGL::m_context_major_version = 0;
GLint MiniGL::m_context_minor_version = 0;
GLint MiniGL::m_context_profile = 0;

GLUquadricObj *MiniGL::m_sphereQuadric = nullptr;
std::vector<MiniGL::ReshapeFct> MiniGL::m_reshapeFct;
std::vector<MiniGL::KeyboardFct> MiniGL::m_keyboardFct;
std::vector<MiniGL::CharFct> MiniGL::m_charFct;
std::vector<MiniGL::MousePressFct> MiniGL::m_mousePressFct;
std::vector<MiniGL::MouseMoveFct> MiniGL::m_mouseMoveFct;
std::vector<MiniGL::MouseWheelFct> MiniGL::m_mouseWheelFct;
GLFWwindow *MiniGL::m_glfw_window = nullptr;
std::vector<MiniGL::Triangle> MiniGL::m_drawTriangle;
std::vector<MiniGL::Line> MiniGL::m_drawLines;
std::vector<MiniGL::Point> MiniGL::m_drawPoints;
bool MiniGL::m_vsync = false;
double MiniGL::m_lastTime;

void MiniGL::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, MiniGL::m_texId);
}
void MiniGL::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void MiniGL::getOpenGLVersion(int &major_version, int &minor_version)
{
    sscanf((const char *)glGetString(GL_VERSION), "%d.%d", &major_version, &minor_version);
}

void MiniGL::coordinateSystem()
{
    Eigen::Vector3f a(0, 0, 0);
    Eigen::Vector3f b(2, 0, 0);
    Eigen::Vector3f c(0, 2, 0);
    Eigen::Vector3f d(0, 0, 2);

    float diffcolor[4] = {1, 0, 0, 1};
    float speccolor[4] = {1, 1, 1, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speccolor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);
    glLineWidth(2);

    glBegin(GL_LINES);
    glVertex3fv(&a[0]);
    glVertex3fv(&b[0]);
    glEnd();

    float diffcolor2[4] = {0, 1, 0, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffcolor2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffcolor2);

    glBegin(GL_LINES);
    glVertex3fv(&a[0]);
    glVertex3fv(&c[0]);
    glEnd();

    float diffcolor3[4] = {0, 0, 1, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffcolor3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffcolor3);

    glBegin(GL_LINES);
    glVertex3fv(&a[0]);
    glVertex3fv(&d[0]);
    glEnd();
    glLineWidth(1);
}

void MiniGL::drawVector(const Vector3r &a, const Vector3r &b, const float w, float *color)
{
    float speccolor[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speccolor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);
    glColor3fv(color);

    glLineWidth(w);

    glBegin(GL_LINES);
    glVertex3v(&a[0]);
    glVertex3v(&b[0]);
    glEnd();

    glLineWidth(1);
}

void MiniGL::drawCylinder(const Vector3r &a, const Vector3r &b, const float *color, const float radius, const unsigned int subdivisions)
{
    float speccolor[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speccolor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);
    glColor3fv(color);

    Real vx = (b.x() - a.x());
    Real vy = (b.y() - a.y());
    Real vz = (b.z() - a.z());
    // handle the degenerate case with an approximation
    if (vz == 0)
        vz = .00000001;
    Real v = sqrt(vx * vx + vy * vy + vz * vz);
    Real ax = static_cast<Real>(57.2957795) * acos(vz / v);
    if (vz < 0.0)
        ax = -ax;
    Real rx = -vy * vz;
    Real ry = vx * vz;

    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);

    glPushMatrix();
    glTranslatef((float)a.x(), (float)a.y(), (float)a.z());
    glRotatef((float)ax, (float)rx, (float)ry, 0.0f);
    // draw the cylinder
    gluCylinder(quadric, radius, radius, v, subdivisions, 1);
    gluQuadricOrientation(quadric, GLU_INSIDE);
    // draw the first cap
    gluDisk(quadric, 0.0, radius, subdivisions, 1);
    glTranslatef(0, 0, (float)v);
    // draw the second cap
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluDisk(quadric, 0.0, radius, subdivisions, 1);
    glPopMatrix();

    gluDeleteQuadric(quadric);
}

void MiniGL::drawSphere(const Vector3r &translation, float radius, float *color, const unsigned int subDivision)
{
    float speccolor[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speccolor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);
    glColor3fv(color);

    if (m_sphereQuadric == nullptr)
    {
        m_sphereQuadric = gluNewQuadric();
        gluQuadricNormals(m_sphereQuadric, GLU_SMOOTH);
    }

    glPushMatrix();
    glTranslated((translation)[0], (translation)[1], (translation)[2]);

    gluSphere(m_sphereQuadric, radius, subDivision, subDivision);
    glPopMatrix();
}

void MiniGL::drawPoint(const Vector3r &translation, const float pointSize, const float *const color)
{
    float speccolor[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speccolor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);
    glColor3fv(color);

    glPointSize(pointSize);

    glBegin(GL_POINTS);
    glVertex3v(&translation[0]);
    glEnd();

    glPointSize(1);
}

void MiniGL::drawTriangle(const Vector3r &a, const Vector3r &b, const Vector3r &c, const Vector3r &norm, float *color)
{
    float speccolor[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speccolor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

    glBegin(GL_TRIANGLES);
    glNormal3v(&norm[0]);
    glVertex3v(&a[0]);
    glVertex3v(&b[0]);
    glVertex3v(&c[0]);
    glEnd();
}

void MiniGL::drawGrid_xz(float *color)
{
    float speccolor[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, speccolor);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

    const int size = 5;

    glBegin(GL_LINES);
    for (int i = -size; i <= size; i++)
    {
        glVertex3f((float)i, 0.0f, (float)-size);
        glVertex3f((float)i, 0.0f, (float)size);
        glVertex3f((float)-size, 0.0f, (float)i);
        glVertex3f((float)size, 0.0f, (float)i);
    }
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex3f((float)-size, 0.0f, 0.0f);
    glVertex3f((float)size, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, (float)-size);
    glVertex3f(0.0f, 0.0f, (float)size);
    glEnd();
}

void MiniGL::setViewport(float pfovy, float pznear, float pzfar, const Vector3r &peyepoint, const Vector3r &plookat)
{
    fovy = pfovy;
    znear = pznear;
    zfar = pzfar;

    glLoadIdentity();
    gluLookAt(peyepoint[0], peyepoint[1], peyepoint[2], plookat[0], plookat[1], plookat[2], 0, 1, 0);

    Matrix4r transformation;
    Real *lookAtMatrix = transformation.data();
    glGetRealv(GL_MODELVIEW_MATRIX, &lookAtMatrix[0]);

    Matrix3r rot;
    Vector3r scale;

    rot.row(0) = Vector3r(transformation(0, 0), transformation(0, 1), transformation(0, 2));
    rot.row(1) = Vector3r(transformation(1, 0), transformation(1, 1), transformation(1, 2));
    rot.row(2) = Vector3r(transformation(2, 0), transformation(2, 1), transformation(2, 2));
    scale[0] = rot.col(0).norm();
    scale[1] = rot.col(1).norm();
    scale[2] = rot.col(2).norm();
    m_translation = Vector3r(transformation(0, 3), transformation(1, 3), transformation(2, 3));

    rot.col(0) = 1.0 / scale[0] * rot.col(0);
    rot.col(1) = 1.0 / scale[1] * rot.col(1);
    rot.col(2) = 1.0 / scale[2] * rot.col(2);

    m_zoom = scale[0];
    m_rotation = Quaternionr(rot);

    glLoadIdentity();
}

void MiniGL::setViewport(float pfovy, float pznear, float pzfar)
{
    fovy = pfovy;
    znear = pznear;
    zfar = pzfar;
}

void MiniGL::setClientSceneFunc(SceneFct func)
{
    scenefunc = func;
}

void MiniGL::init(int argc, char **argv, const int width, const int height, const char *name, const bool vsync, const bool maximized)
{
    fovy = 60;
    znear = 0.5f;
    zfar = 1000;

    m_width = width;
    m_height = height;
    m_vsync = vsync;

    scenefunc = nullptr;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (maximized)
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    if (m_vsync)
        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    else
        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);

    m_glfw_window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!m_glfw_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_glfw_window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(0);

    glfwSetFramebufferSizeCallback(m_glfw_window, reshape);

    getOpenGLVersion(m_context_major_version, m_context_minor_version);
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &m_context_profile);

    LOG_INFO << "OpenGL version " << m_context_major_version << "." << m_context_minor_version;
    LOG_INFO << "Vendor: " << glGetString(GL_VENDOR);
    LOG_INFO << "Renderer: " << glGetString(GL_RENDERER);
    LOG_INFO << "Version: " << glGetString(GL_VERSION);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    // glfwSetKeyCallback(m_glfw_window, keyboard);
    // glfwSetCharCallback(m_glfw_window, char_callback);
    // glfwSetMouseButtonCallback(m_glfw_window, mousePress);
    // glfwSetCursorPosCallback(m_glfw_window, mouseMove);
    // glfwSetScrollCallback(m_glfw_window, mouseWheel);

    int w, h;
    glfwGetWindowSize(m_glfw_window, &w, &h);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    m_lastTime = glfwGetTime();
}

void MiniGL::initTexture()
{
    int value;
    for (int row = 0; row < IMAGE_ROWS; row++)
    {
        for (int col = 0; col < IMAGE_COLS; col++)
        {
            if (((row & 0x8) == 0) ^ ((col & 0x8) == 0))
                value = 192;
            else
                value = 128;
            // 			// Each cell is 8x8, value is 0 or 255 (black or white)
            // 			value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
            texData[row][col][0] = (GLubyte)value;
            texData[row][col][1] = (GLubyte)value;
            texData[row][col][2] = (GLubyte)value;
        }
    }

    glGenTextures(1, &m_texId);
    glBindTexture(GL_TEXTURE_2D, m_texId);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, texData); // Create texture from image data
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glEnable(GL_TEXTURE_2D); // Enable 2D texture

    // Correct texture distortion in perpective projection
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void MiniGL::destroy()
{
    gluDeleteQuadric(m_sphereQuadric);
}

void MiniGL::reshape(GLFWwindow *glfw_window, int w, int h)
{
    if ((w > 0) && (h > 0))
    {
        m_width = w;
        m_height = h;

        for (auto i = 0; i < m_reshapeFct.size(); i++)
            m_reshapeFct[i](m_width, m_height);
        glViewport(0, 0, m_width, m_height);
    }
}

void MiniGL::setClientIdleFunc(IdleFct func)
{
    idlefunc = func;
}

void MiniGL::setClientDestroyFunc(DestroyFct func)
{
    destroyfunc = func;
}

void MiniGL::addKeyFunc(unsigned char k, std::function<void()> const &func)
{
    if (func == nullptr)
        return;
    else
        keyfunc.push_back({func, k});
}

void MiniGL::setProjectionMatrix(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, (Real)width / (Real)height, znear, zfar);
}

void MiniGL::viewport()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRenderMode(GL_RENDER);
    glfwGetFramebufferSize(m_glfw_window, &m_width, &m_height);
    glViewport(0, 0, m_width, m_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setProjectionMatrix(m_width, m_height);
    glMatrixMode(GL_MODELVIEW);

    glTranslatef((float)m_translation[0], (float)m_translation[1], (float)m_translation[2]);
    Matrix3r rot;
    rot = m_rotation.toRotationMatrix();
    Matrix4r transform(Matrix4r::Identity());
    Vector3r scale(m_zoom, m_zoom, m_zoom);
    transform.block<3, 3>(0, 0) = rot;
    transform.block<3, 1>(0, 3) = m_translation;
    transform(0, 0) *= scale[0];
    transform(1, 1) *= scale[1];
    transform(2, 2) *= scale[2];
    Real *transformMatrix = transform.data();
    glLoadMatrix(&transformMatrix[0]);
}

void MiniGL::initLights()
{
    float t = 0.9f;
    float a = 0.2f;
    float amb0[4] = {a, a, a, 1};
    float diff0[4] = {t, 0, 0, 1};
    float spec0[4] = {1, 1, 1, 1};
    float pos0[4] = {-10, 10, 10, 1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
    glEnable(GL_LIGHT0);

    float amb1[4] = {a, a, a, 1};
    float diff1[4] = {0, 0, t, 1};
    float spec1[4] = {1, 1, 1, 1};
    float pos1[4] = {10, 10, 10, 1};
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);
    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    glEnable(GL_LIGHT1);

    float amb2[4] = {a, a, a, 1};
    float diff2[4] = {0, t, 0, 1};
    float spec2[4] = {1, 1, 1, 1};
    float pos2[4] = {0, 10, 10, 1};
    glLightfv(GL_LIGHT2, GL_AMBIENT, amb2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diff2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spec2);
    glLightfv(GL_LIGHT2, GL_POSITION, pos2);
    glEnable(GL_LIGHT2);

    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
}

bool MiniGL::checkOpenGLVersion(const int major_version, const int minor_version)
{
    if ((m_context_major_version > major_version) ||
        ((m_context_major_version == major_version) && (m_context_minor_version >= minor_version)))
        return true;
    return false;
}

void MiniGL::drawElements()
{
    for (unsigned int i = 0; i < m_drawLines.size(); i++)
    {
        Line &l = m_drawLines[i];
        drawVector(l.a, l.b, l.lineWidth, l.color);
    }
    for (unsigned int i = 0; i < m_drawTriangle.size(); i++)
    {
        Triangle &t = m_drawTriangle[i];
        Vector3r n = ((t.b - t.a).cross(t.c - t.a));
        n.normalize();
        drawTriangle(t.a, t.b, t.c, n, t.color);
    }
    for (unsigned int i = 0; i < m_drawPoints.size(); i++)
    {
        Point &p = m_drawPoints[i];
        drawSphere(p.a, p.pointSize, p.color);
    }
}

void MiniGL::error_callback(int error, const char *description)
{
    LOG_ERR << description;
}

void MiniGL::mainLoop()
{
    while (!glfwWindowShouldClose(m_glfw_window))
    {
        if (idlefunc != nullptr)
            idlefunc();

        double currentTime = glfwGetTime();
        if (currentTime - m_lastTime >= 1.0 / 60.0) // render at maximum at 60 fps
        {
            glfwPollEvents();

            glPolygonMode(GL_FRONT_AND_BACK, drawMode);
            viewport();

            drawElements();

            if (scenefunc != nullptr)
                scenefunc();

            if (m_vsync)
                glfwSwapBuffers(m_glfw_window);
            else
                glFlush();
            m_lastTime = currentTime;
        }
    }

    if (destroyfunc != nullptr)
    {
        destroyfunc();
    }

    glfwDestroyWindow(m_glfw_window);

    glfwTerminate();

    destroy();
}

void MiniGL::getWindowPos(int &x, int &y)
{
    glfwGetWindowPos(m_glfw_window, &x, &y);
}

void MiniGL::getWindowSize(int &w, int &h)
{
    glfwGetWindowSize(m_glfw_window, &w, &h);
}
void MiniGL::setWindowPos(int x, int y)
{
    glfwSetWindowPos(m_glfw_window, x, y);
}

void MiniGL::setWindowSize(int w, int h)
{
    glfwSetWindowSize(m_glfw_window, w, h);
}

bool MiniGL::getWindowMaximized()
{
    return glfwGetWindowAttrib(m_glfw_window, GLFW_MAXIMIZED);
}