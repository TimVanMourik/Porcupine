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

TARGET =            PipelineProgram

TEMPLATE =          app

INCLUDEPATH =       include/ \
                    include/Settings \
                    include/NodeEditor \
                    include/NodeTreeEditor \
                    include/CodeEditor

OBJECTS_DIR =       ./obj/

MOC_DIR =           ./moc/

SOURCES +=          $$ROOT/main.cpp \
                    $$ROOT/src/MainWindow.cpp \
                    $$ROOT/src/Settings/Argument.cpp \
                    $$ROOT/src/Settings/DataType.cpp \
                    $$ROOT/src/Settings/NodeLibrary.cpp \
                    $$ROOT/src/Settings/NodeSetting.cpp \
                    $$ROOT/src/Settings/Preferences.cpp \
                    $$ROOT/src/NodeEditor/Link.cpp \
                    $$ROOT/src/NodeEditor/Node.cpp \
                    $$ROOT/src/NodeEditor/NodeEditor.cpp \
                    $$ROOT/src/NodeEditor/Port.cpp \
                    $$ROOT/src/NodeEditor/PortPair.cpp \
                    $$ROOT/src/NodeTreeEditor/NodeTreeEditor.cpp \
                    $$ROOT/src/NodeTreeEditor/NodeTreeItem.cpp \
                    $$ROOT/src/CodeEditor/BashHighlighter.cpp \
                    $$ROOT/src/CodeEditor/CodeEditor.cpp \
                    $$ROOT/src/CodeEditor/MatlabHighlighter.cpp \
                    $$ROOT/src/CodeEditor/PythonHighlighter.cpp \
                    $$ROOT/src/CodeEditor/SyntaxHighlighter.cpp

HEADERS  +=         $$ROOT/include/MainWindow.hpp \
                    $$ROOT/include/Settings/Argument.hpp \
                    $$ROOT/include/Settings/DataType.hpp \
                    $$ROOT/include/Settings/NodeLibrary.hpp \
                    $$ROOT/include/Settings/NodeSetting.hpp \
                    $$ROOT/include/Settings/Preferences.hpp \
                    $$ROOT/include/Settings/Singleton.hpp \
                    $$ROOT/include/NodeEditor/Link.hpp \
                    $$ROOT/include/NodeEditor/Node.hpp \
                    $$ROOT/include/NodeEditor/NodeEditor.hpp \
                    $$ROOT/include/NodeEditor/Port.hpp \
                    $$ROOT/include/NodeEditor/PortPair.hpp \
                    $$ROOT/include/NodeTreeEditor/NodeTreeItem.hpp \
                    $$ROOT/include/NodeTreeEditor/NodeTreeEditor.hpp \
                    $$ROOT/include/CodeEditor/BashHighlighter.hpp \
                    $$ROOT/include/CodeEditor/CodeEditor.hpp \
                    $$ROOT/include/CodeEditor/SyntaxHighlighter.hpp \
                    $$ROOT/include/CodeEditor/MatlabHighlighter.hpp \
                    $$ROOT/include/CodeEditor/PythonHighlighter.hpp

RESOURCES   =       $$ROOT/Dictionaries/schema.qrc


#win32:
#linux-g++:
#linux-g++-64:
#macx:
