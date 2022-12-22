#include "texture.h"
#include "constants.h"

Texture::Texture(std::string name, const Color color)
    :name{name}, color{color} {}


Solid::Solid(const Color color)
    :Texture{"solid", color} {}

Color Solid::uv(double u, double v) const {
    return color;
}

Checkerboard::Checkerboard(const Color color)
    :Texture{"checkerboard", color} {}

Color Checkerboard::uv(double u, double v) const {
    if (std::sin(12*Constants::Pi*u) > 0.0 && std::sin(8*Constants::Pi*v) > 0.0) {
        return color * 0.2;
    }
    if (std::sin(12*Constants::Pi*u) < 0.0 && std::sin(8*Constants::Pi*v) < 0.0) {
        return color * 0.2;
    }
    else {
        return color;
    }
}

Gradient::Gradient(const Color color)
    :Texture{"gradient", color} {}

Color Gradient::uv(double u, double v) const {
    return color * (1-v)*(1-v);
}

VStripe::VStripe(const Color color)
    :Texture{"v-stripe", color} {}
Color VStripe::uv(double u, double v) const {
    if (std::abs(std::sin(Constants::Pi * 16 * u)) < 0.2) {
        return color * 0.2;
    }
    else {
        return color;
    }
}

HStripe::HStripe(const Color color)
    :Texture{"h-stripe", color} {}
Color HStripe::uv(double u, double v) const {
    if (std::abs(std::sin(Constants::Pi * 16 * v)) < 0.2) {
        return color * 0.2;
    }
    else {
        return color;
    }
}

Spiral::Spiral(const Color color)
    :Texture{"spiral", color} {}
Color Spiral::uv(double u, double v) const {
    if (std::sin(12*Constants::Pi*u) > 0.0 && std::sin(8*Constants::Pi*v) > 0.0) {
        return color * 0.2;
    }
    else {
        return color;
    }
}