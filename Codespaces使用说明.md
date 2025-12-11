# GitHub Codespaces 使用说明

## 🚀 快速开始

### 1. 打开 Codespaces
1. 访问：https://github.com/HaoLiu-CQUPT/gym_c-
2. 点击绿色的 "Code" 按钮
3. 选择 "Codespaces" → "Create codespace on main"

### 2. 等待环境配置
- 首次启动需要 3-5 分钟
- 如果看到警告，可以继续使用

### 3. 检查 Qt 是否安装
在终端运行：
```bash
qmake --version
# 或
qmake6 --version
```

## 🔧 如果 Qt 未安装

### 方法1：手动安装（推荐）
```bash
# 安装 Qt6
sudo apt-get update
sudo apt-get install -y qt6-base-dev qt6-base-dev-tools

# 或安装 Qt5
sudo apt-get install -y qtbase5-dev qtbase5-dev-tools
```

### 方法2：使用提供的脚本
```bash
bash .devcontainer/手动安装Qt.sh
```

## 📝 编译和运行项目

### 1. 编译项目
```bash
mkdir -p build
cd build
cmake ..
make
```

### 2. 运行项目
```bash
# 在 build 目录中
./GymManagementSystem

# 或者从项目根目录
cd build && ./GymManagementSystem
```

## 🖥️ 图形界面支持

### 使用 X11 转发（Codespaces 自动支持）
Codespaces 会自动配置 X11 转发，可以直接运行图形程序。

### 如果需要 VNC（可选）
```bash
# 启动 VNC 服务器
./start-vnc.sh

# 然后通过端口转发访问（Codespaces 会自动处理）
```

## ❓ 常见问题

### Q: 编译时找不到 Qt
**A:** 确保 Qt 已安装：
```bash
sudo apt-get install -y qt6-base-dev qt6-base-dev-tools
```

### Q: 运行时没有图形界面
**A:** Codespaces 支持 X11 转发，确保：
1. 环境变量已设置：`export DISPLAY=:0`
2. 使用正确的平台插件：`export QT_QPA_PLATFORM=xcb`

### Q: 编译错误
**A:** 检查：
1. CMake 是否正确找到 Qt：`cmake ..` 应该显示找到 Qt
2. 所有依赖是否安装：`sudo apt-get install -y build-essential cmake`

## 💡 提示

- Codespaces 免费额度：每月 60 小时
- 环境配置只需要一次，后续启动会更快
- 如果遇到问题，可以查看日志：`View Creation Log`

## 🔄 重新配置环境

如果需要重新配置：
```bash
bash .devcontainer/setup.sh
```

