#pragma once

#include <iostream>
#include <string>

#include "light.h"

class Shader {
    public:

    unsigned int ID;

    Shader(string vertexPath, string fragmentPath) {
        GenerateTextureShader(vertexPath, fragmentPath);
    }



    void GenerateTextureShader(string vertexPath, string fragmentPath) {
        string vertexSource = readFile(vertexPath.c_str());         // вертексный шейдер
        const char* vertexShaderSource = vertexSource.c_str();
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        // Проверка ошибок компиляции
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "Ошибка компиляции вершинного шейдера:\n" << infoLog << std::endl;
        }

        string fragmentSource = readFile(fragmentPath.c_str());     // фрагментный шейдер
        const char* fragmentShaderSource = fragmentSource.c_str();
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        // Проверка ошибок
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "Ошибка компиляции фрагментного шейдера:\n" << infoLog << std::endl;
        }

        ID = glCreateProgram();     // создание программы шейдеров
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

        // Проверка ошибок линковки
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            std::cerr << "Ошибка линковки шейдерной программы:\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);     // удаляем шейдеры (отдельные)
        glDeleteShader(fragmentShader);
    }

    void SetInt(const char* name, int value) {
        GLint valueLoc = glGetUniformLocation(ID, name);
        glUniform1i(valueLoc, value);
    }
    void SetInt(string name, int value) {
        SetInt(name.c_str(), value);
    }
    void SetFloat(const char* name, float value) {
        GLint valueLoc = glGetUniformLocation(ID, name);
        glUniform1f(valueLoc, value);
    }
    void SetFloat(string name, float value) {
        SetFloat(name.c_str(), value);
    }
    void SetVec3(const char* name, glm::vec3 value) {
        GLint valueLoc = glGetUniformLocation(ID, name);
        glUniform3f(valueLoc, value.x, value.y, value.z);
    }
    void SetVec3(string name, glm::vec3 value) {
        SetVec3(name.c_str(), value);
    }
    void SetDirLight(const char* name, DirLight value) {
        SetVec3((string(name)+".direction").c_str(), value.direction);
        SetVec3((string(name)+".ambient").c_str(), value.ambient);
        SetVec3((string(name)+".diffuse").c_str(), value.diffuse);
        SetVec3((string(name)+".specular").c_str(), value.specular);
    }
    void SetDirLight(string name, DirLight value) {
        SetDirLight(name.c_str(), value);
    }
    void SetPointLight(const char* name, PointLight value) {
        SetVec3((string(name)+".position").c_str(), value.position);
        SetFloat((string(name)+".constant").c_str(), value.constant);
        SetFloat((string(name)+".linear").c_str(), value.linear);
        SetFloat((string(name)+".quadratic").c_str(), value.quadratic);
        SetVec3((string(name)+".ambient").c_str(), value.ambient);
        SetVec3((string(name)+".diffuse").c_str(), value.diffuse);
        SetVec3( (string(name)+".specular").c_str(), value.specular);
    }
    void SetPointLight(string name, PointLight value) {
        SetPointLight(name.c_str(), value);
    }


    private:
    // Чтение данных из файлов, используется для шейдеров
    string readFile(const char* filepath) {
        ifstream file;
        stringstream buffer;

        file.open(filepath);
        if (!file.is_open()) {
            cerr << "Не удалось открыть файл: " << filepath << std::endl;
            return "";
        }

        buffer << file.rdbuf();
        file.close();

        return buffer.str();
    }
};