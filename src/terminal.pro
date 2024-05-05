QT += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    addressdialog.cpp \
    addresswidget.cpp \
    console.cpp \
    consoletextedit.cpp \
    main.cpp \
    mainwindow.cpp \
    messagedata.cpp \
    messagedialog.cpp \
    messagewidget.cpp \
    savefile.cpp \
    savefiledialog.cpp \
    serialport.cpp \
    shortcutedit.cpp \
    statusbar.cpp \
    tcpclient.cpp \
    tcpserver.cpp \
    udpsocket.cpp

HEADERS += \
    addressdialog.h \
    addresswidget.h \
    console.h \
    consoletextedit.h \
    macros.h \
    mainwindow.h \
    messagedata.h \
    messagedialog.h \
    messagewidget.h \
    savefile.h \
    savefiledialog.h \
    serialport.h \
    shortcutedit.h \
    statusbar.h \
    tcpclient.h \
    tcpserver.h \
    udpsocket.h

FORMS += \
    addressdialog.ui \
    mainwindow.ui \
    messagedialog.ui \
    savefiledialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
