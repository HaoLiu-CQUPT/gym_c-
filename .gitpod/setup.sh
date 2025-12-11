#!/bin/bash
# Gitpod 环境设置脚本
# 安装 Qt 和配置编译环境

set -e

echo "🔧 开始配置 Qt 开发环境..."

# 检查 Qt 是否已安装
QT_DIR="/home/gitpod/Qt/6.5.0/gcc_64"
if [ -d "$QT_DIR" ] && [ -f "$QT_DIR/bin/qmake" ]; then
    echo "✅ Qt 已安装，跳过安装步骤"
else
    echo "📦 下载并安装 Qt..."
    
    # 创建临时目录
    TEMP_DIR=$(mktemp -d)
    cd "$TEMP_DIR"
    
    # 使用 apt 安装 Qt6（更可靠的方法）
    echo "📦 使用 apt 安装 Qt6 开发包..."
    sudo apt-get update
    sudo apt-get install -y \
        qt6-base-dev \
        qt6-base-dev-tools \
        qt6-tools-dev \
        qt6-tools-dev-tools \
        qmake6 \
        cmake \
        ninja-build \
        || {
            echo "⚠️  Qt6 包安装失败，尝试备用方案..."
            # 备用方案：安装 Qt5
            sudo apt-get install -y \
                qtbase5-dev \
                qtbase5-dev-tools \
                qttools5-dev \
                qmake \
                || echo "❌ Qt 安装失败"
        }
    
    # 清理临时目录
    cd -
    rm -rf "$TEMP_DIR"
fi

# 配置环境变量
echo "🔨 配置环境变量..."
mkdir -p /home/gitpod/.bashrc.d

cat > /home/gitpod/.bashrc.d/qt_env.sh << 'EOF'
# Qt 环境变量

# 优先使用 Qt6
if command -v qmake6 &> /dev/null; then
    export PATH="$(dirname $(which qmake6)):$PATH"
    QMAKE_PATH=$(which qmake6)
    QT_PREFIX=$(dirname $(dirname $QMAKE_PATH))
    export CMAKE_PREFIX_PATH="${QT_PREFIX}:${CMAKE_PREFIX_PATH}"
    echo "✅ 使用 Qt6: $QT_PREFIX"
# 备用：使用 Qt5
elif command -v qmake &> /dev/null; then
    export PATH="$(dirname $(which qmake)):$PATH"
    QMAKE_PATH=$(which qmake)
    QT_PREFIX=$(dirname $(dirname $QMAKE_PATH))
    export CMAKE_PREFIX_PATH="${QT_PREFIX}:${CMAKE_PREFIX_PATH}"
    echo "✅ 使用 Qt5: $QT_PREFIX"
fi

# 如果使用手动安装的 Qt
QT_DIR="/home/gitpod/Qt/6.5.0/gcc_64"
if [ -d "$QT_DIR" ] && [ -f "$QT_DIR/bin/qmake" ]; then
    export PATH="$QT_DIR/bin:$PATH"
    export LD_LIBRARY_PATH="$QT_DIR/lib:$LD_LIBRARY_PATH"
    export QT_QPA_PLATFORM_PLUGIN_PATH="$QT_DIR/plugins"
    export CMAKE_PREFIX_PATH="${QT_DIR}:${CMAKE_PREFIX_PATH}"
fi
EOF

# 立即加载环境变量
source /home/gitpod/.bashrc.d/qt_env.sh

# 创建编译脚本
echo "📝 创建编译脚本..."
cat > /workspace/build.sh << 'EOF'
#!/bin/bash
set -e

echo "🔨 开始编译项目..."

# 加载环境变量
if [ -f ~/.bashrc.d/qt_env.sh ]; then
    source ~/.bashrc.d/qt_env.sh
fi

# 创建构建目录
mkdir -p build
cd build

# 优先使用 CMake
if command -v cmake &> /dev/null; then
    echo "📋 使用 CMake 配置项目..."
    
    # 检测 Qt 版本
    if command -v qmake6 &> /dev/null; then
        echo "🔍 检测到 Qt6"
        cmake .. -DCMAKE_BUILD_TYPE=Release
    elif command -v qmake &> /dev/null; then
        echo "🔍 检测到 Qt5"
        # 修改 CMakeLists.txt 使用 Qt5
        cmake .. -DCMAKE_BUILD_TYPE=Release
    else
        echo "❌ 未找到 Qt，请先安装"
        exit 1
    fi
    
    cmake --build . -j$(nproc)
    echo "✅ 编译完成！可执行文件在: build/GymManagementSystem"
# 备用：使用 qmake
elif command -v qmake6 &> /dev/null || command -v qmake &> /dev/null; then
    echo "📋 使用 qmake 编译项目..."
    qmake ../StudentManagementSystem.pro
    make -j$(nproc)
    echo "✅ 编译完成！可执行文件在: build/GymManagementSystem"
else
    echo "❌ 未找到 CMake 或 qmake，请先安装"
    exit 1
fi
EOF

chmod +x /workspace/build.sh

# 创建运行脚本
cat > /workspace/run.sh << 'EOF'
#!/bin/bash
set -e

echo "🚀 启动应用..."

# 检查是否已编译
if [ ! -f "build/GymManagementSystem" ]; then
    echo "⚠️  未找到可执行文件，先编译项目..."
    ./build.sh
fi

# 设置显示
export DISPLAY=:99

# 启动 Xvfb（虚拟显示）
if ! pgrep -x "Xvfb" > /dev/null; then
    echo "🖥️  启动虚拟显示服务器..."
    Xvfb :99 -screen 0 1024x768x24 > /dev/null 2>&1 &
    sleep 2
fi

# 运行应用
cd build
./GymManagementSystem
EOF

chmod +x /workspace/run.sh

# 创建清理脚本
cat > /workspace/clean.sh << 'EOF'
#!/bin/bash
echo "🧹 清理编译文件..."
rm -rf build
echo "✅ 清理完成！"
EOF

chmod +x /workspace/clean.sh

# 复制快速启动脚本
if [ -f /workspace/.gitpod/quick-start.sh ]; then
    cp /workspace/.gitpod/quick-start.sh /workspace/quick-start.sh
    chmod +x /workspace/quick-start.sh
fi

# 创建数据目录
mkdir -p /workspace/data

echo "✅ 环境配置完成！"
echo ""
echo "📋 下一步："
echo "  1. 运行 ./build.sh 编译项目"
echo "  2. 运行 ./run.sh 启动应用"
echo ""
echo "💡 提示：Gitpod 会自动配置 X11 转发，可以直接显示 GUI"

