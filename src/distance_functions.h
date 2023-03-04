#ifndef SDF_DISTANCE_FUNCTIONS_H
#define SDF_DISTANCE_FUNCTIONS_H

#include <cmath>
#include <cstdint>

struct RGBColor {
    uint8_t r, g, b;
};

class SDF {
    RGBColor color_;
public:
    SDF(RGBColor color): color_(color) {}
    virtual double distance(double x, double y) = 0;
    virtual ~SDF() = default;
    RGBColor getColor() {
        return color_;
    }
};


class Circle: public SDF {
    double x_, y_;
    double radius_;
public:
    Circle(double x, double y, double radius, RGBColor color): x_(x), y_(y), radius_(radius), SDF(color) {}
    double distance(double x, double y) override {
        return std::sqrt((x - x_) * (x - x_) + (y - y_) * (y - y_)) - radius_;
    }
};

#endif //SDF_DISTANCE_FUNCTIONS_H
