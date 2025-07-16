#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "colorRGBA.h"
#include "stb_image.h"

using namespace std;

class Shape {
public:

    vector<Point> vertices;
    string texturePath;
    ColorRGBA color;

    Shape() {
        this->vertices = vector<Point>();
    }

    Shape(vector<Point> vertices_) {
        this->vertices = vertices_;
    }

    Shape(vector<Point> vertices_, ColorRGBA color_){
        this->vertices = vertices_;
        this->color = color_;
    }

    Shape(vector<Point> vertices_, string texturePath_) {
        this->vertices = vertices_;
        this->texturePath = texturePath_;
    }

    void AddPoint(Point point) {
        vertices.push_back(point);
    }

    void DeletePoint(Point point) {
        //vertices.erase(std::remove(vertices.begin(), vertices.end(), point), vertices.end());
    }
    void DeletePoint(int index) {
        if (index < vertices.size()) {
            vertices.erase(vertices.begin() + index);
        }
    }

    Shape Copy() {
        return {vertices};
    }

    void SetTexturePosition(Point p1, Point p2) {
        int width, height, channels;
        unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
        stbi_image_free(data);
        float aspect = (float)width / (float)height;
        float w, h;
        if (p1.u != p2.u && p1.v != p2.v) {
            float xd = abs(p1.x - p2.x);
            float ud = abs(p1.u - p2.u);
            w = xd/ud*2;
            float yd = abs(p1.y - p2.y);
            float vd = abs(p1.v - p2.v);
            h = yd/vd*2;
        } else if (p1.u == p2.u) {
            float yd = abs(p1.y - p2.y);
            float vd = abs(p1.v - p2.v);
            h = yd/vd*2;
            w = aspect * h;
        } else if (p1.v == p2.v) {
            float xd = abs(p1.x - p2.x);
            float ud = abs(p1.u - p2.u);
            w = xd/ud*2;
            h = w / aspect;
        } else {
            // same points
            return;
        }
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

};