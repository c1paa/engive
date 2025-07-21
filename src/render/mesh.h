#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    unsigned int id;
    string type;
};

class Mesh {
    public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector <Texture> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        initMesh();
    };

    private:
    unsigned int VAO, VBO, EBO;
    void initMesh() {
        glGenVertexArrays(1, &VAO);    // создаём VAO
        glGenBuffers(1, &VBO);         // создаём VBO
        glGenBuffers(1, &EBO);         // создаём EBO

        glBindVertexArray(VAO);                                 // активируем VAO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);         // активируем VBO

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  // копируем данные вершин в VBO

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);                                  // активируем EBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),       // копируем данные порядка рисовки полигонов в EBO
                     &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);	                                                                        // включаем атрибут
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);    // задаем атрибут
        // говорим OpenGL, как читать вершины: атрибут 0, 3 компоненты float, без нормализации, шаг sizeof(Vertex), смещение 0

        // vertex normals
        glEnableVertexAttribArray(1);                                                                                               // включаем атрибут
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));  // задаем атрибут
        // offsetof - возвращает смещение в байтах указанной структуры, до переменной, переданной во втором аргументе

        // vertex texture coords
        glEnableVertexAttribArray(2);                                                                                                  // включаем атрибут
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));  // задаем атрибут

        glBindVertexArray(0);    // отвязываем VAO
    }

};