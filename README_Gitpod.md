# Gitpod 在线运行指南

## 📖 简介

这个项目已配置好 Gitpod 环境，可以在浏览器中直接运行，**无需本地安装 Qt**！

## 🚀 快速开始

### 方法1：通过 Gitpod 网站

1. **将项目推送到 GitHub**
   ```bash
   git init
   git add .
   git commit -m "Initial commit"
   git remote add origin <你的GitHub仓库地址>
   git push -u origin main
   ```

2. **在浏览器中打开**
   - 访问 https://gitpod.io
   - 在地址栏输入你的 GitHub 仓库地址
   - 或者直接访问：`https://gitpod.io/#<你的GitHub仓库地址>`

3. **等待环境配置完成**
   - Gitpod 会自动安装 Qt 和编译工具
   - 首次启动可能需要 5-10 分钟

### 方法2：使用浏览器扩展

1. 安装 [Gitpod 浏览器扩展](https://www.gitpod.io/docs/browser-extension)
2. 在 GitHub 仓库页面点击 "Gitpod" 按钮

## 📝 使用说明

### 编译项目

在 Gitpod 终端中运行：

```bash
./build.sh
```

### 运行应用

```bash
./run.sh
```

### 清理编译文件

```bash
./clean.sh
```

## 🖥️ 图形界面

Gitpod 支持 X11 图形界面，Qt 应用会自动显示在浏览器中。

如果遇到显示问题，可以：

1. **检查 X11 服务**
   ```bash
   echo $DISPLAY
   ```

2. **手动启动虚拟显示**
   ```bash
   Xvfb :99 -screen 0 1024x768x24 &
   export DISPLAY=:99
   ```

## 🔧 环境配置

### 已安装的组件

- ✅ Qt 6.5.0（或系统 Qt6 包）
- ✅ CMake 3.x
- ✅ GCC 编译器
- ✅ 所有 Qt 依赖库

### 环境变量

- `QT_DIR`: Qt 安装目录
- `DISPLAY`: X11 显示服务器
- `CMAKE_PREFIX_PATH`: CMake 查找 Qt 的路径

## ⚙️ 自定义配置

### 修改 Qt 版本

编辑 `.gitpod/setup.sh`，修改 Qt 版本号：

```bash
QT_DIR="/home/gitpod/Qt/6.5.0/gcc_64"  # 改为你需要的版本
```

### 使用不同的构建系统

项目支持两种构建方式：

1. **CMake**（推荐）
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

2. **qmake**
   ```bash
   qmake StudentManagementSystem.pro
   make
   ```

## 🐛 常见问题

### 问题1：编译失败，找不到 Qt

**解决方案：**
```bash
# 检查 Qt 是否安装
which qmake
qmake --version

# 如果未安装，手动运行安装脚本
bash .gitpod/setup.sh
```

### 问题2：应用无法显示

**解决方案：**
```bash
# 检查 DISPLAY 变量
echo $DISPLAY

# 启动虚拟显示
Xvfb :99 -screen 0 1024x768x24 &
export DISPLAY=:99
```

### 问题3：找不到可执行文件

**解决方案：**
```bash
# 确保已编译
./build.sh

# 检查可执行文件
ls -la build/GymManagementSystem
```

## 💡 提示

1. **首次启动较慢**：Gitpod 需要下载和安装 Qt，请耐心等待
2. **数据持久化**：Gitpod 会保存工作区，但建议将重要数据推送到 Git
3. **免费额度**：Gitpod 免费版每月有使用时间限制
4. **性能**：在线环境性能可能略低于本地，但足够开发和测试

## 📚 更多资源

- [Gitpod 文档](https://www.gitpod.io/docs)
- [Qt 文档](https://doc.qt.io/)
- [CMake 文档](https://cmake.org/documentation/)

## 🎉 开始使用

现在就访问你的 GitHub 仓库，在地址前加上 `gitpod.io/#` 即可开始！

例如：
```
https://gitpod.io/#https://github.com/你的用户名/你的仓库名
```

