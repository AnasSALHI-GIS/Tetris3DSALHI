#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window{
public:
    Window();
    static void framebufferResizeCallback(GLFWwindow *window, int width, int height);
    bool wasWindowResized();
    void resetWindowResizedFlag();
    int width, height;

private:
    bool framebufferResized = false;
    


};
    
#endif