TEMPLATE = app
TARGET = updater-qt
QT += network

OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build

HEADERS = src/updater.h
SOURCES = src/updater.cpp
RESOURCES = src/updater.qrc
FORMS = src/updaterForm.ui

# platform specific defaults, if not overridden on command line
isEmpty(BOOST_LIB_SUFFIX){
  macx:BOOST_LIB_SUFFIX =
  windows:BOOST_LIB_SUFFIX = -mgw9-mt-s-x64-1_73
}

isEmpty(BOOST_LIB_PATH){
  macx:BOOST_LIB_PATH = /opt/local/lib
}

isEmpty(BOOST_INCLUDE_PATH){
  macx:BOOST_INCLUDE_PATH = /opt/local/include
}

!windows:!mac{
  DEFINES += LINUX
  LIBS += -lrt
}

macx:HEADERS += src/macdockiconhandler.h
macx:OBJECTIVE_SOURCES += src/macdockiconhandler.mm
macx:LIBS += -framework Foundation -framework ApplicationServices -framework AppKit
macx:DEFINES += MAC_OSX MSG_NOSIGNAL=0
macx:ICON = images/btcs.icns
macx:TARGET = "updater-qt"

LIBS += -lboost_system$$BOOST_LIB_SUFFIX -lboost_filesystem$$BOOST_LIB_SUFFIX
