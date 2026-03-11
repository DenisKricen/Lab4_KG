cmake_minimum_required(VERSION 3.16)

project(Lab2_KG LANGUAGES CXX)

# Стандарт C++ (Qt 6 вимагає мінімум C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматична генерація мета-файлів Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# CMake звернеться до vcpkg, щоб знайти Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

add_executable( Lab2_KG 
                core/main.cpp
                core/CScene/CScene.cpp
                core/CCanvas/CCanvas.cpp
                core/Figures/CFigure/CFigure.cpp
                core/Figures/CTriangle/CTriangle.cpp
                core/Figures/CHexagon/CHexagon.cpp
                core/CMainWindow/CMainWindow.cpp
                core/CMainWindow/CMainWindow.ui
                core/CProperties/CProperties.cpp
                core/Figures/CBeziersCurve/CBeziersCurve.cpp
                core/CPointDialog/CPointDialog.cpp
                core/utils/utils.cpp
)

target_include_directories(Lab2_KG PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core)

# На обробляй CProperties.cpp через AUTOUIC
set_source_files_properties(core/CProperties/CProperties.cpp PROPERTIES SKIP_AUTOUIC ON)

# Підключаємо бібліотеки Qt до файлу
target_link_libraries(Lab2_KG PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)