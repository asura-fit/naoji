
USE_CROSS=

CTC_DIR=/home/nao/ctc-robocup-1.2.1
AL_DIR=/home/nao/NaoQiRobocup-1.2.0-Linux

LDFLAGS =

ifneq ($(USE_CROSS),)
# CROSS COMPILE
SYSROOT=$(CTC_DIR)/staging/i486-linux
BUILDROOT=$(CTC_DIR)/cross/i486-linux

PATH_CC=${CTC_DIR}/cross/bin

CXX=${PATH_CC}/i486-linux-g++
CC=${PATH_CC}/i486-linux-gcc
LD=${PATH_CC}/i486-linux-ld
AR=${PATH_CC}/i486-linux-ar
RANLIB=${PATH_CC}/i486-linux-ranlib

JAVA_BUILDROOT=/home/sey/opennao/tmp/staging/i486-linux
JAVA_HOME=/usr/lib/jvm/java-6-hotspot
JAVA_HOME_STAGING=$(JAVA_BUILDROOT)$(JAVA_HOME)

else
# NORMAL COMPILE
SYSROOT=/
BUILDROOT=/

PATH_CC=/usr/bin

CXX=${PATH_CC}/c++
CC=${PATH_CC}/gcc
LD=${PATH_CC}/ld
AR=${PATH_CC}/ar
RANLIB=${PATH_CC}/ranlib

JAVA_BUILDROOT=/
JAVA_HOME=/usr/lib/jvm/java-6-openjdk
JAVA_HOME_STAGING=$(JAVA_BUILDROOT)$(JAVA_HOME)

endif

LDFLAGS =
CXXFLAGS =

AL_INC = \
 -I${SYSROOT}/usr/include/python2.5 \
 -I$(AL_DIR)/modules/proxies \
 -I$(AL_DIR)/extern/c/include \
 -I$(AL_DIR)/extern/c/aldebaran/alcommon/include \
 -I$(AL_DIR)/extern/c/aldebaran/alcommon/interface \
 -I$(AL_DIR)/extern/c/aldebaran/alcommon/soap \
 -I$(AL_DIR)/extern/c/src/tinyxml

AL_LIB = \
 -rdynamic -ldl -lpython2.5 -lutil \
  $(AL_DIR)/extern/c/aldebaran/alcommon/lib/linux/libalcommon.a \
  $(AL_DIR)/extern/c/linux/lib/libboost_filesystem-mt.a \
  $(AL_DIR)/extern/c/linux/lib/libboost_signals-mt.a \
  $(AL_DIR)/extern/c/linux/lib/libboost_thread-gcc41-mt.a \
  -lpthread \
  $(AL_DIR)/extern/c/linux/lib/libtinyxml.a

ifneq ($(USE_CROSS),)
JAVA_INC = \
 -I$(JAVA_HOME_STAGING)/include/ \
 -I$(JAVA_HOME_STAGING)/include/linux/

JAVA_LIB = \
 -L$(JAVA_HOME_STAGING)/jre/lib/i386 \
 -L$(JAVA_HOME_STAGING)/jre/lib/i386/server \
 -L$(JAVA_BUILDROOT)/usr/lib \
 -Wl,-rpath -Wl,$(JAVA_HOME)/jre/lib/i386 \
 -Wl,-rpath -Wl,$(JAVA_HOME)/jre/lib/i386/server

CXXINCLUDEPATH = \
-I${SYSROOT}/usr/include/ \
-I${BUILDROOT}/lib/gcc/i486-linux/4.2.2/include/ \
-I${SYSROOT}/usr/include/c++/ \
-I${SYSROOT}/usr/include/c++/i486-linux/
CXXFLAGS +=  --sysroot $(SYSROOT)
LDFLAGS += --sysroot ${SYSROOT} -L${BUILDROOT}/lib
else
JAVA_INC = \
 -I$(JAVA_HOME)/include/ \
 -I$(JAVA_HOME)/include/linux/

JAVA_LIB = \
 -L$(JAVA_HOME)/jre/lib/i386 \
 -L$(JAVA_HOME)/jre/lib/i386/server \
 -L$(JAVA_BUILDROOT)/usr/lib \
 -Wl,-rpath -Wl,$(JAVA_HOME)/jre/lib/i386 \
 -Wl,-rpath -Wl,$(JAVA_HOME)/jre/lib/i386/server

CXXINCLUDEPATH = \
-I${SYSROOT}/usr/include/ \
-I${BUILDROOT}/lib/gcc/i486-linux-gnu/4.3/include/ \
-I${SYSROOT}/usr/include/c++/4.3/ \
-I${SYSROOT}/usr/include/c++/4.3/i486-linux-gnu/
endif
JAVA_INC += -I./include/
JAVA_LIB += -ljava -ljvm -lverify

CXXFLAGS += $(CXXINCLUDEPATH)
LDFLAGS += -lgcc -lc -lstdc++ -ldl

all : naoji_main libnaoji.so libnaojin.so

naoji_main : almain.o NaojiModule.o
	$(CXX) almain.o NaojiModule.o $(LDFLAGS) $(JAVA_LIB) $(AL_LIB) -o $@

libnaoji.so : alboot.o NaojiModule.o
	$(CXX) -shared -fPIC $(LDFLAGS) $(JAVA_LIB) $(AL_LIB) alboot.o NaojiModule.o -o $@

libnaojin.so : NaojiNatives.o
	$(CXX) -shared -fPIC $(LDFLAGS) $(JAVA_LIB) $(AL_LIB) NaojiNatives.o -o $@

.cpp.o : NaojiModule.hpp NaojiNatives.hpp
	$(CXX) $(CXXFLAGS) $(JAVA_INC) $(AL_INC) -c $*.cpp

clean :
	rm -f *.o naoji_main libnaoji.so libnaojin.so
