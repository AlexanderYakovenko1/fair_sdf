#include <iostream>
#include <vector>

#include "src/image.h"
#include "src/distance_functions.h"
#include "src/scene.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    Image<uint8_t> rgb_image(768, 768, 3);
    std::vector<std::shared_ptr<SDF>> objs = {
        std::make_shared<SDFImage>("../sdf.png", -1, -1., 1.5, RGBColor{255, 0, 0})
//        std::make_shared<AxisAlignedEquilateralTriangle>(-0.25, 0.0, 0.25, RGBColor{255, 0, 0})
//            std::make_shared<Intersection>(
//                    std::make_shared<AxisAlignedRectangle>(0., 0., 0.25, 0.5, RGBColor{0, 255, 0}),
//                    std::make_shared<Segment>(-0.5, -0.25, 1.0, 0.0, RGBColor{0, 0, 255}), true),
//        std::make_shared<Intersection>(
//        std::make_shared<Circle>(0.0, 0.0, 0.5, RGBColor{255, 0, 0}),
//        std::make_shared<Intersection>(std::make_shared<Circle>(0.5, 0.5, 0.5, RGBColor{0, 255, 0}),
//                                       std::make_shared<Circle>(0.5, -0.5, 0.5, RGBColor{0, 0, 255}), true), true)
    };
    Scene scene(objs, -1., 1., -1., 1., {63, 128, 192});
    scene.RenderToImage(rgb_image, 1e-3);

    Save8bitRgbImage("../test.png", rgb_image);

}