#-------------------------------------------------
#
# Project created by QtCreator 2018-12-27T18:02:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MQTTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 使用QT5.8.0_MINGW32 测试通过， 依赖于： https://github.com/qt/qtmqtt.git
LIBS += -LE:/EWorkSpace/20190109_mqtt/build-qtmqtt-Qt580_MINGW_32BIT-Release/bin -lQt5Mqtt

INCLUDEPATH += E:/EWorkSpace/20190109_mqtt/build-qtmqtt-Qt580_MINGW_32BIT-Release/include


SOURCES += main.cpp \
    mainwidget.cpp \
    mqttclient.cpp

HEADERS  += \
    mainwidget.h \
    mqttclient.h

FORMS    += \
    mainwidget.ui
