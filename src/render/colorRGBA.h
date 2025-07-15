#pragma once

class ColorRGBA {
    public:
    float r, g, b, a;
    ColorRGBA(float r, float g, float b, float a = 1.0f) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    ColorRGBA() {}
    void GetRGB(float* out) {
        out[0] = r;
        out[1] = g;
        out[2] = b;
    }
    void GetRGBA(float* out) {
        out[0] = r;
        out[1] = g;
        out[2] = b;
        out[3] = a;
    }
    operator float*() {
        float* rgba[4] = {&r, &g, &b, &a};
        return rgba[0];
    }
};