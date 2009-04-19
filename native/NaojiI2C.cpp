#include <iostream>
#include <cassert>
#include <map>

#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <sys/ioctl.h>
//#include <linux/i2c.h>
//#include <linux/i2c-dev.h>

#include <jni.h>       /* where everything is defined */

// include JNI Headers

#include "NaojiI2C.hpp"

#include "jp_ac_fit_asura_naoji_i2c_I2Cdev.h"

#include "jni_utils.hpp"

using namespace std;
using namespace Naoji;

#ifndef JNIEXPORT
#define JNIEXPORT
#endif
#ifndef JNICALL
#define JNICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define DSPIC_I2C_ADDR 0x8
#define DSPIC_VERSION_REG 170
#define DSPIC_SWITCH_REG 220
#define I2C_DEVICE "/dev/i2c-0"
#define I2C_SLAVE 0x0703

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_i2c_I2Cdev__1createI2Cdev(JNIEnv *env,
		jclass, jstring deviceName) {
	const char *chars = env->GetStringUTFChars(deviceName, NULL);
	jint dev = open(chars, O_RDWR);
	env->ReleaseStringUTFChars(deviceName, chars);
	return dev;
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_i2c_I2Cdev__1destroy(JNIEnv *, jclass,
		jint dev) {
	close(dev);
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_i2c_I2Cdev__1init(JNIEnv *, jclass,
		jint dev) {
	jint res;
	res = ioctl(dev, I2C_SLAVE, DSPIC_I2C_ADDR);
	if (res)
		return res;

	jint val = I2Cdev_read_byte(dev, DSPIC_VERSION_REG);
	if (val == -1) {
		return -1;
	}
	if (val < 2) {
		return 1000 + val;
	}
	return 0;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_i2c_I2Cdev__1getSelectedCamera(
		JNIEnv *, jclass, jint dev) {
	jint res = I2Cdev_read_byte(dev, DSPIC_SWITCH_REG);
	return res;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_i2c_I2Cdev__1selectCamera(JNIEnv *,
		jclass, jint dev, jint id) {
	union i2c_smbus_data data;
	data.block[0] = 1;
	data.block[1] = static_cast<__u8 > (id);
	jint res = I2Cdev_write(dev, DSPIC_SWITCH_REG, I2C_SMBUS_BLOCK_DATA, &data);
	return res;
}

}
