//
// Created by philip on 1/4/24.
//

#ifndef COLOURSPACETRANSFORMATION_IMAGEFACTORY_H
#define COLOURSPACETRANSFORMATION_IMAGEFACTORY_H

#include "Image.h"

class ImageFactory{
public:
    static std::unique_ptr<Image> createImage(const int &width, const int &height, const int &channels, const QPixmap &pixmap,
                             const ColorSpace &colorSpace,
                             const std::unique_ptr<OIIO::ImageInput> &imageInput);
};
#endif //COLOURSPACETRANSFORMATION_IMAGEFACTORY_H
