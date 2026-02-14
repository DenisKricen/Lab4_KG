FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libgl1-mesa-dev \
    git \
    gdb \
    
    qt6-base-dev \
    qt6-base-dev-tools \
    qt6-tools-dev-tools \
    designer-qt6 \

    && rm -rf /var/lib/apt/lists/*

ENV QT_XCB_GL_INTEGRATION=none

ARG USERNAME=ubuntu
USER $USERNAME