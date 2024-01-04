//
// Created by philip on 12/30/23.
//
#include "../include/ColorSpaceConverter.h"
#include "../include/CharImage.h"
#include "../include/FloatImage.h"
#include <cmath>

const std::string ColourSpaceConverter::KEY_DELIMITER = ":";


std::map<std::string, ColourSpaceConverter::ConverterFunc<float>> ColourSpaceConverter::FLOAT_CONVERT_MAP = {
        {getConversionMapKey(ColorSpace::HSV, ColorSpace::RGB),
                HSVtoRGB}
};


std::map<std::string, ColourSpaceConverter::ConverterFunc<unsigned char>> ColourSpaceConverter::CHAR_CONVERT_MAP = {
        {getConversionMapKey(ColorSpace::RGB, ColorSpace::GRAY),
                RGBtoGRAY},
        {getConversionMapKey(ColorSpace::RGB, ColorSpace::HSV),
                RGBtoHSV},
        {getConversionMapKey(ColorSpace::RGB, ColorSpace::RGBA),
                RGBtoRGBA},
        {getConversionMapKey(ColorSpace::RGBA, ColorSpace::RGB),
                RGBAtoRGB},
        {getConversionMapKey(ColorSpace::RGBA, ColorSpace::GRAY),
                RGBAtoGRAY}
};


std::string ColourSpaceConverter::getConversionMapKey(const ColorSpace &from, const ColorSpace &to) {
    return ColorSpacetoString(from) + KEY_DELIMITER +
           ColorSpacetoString(to);
}


std::unique_ptr<Image>
ColourSpaceConverter::RGBtoGRAY(const std::vector<unsigned char> &pixels, const int &width, const int &height) {
    const int resultChannels = 1;
    const int originalChannels = 3;

    std::vector<unsigned char> result(width * height * resultChannels);
    for (int pixelIndex = 0, resultIndex = 0; resultIndex < result.size(); pixelIndex += originalChannels, resultIndex += resultChannels) {
        unsigned char r = pixels[pixelIndex];
        unsigned char g = pixels[pixelIndex + 1];
        unsigned char b = pixels[pixelIndex + 2];

        // Calculate luminance using the formula Y = 0.2126*R + 0.7152*G + 0.0722*B
        float luminance = 0.2126f * r + 0.7152f * g + 0.0722f * b;
        result[resultIndex] = static_cast<unsigned char>(luminance);
    }

    QImage convertedImage(result.data(), width, height, resultChannels * width, QImage::Format_Grayscale8);
    return std::make_unique<CharImage>(width, height, resultChannels, QPixmap::fromImage(convertedImage), ColorSpace::GRAY, result);
}

std::unique_ptr<Image>
ColourSpaceConverter::RGBAtoGRAY(const std::vector<unsigned char> &pixels, const int &width, const int &height) {
    const int resultChannels = 1;
    const int originalChannels = 4;

    std::vector<unsigned char> result(width * height * resultChannels);
    for (int pixelIndex = 0, resultIndex = 0; resultIndex < result.size(); pixelIndex += originalChannels, resultIndex += resultChannels) {
        unsigned char r = pixels[pixelIndex];
        unsigned char g = pixels[pixelIndex + 1];
        unsigned char b = pixels[pixelIndex + 2];

        // Calculate luminance using the formula Y = 0.2126*R + 0.7152*G + 0.0722*B
        float luminance = 0.2126f * r + 0.7152f * g + 0.0722f * b;
        result[resultIndex] = static_cast<unsigned char>(luminance);
    }

    QImage convertedImage(result.data(), width, height, resultChannels * width, QImage::Format_Grayscale8);
    return std::make_unique<CharImage>(width, height, resultChannels, QPixmap::fromImage(convertedImage), ColorSpace::GRAY, result);
}

