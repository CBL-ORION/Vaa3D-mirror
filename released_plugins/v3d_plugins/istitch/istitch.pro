
TEMPLATE      = lib
CONFIG       += qt plugin warn_off
#CONFIG       += x86_64

V3DMAINDIR = ../../../v3d_main

INCLUDEPATH  += $$V3DMAINDIR/basic_c_fun
INCLUDEPATH  += $$V3DMAINDIR/common_lib/include

HEADERS       = istitch.h 
HEADERS      +=	istitch_gui.h
HEADERS      +=	$$V3DMAINDIR/basic_c_fun/stackutil.h
HEADERS      +=	$$V3DMAINDIR/basic_c_fun/mg_utilities.h
HEADERS      += $$V3DMAINDIR/basic_c_fun/mg_image_lib.h

SOURCES       = istitch.cpp
SOURCES      +=	$$V3DMAINDIR/basic_c_fun/stackutil.cpp
SOURCES      +=	$$V3DMAINDIR/basic_c_fun/mg_utilities.cpp
SOURCES      +=	$$V3DMAINDIR/basic_c_fun/mg_image_lib.cpp

LIBS         += -lm -L$$V3DMAINDIR/common_lib/lib -lv3dtiff
LIBS         += -lpthread
LIBS	     += -lfftw3f -lfftw3f_threads
#LIBS	     += -L/usr/local/lib/libfftw3f.a -L/usr/local/lib/libfftw3f_threads.a

TARGET        = $$qtLibraryTarget(imageStitch)
DESTDIR       = $$V3DMAINDIR/../v3d/plugins/iStitch

