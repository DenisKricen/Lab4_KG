FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    #Base utilities
    build-essential \
    cmake \
    libgl1-mesa-dev \
    git \
    gdb \

    #To resize windows
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-xinerama0 \
    libxcb-xfixes0 \
    libxkbcommon-x11-0 \
    libxcb-cursor0 \
    
    #QT
    qt6-base-dev \
    qt6-base-dev-tools \
    qt6-tools-dev-tools \
    designer-qt6 \

    && rm -rf /var/lib/apt/lists/*

ENV QT_XCB_GL_INTEGRATION=none
