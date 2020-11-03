QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(Controller/Controller.pri)
include(Definitions/Definitions.pri)
include(Helper/Helper.pri)
include(Interface/Interface.pri)
include(World/Characters/Characters.pri)
include(World/Equipment/Equipment.pri)
include(World/Generate/Generate.pri)
include(World/Level/Level.pri)