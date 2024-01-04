//
// Created by philip on 1/4/24.
//


#include "../include/CharImage.h"


CharImage::CharImage(const int &width, const int &height, const int &channels, const QPixmap &guiImage,
                     const ColorSpace &colorSpace, const std::unique_ptr<OIIO::ImageInput> &imageInput) : Image(width, height, channels, guiImage, colorSpace) {
    // Allocate memory for pixels
    pixels = std::vector<unsigned char>(width * height * channels);

    // Read image pixels with subimage, miplevel, and other parameters
    if (!imageInput->read_image(0, 0, 0, channels, OIIO::TypeDesc::UINT8, pixels.data())) {
        throw std::runtime_error("Failed to read image pixels.");
    }
}

std::vector<unsigned char> CharImage::getPixels() const {
    return pixels;
}

CharImage::CharImage(const int &width, const int &height, const int &channels, const QPixmap &guiImage,
                     const ColorSpace &colorSpace, std::vector<unsigned char> &pixels) : Image(width, height, channels, guiImage, colorSpace), pixels(pixels){

}
