cmake_minimum_required(VERSION 3.27)
project(ColourSpaceTransformation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/philip/Qt/5.15.2/gcc_64/")
set(CMAKE_TOOLCHAIN_FILE "/home/philip/Applications/vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(spdlog REQUIRED)
find_package(Boost REQUIRED filesystem system thread)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(ColourSpaceTransformation
        src/main.cpp
        include/ColorSpaceConverter.h
        src/ColorSpaceConverter.cpp
        include/ColorSpace.h
        src/Image.cpp
        include/Image.h
        include/CharImage.h
        src/CharImage.cpp
        include/ImageFactory.h
        src/ImageFactory.cpp
        include/FloatImage.h
        src/FloatImage.cpp
)

target_link_libraries(ColourSpaceTransformation PRIVATE spdlog::spdlog
        OpenImageIO::OpenImageIO
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Boost::filesystem
        Boost::system
        Boost::thread)