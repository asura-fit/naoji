
CTC_DIR=/home/nao/ctc-robocup-1.2.1
AL_DIR=/home/nao/NaoQiRobocup-1.2.0-Linux

JAVA_STAGING=/home/sey/opennao/tmp/staging
JAVA_HOME=/usr/lib/jvm/java-6-hotspot
JAVA_HOME_STAGING=$(JAVA_STAGING)/i486-linux$(JAVA_HOME)

PATH_CC=${CTC_DIR}/cross/bin

CXX=${PATH_CC}/i486-linux-g++
CC=${PATH_CC}/i486-linux-gcc
LD=${PATH_CC}/i486-linux-ld
AR=${PATH_CC}/i486-linux-ar
RANLIB=${PATH_CC}/i486-linux-ranlib

LDFLAGS = --sysroot ${CTC_DIR}/staging/i486-linux \
 -L${CTC_DIR}/cross/i486-linux/lib \
 -lgcc -lc -lstdc++ -ldl

AL_INC = \
 -I${CTC_DIR}/staging/i486-linux/usr/include/python2.5 \
 -I$(AL_DIR)/modules/proxies \
 -I$(AL_DIR)/extern/c/include \
 -I$(AL_DIR)/extern/c/aldebaran/alcommon/include \
 -I$(AL_DIR)/extern/c/aldebaran/alcommon/interface \
 -I$(AL_DIR)/extern/c/aldebaran/alcommon/soap \
 -I$(AL_DIR)/extern/c/src/tinyxml

AL_LIB = \
 -rdynamic -ldl -lpython2.5 -ldl -lpython2.5 -lutil \
  $(AL_DIR)/extern/c/aldebaran/alcommon/lib/linux/libalcommon.a \
  $(AL_DIR)/extern/c/linux/lib/libboost_filesystem-mt.a \
  $(AL_DIR)/extern/c/linux/lib/libboost_signals-mt.a \
  $(AL_DIR)/extern/c/linux/lib/libboost_thread-gcc41-mt.a \
  -lpthread \
  $(AL_DIR)/extern/c/linux/lib/libtinyxml.a

JAVA_INC = \
 -I$(JAVA_HOME_STAGING)/include/ \
 -I$(JAVA_HOME_STAGING)/include/linux/

JAVA_LIB = \
 -L$(JAVA_HOME_STAGING)/jre/lib/i386 \
 -L$(JAVA_HOME_STAGING)/jre/lib/i386/server \
 -L$(JAVA_STAGING)/i486-linux/usr/lib \
 -ljava -ljvm -lverify -lffi \
 -Wl,-rpath -Wl,$(JAVA_HOME)/jre/lib/i386 \
 -Wl,-rpath -Wl,$(JAVA_HOME)/jre/lib/i386/server

CXXINCLUDEPATH = \
-I${CTC_DIR}/staging/i486-linux/usr/include/ \
-I${CTC_DIR}/cross/lib/gcc/i486-linux/4.2.2/include/ \
-I${CTC_DIR}/staging/i486-linux/usr/include/c++/ \
-I${CTC_DIR}/staging/i486-linux/usr/include/c++/i486-linux/

CXXFLAGS = --sysroot ${CTC_DIR}/staging/i486-linux/ $(CXXINCLUDEPATH)

all : naoji_main naoji.so

naoji_main : almain.o NaojiModule.o
	$(CXX) almain.o NaojiModule.o $(LDFLAGS) $(JAVA_LIB) $(AL_LIB) -o $@

naoji.so : alboot.o NaojiModule.o
	$(CXX) -shared -fPIC $(LDFLAGS) $(JAVA_LIB) $(AL_LIB) alboot.o NaojiModule.o -o $@

.cpp.o : NaojiModule.hpp
	$(CXX) $(CXXFLAGS) $(JAVA_INC) $(AL_INC) -c $*.cpp
