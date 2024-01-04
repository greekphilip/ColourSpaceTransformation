//
// Created by philip on 12/30/23.
//

#ifndef COLOURSPACETRANSFORMATION_IMAGE_H
#define COLOURSPACETRANSFORMATION_IMAGE_H

#include <QPixmap>
#include "ColorSpace.h"
#include <OpenImageIO/imageio.h>
#include <QDebug>


class Image {
public:
    Image(const int &width, const int &height, const int &channels, const QPixmap &guiImage,
          const ColorSpace &colorSpace);

    virtual int getWidth() const;

    virtual int getChannels() const;

    virtual const QPixmap &getGuiImage() const;

    virtual int getHeight() const;

    virtual ColorSpace getColorSpace() const;


private:

    QPixmap guiImage;
    int channels;
    int width;
    int height;
    ColorSpace colorSpace;
    std::string fileExtension;
};

#endif //COLOURSPACETRANSFORMATION_IMAGE_H
