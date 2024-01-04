//
// Created by philip on 12/30/23.
//

#ifndef COLOURSPACETRANSFORMATION_COLORSPACE_H
#define COLOURSPACETRANSFORMATION_COLORSPACE_H

#include "Image.h"

enum class ColorSpace {
    RGB,
    RGBA,
    HSV,
    GRAY
};

static std::string ColorSpacetoString(const ColorSpace &colorSpace) {
    switch (colorSpace) {
        case ColorSpace::RGB:
            return "RGB";
        case ColorSpace::RGBA:
            return "RGBA";
        case ColorSpace::GRAY:
            return "GRAY";
        case ColorSpace::HSV:
            return "HSV";
        default:
            return "";
    }
}

static ColorSpace StringToColorSpace(const std::string &text) {
    if ("RGB" == text) {
        return ColorSpace::RGB;
    } else if ("RGBA" == text) {
        return ColorSpace::RGBA;
    } else if ("GRAY" == text) {
        return ColorSpace::GRAY;
    } else if ("HSV" == text) {
        return ColorSpace::HSV;
    } else {
        throw std::runtime_error("Illegal Argument " + text);
    }
}

static int ColorSpaceEnd() {
    return static_cast<int>(ColorSpace::GRAY);
}

#endif //COLOURSPACETRANSFORMATION_COLORSPACE_H
