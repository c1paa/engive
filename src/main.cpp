#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <vector>

#include "../src/render/renderer.h"


using namespace std;
using namespace glm;

int main() {
    if (!glfwInit()) {
        std::cerr << "ERROR: Init GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Engive fps: 0", nullptr, nullptr);
    if (!window) {
        std::cerr << "ERROR: Creating window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ERROR: Init GLAD" << std::endl;
        return -1;
    }

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    float vertices1[] = {
        -0.2f, 1.0f, 0.0f,
        -0.2f, -1.0f, 0.0f,
        0.2f, 1.0f, 0.0f,
    };

    float vertices2[] = {
        0.2f, 1.0f, 0.0f,
        -0.2f, -1.0f, 0.0f,
        0.2f, -1.0f, 0.0f,
    };

    float vertices3[] = {
        -0.6f, -0.6f, 0.0f,
        0.6f, -0.6f, 0.0f,
        0.6f, -1.0f, 0.0f,
    };

    float vertices4[] = {
        -0.6f, -1.0f, 0.0f,
        -0.6f, -0.6f, 0.0f,
        0.6f, -1.0f, 0.0f,
    };

    float verticesUV[] = {
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.9f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.9f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.6f, 0.0f, 0.0f, 1.0f, 0.5f,
    };
    vector<float> vertices6 = {
        -0.5f, 0.5f, 0.0f, 0.1f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, -0.3f, 0.0f,
        -0.8f, 0.0f, 0.0f, 0.0f, 0.5f
    };
    vector<Point> vp = {
        Point(-0.5f, 0.5f, 0.0f, 0.0f, 1.0f),
        Point(0.0f, 0.6f, 0.0f, 0.0f, 1.0f),
        Point(0.5f, 0.5f, 0.0f, 1.0f, 1.0f),
        Point(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
        Point(0.0f, -0.6f, 0.0f, 1.0f, 0.0f),
        Point(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f),
        Point(0.1f, 0.0f, 0.0f, 0.0f, 0.5f)
    };

    vector<Point> vp2 = {
        Point(100.0f, 500.0f, 0.0f, 0.0f, 1.0f),
        Point(500.0f, 500.0f, 0.0f, 1.0f, 1.0f),
        Point(500.0f, 100.0f, 0.0f, 1.0f, 0.0f),
        Point(100.0f, 100.0f, 0.0f, 0.0f, 0.0f),
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        1, 2, 3    // second triangle
    };




    //  - 1. refactoring, coments
    //  -  2. - point, rectangle, ellipse
    //   3. shape
    //  - 4. settexturepos
    //   5. text button input cursor
    //   6. ECS types
    //  - 7. - pixels


    // https://learnopengl.com/Getting-started/Textures









    Renderer renderer(window);


    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) {
            double fps = double(nbFrames) / (currentTime - lastTime);
            stringstream ss;
            ss << "Engive fps: " << int(fps);
            glfwSetWindowTitle(window, ss.str().c_str());

            nbFrames = 0;
            lastTime = currentTime;
        }

        // Очистка экрана
        glClear(GL_COLOR_BUFFER_BIT);

        float color[] = {1, 1, 1};
        float color2[] = {0, 1, 1};
        ColorRGBA color3(1, 1, 0);

        // renderer.DrawTriangle(vertices1, color);
        // renderer.DrawPoligon(verticesUV, indices, "../src/textures/pig.jpg");
        // renderer.DrawShape(vertices6, "../src/textures/wall.jpg");
        // renderer.DrawShape(vertices6, color2);

        Shape shape(vp2, "../src/textures/wall.jpg");
        shape.color = color3;
        Point p1(100.0f, 100.0f, 0.0f, 0.0f, 0.0f);
        Point p2(500.0f, 500.0f, 5.0f, 1.0f, 1.0f);
        shape.SetTexturePosition(p1, p2);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        renderer.DrawShape(shape, COLOR_DRAWTYPE, trans);

        // Меняем буферы (движок окон)
        glfwSwapBuffers(window);
        glfwPollEvents();



        // glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);

        // glfwSwapBuffers(window);
        // glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
