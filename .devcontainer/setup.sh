#!/bin/bash
# 不设置 set -e，允许脚本继续执行即使某些步骤失败

echo "🚀 开始配置 Qt 开发环境..."

# 确保在正确的目录
cd "${WORKSPACE_FOLDER:-/workspaces/${GITHUB_REPOSITORY##*/}}"

# 更新系统（允许失败，继续执行）
echo "📦 更新软件包列表..."
sudo apt-get update || echo "⚠️  更新失败，继续执行..."

# 安装基础编译工具
echo "📦 安装编译工具..."
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
    libxcb-xinput-dev \
    libfontconfig1-dev \
    libfreetype6-dev \
    libx11-dev \
    libx11-xcb-dev \
    libxext-dev \
    libxfixes-dev \
    libxi-dev \
    libxrender-dev \
    libxkbcommon-x11-dev || echo "⚠️  部分依赖安装失败，继续..."

# 尝试安装 Qt6（优先）
echo "📦 尝试安装 Qt6..."
if sudo apt-get install -y qt6-base-dev qt6-base-dev-tools 2>&1 | tee /tmp/qt6_install.log; then
    echo "✅ Qt6 安装成功"
    export QT_VERSION=6
    QT_INSTALLED=true
else
    echo "⚠️  Qt6 安装失败，尝试 Qt5..."
    # 如果 Qt6 不可用，尝试 Qt5
    if sudo apt-get install -y qtbase5-dev qtbase5-dev-tools qttools5-dev-tools 2>&1 | tee /tmp/qt5_install.log; then
        echo "✅ Qt5 安装成功"
        export QT_VERSION=5
        QT_INSTALLED=true
    else
        echo "⚠️  Qt 安装失败，但环境可以继续使用"
        echo "💡 提示：你可以稍后手动安装 Qt，或使用在线安装方式"
        QT_INSTALLED=false
    fi
fi

# 安装 X11 和 VNC（用于图形界面，可选）
echo "📦 安装图形界面支持..."
sudo apt-get install -y xvfb x11vnc fluxbox || echo "⚠️  图形界面工具安装失败，继续..."

# 创建启动脚本（如果目录存在）
WORKSPACE_DIR="${WORKSPACE_FOLDER:-/workspaces/${GITHUB_REPOSITORY##*/}}"
if [ -d "$WORKSPACE_DIR" ]; then
    cat > "$WORKSPACE_DIR/start-vnc.sh" << 'EOF'
#!/bin/bash
Xvfb :99 -screen 0 1024x768x24 &
export DISPLAY=:99
fluxbox &
x11vnc -display :99 -nopw -listen localhost -xkb -ncache 10 -ncache_cr -forever &
EOF
    chmod +x "$WORKSPACE_DIR/start-vnc.sh" || true
fi

echo ""
echo "✅ 环境配置完成！"
echo ""
if [ "$QT_INSTALLED" = true ]; then
    echo "📝 使用说明："
    echo "  1. 编译项目: mkdir -p build && cd build && cmake .. && make"
    echo "  2. 运行项目: cd build && ./GymManagementSystem"
    echo "  3. 如果需要 VNC: ./start-vnc.sh"
else
    echo "⚠️  Qt 未安装，请手动安装："
    echo "  sudo apt-get install -y qt6-base-dev qt6-base-dev-tools"
    echo "  或"
    echo "  sudo apt-get install -y qtbase5-dev qtbase5-dev-tools"
fi
echo ""

