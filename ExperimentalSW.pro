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
    experimenttrial.h \
    logthread.h \
    locationawarewidget.h \
    mainwindow.h
SOURCES += datareader.cpp \
    experimenttrial.cpp \
    Hello.cpp \
    logthread.cpp \
    locationawarewidget.cpp \
    mainwindow.cpp
OTHER_FILES += example.xml
