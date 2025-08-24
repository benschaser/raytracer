#pragma once
#include "color.h"

class Texture {
public:
    Texture(std::string name, const Color color);
    virtual ~Texture() {};
    virtual Color uv(double u, double v) const = 0;

protected:
    std::string name;
    Color color;
};

class Solid : public Texture {
public:
    Solid(const Color color);
    Color uv(double u, double v) const override;
};

class Checkerboard : public Texture {
public:
    Checkerboard(const Color color);
    Color uv(double u, double v) const override;
};

class Gradient : public Texture {
public:
    Gradient(const Color color);
    Color uv(double u, double v) const override;
};

class VStripe : public Texture {
public:
    VStripe(const Color color);
    Color uv(double u, double v) const override;
};

class HStripe : public Texture {
public:
    HStripe(const Color color);
    Color uv(double u, double v) const override;
};

class Spiral : public Texture {
public:
    Spiral(const Color color);
    Color uv(double u, double v) const override;
};