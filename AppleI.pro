#-------------------------------------------------
#
# Project created by QtCreator 2019-03-16T02:33:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppleI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
	cpu6502/cpu6502.cpp \
	utils/utils.cpp \
    console.cpp \
    computer/systembus.cpp \
    computer/computer.cpp \
    computer/keyboard.cpp \
    cpu6502/memory.cpp \
    qtkeyboard.cpp

HEADERS  += mainwindow.h \
	cpu6502/cpu6502.h \
	utils/utils.h \
	console.h \
    cpu6502/memory.h \
    computer/systembus.h \
    computer/device.h \
    computer/computer.h \
    computer/keyboard.h \
    qtkeyboard.h

FORMS    += mainwindow.ui
