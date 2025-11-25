#include "window.h"
#include <GLFW/glfw3.h>


Window::Window()
{
    
}


void Window::framebufferResizeCallback(GLFWwindow *window, int width, int height)
{
    auto lveWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    lveWindow->framebufferResized = true;
    lveWindow->width = width;
    lveWindow->height = height;
}

bool Window::wasWindowResized()
{
    return framebufferResized ;
}

void Window::resetWindowResizedFlag()
{
     framebufferResized = false ;
}
