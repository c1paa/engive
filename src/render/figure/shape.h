#pragma once

#include <vector>
#include <string>

using namespace std;

class Shape : public Figure {
public:
    Shape() : Figure() {}

    Shape(vector<Point> vertices_) : Figure(vertices_){}

    Shape(vector<Point> vertices_, ColorRGBA color_) : Figure(vertices_, color_){}

    Shape(vector<Point> vertices_, string texturePath_) : Figure(vertices_, texturePath_){}

    void AddPoint(Point point) {
        vertices.push_back(point);
    }

    void DeletePoint(Point point) {
        // vertices.erase(find(vertices.begin(), vertices.end(), point));
    }

    Shape Copy() {
        return {vertices};
    }

};