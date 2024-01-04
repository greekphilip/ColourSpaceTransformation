#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <memory>
#include <QPainter>
#include <QButtonGroup>
#include <QRadioButton>
#include "../include/Image.h"
#include "../include/ColorSpaceConverter.h"
#include "../include/ImageFactory.h"
#include <OpenImageIO/imagebuf.h>


std::unique_ptr<Image> image;
std::unique_ptr<Image> convertedImage;


void loadImage(QWidget &window, QLabel &imageLabel, QLabel &detectedLabel, QLabel &colorSpaceLabel,
          QPushButton &convertButton) {
    qDebug() << "Import button clicked.";

    // Open a file dialog for image selection
    QString imagePath = QFileDialog::getOpenFileName(&window, "Select Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!imagePath.isEmpty()) {
        try {
            qDebug() << "Image selected:" << imagePath;

            QPixmap pixmap(imagePath);
            std::unique_ptr<OIIO::ImageInput> imageInput = OIIO::ImageInput::open(imagePath.toStdString());
            // Get image specs
            const OIIO::ImageSpec &spec = imageInput->spec();
            const int width = spec.width;
            const int height = spec.height;
            const int channels = spec.nchannels;
            ColorSpace colorSpace = ColourSpaceConverter::resolveColorSpace(pixmap, channels);


            image = ImageFactory::createImage(width, height, channels, pixmap, colorSpace, imageInput);

            // Load and display the selected image
            int windowWidth = window.width();
            int windowHeight = window.height();
            if (width < windowWidth || height < windowHeight) {
                windowWidth = width;
                windowHeight = height;
            }
            imageLabel.setPixmap(pixmap.scaled(windowWidth, windowHeight, Qt::KeepAspectRatio));
            imageLabel.setAlignment(Qt::AlignCenter); // Align the image to the center

            detectedLabel.setText(QString("Original Color Space Detected: "));
            colorSpaceLabel.setText(QString(ColorSpacetoString(colorSpace).c_str()));
            convertButton.setEnabled(true);
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } else {
        qDebug() << "No image selected.";

        // Clear the label if no image selected
        imageLabel.clear();
    }
}

void convertImage(QWidget &window, QLabel &imageLabel, QButtonGroup &radioGroup) {
    try {
        std::string selectedColorSpaceString = radioGroup.checkedButton()->text().toStdString();
        ColorSpace to = StringToColorSpace(selectedColorSpaceString);
        convertedImage = ColourSpaceConverter::convertColorSpace(image, to);



        int width = window.width();
        int height = window.height();
        if (image->getWidth() < width || image->getHeight() < height) {
            width = image->getWidth();
            height = image->getHeight();
        }


        imageLabel.setPixmap(convertedImage->getGuiImage().scaled(width, height, Qt::KeepAspectRatio));
        imageLabel.setAlignment(Qt::AlignCenter); // Align the image to the center
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        imageLabel.clear();
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the main window
    QWidget window;
    window.setWindowTitle("Image Importer");

    // Create a vertical layout for the window
    QVBoxLayout layout(&window);

    // Create a label for displaying the image
    QLabel imageLabel(new QLabel(&window));
    layout.addWidget(&imageLabel);

    QHBoxLayout saveLayout(&window);
    layout.addLayout(&saveLayout);
    // Create a button for importing an image
    QPushButton importButton("Import Image", &window);
    saveLayout.addWidget(&importButton);


    QHBoxLayout detectedLayout;
    layout.addLayout(&detectedLayout);
    // Text to display color space

    QLabel detectedLabel(&window);
    detectedLayout.addWidget(&detectedLabel);

    QLabel colorSpaceLabel(&window);
    detectedLayout.addWidget(&colorSpaceLabel);

    QHBoxLayout radioLayout; // Create a horizontal layout for radio buttons
    layout.addLayout(&radioLayout); // Add the horizontal layout to the main vertical layout

    QButtonGroup radioGroup(&window);
    for (int i = 0, end = ColorSpaceEnd(); i <= end; i++) {
        const QString radioText(ColorSpacetoString(static_cast<ColorSpace>(i)).c_str());
        QRadioButton *radioButton = new QRadioButton(radioText, &window);
        radioGroup.addButton(radioButton, i);
        radioLayout.addWidget(radioButton);
    }

    QPushButton convertButton("Convert", &window);
    convertButton.setDisabled(true);
    layout.addWidget(&convertButton);

    // Connect button click event to open file dialog and display image
    QObject::connect(&importButton, &QPushButton::clicked,
                     [&window, &imageLabel, &detectedLabel, &colorSpaceLabel, &convertButton]() {
                         loadImage(window, imageLabel, detectedLabel, colorSpaceLabel, convertButton);
                     });

    QObject::connect(&convertButton, &QPushButton::clicked, [&window, &imageLabel, &radioGroup]() {
        convertImage(window, imageLabel, radioGroup);
    });


    // Set the layout and show the window
    window.setLayout(&layout);
    window.setGeometry(100, 100, 600, 600); // Set window size
    window.show();

    return app.exec();
}