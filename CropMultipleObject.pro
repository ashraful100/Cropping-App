#-------------------------------------------------
#
# Project created by QtCreator 2017-12-30T04:59:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CropMultipleObject
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp\
        myqlabel.cpp \
    displayobject.cpp \
    manual.cpp

HEADERS  += mainwindow.h\
            myqlabel.h \
    displayobject.h \
    manual.h

FORMS    += mainwindow.ui \
    displayobject.ui \
    manual.ui

RC_FILE = cropmultipleobject.rc

#win32:CONFIG(release, debug|release): LIBS += C:\Users\ASHRAF\Documents\build-CropMultipleObject-Desktop_Qt_5_8_0_MinGW_32bit-Release\release\OpenCV\libs\libopencv_core249.dll
#else:win32:CONFIG(debug, debug|release): LIBS += C:\Users\ASHRAF\Documents\build-CropMultipleObject-Desktop_Qt_5_8_0_MinGW_32bit-Debug\debug\OpenCV\libs\libopencv_core249.dll

#win32:CONFIG(release, debug|release): LIBS += C:\Users\ASHRAF\Documents\build-CropMultipleObject-Desktop_Qt_5_8_0_MinGW_32bit-Release\release\OpenCV\libs\libopencv_highgui249.dll
#else:win32:CONFIG(debug, debug|release): LIBS += C:\Users\ASHRAF\Documents\build-CropMultipleObject-Desktop_Qt_5_8_0_MinGW_32bit-Debug\debug\OpenCV\libs\libopencv_core249.dll

#INCLUDEPATH += C:\Users\ASHRAF\Documents\build-CropMultipleObject-Desktop_Qt_5_8_0_MinGW_32bit-Release\release\OpenCV\include


INCLUDEPATH += C://opencv//sources//release//install//include
INCLUDEPATH += C://opencv//sources//include//opencv2
#LIBS += -LC://opencv//sources//release//bin//*.dll

LIBS += C:\opencv\sources\release\bin\libopencv_calib3d249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_contrib249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_core249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_features2d249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_flann249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_gpu249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_highgui249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_imgproc249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_legacy249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_ml249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_nonfree249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_objdetect249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_ocl249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_photo249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_stitching249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_superres249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_video249.dll
LIBS += C:\opencv\sources\release\bin\libopencv_videostab249.dll
LIBS += C:\opencv\sources\release\bin\opencv_ffmpeg249.dll
