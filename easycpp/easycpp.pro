#-------------------------------------------------
#
# Project created by QtCreator 2016-07-20T18:16:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = easycpp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = lib


SOURCES += \
    main.cpp \
    easycpp/helpers/string.cpp \    
    easycpp/helpers/datetime.cpp \
    easycpp/helpers/file.cpp \
    easycpp/helpers/log.cpp \
    easycpp/helpers/type.cpp \
    easycpp/helpers/json.cpp \
    easycpp/libraries/exception.cpp \
    easycpp/models/redis.cpp \    
    easycpp/helpers/http.cpp


INCLUDEPATH += /usr/local/include/
LIBS += -lboost_system -lhiredis -levent -lboost_filesystem

HEADERS += \
    easycpp/helpers/string.h \
    easycpp/helpers/datetime.h \
    easycpp/helpers/file.h \
    easycpp/helpers/log.h \
    easycpp/helpers/type.h \
    easycpp/helpers/json.h \
    easycpp/libraries/json.h \
    easycpp/libraries/exception.h \
    easycpp/models/redis.h \
    easycpp/helpers/http.h
