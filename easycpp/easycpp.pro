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

TEMPLATE = app


SOURCES += main.cpp


INCLUDEPATH += /usr/local/include/
LIBS += -lboost_system -lhiredis -levent -lssl -lcrypto

HEADERS += \
    easycpp/helpers/type.hpp \
    easycpp/helpers/string.hpp \
    easycpp/helpers/log.hpp \
    easycpp/helpers/json.hpp \
    easycpp/helpers/http.hpp \
    easycpp/helpers/file.hpp \
    easycpp/helpers/datetime.hpp \
    easycpp/libraries/json.hpp \
    easycpp/libraries/exception.hpp \
    easycpp/models/redis.hpp
