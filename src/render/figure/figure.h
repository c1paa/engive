#pragma once

#include <vector>
#include <string>

#include "drawFigure.h"
#include "../colorRGBA.h"
// #define STB_IMAGE_IMPLEMENTATION
// #include "../stb_image.h"

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

    void SetTexturePosition(Point p1, Point p2) {
        int width, height, channels;
        //unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
        cout << endl;
        if (p1.u != p2.u && p1.v != p2.v) {
            float xd = abs(p1.x - p2.x);
            float ud = abs(p1.u - p2.u);
            float w = xd/ud*2;
            //cout << xd << " " << ud << " " << w << endl;
            float yd = abs(p1.y - p2.y);
            float vd = abs(p1.v - p2.v);
            float h = yd/vd*2;
            float xc = (p1.x + p2.x)/2;
            float yc = (p1.y + p2.y)/2;
            for (int i = 0; i < vertices.size(); i++) {
                float x0d = xc - vertices[i].x;
                vertices[i].u = - 2 * x0d / w + 0.5f;
                float y0d = yc - vertices[i].y;
                vertices[i].v = - 2 * y0d / h - 0.25f;
                //cout << vertices[i].x << " " << vertices[i].y << " " << vertices[i].u << " " << vertices[i].v << endl;
            }
        }

        //stbi_image_free(data);
    }

};