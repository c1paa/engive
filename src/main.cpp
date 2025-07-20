#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "../src/render/renderer.h"


using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

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
        Point(-0.5f, 0.5f, 0.0f, 0.0f, 1.0f),
        Point(0.5f, 0.5f, 0.0f, 1.0f, 1.0f),
        Point(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
        Point(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f),
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        1, 2, 3    // second triangle
    };

    float cube[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        //
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    float cubeNormalsTextures[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};




    //  - 1. refactoring, coments
    //  -  2. - point, rectangle, ellipse
    //  -  3. shape
    //  - 4. settexturepos
    //   5. text button input cursor
    //   6. ECS types
    //  - 7. - pixels
    //     create poligons assimp
    //     - camera class
    //     - delete ram
    //     - generate shader once
    //     - model view projection understand
    //     - transform?
    //


    // https://learnopengl.com/Getting-started/Textures








    Camera camera(vec3(0, 1, 4), vec3(0, 0, -1));
    Renderer renderer(window, camera);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowUserPointer(window, &camera);
    glfwSetKeyCallback(window, Input::keyboard_callback);
    glfwSetCursorPosCallback(window, Input::mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetKeyCallback(window, key_callback);
    glEnable(GL_DEPTH_TEST);
    GLfloat deltaTime = 0.0f;	// Время, прошедшее между последним и текущим кадром
    GLfloat lastFrame = 0.0f;



    while (!glfwWindowShouldClose(window)) {
        if (Input::cursorCatch)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        glfwPollEvents();
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        stringstream ss;
        ss << "Engive fps: " << int(1.0f / deltaTime);
        glfwSetWindowTitle(window, ss.str().c_str());

        camera.update_callbacks(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Очистка экрана
        glClear(GL_COLOR_BUFFER_BIT);

        float color[] = {0.7f, 0.8f, 0.31f};
        float color2[] = {1, 1, 1};
        Renderer::Material m;
        m.ambient = vec3(1.0f, 0.5f, 0.31f);
        m.diffuse = vec3(1.0f, 0.5f, 0.31f);
        m.specular = vec3(0.5f, 0.5f, 0.5f);
        m.shininess = 32;

        Renderer::Light light;
        light.ambient = vec3(0.2f, 0.2f, 0.2f);
        light.diffuse = vec3(0.5f, 0.5f, 0.5f);
        light.specular = vec3(1.0f, 1.0f, 1.0f);
        light.position = vec3(sin((float)glfwGetTime())*2.0f, 1, cos((float)glfwGetTime())*2.0f);;

        ColorRGBA color3(1, 1, 0);

        // renderer.DrawTriangle(vertices1, color);
        // renderer.DrawPoligon(verticesUV, indices, "../src/textures/pig.jpg");
        // renderer.DrawShape(vertices6, "../src/textures/wall.jpg");
        // renderer.DrawShape(vertices6, color2);

        Shape shape(vp2, "../src/textures/minecraft.jpg");
        shape.color = color3;
        Point p1(100.0f, 100.0f, 0.0f, 0.0f, 0.0f);
        Point p2(500.0f, 500.0f, 5.0f, 1.0f, 1.0f);
        // shape.SetTexturePosition(p1, p2);
        // glm::mat4 trans = glm::mat4(1.0f);
        // trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

        mat4 transLight = glm::mat4(1.0f);
        transLight = glm::translate(transLight, light.position);
        transLight = glm::scale(transLight, glm::vec3(0.2f));
        // mat4 transCube = glm::mat4(1.0f);
        // transCube = rotate(transCube, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        unsigned int a[12];
        renderer.DrawPoligon(cubeNormalsTextures, m, "../src/textures/container.png", "../src/textures/container_specular.png",light, a, 36, 12, renderer.textureShader);
        renderer.DrawPoligon(cubeNormalsTextures, m, light, a, 36, 12, renderer.lightShader, transLight);
        // renderer.DrawPoligon(cube, a, "../src/textures/pig.jpg", 36, 12, mat4(1.0f));
        // Меняем буферы (движок окон)
        glfwSwapBuffers(window);



        // glClearColor(0.5f, 0.2f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);

        // glfwSwapBuffers(window);
        // glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
