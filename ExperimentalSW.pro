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

HEADERS += datareader.h \
    experimentdataobject.h \
    experimenttrial.h \
logthread.h
SOURCES += datareader.cpp \
    experimentdataobject.cpp \
    experimenttrial.cpp \
 Hello.cpp \
    logthread.cpp
