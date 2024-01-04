//
// Created by philip on 1/4/24.
//

#ifndef COLOURSPACETRANSFORMATION_CHARIMAGE_H
#define COLOURSPACETRANSFORMATION_CHARIMAGE_H

#include "Image.h"

class CharImage : public Image{

private:
    std::vector<unsigned char> pixels;
public:
    CharImage(const int &width, const int &height, const int &channels, const QPixmap &guiImage,
              const ColorSpace &colorSpace, const std::unique_ptr<OIIO::ImageInput> &imageInput);

    CharImage(const int &width, const int &height, const int &channels, const QPixmap &guiImage,
              const ColorSpace &colorSpace, std::vector<unsigned char> &pixels);
    std::vector<unsigned char> getPixels() const;

};

#endif //COLOURSPACETRANSFORMATION_CHARIMAGE_H