std::unique_ptr<Image>
ColourSpaceConverter::RGBtoRGBA(const std::vector<unsigned char> &pixels, const int &width, const int &height) {
    const int resultChannels = 4;
    const int originalChannels = 3;

    std::vector<unsigned char> result(width * height * resultChannels);
    for (int pixelIndex = 0, resultIndex=0; pixelIndex < pixels.size(); pixelIndex += originalChannels, resultIndex+=resultChannels) {
        unsigned char r = pixels[pixelIndex];
        unsigned char g = pixels[pixelIndex + 1];
        unsigned char b = pixels[pixelIndex + 2];


        result[resultIndex] = r;
        result[resultIndex + 1] = g;
        result[resultIndex + 2] = b;
        result[resultIndex + 3] = 255;
    }

    QImage convertedImage(result.data(), width, height, resultChannels * width, QImage::Format_RGBA8888);
    return std::make_unique<CharImage>(width, height, resultChannels, QPixmap::fromImage(convertedImage), ColorSpace::RGBA, result);
}


std::unique_ptr<Image>
ColourSpaceConverter::RGBAtoRGB(const std::vector<unsigned char> &pixels, const int &width, const int &height) {
    const int resultChannels = 3;
    const int originalChannels = 4;
    std::vector<unsigned char> result(width * height * resultChannels);
    for (int pixelIndex = 0, resultIndex=0; pixelIndex < pixels.size(); pixelIndex += originalChannels, resultIndex+=resultChannels) {
        unsigned char r = pixels[pixelIndex];
        unsigned char g = pixels[pixelIndex + 1];
        unsigned char b = pixels[pixelIndex + 2];


        result[resultIndex] = r;
        result[resultIndex + 1] = g;
        result[resultIndex + 2] = b;
    }

    QImage convertedImage(result.data(), width, height, resultChannels * width, QImage::Format_RGB888);
    return std::make_unique<CharImage>(width, height, resultChannels, QPixmap::fromImage(convertedImage), ColorSpace::RGB, result);
}


std::unique_ptr<Image>
ColourSpaceConverter::RGBtoHSV(const std::vector<unsigned char> &pixels, const int &width, const int &height) {
    const int resultChannels = 3;
    const int originalChannels = 3;
    std::vector<float> result(width * height * resultChannels);
    for (int pixelIndex = 0; pixelIndex < result.size(); pixelIndex += originalChannels) {
        float r = pixels[pixelIndex] / 255.0f;
        float g = pixels[pixelIndex + 1] / 255.0f;
        float b = pixels[pixelIndex + 2] / 255.0f;

        float max = fmax(fmax(r, g), b);
        float min = fmin(fmin(r, g), b);
        float delta = max - min;

        float h = 0, s = 0, v = max; // Initialize Hue, Saturation, Value


        if (delta != 0) {
            if (max == r) {
                h = 60 * fmod(((g - b) / delta), 6.0f);
            } else if (max == g) {
                h = 60 * (((b - r) / delta) + 2.0f);
            } else if (max == b) {
                h = 60 * (((r - g) / delta) + 4.0f);
            }

            if (max != 0) {
                s = delta / max;
            }
        }

        // Adjust value (brightness) for white pixels
        if (max == 0) {
            v = 0; // For black pixels
        } else if (max == 1 && min == 1) {
            v = 1; // For white pixels
        }


        result[pixelIndex] = h;
        result[pixelIndex + 1] = s;
        result[pixelIndex + 2] = v;
    }

    return HSVtoRGB(result, width, height);
}


