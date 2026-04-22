cmake_minimum_required(VERSION 3.16)

project(Lab2_KG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

add_executable( Lab4_KG 
                core/main.cpp
                core/CScene/CScene.cpp
                core/CCanvas/CCanvas.cpp
                core/CMainWindow/CMainWindow.cpp
                core/CMainWindow/CMainWindow.ui

                core/CImage/CImage.cpp
                core/CImageTransfer/CImageTransfer.cpp
                core/CMouseObserver/CMouseObserver.cpp
                core/COverlayImage/COverlayImage.cpp
                core/CPixelViewer/CPixelViewer.cpp
                core/CColorMath/CColorMath.cpp
                core/CImageManager/CImageManager.cpp
)

target_include_directories(Lab4_KG PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core)
target_link_libraries(Lab4_KG PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)