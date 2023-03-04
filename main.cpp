#include <iostream>
#include <vector>

#include "src/image.h"
#include "src/distance_functions.h"
#include "src/scene.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    Image<uint8_t> rgb_image(768, 1024, 3);
    std::vector<std::shared_ptr<SDF>> objs = {
        std::make_shared<Circle>(0.0, 0.0, 1.0, RGBColor{255, 0, 0})
    };
    Scene scene(objs, -1., 1., -1., 1., {127, 127, 0});
    scene.RenderToImage(rgb_image);

    Save8bitRgbImage("../test.png", rgb_image);

}