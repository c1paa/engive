#include "input.h"
#include <GLFW/glfw3.h>
#include <iostream>

bool Input::keys[1024] = { false };
double Input::mouseX = 0.0;
double Input::mouseY = 0.0;
bool Input::cursorCatch = true;

void Input::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;
    if (action == GLFW_RELEASE && key == GLFW_KEY_ESCAPE)
        Input::cursorCatch = !Input::cursorCatch;
}

void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}