# vcpkg 和 Qt 安装指南

## 方法一：使用自动化脚本（推荐）

### 步骤 1：安装 Git
如果还没有安装 Git，请先下载安装：
- 下载地址：https://git-scm.com/download/win
- 安装时选择默认选项即可

### 步骤 2：运行安装脚本
1. 双击运行 `安装vcpkg和Qt.bat`
2. 等待安装完成（可能需要30-60分钟，取决于网络速度）
3. 安装完成后运行 `配置环境变量.bat` 配置环境变量

### 步骤 3：验证安装
打开新的命令行窗口，运行：
```bash
qmake --version
```
如果显示版本号，说明安装成功！

## 方法二：手动安装

### 1. 安装 vcpkg

```bash
# 克隆 vcpkg
cd D:\
git clone https://github.com/Microsoft/vcpkg.git

# 进入 vcpkg 目录
cd vcpkg

# 运行引导脚本
.\bootstrap-vcpkg.bat
```

### 2. 安装 Qt

```bash
# 安装 Qt（x64版本，包含所有基础组件）
.\vcpkg.exe install qt5-base:x64-windows

# 或者安装完整版 Qt（包含所有模块，但体积更大）
.\vcpkg.exe install qt5[all]:x64-windows
```

### 3. 配置环境变量

将以下路径添加到系统 PATH 环境变量：
```
D:\vcpkg\installed\x64-windows\tools\qt5\bin
```

**或者使用命令行（需要管理员权限）：**
```bash
setx PATH "%PATH%;D:\vcpkg\installed\x64-windows\tools\qt5\bin" /M
```

### 4. 验证安装

重启命令行后运行：
```bash
qmake --version
```

## 使用 vcpkg 安装的 Qt 编译项目

安装完成后，可以使用提供的 `编译.bat` 脚本编译项目，或者手动运行：

```bash
# 设置 vcpkg 工具链（可选，如果使用 CMake）
set VCPKG_ROOT=D:\vcpkg

# 使用 qmake 编译
qmake StudentManagementSystem.pro
mingw32-make
```

## 常见问题

### 1. Git 克隆失败
- 检查网络连接
- 可能需要设置代理
- 或者手动下载 vcpkg 的 zip 包解压

### 2. Qt 安装很慢
- 这是正常的，Qt 库文件较大（约 200-500MB）
- 建议在网络良好的情况下安装
- 可以使用镜像源加速

### 3. 找不到 qmake
- 检查环境变量是否正确配置
- 重启命令行窗口
- 检查 Qt 是否真的安装在 `D:\vcpkg\installed\x64-windows\tools\qt5\bin`

### 4. 编译错误
- 确保安装了 C++ 编译器（MinGW 或 MSVC）
- 检查 vcpkg 是否正确安装了 Qt

## 替代方案

如果 vcpkg 安装困难，可以考虑：
1. 直接从 Qt 官网下载 Qt 安装包
2. 使用包管理器如 Chocolatey：`choco install qt5`
3. 使用学校机房已安装 Qt 的电脑编译



