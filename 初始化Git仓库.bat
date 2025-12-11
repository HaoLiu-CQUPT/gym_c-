@echo off
chcp 65001 >nul
echo ========================================
echo Git 仓库初始化脚本
echo ========================================
echo.

REM 检查是否已存在 .git 目录
if exist .git (
    echo ⚠️  Git 仓库已存在！
    echo.
    echo 当前 Git 状态：
    git status
    echo.
    pause
    exit /b
)

REM 检查是否安装了 Git
where git >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ 未检测到 Git，请先安装 Git
    echo.
    echo 下载地址：https://git-scm.com/download/win
    echo.
    pause
    exit /b 1
)

echo ✅ 检测到 Git
echo.

REM 初始化 Git 仓库
echo 📦 初始化 Git 仓库...
git init
if %errorlevel% neq 0 (
    echo ❌ Git 初始化失败
    pause
    exit /b 1
)

echo ✅ Git 仓库初始化成功
echo.

REM 创建 .gitignore 文件（如果不存在）
if not exist .gitignore (
    echo 📝 创建 .gitignore 文件...
    (
        echo # 编译输出
        echo build/
        echo *.o
        echo *.a
        echo *.so
        echo *.exe
        echo.
        echo # Qt 相关
        echo *.pro.user
        echo *.pro.user.*
        echo *.qmake.stash
        echo moc_*.cpp
        echo moc_*.h
        echo qrc_*.cpp
        echo ui_*.h
        echo.
        echo # IDE 文件
        echo .vscode/
        echo .idea/
        echo *.swp
        echo *.swo
        echo *~
        echo.
        echo # 系统文件
        echo .DS_Store
        echo Thumbs.db
        echo.
        echo # 数据文件（可选，如果需要版本控制可以注释掉）
        echo # data/
        echo # *.txt
    ) > .gitignore
    echo ✅ .gitignore 创建成功
    echo.
)

REM 添加所有文件
echo 📤 添加文件到 Git...
git add .
if %errorlevel% neq 0 (
    echo ❌ 添加文件失败
    pause
    exit /b 1
)

echo ✅ 文件添加成功
echo.

REM 创建初始提交
echo 💾 创建初始提交...
git commit -m "Initial commit: Gym Management System with Gitpod configuration"
if %errorlevel% neq 0 (
    echo ⚠️  提交失败（可能是没有更改或未配置用户信息）
    echo.
    echo 如果是因为未配置用户信息，请运行：
    echo   git config --global user.name "你的名字"
    echo   git config --global user.email "你的邮箱"
    echo.
    pause
    exit /b 1
)

echo ✅ 初始提交成功
echo.

REM 显示当前状态
echo 📋 当前 Git 状态：
git status
echo.

echo ========================================
echo ✅ Git 仓库初始化完成！
echo ========================================
echo.
echo 📝 下一步操作：
echo.
echo 1. 在 GitHub 上创建新仓库
echo    - 访问 https://github.com/new
echo    - 创建仓库（不要初始化 README）
echo.
echo 2. 连接到远程仓库：
echo    git remote add origin https://github.com/你的用户名/仓库名.git
echo    git branch -M main
echo    git push -u origin main
echo.
echo 3. 在 Gitpod 中打开：
echo    https://gitpod.io/#https://github.com/你的用户名/仓库名
echo.
pause

