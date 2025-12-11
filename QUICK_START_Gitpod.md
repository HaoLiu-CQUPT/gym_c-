# 🚀 Gitpod 快速开始指南

## 一分钟快速开始

### 步骤 1：推送到 GitHub

```bash
git init
git add .
git commit -m "Add Gitpod configuration"
git remote add origin <你的GitHub仓库地址>
git push -u origin main
```

### 步骤 2：打开 Gitpod

在浏览器中访问：
```
https://gitpod.io/#<你的GitHub仓库地址>
```

或者安装 [Gitpod 浏览器扩展](https://www.gitpod.io/docs/browser-extension)，然后在 GitHub 仓库页面点击 "Gitpod" 按钮。

### 步骤 3：等待环境配置

首次启动会自动：
- ✅ 安装 Qt 6（或 Qt 5）
- ✅ 安装编译工具（CMake、GCC）
- ✅ 配置环境变量
- ✅ 创建编译和运行脚本

**预计时间：5-10 分钟**

### 步骤 4：运行项目

环境配置完成后，在终端运行：

```bash
./quick-start.sh
```

或者分步执行：

```bash
# 编译
./build.sh

# 运行
./run.sh
```

## 📋 可用命令

| 命令 | 说明 |
|------|------|
| `./quick-start.sh` | 一键编译并运行 |
| `./build.sh` | 编译项目 |
| `./run.sh` | 运行应用 |
| `./clean.sh` | 清理编译文件 |

## 🖥️ 查看图形界面

Gitpod 会自动配置 X11 图形界面，Qt 应用会直接显示在浏览器中。

如果看不到界面，检查：
```bash
echo $DISPLAY  # 应该显示 :99
```

## ❓ 常见问题

**Q: 编译失败，找不到 Qt？**  
A: 运行 `bash .gitpod/setup.sh` 重新安装

**Q: 应用无法显示？**  
A: 运行 `Xvfb :99 -screen 0 1024x768x24 &` 启动虚拟显示

**Q: 首次启动很慢？**  
A: 正常，需要下载和安装 Qt，请耐心等待

## 🎉 完成！

现在你可以在浏览器中运行 Qt 应用了，无需本地安装任何软件！

更多详细信息请查看 [README_Gitpod.md](README_Gitpod.md)

