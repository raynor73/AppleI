#-------------------------------------------------
#
# Project created by QtCreator 2019-03-16T02:33:59
#
#-------------------------------------------------

QT       += core gui
CONFIG += exception

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
    qtkeyboard.cpp \
    computer/display.cpp \
    qtdisplay.cpp \
    computer/rom.cpp \
    computer/ram.cpp \
    loadtxtmodel.cpp \
    loadbinmodel.cpp \
    modelwithstate.cpp \
    test/testmemory.cpp \
    test/cpuoperation.cpp \
    test/testcase.cpp \
	test/cpustate.cpp \
	test/m6502.cpp \
	test/memory.cpp \
    cpu6502/cpu6502memory.cpp

HEADERS  += mainwindow.h \
	cpu6502/cpu6502.h \
	utils/utils.h \
	console.h \
    computer/systembus.h \
    computer/device.h \
    computer/computer.h \
    computer/keyboard.h \
    qtkeyboard.h \
    computer/display.h \
    qtdisplay.h \
    computer/rom.h \
    computer/ram.h \
	loadtxtmodel.h \
    loadbinmodel.h \
    modelwithstate.h \
    test/testmemory.h \
    test/cpuoperation.h \
    test/testcase.h \
	test/cpustate.h \
	test/m6502.h \
	test/memory.h \
    cpu6502/cpu6502memory.h

FORMS    += \
    mainwindow2.ui
