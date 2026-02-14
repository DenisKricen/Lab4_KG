cmake_minimum_required(VERSION 3.16)

project(Lab1_KG LANGUAGES CXX)

# Стандарт C++ (Qt 6 вимагає мінімум C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматична генерація мета-файлів Qt (це магія Qt)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Ось тут CMake звернеться до vcpkg, щоб знайти Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

add_executable( Lab1_KG 
                core/main.cpp
                core/CScene/CScene.cpp
                core/CFigure/CFigure.cpp
                core/CMainWindow/CMainWindow.cpp
                core/CMainWindow/CMainWindow.ui
)

# Підключаємо бібліотеки Qt до твого файлу
target_link_libraries(Lab1_KG PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)