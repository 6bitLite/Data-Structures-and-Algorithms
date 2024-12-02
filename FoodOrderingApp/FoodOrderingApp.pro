QT += core gui widgets

CONFIG += c++17

# Optional: Uncomment this to disable deprecated APIs before Qt 6.0.0
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    queue.cpp

HEADERS += \
    mainwindow.h \
    queue.h

# Removed the UI file as it's not used
# FORMS += mainwindow.ui

# Default rules for deployment (if needed)
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
