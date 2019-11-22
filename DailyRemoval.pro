#-------------------------------------------------
#
# Project created by QtCreator 2018-07-12T10:25:45
#
#-------------------------------------------------

QT       += core gui
QT       += core gui multimedia     #添加多媒体库

OBJECTS_DIR  = tmp
MOC_DIR      = tmp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DailyRemoval
TEMPLATE = app


SOURCES += main.cpp\
        dailyremoval.cpp \
    m_widget.cpp \
    m_instruction.cpp \
    block.cpp \
    map.cpp \
    putong.cpp \
    kongkuai.cpp \
    guanqia_1.cpp \
    tothemoon.cpp

HEADERS  += dailyremoval.h \
    block.h \
    m_widget.h \
    m_instruction.h \
    map.h \
    main.h \
    putong.h \
    kongkuai.h \
    guanqia_1.h \
    tothemoon.h

FORMS    += dailyremoval.ui \
    m_widget.ui \
    m_instruction.ui \
    guanqia_1.ui

RESOURCES += \
    resources.qrc


RC_ICONS =removal.ico
