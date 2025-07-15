#pragma once

#include <vector>
#include <string>

#include <iostream>

#include "../colorRGBA.h"

using namespace std;

class DrawFigure {
    public:

    vector <float> vertices;
    string texturePath;
    ColorRGBA color;

    bool IsTextureType = false;

    DrawFigure (vector<Point> vertices_, ColorRGBA color_) {
        for (int i = 0; i < vertices_.size(); i++) {
            this->vertices.push_back(vertices_[i].x);
            this->vertices.push_back(vertices_[i].y);
            this->vertices.push_back(vertices_[i].z);
        }
        this->color = color_;
        IsTextureType = false;
    }

    DrawFigure (vector<Point> vertices_, string texturePath_) {
        for (int i = 0; i < vertices_.size(); i++) {
            this->vertices.push_back(vertices_[i].x);
            this->vertices.push_back(vertices_[i].y);
            this->vertices.push_back(vertices_[i].z);
            this->vertices.push_back(vertices_[i].u);
            this->vertices.push_back(vertices_[i].v);
        }
        this->texturePath = texturePath_;
        IsTextureType = true;
    }

};
