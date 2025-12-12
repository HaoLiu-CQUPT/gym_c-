#!/bin/bash
# 如果自动安装失败，可以手动运行此脚本

echo "🔧 手动安装 Qt..."

# 更新软件包列表
sudo apt-get update

# 尝试安装 Qt6
echo "尝试安装 Qt6..."
if sudo apt-get install -y qt6-base-dev qt6-base-dev-tools; then
    echo "✅ Qt6 安装成功！"
    qmake6 --version || qmake --version
    exit 0
fi

# 如果 Qt6 失败，尝试 Qt5
echo "Qt6 不可用，尝试 Qt5..."
if sudo apt-get install -y qtbase5-dev qtbase5-dev-tools; then
    echo "✅ Qt5 安装成功！"
    qmake --version
    exit 0
fi

echo "❌ Qt 安装失败"
echo "💡 提示：可以尝试从源码编译或使用其他方式安装"
exit 1


