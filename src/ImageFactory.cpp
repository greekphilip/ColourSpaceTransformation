//
// Created by philip on 1/4/24.
//

#include "../include/ImageFactory.h"
#include "../include/CharImage.h"
#include "../include/FloatImage.h"

std::unique_ptr<Image> ImageFactory::createImage(const int &width, const int &height, const int &channels, const QPixmap &pixmap,
                                const ColorSpace &colorSpace, const std::unique_ptr<OIIO::ImageInput> &imageInput) {
    switch (colorSpace) {
        case ColorSpace::RGB:
        case ColorSpace::RGBA:
        case ColorSpace::GRAY:
            return std::make_unique<CharImage>(width, height, channels, pixmap, colorSpace, imageInput);
        case ColorSpace::HSV:
            return std::make_unique<FloatImage>(width, height, channels, pixmap, colorSpace, imageInput);
        default:
            throw std::runtime_error("Unsupported Image");
    }
}


