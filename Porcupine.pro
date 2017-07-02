#-------------------------------------------------
#
# Project created by QtCreator 2014-01-08T10:23:07
#
#-------------------------------------------------


ROOT                                    = $$_PRO_FILE_PWD_

QT                                     += widgets core gui printsupport

CONFIG                                 += static

macx:{
    QMAKE_MAC_SDK                       = macosx10.12
    QMAKE_MACOSX_DEPLOYMENT_TARGET      = 10.12
    QMAKE_CXXFLAGS                     += -stdlib=libc++
    QMAKE_CXXFLAGS                     += -std=c++11

    DEFINES                            += DARWIN
    ICON                                = $$ROOT/Resources/Icon/porcupine.icns

    QMAKE_RPATHDIR                      = /Applications/Qt/5.7/clang_64/lib
}

QMAKE_CXXFLAGS                         += -std=gnu++0x

TARGET                                  = bin/Porcupine

TEMPLATE                                = app

INCLUDEPATH                             = include/ \
                                          include/Settings \
                                          include/NodeEditor \
                                          include/NodeTreeEditor \
                                          include/CodeEditor \
                                          include/ParameterEditor

OBJECTS_DIR                             = ./obj/

MOC_DIR                                 = ./moc/

SOURCES                                += $$ROOT/main.cpp \
                                          $$ROOT/src/MainWindow.cpp \
                                          $$ROOT/src/Settings/Argument.cpp \
                                          $$ROOT/src/Settings/NodeLibrary.cpp \
                                          $$ROOT/src/Settings/NodeSetting.cpp \
                                          $$ROOT/src/Settings/Preferences.cpp \
                                          $$ROOT/src/ParameterEditor/ParameterEditor.cpp \
                                          $$ROOT/src/NodeEditor/Link.cpp \
                                          $$ROOT/src/NodeEditor/Node.cpp \
                                          $$ROOT/src/NodeEditor/NodeAntenna.cpp \
                                          $$ROOT/src/NodeEditor/NodeEditor.cpp \
                                          $$ROOT/src/NodeEditor/Port.cpp \
                                          $$ROOT/src/NodeEditor/PortPair.cpp \
                                          $$ROOT/src/NodeEditor/PostIt.cpp \
                                          $$ROOT/src/NodeEditor/SelectionBox.cpp \
                                          $$ROOT/src/NodeTreeEditor/NodeTreeEditor.cpp \
                                          $$ROOT/src/NodeTreeEditor/NodeTreeItem.cpp \
                                          $$ROOT/src/NodeTreeEditor/PortBlock.cpp \
                                          $$ROOT/src/NodeTreeEditor/PortRow.cpp \
                                          $$ROOT/src/CodeEditor/BashHighlighter.cpp \
                                          $$ROOT/src/CodeEditor/CodeEditor.cpp \
                                          $$ROOT/src/CodeEditor/CodeGenerator.cpp \
                                          $$ROOT/src/CodeEditor/MatlabHighlighter.cpp \
                                          $$ROOT/src/CodeEditor/PythonHighlighter.cpp \
                                          $$ROOT/src/CodeEditor/SyntaxHighlighter.cpp \
                                          $$ROOT/src/CodeEditor/TvmGenerator.cpp \
                                          $$ROOT/src/CodeEditor/NipypeGenerator.cpp

HEADERS                                += $$ROOT/include/MainWindow.hpp \
                                          $$ROOT/include/Settings/Argument.hpp \
                                          $$ROOT/include/Settings/NodeLibrary.hpp \
                                          $$ROOT/include/Settings/NodeSetting.hpp \
                                          $$ROOT/include/Settings/Preferences.hpp \
                                          $$ROOT/include/Settings/Singleton.hpp \
                                          $$ROOT/include/ParameterEditor/ParameterEditor.hpp \
                                          $$ROOT/include/NodeEditor/Link.hpp \
                                          $$ROOT/include/NodeEditor/Node.hpp \
                                          $$ROOT/include/NodeEditor/NodeAntenna.hpp \
                                          $$ROOT/include/NodeEditor/NodeEditor.hpp \
                                          $$ROOT/include/NodeEditor/Port.hpp \
                                          $$ROOT/include/NodeEditor/PortPair.hpp \
                                          $$ROOT/include/NodeEditor/PostIt.hpp \
                                          $$ROOT/include/NodeEditor/SelectionBox.hpp \
                                          $$ROOT/include/NodeTreeEditor/NodeTreeItem.hpp \
                                          $$ROOT/include/NodeTreeEditor/NodeTreeEditor.hpp \
                                          $$ROOT/include/NodeTreeEditor/PortBlock.hpp \
                                          $$ROOT/include/NodeTreeEditor/PortRow.hpp \
                                          $$ROOT/include/CodeEditor/BashHighlighter.hpp \
                                          $$ROOT/include/CodeEditor/CodeEditor.hpp \
                                          $$ROOT/include/CodeEditor/SyntaxHighlighter.hpp \
                                          $$ROOT/include/CodeEditor/MatlabHighlighter.hpp \
                                          $$ROOT/include/CodeEditor/PythonHighlighter.hpp \
                                          $$ROOT/include/CodeEditor/TvmGenerator.hpp \
                                          $$ROOT/include/CodeEditor/NipypeGenerator.hpp \
                                          $$ROOT/include/CodeEditor/CodeGenerator.hpp

RESOURCES                               = $$ROOT/resources/resources.qrc

win32:RC_ICONS                         += $$ROOT/resources/icon/porcupine.ico
#linux-g++:
#linux-g++-64:
