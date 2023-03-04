#ifndef SDF_DISTANCE_FUNCTIONS_H
#define SDF_DISTANCE_FUNCTIONS_H

#include <cmath>
#include <cstdint>
#include <memory>
#include <utility>

struct RGBColor {
    uint8_t r, g, b;
};

class SDF {
public:
    SDF() = default;
    virtual double distance(double x, double y) = 0;
    virtual ~SDF() = default;
    virtual RGBColor getColor(double x, double y) = 0;
};


class Circle: public SDF {
    double x_, y_;
    double radius_;
    RGBColor color_;
public:
    Circle(double x, double y, double radius, RGBColor color): x_(x), y_(y), radius_(radius), color_(color) {}
    double distance(double x, double y) override {
        return std::sqrt((x - x_) * (x - x_) + (y - y_) * (y - y_)) - radius_;
    }
    RGBColor getColor(double x, double y) override {
        return color_;
    }
};

double sminCubic(double a, double b, double k)
{
    double h = std::max( k-abs(a-b), 0.0 )/k;
    double m = h*h*h*0.5;
    double s = m*k*(1.0/3.0);
    return (a<b) ? a-s : b-s;
}

double sminCubicCol(double a, double b, double k)
{
    double h = std::max( k-abs(a-b), 0.0 )/k;
    double m = h*h*h*0.5;
    double s = m*k*(1.0/3.0);
    return (a<b) ? m : 1-m;
}

class Intersection: public SDF {
    std::shared_ptr<SDF> first_;
    std::shared_ptr<SDF> second_;
    bool smooth_;
    double smoothness_;
public:
    Intersection(std::shared_ptr<SDF>&& first, std::shared_ptr<SDF>&& second,
                 bool smooth=false, double smoothness=0.125):
         first_(std::move(first)),
         second_(std::move(second)),
         smooth_(smooth),
         smoothness_(smoothness)
    {}
    double distance(double x, double y) override {
        if (smooth_) {
            return sminCubic(first_->distance(x, y), second_->distance(x, y), smoothness_);
        } else {
            return std::min(first_->distance(x, y), second_->distance(x, y));
        }
    }
    RGBColor getColor(double x, double y) override {
        double first_dist = first_->distance(x, y);
        double second_dist = second_->distance(x, y);
        if (smooth_) {
            double blend = sminCubicCol(second_dist, first_dist, smoothness_);
            auto fcol = first_->getColor(x, y);
            auto scol = second_->getColor(x, y);
            return {
                    uint8_t(sqrt(double(fcol.r) * double(fcol.r) * blend + double(scol.r) * double(scol.r) * (1 - blend))),
                    uint8_t(sqrt(double(fcol.g) * double(fcol.g) * blend + double(scol.g) * double(scol.g) * (1 - blend))),
                    uint8_t(sqrt(double(fcol.b) * double(fcol.b) * blend + double(scol.b) * double(scol.b) * (1 - blend)))
            };
        } else {
            if (first_dist < second_dist) {
                return first_->getColor(x, y);
            } else {
                return second_->getColor(x, y);
            }
        }
    }
};

#endif //SDF_DISTANCE_FUNCTIONS_H
