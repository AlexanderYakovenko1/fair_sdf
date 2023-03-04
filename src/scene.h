#ifndef SDF_SCENE_H
#define SDF_SCENE_H

#include <vector>
#include <map>
#include <memory>
#include "distance_functions.h"
#include "image.h"

class Scene {
    std::vector<std::shared_ptr<SDF>> objects_;             // all objects in the scene
    double x_min_, x_max_, y_min_, y_max_; // left right top bottom borders of scene
    RGBColor background_;
public:
    Scene(const std::vector<std::shared_ptr<SDF>>& objects, double x_min, double x_max, double y_min, double y_max, RGBColor background):
        objects_(objects),
        x_min_(x_min),
        x_max_(x_max),
        y_min_(y_min),
        y_max_(y_max),
        background_(background)
    {}

    template<typename pixel_type>
    void RenderToImage(Image<pixel_type>& image, double eps=1e-3) {
        for (int i = 0; i < image.height_; ++i) {
            for (int j = 0; j < image.width_; ++j) {
                double y = y_min_ + double(j) / image.width_ * (y_max_ - y_min_);
                double x = x_min_ + double(i) / image.height_ * (x_max_ - x_min_);

//                std::multimap<double, std::shared_ptr<SDF>> hits;  // hits sorted by distance
                std::shared_ptr<SDF> hit;
                for (auto object : objects_) {
                    if (object->distance(x, y) < eps) {
                        hit = object;
                    }
                }
                RGBColor color = background_;
                if (hit) {
                    color = hit->getColor();
                }
                image(i, j, 0) = color.r;
                image(i, j, 1) = color.g;
                image(i, j, 2) = color.b;
            }
        }
    }
};

#endif //SDF_SCENE_H
