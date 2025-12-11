# 在线运行Qt应用说明

## 当前项目状态
这是一个标准的Qt Widgets桌面应用程序，**不能直接在在线Qt平台上运行**，因为：
1. 需要Qt库和编译器
2. 使用了本地文件系统保存数据
3. 需要MOC（Meta-Object Compiler）处理

## 在线运行方案

### 方案1：转换为Qt WebAssembly（推荐但需要修改）

**优点：**
- 可以在浏览器中直接运行
- 无需下载Qt软件
- 跨平台访问

**缺点：**
- 需要修改代码（文件系统操作改为Web存储）
- 需要配置WebAssembly编译环境
- 首次加载可能较慢

**需要修改的地方：**
1. `datamanager.cpp` - 将文件保存改为使用IndexedDB或LocalStorage
2. 项目配置 - 添加WebAssembly编译配置
3. 可能需要调整UI以适应浏览器环境

### 方案2：使用在线IDE（如Gitpod、GitHub Codespaces）

**优点：**
- 可以在浏览器中开发
- 支持完整的Qt环境

**缺点：**
- 仍需要配置Qt环境
- 需要网络连接
- 可能需要付费

### 方案3：使用Qt在线示例平台

Qt官方提供在线体验平台，但只能运行预制的示例，不能运行自定义项目。

## 推荐做法

如果您想快速在线运行，建议：

1. **短期方案**：使用Gitpod或GitHub Codespaces配置Qt环境
2. **长期方案**：将应用转换为WebAssembly版本（需要重构数据存储部分）

## 快速测试方案

如果您只是想测试功能，可以考虑：
- 使用Replit的C++环境（但需要手动配置Qt）
- 使用Docker容器在线运行
- 使用GitHub Actions编译后部署到GitHub Pages（WebAssembly版本）

## 注意事项

WebAssembly版本的限制：
- 不能直接访问本地文件系统
- 某些Qt功能可能不支持
- 性能可能略低于原生应用
- 需要Web服务器托管

