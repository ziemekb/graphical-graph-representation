QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AbstractGraph.cpp \
        BuildToolsManager.cpp \
        DestructionCursor.cpp \
        Edge.cpp \
        GraphFactory.cpp \
        GraphRepresentation.cpp \
        MainMenu.cpp \
        MainWindow.cpp \
        Node.cpp \
        NodeCursor.cpp \
        PhantomEdge.cpp \
        UnweightedUndirectedGraph.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AbstractGraph.h \
    BuildToolsManager.h \
    DestructionCursor.h \
    Edge.h \
    GraphFactory.h \
    GraphRepresentation.h \
    MainMenu.h \
    MainWindow.h \
    Node.h \
    NodeCursor.h \
    PhantomEdge.h \
    UnweightedUndirectedGraph.h

RESOURCES += \
    resources.qrc
