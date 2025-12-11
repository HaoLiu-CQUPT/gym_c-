# Gitpod Dockerfile
# 基于 Ubuntu 22.04，安装 Qt 和编译工具

FROM gitpod/workspace-base:latest

# 安装系统依赖
USER root
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libx11-dev \
    libxext-dev \
    libxrender-dev \
    libfontconfig1-dev \
    libdbus-1-dev \
    libxkbcommon-dev \
    libxkbcommon-x11-dev \
    libxcb1-dev \
    libxcb-glx0-dev \
    libxcb-keysyms1-dev \
    libxcb-image0-dev \
    libxcb-shm0-dev \
    libxcb-icccm4-dev \
    libxcb-sync-dev \
    libxcb-xfixes0-dev \
    libxcb-shape0-dev \
    libxcb-randr0-dev \
    libxcb-render-util0-dev \
    libxcb-util-dev \
    libxcb-xinerama0-dev \
    libxcb-xkb-dev \
    libx11-xcb-dev \
    xvfb \
    x11vnc \
    fluxbox \
    wget \
    curl \
    git \
    && rm -rf /var/lib/apt/lists/*

# 切换到 gitpod 用户
USER gitpod

# 设置工作目录
WORKDIR /home/gitpod

# 创建 Qt 安装目录
RUN mkdir -p /home/gitpod/Qt

# 设置环境变量（将在 setup.sh 中进一步配置）
ENV PATH="/home/gitpod/Qt/6.5.0/gcc_64/bin:${PATH}"
ENV LD_LIBRARY_PATH="/home/gitpod/Qt/6.5.0/gcc_64/lib:${LD_LIBRARY_PATH}"
ENV QT_QPA_PLATFORM_PLUGIN_PATH="/home/gitpod/Qt/6.5.0/gcc_64/plugins"

