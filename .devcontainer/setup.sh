#!/bin/bash
set -e

echo "🚀 开始配置 Qt 开发环境..."

# 更新系统
sudo apt-get update

# 安装基础编译工具
sudo apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    libgl1-mesa-dev \
    libxkbcommon-dev \
    libxcb1-dev \
    libxcb-render0-dev \
    libxcb-render-util0-dev \
    libxcb-xinerama0-dev \
    libxcb-cursor-dev \
    libxcb-icccm4-dev \
    libxcb-image0-dev \
    libxcb-shm0-dev \
    libxcb-util-dev \
    libxcb-xfixes0-dev \
    libxcb-xkb-dev \
    libxcb-keysyms1-dev \
    libxcb-randr0-dev \
    libxcb-shape0-dev \
    libxcb-sync-dev \
    libxcb-xinerama0-dev \
    libxcb-xinput-dev \
    libfontconfig1-dev \
    libfreetype6-dev \
    libx11-dev \
    libx11-xcb-dev \
    libxext-dev \
    libxfixes-dev \
    libxi-dev \
    libxrender-dev \
    libxcb1-dev \
    libxkbcommon-x11-dev

# 尝试安装 Qt6（优先）
if sudo apt-get install -y qt6-base-dev qt6-base-dev-tools 2>/dev/null; then
    echo "✅ Qt6 安装成功"
    export QT_VERSION=6
else
    # 如果 Qt6 不可用，尝试 Qt5
    echo "⚠️  Qt6 不可用，尝试安装 Qt5..."
    if sudo apt-get install -y qt5-default qtbase5-dev qtbase5-dev-tools qttools5-dev-tools; then
        echo "✅ Qt5 安装成功"
        export QT_VERSION=5
    else
        echo "❌ Qt 安装失败，请手动安装"
        exit 1
    fi
fi

# 安装 X11 和 VNC（用于图形界面）
sudo apt-get install -y xvfb x11vnc fluxbox

# 创建启动脚本
cat > /workspace/start-vnc.sh << 'EOF'
#!/bin/bash
Xvfb :99 -screen 0 1024x768x24 &
export DISPLAY=:99
fluxbox &
x11vnc -display :99 -nopw -listen localhost -xkb -ncache 10 -ncache_cr -forever &
EOF

chmod +x /workspace/start-vnc.sh

echo "✅ 环境配置完成！"
echo ""
echo "📝 使用说明："
echo "  1. 编译项目: mkdir build && cd build && cmake .. && make"
echo "  2. 运行项目: ./GymManagementSystem"
echo "  3. 如果需要 VNC: ./start-vnc.sh"
echo ""

