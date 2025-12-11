@echo off
chcp 65001 >nul
echo ========================================
echo 推送到 GitHub 脚本
echo ========================================
echo.

REM 检查是否是 Git 仓库
if not exist .git (
    echo ❌ 当前目录不是 Git 仓库
    echo.
    echo 请先运行 "初始化Git仓库.bat"
    echo.
    pause
    exit /b 1
)

REM 检查是否配置了远程仓库
git remote -v >nul 2>&1
if %errorlevel% neq 0 (
    echo ⚠️  未配置远程仓库
    echo.
    set /p REPO_URL="请输入 GitHub 仓库地址（例如：https://github.com/用户名/仓库名.git）: "
    if "!REPO_URL!"=="" (
        echo ❌ 未输入仓库地址
        pause
        exit /b 1
    )
    echo.
    echo 📡 添加远程仓库...
    git remote add origin !REPO_URL!
    echo ✅ 远程仓库添加成功
    echo.
)

REM 显示当前状态
echo 📋 当前 Git 状态：
git status
echo.

REM 检查是否有未提交的更改
git diff --quiet
if %errorlevel% neq 0 (
    echo 📝 检测到未提交的更改
    echo.
    set /p COMMIT_MSG="请输入提交信息（直接回车使用默认）: "
    if "!COMMIT_MSG!"=="" (
        set COMMIT_MSG=Update files
    )
    echo.
    echo 💾 提交更改...
    git add .
    git commit -m "!COMMIT_MSG!"
    if %errorlevel% neq 0 (
        echo ❌ 提交失败
        pause
        exit /b 1
    )
    echo ✅ 提交成功
    echo.
)

REM 检查分支名称
git branch --show-current > temp_branch.txt
set /p CURRENT_BRANCH=<temp_branch.txt
del temp_branch.txt

if not "!CURRENT_BRANCH!"=="main" (
    if not "!CURRENT_BRANCH!"=="master" (
        echo 🔀 当前分支: !CURRENT_BRANCH!
        set /p RENAME_BRANCH="是否重命名为 main？(Y/N): "
        if /i "!RENAME_BRANCH!"=="Y" (
            git branch -M main
            set CURRENT_BRANCH=main
        )
    )
)

REM 推送到远程
echo.
echo 📤 推送到 GitHub...
echo.

REM 检查是否已设置上游分支
git rev-parse --abbrev-ref --symbolic-full-name @{u} >nul 2>&1
if %errorlevel% neq 0 (
    echo 🔗 设置上游分支并推送...
    git push -u origin !CURRENT_BRANCH!
) else (
    echo 📤 推送到远程仓库...
    git push
)

if %errorlevel% neq 0 (
    echo.
    echo ❌ 推送失败
    echo.
    echo 可能的原因：
    echo 1. 未配置 GitHub 认证
    echo 2. 仓库地址不正确
    echo 3. 网络连接问题
    echo.
    echo 💡 提示：如果使用 HTTPS，可能需要配置 Personal Access Token
    echo    访问：https://github.com/settings/tokens
    echo.
    pause
    exit /b 1
)

echo.
echo ========================================
echo ✅ 推送成功！
echo ========================================
echo.

REM 显示远程仓库信息
git remote get-url origin > temp_url.txt
set /p REPO_URL=<temp_url.txt
del temp_url.txt

echo 📦 仓库地址: !REPO_URL!
echo.
echo 🚀 在 Gitpod 中打开：
echo    https://gitpod.io/#!REPO_URL!
echo.
echo 或者访问 GitHub 网页版查看：
echo    !REPO_URL!
echo.
pause

