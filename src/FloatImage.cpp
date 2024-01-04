//
// Created by philip on 1/4/24.
//
#include "../include/FloatImage.h"


FloatImage::FloatImage(const int &width, const int &height, const int &channels, const QPixmap &guiImage,
                     const ColorSpace &colorSpace, const std::unique_ptr<OIIO::ImageInput> &imageInput) : Image(width, height, channels, guiImage, colorSpace) {
    // Allocate memory for pixels
    pixels = std::vector<float>(width * height * channels);

    // Read image pixels with subimage, miplevel, and other parameters
    if (!imageInput->read_image(0, 0, 0, channels, OIIO::TypeDesc::FLOAT, pixels.data())) {
        throw std::runtime_error("Failed to read image pixels.");
    }
}

std::vector<float> FloatImage::getPixels() const {
    return pixels;
}

FloatImage::FloatImage(const int &width, const int &height, const int &channels, const QPixmap &guiImage,
                     const ColorSpace &colorSpace, std::vector<float> &pixels) : Image(width, height, channels, guiImage, colorSpace), pixels(pixels){

}
