LIBS += -lMultiWidgets \
    -lRadiant \
    -lLuminous \
    -lPoetic \
    -lValuable \
    -lFluffy \
    -lResonant \
    -lNimble \
    -lMultiStateDisplay \
    -lVideoDisplay \
    -lMultiTouch \
    -lScreenplay \
    -lPatterns \
    -lBox2D

LIBS += -lSDLmain
linux-*:LIBS += -lThreadedRendering

#INCLUDEPATH += ../yaml-cpp/include/


HEADERS += datareader.h \
    experimenttrial.h \
    logthread.h \
    locationawarewidget.h \
    mainwindow.h \
    connectioncheck.h \
    settings.h \
    roundwidget.h \
    delaydaddthread.h
SOURCES += datareader.cpp \
    experimenttrial.cpp \
    Hello.cpp \
    logthread.cpp \
    locationawarewidget.cpp \
    mainwindow.cpp \
    connectioncheck.cpp \
    roundwidget.cpp \
    delaydaddthread.cpp
OTHER_FILES += example.xml \
    licence.txt \
    task_done.wav \
    clockwise.png \
    counterclockwise.png

#unix:!macx:!symbian: LIBS += -L$$PWD/../yaml-cpp/build/ -lyaml-cpp

#INCLUDEPATH += $$PWD/../yaml-cpp/build
#DEPENDPATH += $$PWD/../yaml-cpp/build

#unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../yaml-cpp/build/libyaml-cpp.a


