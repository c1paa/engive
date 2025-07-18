#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "point.h"
#include "shape.h"
#include "colorRGBA.h"
#include "camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using namespace glm;

class Renderer {
    public:

    GLFWwindow* window;
    Camera& camera;
    unsigned int textureShader, colorShader;

    Renderer(GLFWwindow* window, Camera& camera):camera(camera){
        this->window = window;
        textureShader = GenerateTextureShader();
        colorShader = GenerateColorShader();
    }

    unsigned int GenerateTextureShader() {
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
        glDeleteShader(vertexShader);     // удаляем шейдеры (отдельные)
        glDeleteShader(fragmentShader);
        return shaderProgram;
    }

    unsigned int GenerateColorShader() {
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
        glDeleteShader(vertexShader);     // удаляем шейдеры (отдельные)
        glDeleteShader(fragmentShader);
        return shaderProgram;
    }

    // Рисование полигона по трем вершинам с определенным цветом
    void DrawPoligon(float* vertices, float* color, unsigned int* indices, int vertices_size = 3, int indices_size = 1, mat4 trans = mat4(1.0f)) {
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

                // Draw =====================================================================================================

        // Используем шейдеры
        glUseProgram(colorShader);

        // задаем цвет
        int colorLocation = glGetUniformLocation(colorShader, "uColor");
        glUniform4f(colorLocation, color[0], color[1], color[2], color[3]);

        unsigned int transformLoc = glGetUniformLocation(colorShader, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        // unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        //
        // unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        //
        // unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        // glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Привязываем VAO с треугольником
        glBindVertexArray(VAO);

        // Рисуем треугольник
        glDrawElements(GL_TRIANGLES, indices_size * 3, GL_UNSIGNED_INT, 0);

        glDeleteBuffers(1, &VBO);            // удаляем VBO
        glDeleteVertexArrays(1, &VAO);       // удаляем VAO
        glDeleteBuffers(1, &EBO);

        glBindVertexArray(0);
        glUseProgram(0);
    }


    //  Метод для рисования фигуры по вершинам с определенным цветом
    void DrawShape(vector<float> vertices, float* color, mat4 trans = mat4(1.0f)) {
        vector<unsigned int> indices(0);
        indices = GenerateIndices(vertices, 3);
        DrawPoligon(vertices.data(), color, indices.data(), vertices.size()/3, indices.size()/3, trans);
    }




    void DrawPoligon(float* vertices, unsigned int* indices, string texturePath, int vertices_size = 3, int indices_size = 1, mat4 trans = mat4(1.0f)) {
        //glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        //model = rotate(model, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));
       // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        mat4 view = camera.LookAt();
        int window_width, window_height;
        glfwGetFramebufferSize(window, &window_width, &window_height); // Получаем актуальный размер окна
        projection = glm::perspective(glm::radians(60.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);



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

        // Draw =============================================================================================

        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(textureShader);

        unsigned int transformLoc = glGetUniformLocation(textureShader, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        // unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        unsigned int viewLoc = glGetUniformLocation(textureShader, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        unsigned int projectionLoc = glGetUniformLocation(textureShader, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, indices_size * 3, GL_UNSIGNED_INT, 0);
       // glDrawArrays(GL_TRIANGLES, 0, 36);
        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            unsigned int modelLoc = glGetUniformLocation(textureShader, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glDeleteBuffers(1, &VBO);            // удаляем VBO
        glDeleteVertexArrays(1, &VAO);       // удаляем VAO
        glDeleteBuffers(1, &EBO);
        glDeleteTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
        glUseProgram(0);

    }



    // Метод наложения картинки на фигура по вершинам
    // Лучше использовать для прямоугольников
    void DrawShape(vector<float> vertices, string texturePath) {
        vector<unsigned int> indices(0);
        indices = GenerateIndices(vertices, 5);
        DrawPoligon(vertices.data(), indices.data(), texturePath, vertices.size()/5, indices.size()/3);
    }


#define COLOR_DRAWTYPE true
#define TEXTURE_DRAWTYPE false

    void DrawShape(Shape shape, bool drawType = COLOR_DRAWTYPE, mat4 trans = mat4(1.0f)) {
        vector <float> vertices;
        vector <Point> vertices_ = shape.vertices;
        if (drawType) {
            for (int i = 0; i < vertices_.size(); i++) {
                vertices.push_back(vertices_[i].x);
                vertices.push_back(vertices_[i].y);
                vertices.push_back(vertices_[i].z);
            }
            DrawShape(vertices, shape.color, trans);
        } else {
            for (int i = 0; i < vertices_.size(); i++) {
                vertices.push_back(vertices_[i].x);
                vertices.push_back(vertices_[i].y);
                vertices.push_back(vertices_[i].z);
                vertices.push_back(vertices_[i].u);
                vertices.push_back(vertices_[i].v);
            }
            DrawShape(vertices, shape.texturePath);
        }
    }



    private:

    struct Vec2 {
        float x, y;
    };

    // Проверка, в каком направлении обход: >0 — против часовой, <0 — по часовой
    float cross(const Vec2& a, const Vec2& b, const Vec2& c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    // Проверка, находится ли точка p внутри треугольника abc
    bool pointInTriangle(const Vec2& p, const Vec2& a, const Vec2& b, const Vec2& c) {
        float area = fabs(cross(a, b, c));
        float a1 = fabs(cross(p, a, b));
        float a2 = fabs(cross(p, b, c));
        float a3 = fabs(cross(p, c, a));
        return fabs(area - (a1 + a2 + a3)) < 1e-5f;
    }

    vector<unsigned int> GenerateIndices(vector<float> vertices, int vertix_size) {
        int n = vertices.size() / vertix_size;
        if (n < 3) return {};

        // Скопируем вершины в Vec2
        vector<Vec2> points(n);
        for (int i = 0; i < n; ++i) {
            points[i] = {vertices[i * vertix_size], vertices[i * vertix_size + 1]};
        }

        // Начальный порядок вершин
        vector<int> V(n);
        for (int i = 0; i < n; ++i) V[i] = i;

        // Проверим направление обхода
        float sum = 0;
        for (int i = 0; i < n; ++i) {
            Vec2 p0 = points[i];
            Vec2 p1 = points[(i + 1) % n];
            sum += (p1.x - p0.x) * (p1.y + p0.y);
        }
        // Если по часовой, то перевернём
        if (sum > 0) reverse(V.begin(), V.end());

        vector<unsigned int> indices;
        int count = 0;
        while (V.size() > 3 && count < 1000) {
            bool earFound = false;
            for (int i = 0; i < V.size(); ++i) {
                int i0 = V[(i - 1 + V.size()) % V.size()];
                int i1 = V[i];
                int i2 = V[(i + 1) % V.size()];

                Vec2& a = points[i0];
                Vec2& b = points[i1];
                Vec2& c = points[i2];

                if (cross(a, b, c) <= 0) continue;  // невыпуклая вершина — не ухо

                // Проверим, нет ли других точек внутри уха
                bool hasPointInside = false;
                for (int j = 0; j < V.size(); ++j) {
                    int vi = V[j];
                    if (vi == i0 || vi == i1 || vi == i2) continue;
                    if (pointInTriangle(points[vi], a, b, c)) {
                        hasPointInside = true;
                        break;
                    }
                }

                if (hasPointInside) continue;

                // Ухо найдено
                indices.push_back(i0);
                indices.push_back(i1);
                indices.push_back(i2);
                V.erase(V.begin() + i);
                earFound = true;
                break;
            }
            if (!earFound) break; // что-то пошло не так
            count++;
        }

        // Последний треугольник
        if (V.size() == 3) {
            indices.push_back(V[0]);
            indices.push_back(V[1]);
            indices.push_back(V[2]);
        }

        return indices;
    }


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