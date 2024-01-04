//
// Created by philip on 12/30/23.
//
#include <OpenImageIO/imageio.h>
#include "Image.h"
#include <QPixmap>
#include "ColorSpace.h"
#include "QColorSpace"

#ifndef COLOURSPACETRANSFORMATION_COLORSPACECONVERTER_H
#define COLOURSPACETRANSFORMATION_COLORSPACECONVERTER_H


class ColourSpaceConverter {
public:
    template <typename T>
    using ConverterFunc = std::function<std::unique_ptr<Image>(const std::vector<T> &pixels, const int &width, const int &height)>;


    static std::unique_ptr<Image> convertColorSpace(const std::unique_ptr<Image> &image, const ColorSpace &toColorSpace);


    static std::unique_ptr<Image> RGBtoGRAY(const std::vector<unsigned char> &pixels, const int &width, const int &height);

    static std::unique_ptr<Image> RGBAtoGRAY(const std::vector<unsigned char> &pixels, const int &width, const int &height);

    static std::unique_ptr<Image> RGBtoHSV(const std::vector<unsigned char> &pixels, const int &width, const int &height);

    static std::unique_ptr<Image> RGBtoRGBA(const std::vector<unsigned char> &pixels, const int &width, const int &height);

    static std::unique_ptr<Image> RGBAtoRGB(const std::vector<unsigned char> &pixels, const int &width, const int &height);

    static std::unique_ptr<Image> HSVtoRGB(const std::vector<float> &pixels, const int &width, const int &height);

    static ColorSpace resolveColorSpace(const QPixmap &guiImage, const int &channels);

private:
    static std::map<std::string, ConverterFunc<float>> FLOAT_CONVERT_MAP;
    static std::map<std::string, ConverterFunc<unsigned char>> CHAR_CONVERT_MAP;
    const static std::string KEY_DELIMITER;
    static std::string getConversionMapKey(const ColorSpace &from, const ColorSpace &to);
    template <typename T>
    static std::unique_ptr<Image> convertColorSpace(const std::unique_ptr<Image> &image, const ColorSpace &toColorSpace, const std::vector<T> &pixels);
    static std::unique_ptr<Image> resolveConversionFunction(const std::unique_ptr<Image> &image, const ColorSpace &toColorSpace,
                                                            const std::vector<unsigned char> &pixels);
    static std::unique_ptr<Image> resolveConversionFunction(const std::unique_ptr<Image> &image, const ColorSpace &toColorSpace,
                                                            const std::vector<float> &pixels);
};

#endif //COLOURSPACETRANSFORMATION_COLORSPACECONVERTER_H
