#pragma once

#include <vector>
#include <string>

#include "drawFigure.h"
#include "../colorRGBA.h"

using namespace std;

class Figure {
    public:

    vector<Point> vertices;
    string texturePath;
    ColorRGBA color;

    Figure() {
        this->vertices = vector<Point>();
    }

    Figure(vector<Point> vertices_) {
        this->vertices = vertices_;
    }

    Figure(vector<Point> vertices_, string texturePath_) {
        this->vertices = vertices_;
        this->texturePath = texturePath_;
    }

    Figure(vector<Point> vertices_, ColorRGBA color_) {
        this->vertices = vertices_;
        this->color = color_;
    }

    DrawFigure GetColorDrawFigure() {
        return DrawFigure(this->vertices, this->color);
    }
    DrawFigure GetTextureDrawFigure() {
        return DrawFigure(this->vertices, this->texturePath);
    }

};