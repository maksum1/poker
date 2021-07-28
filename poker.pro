TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        card.cpp \
        combinator.cpp \
        combo.cpp \
        kicker.cpp \
        main.cpp \
        parser.cpp \
        player.cpp \
        round.cpp

HEADERS += \
    card.h \
    combinator.h \
    combo.h \
    kicker.h \
    parser.h \
    player.h \
    round.h
