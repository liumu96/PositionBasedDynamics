#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window
{
private:
    int width;
    int height;
    const char *title;
    GLFWwindow *window;

public:
    Window(int width, int height, const char *);

    void initWindow();

    void render();

    void processInput();
};