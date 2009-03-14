
CTC_DIR=/home/nao/ctc-robocup-1.2.1

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
 -L${CTC_DIR}/cross/i486-linux/lib

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

#all : libHelloWorldJNI.so

libHelloWorldJNI.so : HelloWorldJNI.cpp HelloWorldJNI.h
	$(CXX) -shared -fPIC $(CXXFLAGS) $(JAVA_INC) HelloWorldJNI.cpp -o libHelloWorldJNI.so

bootstrap.o : bootstrap.c
	$(CXX) $(CXXFLAGS) $(JAVA_INC) -c $*.c

bootstrap : bootstrap.o
	$(CXX) $(LDFLAGS) $(JAVA_LIB) $@.o -o $@

helloworld : helloworld.c
	$(CXX) $(CXXFLAGS) -c $@.c
	$(CXX) $(LDFLAGS) -o $@ $@.o
