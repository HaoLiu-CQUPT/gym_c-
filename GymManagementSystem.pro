QT += core gui widgets

CONFIG += c++11

TARGET = GymManagementSystem
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    loginwindow.cpp \
    memberdialog.cpp \
    coachdialog.cpp \
    coursedialog.cpp \
    equipdialog.cpp \
    reservationdialog.cpp \
    statisticsdialog.cpp \
    user.cpp \
    member.cpp \
    coach.cpp \
    course.cpp \
    equipment.cpp \
    reservation.cpp \
    datamanager.cpp

HEADERS += \
    mainwindow.h \
    loginwindow.h \
    memberdialog.h \
    coachdialog.h \
    coursedialog.h \
    equipdialog.h \
    reservationdialog.h \
    statisticsdialog.h \
    user.h \
    member.h \
    coach.h \
    course.h \
    equipment.h \
    reservation.h \
    datamanager.h

# FORMS 文件已移除，使用代码创建UI