std::unique_ptr<Image>
ColourSpaceConverter::HSVtoRGB(const std::vector<float> &pixels, const int &width, const int &height) {
    const int resultChannels = 3;
    const int originalChannels = 3;

    std::vector<unsigned char> result(width * height * resultChannels);

    for (size_t i = 0; i < pixels.size(); i += 3) {
        float h = pixels[i];       // Hue
        float s = pixels[i + 1];   // Saturation
        float v = pixels[i + 2];   // Value

        // Convert HSV to RGB
        float c = v * s; // Chroma
        float hp = h / 60.0f;
        float x = c * (1 - std::abs(std::fmod(hp, 2) - 1));
        float m = v - c;

        float r = 0, g = 0, b = 0;
        if (hp >= 0 && hp < 1) {
            r = c;
            g = x;
        } else if (hp >= 1 && hp < 2) {
            r = x;
            g = c;
        } else if (hp >= 2 && hp < 3) {
            g = c;
            b = x;
        } else if (hp >= 3 && hp < 4) {
            g = x;
            b = c;
        } else if (hp >= 4 && hp < 5) {
            r = x;
            b = c;
        } else if (hp >= 5 && hp < 6) {
            r = c;
            b = x;
        }

        // Scale RGB values to 0-255 and convert to unsigned char
        r = (r + m) * 255.0f;
        g = (g + m) * 255.0f;
        b = (b + m) * 255.0f;

        // Ensure RGB values are within 0-255 range
        r = std::min(std::max(r, 0.0f), 255.0f);
        g = std::min(std::max(g, 0.0f), 255.0f);
        b = std::min(std::max(b, 0.0f), 255.0f);

        // Assign converted RGB values to the result vector
        result.push_back(static_cast<unsigned char>(r));
        result.push_back(static_cast<unsigned char>(g));
        result.push_back(static_cast<unsigned char>(b));
    }

    QImage convertedImage(result.data(), width, height, resultChannels * width, QImage::Format_RGB888);
    return std::make_unique<CharImage>(width, height, resultChannels, QPixmap::fromImage(convertedImage), ColorSpace::RGB, result);
}



std::unique_ptr<Image>
ColourSpaceConverter::convertColorSpace(const std::unique_ptr<Image> &image, const ColorSpace &toColorSpace) {
    if (auto *derivedPtr = dynamic_cast<CharImage *>(image.get())) {
        return convertColorSpace(image, toColorSpace, derivedPtr->getPixels());
    } else if (auto *derivedPtr2 = dynamic_cast<FloatImage *>(image.get())) {
        return convertColorSpace(image, toColorSpace, derivedPtr2->getPixels());
    } else {
        throw std::runtime_error("Error. No Conversion Map Found.");
    }
}

template<typename T>
std::unique_ptr<Image>
ColourSpaceConverter::convertColorSpace(const std::unique_ptr<Image> &image, const ColorSpace &toColorSpace,
                                        const std::vector<T> &pixels) {
    return resolveConversionFunction(image, toColorSpace, pixels);
}

std::unique_ptr<Image>
ColourSpaceConverter::resolveConversionFunction(const std::unique_ptr<Image> &image, const ColorSpace &toColorSpace,
                                                const std::vector<unsigned char> &pixels) {
    std::string key = getConversionMapKey(image->getColorSpace(), toColorSpace);
    if (CHAR_CONVERT_MAP.count(key) > 0) {
        ConverterFunc<unsigned char> function = CHAR_CONVERT_MAP.at(key);
        return function(pixels, image->getWidth(), image->getHeight());
    } else {
        throw std::runtime_error(
                "Color Space conversion not supported: " + ColorSpacetoString(image->getColorSpace()) + " -> " +
                ColorSpacetoString(toColorSpace));
    }
}

std::unique_ptr<Image>
ColourSpaceConverter::resolveConversionFunction(const std::unique_ptr<Image> &image, const ColorSpace &toColorSpace,
                                                const std::vector<float> &pixels) {
    std::string key = getConversionMapKey(image->getColorSpace(), toColorSpace);
    if (FLOAT_CONVERT_MAP.count(key) > 0) {
        ConverterFunc<float> function = FLOAT_CONVERT_MAP.at(key);
        return function(pixels, image->getWidth(), image->getHeight());
    } else {
        throw std::runtime_error(
                "Color Space conversion not supported: " + ColorSpacetoString(image->getColorSpace()) + " -> " +
                ColorSpacetoString(toColorSpace));
    }
}

ColorSpace ColourSpaceConverter::resolveColorSpace(const QPixmap &guiImage, const int &channels) {
    switch (guiImage.toImage().format()) {
        case QImage::Format_Grayscale8:
        case QImage::Format_Grayscale16:
            return ColorSpace::GRAY;
        case QImage::Format_RGB888:
            return ColorSpace::RGB;
        case QImage::Format_RGBA8888:
            return ColorSpace::RGBA;
        default:
            if (channels == 1) {
                return ColorSpace::GRAY;
            }

            if (channels == 4) {
                return ColorSpace::RGBA;
            }

            if (channels == 3) {
                return ColorSpace::RGB;
            }
            throw std::runtime_error("Undefined Color Space for Image!");
    }
}