cmake_minimum_required(VERSION 3.7)
project(nlmeans_app)

set(CMAKE_CXX_STANDARD 14)

# find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ";" ${QT5_PACKAGE_DIR})

find_package(OpenCV REQUIRED)

# include_directories(/usr/include/qt5)

set(SOURCE_FILES
        main.cpp
        )

add_executable(opencv_app ${SOURCE_FILES})

# TARGET_LINK_LIBRARIES(opencv_app Qt5::Core Qt5::Widgets Qt5::Gui ${OpenCV_LIBS})

TARGET_LINK_LIBRARIES(opencv_app ${OpenCV_LIBS})