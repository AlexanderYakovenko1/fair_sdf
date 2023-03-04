#ifndef SDF_IMAGE_H
#define SDF_IMAGE_H

#include <cstdint>
#include <vector>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

template <typename pixel_type>
class Image {
public:
    const size_t height_, width_, channels_;
private:
    size_t size_;
    std::vector<pixel_type> pixel_data_;
public:
    Image(size_t height, size_t width, size_t channels):
            height_(height),
            width_(width),
            channels_(channels),
            size_(height_ * width_ * channels_),
            pixel_data_(size_, pixel_type()) {}

    pixel_type& operator()(size_t x, size_t y, size_t z) {
        size_t idx = x * width_ * channels_ + y * channels_ + z;

        return pixel_data_[idx];
    }

    friend void Save8bitRgbImage(const std::string&, const Image<uint8_t>&);
};

void Save8bitRgbImage(const std::string& path, const Image<uint8_t>& image) {
    stbi_write_png(path.c_str(), image.width_, image.height_, STBI_rgb, image.pixel_data_.data(), image.width_ * image.channels_);
}
#endif //SDF_IMAGE_H
