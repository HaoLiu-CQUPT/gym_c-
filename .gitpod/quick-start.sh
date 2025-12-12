#!/bin/bash
# Gitpod 快速启动脚本
# 一键编译并运行项目

set -e

echo "🚀 快速启动 Qt 项目"
echo "===================="
echo ""

# 检查环境
echo "📋 检查环境..."
if ! command -v cmake &> /dev/null && ! command -v qmake &> /dev/null && ! command -v qmake6 &> /dev/null; then
    echo "❌ 未找到编译工具，正在安装..."
    bash .gitpod/setup.sh
fi

# 加载环境变量
if [ -f ~/.bashrc.d/qt_env.sh ]; then
    source ~/.bashrc.d/qt_env.sh
fi

# 编译项目
echo ""
echo "🔨 编译项目..."
./build.sh

# 运行项目
echo ""
echo "🎯 启动应用..."
./run.sh


