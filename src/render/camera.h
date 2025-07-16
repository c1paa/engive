#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>

#include "input.h"


// #include "input.h"

using namespace std;
using namespace glm;


class Camera {
    public:
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    float yaw;
    float pitch;
    bool firstMouse = true;
    double lastX, lastY;
    Camera(){}
    Camera(vec3 position, vec3 front) {
        this->position = position;
        this->front = front;
        up = vec3(0, 1, 0);
    }
    mat4 LookAt() {
        return lookAt(position, position + front, up);
    }
    void update_callbacks(GLfloat deltatime)
    {
        // WASD
        GLfloat cameraSpeed = 2.0f * deltatime;
        if(Input::keys[GLFW_KEY_W])
            position += cameraSpeed * front;
        if(Input::keys[GLFW_KEY_S])
            position -= cameraSpeed * front;
        if(Input::keys[GLFW_KEY_A])
            position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
        if(Input::keys[GLFW_KEY_D])
            position += glm::normalize(glm::cross(front, up)) * cameraSpeed;

        mouse_callback(Input::mouseX, Input::mouseY);
    }

    void mouse_callback(double xpos, double ypos)
    {
        if(firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        GLfloat sensitivity = 0.05;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 frontv;
        frontv.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        frontv.y = sin(glm::radians(pitch));
        frontv.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(frontv);
    }
};