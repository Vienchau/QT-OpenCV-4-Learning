QT += core gui multimedia
        QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    capturethread.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    capturethread.h \
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
LIBS += D:\MY_WORK\OPENCV\opencv\release\bin\libopencv_video454.dll
LIBS += D:\MY_WORK\OPENCV\opencv\release\bin\libopencv_videoio454.dll


INCLUDEPATH += D:\MY_WORK\Qt\Qt\6.2.3\mingw_64\include
LIBS += D:\MY_WORK\Qt\Qt\6.2.3\mingw_64\bin\Qt6Multimedia.dll
