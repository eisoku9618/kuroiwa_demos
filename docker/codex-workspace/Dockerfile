FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Tokyo

RUN apt update && apt install -y --no-install-recommends \
    ca-certificates \
    curl \
    git \
    bash \
    sudo \
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    gdb \
    vim \
    less \
    ripgrep \
    jq \
    python3 \
    python3-dev \
    python3-pip \
    python3-numpy \
    nodejs \
    npm \
    libboost-all-dev \
    libeigen3-dev \
    libxml2-dev \
    libtinyxml-dev \
    libpcre3-dev \
    liblog4cxx-dev \
    libjsoncpp-dev \
    libqhull-dev \
    && rm -rf /var/lib/apt/lists/*

RUN npm i -g @openai/codex
