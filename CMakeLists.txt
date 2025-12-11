# CMakeLists.txt - 使用CMake编译（如果安装了CMake）

cmake_minimum_required(VERSION 3.10)
project(GymManagementSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 优先查找Qt6，如果找不到则使用Qt5
find_package(Qt6 QUIET COMPONENTS Core Widgets Gui)
if(Qt6_FOUND)
    message(STATUS "使用 Qt6")
    set(QT_VERSION_MAJOR 6)
else()
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)
    message(STATUS "使用 Qt5")
    set(QT_VERSION_MAJOR 5)
endif()

# 包含头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 源文件
set(SOURCES
    main.cpp
    mainwindow.cpp
    loginwindow.cpp
    memberdialog.cpp
    coachdialog.cpp
    coursedialog.cpp
    equipdialog.cpp
    reservationdialog.cpp
    statisticsdialog.cpp
    user.cpp
    member.cpp
    coach.cpp
    course.cpp
    equipment.cpp
    reservation.cpp
    datamanager.cpp
)

# 头文件
set(HEADERS
    mainwindow.h
    loginwindow.h
    memberdialog.h
    coachdialog.h
    coursedialog.h
    equipdialog.h
    reservationdialog.h
    statisticsdialog.h
    user.h
    member.h
    coach.h
    course.h
    equipment.h
    reservation.h
    datamanager.h
)

# 自动处理Qt的MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 链接Qt库
if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(${PROJECT_NAME}
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
    )
else()
    target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
    )
endif()



