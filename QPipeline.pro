#-------------------------------------------------
#
# Project created by QtCreator 2014-01-08T10:23:07
#
#-------------------------------------------------

ROOT=$$_PRO_FILE_PWD_

QT +=               core gui xmlpatterns xml

greaterThan(QT_MAJOR_VERSION, 4):{
    QT +=           widgets
}

CONFIG += static

macx:{
    QMAKE_CXXFLAGS += -stdlib=libc++
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
}

QMAKE_CXXFLAGS +=   -std=gnu++0x

TARGET =            QPipeline

TEMPLATE =          app

INCLUDEPATH =       include/

OBJECTS_DIR =       ./obj/

SOURCES +=          $$ROOT/main.cpp \
                    $$ROOT/src/Link.cpp \
                    $$ROOT/src/MainWindow.cpp \
                    $$ROOT/src/Node.cpp \
                    $$ROOT/src/NodeEditor.cpp \
                    $$ROOT/src/NodeLibrary.cpp \
                    $$ROOT/src/NodeSetting.cpp \
                    $$ROOT/src/Port.cpp \
                    $$ROOT/src/Argument.cpp \
                    $$ROOT/src/DataType.cpp \
                    $$ROOT/src/Preferences.cpp \
                    $$ROOT/src/NodeListView.cpp \
                    $$ROOT/src/NodeTreeModel.cpp \
    src/PortPair.cpp

HEADERS  +=         $$ROOT/include/Link.hpp \
                    $$ROOT/include/MainWindow.hpp \
                    $$ROOT/include/Node.hpp \
                    $$ROOT/include/NodeEditor.hpp \
                    $$ROOT/include/NodeLibrary.hpp \
                    $$ROOT/include/NodeSetting.hpp \
                    $$ROOT/include/Port.hpp \
                    $$ROOT/include/Singleton.hpp \
                    $$ROOT/include/Argument.hpp \
                    $$ROOT/include/DataType.hpp \
                    $$ROOT/include/Preferences.hpp \
                    $$ROOT/include/NodeListView.hpp \
                    $$ROOT/include/NodeTreeModel.hpp \
    include/PortPair.hpp

RESOURCES   =       $$ROOT/Dictionaries/schema.qrc


#win32:
#linux-g++:
#linux-g++-64:
#macx:
