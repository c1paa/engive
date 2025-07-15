#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "point.h"
#include "shape.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;


class Renderer {
    public:

    // Рисование полигона по трем вершинам с определенным цветом
    void DrawPoligon(float* vertices, float* color, unsigned int* indices = new unsigned int[3]{0, 1, 2}, int vertices_size = 3, int indices_size = 1) {
        GLuint VAO, VBO;
        unsigned int EBO;

        glGenBuffers(1, &EBO);      // создаем EBO
        glGenVertexArrays(1, &VAO);  // создаём VAO
        glGenBuffers(1, &VBO);       // создаём VBO

        glBindVertexArray(VAO);      // активируем VAO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);           // активируем VBO
        glBufferData(GL_ARRAY_BUFFER, vertices_size * 3 * sizeof(float), vertices, GL_STATIC_DRAW);  // копируем данные вершин в VBO

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);       // активируем EBO
        // копируем данные порядка рисовки полигонов в VBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        // говорим OpenGL, как читать вершины: атрибут 0, 3 компоненты float, без нормализации, шаг 3 float, смещение 0
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  // включаем этот атрибут

        glBindBuffer(GL_ARRAY_BUFFER, 0);  // отвязываем VBO
        glBindVertexArray(0);              // отвязываем VAO

        // shaders ====================================================================================

        string vertexSource = readFile("../src/shaders/poligon_color.vert");         // вертексный шейдер
        const char* vertexShaderSource = vertexSource.c_str();
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        // проверка ошибок компиляции
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "Ошибка компиляции вершинного шейдера:\n" << infoLog << std::endl;
        }

        string fragmentSource = readFile("../src/shaders/poligon_color.frag");     // фрагментный шейдер
        const char* fragmentShaderSource = fragmentSource.c_str();
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        // проверка ошибок
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "Ошибка компиляции фрагментного шейдера:\n" << infoLog << std::endl;
        }

        unsigned int shaderProgram = glCreateProgram();     // создание программы шейдеров
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // проверка ошибок линковки
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "Ошибка линковки шейдерной программы:\n" << infoLog << std::endl;
        }

        // Draw =====================================================================================================

        // Используем шейдеры
        glUseProgram(shaderProgram);

        // задаем цвет
        int colorLocation = glGetUniformLocation(shaderProgram, "uColor");
        glUniform3f(colorLocation, color[0], color[1], color[2]);

        // Привязываем VAO с треугольником
        glBindVertexArray(VAO);

        // Рисуем треугольник
        glDrawElements(GL_TRIANGLES, indices_size * 3, GL_UNSIGNED_INT, 0);

        // glDeleteBuffers(1, &VBO);            // удаляем VBO
        // glDeleteVertexArrays(1, &VAO);       // удаляем VAO

        glDeleteShader(vertexShader);     // удаляем шейдеры (отдельные)
        glDeleteShader(fragmentShader);

    }


    //  Метод для рисования фигуры по вершинам с определенным цветом
    void DrawShape(vector<float> vertices, float* color) {
        vector<unsigned int> indices(0);
        for (int i = 1; i < vertices.size()/3-1; i++) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i+1);
        }
        DrawPoligon(vertices.data(), color, indices.data(), vertices.size()/3, indices.size()/3);
    }




    void DrawPoligon(float* vertices, unsigned int* indices, string texturePath, int vertices_size = 3, int indices_size = 1) {
        GLuint VAO, VBO;
        unsigned int EBO;

        glGenBuffers(1, &EBO);       // создаём EBO
        glGenVertexArrays(1, &VAO);  // создаём VAO
        glGenBuffers(1, &VBO);       // создаём VBO

        glBindVertexArray(VAO);      // активируем VAO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);           // активируем VBO
        glBufferData(GL_ARRAY_BUFFER, vertices_size * 5 * sizeof(float), vertices, GL_STATIC_DRAW);  // копируем данные вершин в VBO

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);       // активируем EBO
        //   копируем данные порядка рисовки полигонов в EBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        // говорим OpenGL, как читать вершины: атрибут 0, 3 компоненты float, без нормализации, шаг 3 float, смещение 0
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  // включаем этот атрибут

        // говорим OpenGL, как читать вершины: атрибут 0, 3 компоненты float, без нормализации, шаг 3 float, смещение 0
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);  // включаем этот атрибут

        glBindBuffer(GL_ARRAY_BUFFER, 0);  // отвязываем VBO
        glBindVertexArray(0);              // отвязываем VAO

        // texture ===============================================================================================

        unsigned int texture;   // подключение тектуры
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // параметры обёртки и фильтрации
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // загрузка изображения
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // переворот, чтобы не было вверх ногами
        unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture " << stbi_failure_reason() << std::endl;
        }
        stbi_image_free(data);


        // shaders ===========================================================================


        string vertexSource = readFile("../src/shaders/poligon_texture.vert");         // вертексный шейдер
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

        string fragmentSource = readFile("../src/shaders/poligon_texture.frag");     // фрагментный шейдер
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

        unsigned int shaderProgram = glCreateProgram();     // создание программы шейдеров
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Проверка ошибок линковки
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << "Ошибка линковки шейдерной программы:\n" << infoLog << std::endl;
        }

        // Draw =============================================================================================

        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(shaderProgram);

        glDeleteShader(vertexShader);     // удаляем шейдеры (отдельные)
        glDeleteShader(fragmentShader);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices_size * 3, GL_UNSIGNED_INT, 0);

        // glDeleteBuffers(1, &VBO);            // удаляем VBO
        // glDeleteVertexArrays(1, &VAO);       // удаляем VAO
    }



    // Метод наложения картинки на фигура по вершинам
    // Лучше использовать для прямоугольников
    void DrawShape(vector<float> vertices, string texturePath) {
        vector<unsigned int> indices(0);
        for (int i = 1; i < vertices.size()-1; i++) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i+1);
        }
        DrawPoligon(vertices.data(), indices.data(), texturePath, vertices.size()/5, indices.size()/3);
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