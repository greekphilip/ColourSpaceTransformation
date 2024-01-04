//
// Created by philip on 1/4/24.
//

#ifndef COLOURSPACETRANSFORMATION_FLOATIMAGE_H
#define COLOURSPACETRANSFORMATION_FLOATIMAGE_H
#include "Image.h"

class FloatImage : public Image{

private:
    std::vector<float> pixels;
public:
    FloatImage(const int &width, const int &height, const int &channels, const QPixmap &guiImage,
              const ColorSpace &colorSpace, const std::unique_ptr<OIIO::ImageInput> &imageInput);

    FloatImage(const int &width, const int &height, const int &channels, const QPixmap &guiImage,
              const ColorSpace &colorSpace, std::vector<float> &pixels);

    std::vector<float> getPixels() const;

};
#endif //COLOURSPACETRANSFORMATION_FLOATIMAGE_H
