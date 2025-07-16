#include <GLFW/glfw3.h>

class Input {
private:
    Input() = delete;
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

public:
    static bool keys[1024];
    static double mouseX, mouseY;
    static bool cursorCatch;

    static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

};