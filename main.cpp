#include <iostream>
#include <vector>
#include <chrono>

#include "src/image.h"
#include "src/distance_functions.h"
#include "src/scene.h"


/// YDS logo lookalike
/// Shows off different primitives implemented
Scene Scene1() {
    return Scene({
        std::make_shared<AxisAlignedEquilateralTriangle>(-0.66, 0.0, 0.25, Color({255, 197, 70})),
        std::make_shared<Circle>(0.0, 0.0, 0.25, Color({225, 11, 16})),
        std::make_shared<AxisAlignedRectangle>(0.66, 0.0, 0.25, 0.25, Color({0, 0, 0})),
    }, -1, 1, -1, 1, {79, 134, 160});
}

Scene Scene2() {
    return Scene({
        std::make_shared<Overlay>(
            std::make_shared<Circle>(-0.15, -0.3, 0.25, RGBColor{255, 0, 0}),
            std::make_shared<Circle>(0.15, -0.3, 0.25, RGBColor{255, 160, 0})
        ),
        std::make_shared<Overlay>(
            std::make_shared<AxisAlignedRectangle>(0., 0.3, 0.35, 0.25,
                                                   Color({255, 84, 126},
                                                         {109, 252, 255},
                                                         {0,0,0}, 4, 0.03)),
            std::make_shared<Intersection>(
                std::make_shared<Intersection>(
                    std::make_shared<Intersection>(
                        std::make_shared<Intersection>(
                            std::make_shared<AxisAlignedRectangle>(0., 0., 0.55, 0.75,
                                                                   Color({0, 204, 255},
                                                                         {0, 120, 255},
                                                                         {255,255,255}, 2, 0.1)),
                            std::make_shared<Segment>(-0.75, -0.7, 0.75, -0.45, RGBColor{0, 120, 255}),
                        true),
                        std::make_shared<Segment>(-0.75, -0.1, 0.75, -0.25, RGBColor{255, 0, 255}),
                    true),
                    std::make_shared<Segment>(-0.75, 0.1, 0.75, 0.3, RGBColor{120, 255, 0}),
                true),
                std::make_shared<Segment>(-0.75, 0.7, 0.75, 0.45, RGBColor{120, 120, 190}),
            true)
        )
    }, -1, 1, -1, 1, {160, 134, 79});
}

Scene Scene3() {
    return Scene({
        std::make_shared<Overlay>(
            std::make_shared<SDFImage>("../A.png", -0.7, -0.7, 0.3, Color({0, 0, 0})),
            std::make_shared<SDFImage>("../Y.png", -0.525, -0.6, 0.3, Color({255, 255, 255})),
        0.7),
        std::make_shared<SDFImage>("../sdf.png", 0, 0.1, 1., Color({255, 152, 70}, {255, 222, 0}, {255,255,255}, 3, 0.4)),
        std::make_shared<AxisAlignedEquilateralTriangle>(0, 0, .75, Color({255, 90, 90}, 0.1, {0, 0, 0})),
        std::make_shared<Intersection>(
            std::make_shared<Circle>(0.725, -0.7, 0.125, Color({255, 0, 0})),
            std::make_shared<Intersection>(
                    std::make_shared<Circle>(0.475, -0.7, 0.125, Color({0, 255, 0})),
                    std::make_shared<Circle>(0.6, -0.5, 0.125, Color({0, 0, 255})),
            true),
        true)
    }, -1, 1, -1, 1, {192, 192, 192});
}


int main() {
    Image<uint8_t> rgb_image(1024, 1024, 3);

    std::cout << "Rendering Scene1..." << std::flush;
    auto scene = Scene1();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    scene.RenderToImage(rgb_image, 2e-3);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    Save8bitRgbImage("../scene1.png", rgb_image);
    std::cout << " Done" << std::endl;
    std::cout << "It took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " [µs]" << std::endl;

    std::cout << "Rendering Scene2..." << std::flush;
    scene = Scene2();
    begin = std::chrono::steady_clock::now();
    scene.RenderToImage(rgb_image, 2e-3);
    end = std::chrono::steady_clock::now();
    Save8bitRgbImage("../scene2.png", rgb_image);
    std::cout << " Done" << std::endl;
    std::cout << "It took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " [µs]" << std::endl;

    std::cout << "Rendering Scene3..." << std::flush;
    scene = Scene3();
    begin = std::chrono::steady_clock::now();
    scene.RenderToImage(rgb_image, 2e-3);
    end = std::chrono::steady_clock::now();
    Save8bitRgbImage("../scene3.png", rgb_image);
    std::cout << " Done" << std::endl;
    std::cout << "It took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " [µs]" << std::endl;

}