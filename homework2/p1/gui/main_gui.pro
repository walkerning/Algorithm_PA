QMAKE_CXXFLAGS += --std=c++11
QT += core gui widgets
FORMS += gamegui.ui

# ugly.. but work
INCLUDEPATH += ../
SOURCES = main_gui.cpp gamegui.cpp boardgui.cpp ../algo/algo.cpp
HEADERS = gamegui.h boardgui.h


# build dir
release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
