QT += gui

TEMPLATE = lib
CONFIG += plugin
INCLUDEPATH += D:\MY_WORK\QT5OPENCV\QT-OpenCV-4-Learning\workspaceQT\ImageEditor4\ImageEditor4
CONFIG += c++11


INCLUDEPATH += D:\MY_WORK\OPENCV\opencv\release\install\include

LIBS += D:\MY_WORK\OPENCV\opencv\release\bin\libopencv_core454.dll
LIBS += D:\MY_WORK\OPENCV\opencv\release\bin\libopencv_imgproc454.dll
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    erode_plugin.cpp

HEADERS += \
    erode_plugin.h\


DISTFILES += ErodePlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
