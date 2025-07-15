#pragma once

class Point {
    public:
    float x, y, z, u, v;

    Point() {
        x = 0;
        y = 0;
        z = 0;
        u = 0;
        v = 0;
    }

    Point(float x_, float y_, float z_, float u_, float v_) {
        x = x_;
        y = y_;
        z = z_;
        u = u_;
        v = v_;
    }
    void GetXYZUV(float* out) const {
        out[0] = x;
        out[1] = y;
        out[2] = z;
        out[3] = u;
        out[4] = v;
    }
    void GetXYZ(float* out) const{
        out[0] = x;
        out[1] = y;
        out[2] = z;
    }
    void GetXY(float* out) const{
        out[0] = x;
        out[1] = y;
    }
    void GetUV(float* out) const{
        out[0] = u;
        out[1] = v;
    }
    Point Copy() {
        return Point(x, y, z, u, v);
    }
};
