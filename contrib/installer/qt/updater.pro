HEADERS = updater.h
SOURCES = updater.cpp
RESOURCES = updater.qrc
FORMS = updaterForm.ui

# platform specific defaults, if not overridden on command line
isEmpty(BOOST_LIB_SUFFIX){
  macx:BOOST_LIB_SUFFIX = -mt
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

macx:HEADERS += src/qt/macdockiconhandler.h
macx:OBJECTIVE_SOURCES += src/qt/macdockiconhandler.mm
macx:LIBS += -framework Foundation -framework ApplicationServices -framework AppKit
macx:DEFINES += MAC_OSX MSG_NOSIGNAL=0
macx:ICON = src/qt/res/icons/bitcoin.icns
macx:TARGET = "updater-qt"

LIBS += -lboost_system$$BOOST_LIB_SUFFIX -lboost_filesystem$$BOOST_LIB_SUFFIX
