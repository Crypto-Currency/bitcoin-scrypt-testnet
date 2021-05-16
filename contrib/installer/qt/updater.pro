HEADERS = updater.h
SOURCES = updater.cpp
RESOURCES = updater.qrc
FORMS = updaterForm.ui

# platform specific defaults, if not overridden on command line
isEmpty(BOOST_LIB_SUFFIX)
{
    macx:BOOST_LIB_SUFFIX = -mt
    windows:BOOST_LIB_SUFFIX = -mgw9-mt-s-x64-1_73
}

isEmpty(BOOST_LIB_PATH)
{
    macx:BOOST_LIB_PATH = /opt/local/lib
}

isEmpty(BOOST_INCLUDE_PATH)
{
    macx:BOOST_INCLUDE_PATH = /opt/local/include
}


LIBS += -lboost_system$$BOOST_LIB_SUFFIX -lboost_filesystem$$BOOST_LIB_SUFFIX
