#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"

#include <string>

// Window
Window *window;
static int g_windowWidth = 640;
static int g_windowHeight = 640;
std::string title = "Position Based Dynamics";

int main()
{
    try
    {
        // todo
        /**
         * 1. init the window
         * 2. init the scene: including the simulating object
         * 3. setting the iteration loop
         * 4. solver for animation
         */
        window = new Window(g_windowWidth, g_windowHeight, title.c_str());
        window->render();

        return 0;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Position Based Dynamics" << std::endl;
}