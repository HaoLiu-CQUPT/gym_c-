# 🏋️ 健身房管理系统 (Gym Management System)

一个基于 Qt Widgets 开发的桌面应用程序，用于管理健身房的会员、教练、课程、器械和预约等业务。

## 📋 目录

- [功能特性](#功能特性)
- [技术栈](#技术栈)
- [系统要求](#系统要求)
- [快速开始](#快速开始)
- [项目结构](#项目结构)
- [功能模块](#功能模块)
- [用户角色](#用户角色)
- [编译运行](#编译运行)
- [在线运行](#在线运行)
- [数据存储](#数据存储)
- [开发说明](#开发说明)
- [常见问题](#常见问题)
- [许可证](#许可证)

## ✨ 功能特性

### 核心功能

- **用户认证系统**
  - 多角色登录（管理员、前台、教练）
  - 安全的密码验证机制

- **会员管理**
  - 添加、编辑、删除会员信息
  - 会员信息查询和搜索
  - 会员状态管理

- **教练管理**
  - 教练信息管理
  - 教练课程关联
  - 教练查询功能

- **课程管理**
  - 课程创建和编辑
  - 课程与教练关联
  - 课程信息维护

- **器械管理**
  - 器械信息管理
  - 器械状态跟踪
  - 器械查询功能

- **预约管理**
  - 会员课程预约
  - 预约时间管理
  - 预约查询和统计

- **统计报表**
  - 会员统计
  - 收入统计
  - 活跃会员统计
  - 数据可视化

- **数据管理**
  - 数据持久化存储
  - 数据导入导出
  - 数据备份功能

## 🛠️ 技术栈

- **框架**: Qt 5.x / Qt 6.x (Qt Widgets)
- **语言**: C++11
- **构建系统**: CMake / qmake
- **数据存储**: 文件系统 (JSON/文本格式)
- **UI**: Qt Widgets (原生桌面应用)

## 💻 系统要求

### 最低要求

- **操作系统**: Windows 7+, Linux, macOS 10.12+
- **Qt 版本**: Qt 5.12+ 或 Qt 6.0+
- **编译器**: 
  - Windows: MinGW 或 MSVC
  - Linux: GCC 5.0+
  - macOS: Clang
- **CMake**: 3.10+ (可选，如果使用 CMake 构建)

## 🚀 快速开始

### 方法一：使用 Qt Creator（推荐新手）

1. **安装 Qt**
   - 访问 [Qt 官网](https://www.qt.io/download) 下载 Qt Online Installer
   - 安装 Qt 6.x 或 Qt 5.x 及 MinGW 编译器
   - 安装 Qt Creator IDE

2. **打开项目**
   - 启动 Qt Creator
   - 文件 → 打开文件或项目
   - 选择 `GymManagementSystem.pro`

3. **配置构建套件**
   - 选择已安装的 Qt 版本和编译器
   - 点击"配置项目"

4. **运行**
   - 点击左下角的运行按钮（绿色播放图标）

### 方法二：使用命令行

#### Windows (MinGW)

```powershell
# 进入项目目录
cd d:\c++_work

# 生成 Makefile
qmake GymManagementSystem.pro

# 编译
mingw32-make

# 运行
.\GymManagementSystem.exe
```

#### Linux

```bash
# 安装依赖
sudo apt-get install qt6-base-dev qt6-base-dev-tools cmake build-essential

# 编译
mkdir build && cd build
cmake ..
make

# 运行
./GymManagementSystem
```

#### macOS

```bash
# 安装 Qt (使用 Homebrew)
brew install qt@6

# 编译
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt@6)
make

# 运行
./GymManagementSystem
```

详细安装说明请参考 [运行指南_Windows.md](运行指南_Windows.md)

## 📁 项目结构

```
c++_work/
├── .devcontainer/          # GitHub Codespaces 配置
├── .gitpod/               # Gitpod 配置
├── CMakeLists.txt         # CMake 构建配置
├── GymManagementSystem.pro # qmake 项目文件
│
├── main.cpp               # 程序入口
├── loginwindow.h/cpp      # 登录窗口
├── mainwindow.h/cpp       # 主窗口
│
├── user.h/cpp             # 用户类
├── member.h/cpp           # 会员类
├── coach.h/cpp            # 教练类
├── course.h/cpp           # 课程类
├── equipment.h/cpp        # 器械类
├── reservation.h/cpp      # 预约类
├── datamanager.h/cpp      # 数据管理类
│
├── memberdialog.h/cpp     # 会员管理对话框
├── coachdialog.h/cpp      # 教练管理对话框
├── coursedialog.h/cpp     # 课程管理对话框
├── equipdialog.h/cpp      # 器械管理对话框
├── reservationdialog.h/cpp # 预约管理对话框
├── statisticsdialog.h/cpp  # 统计对话框
│
└── README.md              # 项目说明文档
```

## 🎯 功能模块

### 1. 用户认证模块

- **登录系统**: 支持用户名和密码登录
- **角色管理**: 三种用户角色（管理员、前台、教练）
- **权限控制**: 不同角色拥有不同的功能权限

### 2. 会员管理模块

- 会员信息录入（姓名、电话、会员卡号等）
- 会员信息修改和删除
- 会员查询和搜索
- 会员状态管理（活跃/暂停/过期）

### 3. 教练管理模块

- 教练信息管理
- 教练课程关联
- 教练查询功能

### 4. 课程管理模块

- 课程创建和编辑
- 课程信息维护
- 课程与教练关联

### 5. 器械管理模块

- 器械信息录入
- 器械状态跟踪
- 器械查询和维护记录

### 6. 预约管理模块

- 会员课程预约
- 预约时间管理
- 预约冲突检测
- 预约查询和统计

### 7. 统计报表模块

- 会员统计（总数、活跃数等）
- 收入统计
- 课程统计
- 数据可视化展示

## 👥 用户角色

### 管理员 (Admin)
- 拥有所有功能的完全访问权限
- 可以管理所有数据
- 可以查看所有统计信息

### 前台 (Reception)
- 可以管理会员信息
- 可以处理预约
- 可以查看部分统计信息

### 教练 (Coach)
- 可以查看自己的课程信息
- 可以查看预约信息
- 可以管理自己的课程

## 🌐 在线运行

如果不想在本地安装 Qt，可以使用在线开发环境：

### GitHub Codespaces（推荐）

1. 访问项目 GitHub 仓库
2. 点击 "Code" → "Codespaces" → "Create codespace on main"
3. 等待环境配置完成
4. 在终端中运行：
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ./GymManagementSystem
   ```

### Gitpod

1. 访问：`https://gitpod.io/HaoLiu-CQUPT/gym_c-.git`
2. 等待环境自动配置
3. 运行编译脚本：
   ```bash
   ./build.sh
   ./run.sh
   ```

详细说明请参考：
- [README_Gitpod.md](README_Gitpod.md)
- [运行平台选择指南.md](运行平台选择指南.md)

## 💾 数据存储

- **存储位置**: 项目目录下的 `data/` 文件夹
- **存储格式**: JSON/文本文件
- **数据文件**:
  - `users.txt` - 用户数据
  - `members.txt` - 会员数据
  - `coaches.txt` - 教练数据
  - `courses.txt` - 课程数据
  - `equipment.txt` - 器械数据
  - `reservations.txt` - 预约数据

数据会在程序启动时自动加载，退出时自动保存。

## 🔧 开发说明

### 代码规范

- 使用 C++11 标准
- 类名使用 PascalCase（如 `MainWindow`）
- 函数名使用 camelCase（如 `onAddMember`）
- 私有成员变量使用描述性命名

### 添加新功能

1. 在相应的类中添加方法
2. 在 `DataManager` 中添加数据管理逻辑
3. 在 UI 中添加相应的界面元素
4. 更新数据存储逻辑

### 构建选项

**使用 CMake**:
```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt
cmake --build .
```

**使用 qmake**:
```bash
qmake GymManagementSystem.pro
make  # 或 mingw32-make (Windows)
```

## ❓ 常见问题

### Q: 编译时找不到 Qt？

**A**: 确保 Qt 已正确安装，并在 CMake 命令中指定路径：
```bash
cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.5.0\mingw_64"
```

### Q: 运行时缺少 DLL 文件？

**A**: 将 Qt 的 bin 目录添加到系统 PATH，或将所需的 DLL 复制到可执行文件目录。

### Q: 如何修改默认数据？

**A**: 编辑 `datamanager.cpp` 中的 `initDefaultData()` 函数，或直接修改 `data/` 目录下的数据文件。

### Q: 支持数据库吗？

**A**: 当前版本使用文件系统存储，未来版本可能会添加数据库支持。

## 📝 更新日志

### v1.0.0
- ✅ 基础功能实现
- ✅ 用户认证系统
- ✅ 会员、教练、课程、器械、预约管理
- ✅ 统计报表功能
- ✅ 数据持久化存储
