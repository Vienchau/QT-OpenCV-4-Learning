QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    editor_plugin_interface.h \
    editor_plugin_interface.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += D:\MY_WORK\OPENCV\opencv\release\install\include

LIBS += D:\MY_WORK\OPENCV\opencv\release\bin\libopencv_core454.dll
LIBS += D:\MY_WORK\OPENCV\opencv\release\bin\libopencv_imgproc454.dll
#LIBS += D:\MY_WORK\OPENCV\opencv\release\install\x64\mingw\bin\libopencv_core454.dll
#LIBS += D:\MY_WORK\OPENCV\opencv\release\install\x64\mingw\bin\libopencv_imgproc454.dll


