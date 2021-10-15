TEMPLATE = app

CONFIG -= qt
CONFIG += console
CONFIG += boost164
CONFIG += no_install

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lgtest
LIBS += -lreg_12
LIBS += -lOSIndependent

SOURCES += \
        CheckDataBlock.cpp \
        CheckEvent.cpp \
        CheckKey.cpp \
        CheckMap.cpp \
        CheckStr.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:{
    LIBS += -lpthread -lrt
    LIBS += -l:libboost_filesystem-mt.a \
    -l:libboost_system-mt.a \
    -l:libboost_filesystem.a \
    -l:libboost_system.a \
    -l:libboost_thread-mt.a
}
