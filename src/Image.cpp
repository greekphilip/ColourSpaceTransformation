//
// Created by philip on 12/30/23.
//

#include "../include/Image.h"
#include "../include/CharImage.h"


Image::Image(const int &width, const int &height, const int &channels, const QPixmap &guiImage,
             const ColorSpace &colorSpace)
        : width(width), height(height), channels(channels), guiImage(guiImage), colorSpace(colorSpace) {
}


const QPixmap &Image::getGuiImage() const {
    return guiImage;
}


int Image::getChannels() const {
    return channels;
}


int Image::getWidth() const {
    return width;
}


int Image::getHeight() const {
    return height;
}


ColorSpace Image::getColorSpace() const {
    return colorSpace;
}
