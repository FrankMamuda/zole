TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game.cpp \
    ai.cpp

HEADERS += \
    game.h \
    main.h \
    gamestate.h \
    debug.h \
    ai.h

