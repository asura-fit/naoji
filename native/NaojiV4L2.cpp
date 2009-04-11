#include <iostream>
#include <cassert>
#include <map>

#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <jni.h>       /* where everything is defined */

// include JNI Headers

#include "NaojiV4L2.hpp"

#include "jp_ac_fit_asura_naoji_v4l2_Videodev.h"

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

inline jint I2Cdev_read_byte(int dev, __u8 command) {
	union i2c_smbus_data data;
	struct i2c_smbus_ioctl_data arg;
	arg.read_write = I2C_SMBUS_READ;
	arg.command = command;
	arg.size = I2C_SMBUS_BYTE;
	arg.data = &data;

	jint res = ioctl(dev, I2C_SMBUS, &arg);
	if (res == 0)
		return data.byte;
	return res;
}

inline jint I2Cdev_write(int dev, __u8 command, int size, i2c_smbus_data *data) {
	struct i2c_smbus_ioctl_data arg;
	arg.read_write = I2C_SMBUS_WRITE;
	arg.command = command;
	arg.size = size;
	arg.data = data;

	jint res = ioctl(dev, I2C_SMBUS, &arg);
	return res;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_i2c_I2Cdev__1init(JNIEnv *, jclass,
		jint dev) {
	jint res;
	res = ioctl(dev, I2C_SLAVE, DSPIC_I2C_ADDR);

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
	// select camera
	union i2c_smbus_data data;
	data.block[0] = 1;
	data.block[1] = static_cast<__u8 > (id);
	jint res = I2Cdev_write(dev, DSPIC_SWITCH_REG, I2C_SMBUS_BLOCK_DATA, &data);
	return res;
}

static std::map<std::string, jint> sV4L2IntConst;
static std::map<std::string, jlong> sV4L2LongConst;

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1_1init(JNIEnv *, jclass) {
	sV4L2IntConst["V4L2_CID_BRIGHTNESS"] = V4L2_CID_BRIGHTNESS;
	sV4L2IntConst["V4L2_CID_CONTRAST"] = V4L2_CID_CONTRAST;
	sV4L2IntConst["V4L2_CID_SATURATION"] = V4L2_CID_SATURATION;
	sV4L2IntConst["V4L2_CID_HUE"] = V4L2_CID_HUE;
	sV4L2IntConst["V4L2_CID_VFLIP"] = V4L2_CID_VFLIP;
	sV4L2IntConst["V4L2_CID_HFLIP"] = V4L2_CID_HFLIP;
	sV4L2IntConst["V4L2_CID_RED_BALANCE"] = V4L2_CID_RED_BALANCE;
	sV4L2IntConst["V4L2_CID_BLUE_BALANCE"] = V4L2_CID_BLUE_BALANCE;
	sV4L2IntConst["V4L2_CID_GAIN"] = V4L2_CID_GAIN;
	sV4L2IntConst["V4L2_CID_HCENTER"] = V4L2_CID_HCENTER;
	sV4L2IntConst["V4L2_CID_VCENTER"] = V4L2_CID_VCENTER;
	sV4L2IntConst["V4L2_CID_AUTOGAIN"] = V4L2_CID_AUTOGAIN;
	sV4L2IntConst["V4L2_CID_AUTO_WHITE_BALANCE"] = V4L2_CID_AUTO_WHITE_BALANCE;
	// In lxv4l2/ov7670.c, V4L2_CID_AUDIO_MUTE means AEC Enable
	//	sV4L2IntConst["V4L2_CID_EXPOSURE_AUTO"] = V4L2_CID_AUDIO_MUTE;
	sV4L2IntConst["V4L2_CID_AUDIO_MUTE"] = V4L2_CID_AUDIO_MUTE;
	sV4L2IntConst["V4L2_CID_EXPOSURE"] = V4L2_CID_EXPOSURE;
	// Aldebaran's non-standard header.
	sV4L2IntConst["V4L2_CID_CAM_INIT"] = 0x980919;
	//	sV4L2IntConst["V4L2_CID_CAM_INIT"] = V4L2_CID_CAM_INIT;

	sV4L2LongConst["V4L2_STD_UNK101"] = 0x10000000UL; /* HD_480P */
	sV4L2LongConst["V4L2_STD_UNK102"] = 0x20000000UL;/* HD_525P */
	sV4L2LongConst["V4L2_STD_UNK103"] = 0x40000000UL;/* HD_720P */
	sV4L2LongConst["V4L2_STD_UNK104"] = 0x80000000UL;/* HD_1080I */
	sV4L2LongConst["V4L2_STD_UNK105"] = 0x08000000UL;/* HD_VGA */
	sV4L2LongConst["V4L2_STD_UNK106"] = 0x04000000UL; /* HD_QVGA */
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1_1getIntConst(
		JNIEnv *env, jclass, jstring jstr) {
	// TODO Use String.hashCode() instead of strcmp().
	const char *chars = env->GetStringUTFChars(jstr, NULL);
	jassert(env, sV4L2IntConst.count(chars) > 0);
	jint id = sV4L2IntConst[chars];
	env->ReleaseStringUTFChars(jstr, chars);
	return id;
}

JNIEXPORT
jint
JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1createVideodev(JNIEnv *env,
		jclass, jstring deviceName) {
	const char *chars = env->GetStringUTFChars(deviceName, NULL);
	jint dev = open(chars, O_RDWR);
	env->ReleaseStringUTFChars(deviceName, chars);
	return dev;
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1destroy(JNIEnv *,
		jclass, jint dev) {
	close(dev);
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1dequeueBuffer(
		JNIEnv *env, jclass, jint dev, jobject bufferObj) {

	struct v4l2_buffer buffer;
	memset(&buffer, 0, sizeof(buffer));
	buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buffer.memory = V4L2_MEMORY_MMAP;

	jint res = ioctl(dev, VIDIOC_DQBUF, &buffer);
	if (res < 0) {
		return res;
	}

	// TODO fieldIDをキャッシュする.
	jassert(env, bufferObj != NULL);

	jclass bufferClass = env->GetObjectClass(bufferObj);
	jassert(env, bufferClass != NULL);

	jfieldID indexField = env->GetFieldID(bufferClass, "index", "I");
	jassert(env, indexField != NULL);

	jfieldID timestampField = env->GetFieldID(bufferClass, "timestamp", "J");
	jassert(env, timestampField != NULL);

	jfieldID lengthField = env->GetFieldID(bufferClass, "length", "I");
	jassert(env, lengthField != NULL);

	jlong timestamp = (jlong) buffer.timestamp.tv_sec * 1000000
			+ buffer.timestamp.tv_usec;

	env->SetLongField(bufferObj, timestampField, timestamp);
	env->SetIntField(bufferObj, lengthField, buffer.bytesused);
	env->SetIntField(bufferObj, indexField, buffer.index);

	return 0;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1enqueueBuffer(JNIEnv *,
		jclass, jint dev, jint index) {
	struct v4l2_buffer buffer;
	memset(&buffer, 0, sizeof(buffer));
	buffer.index = index;
	buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buffer.memory = V4L2_MEMORY_MMAP;

	jint res = ioctl(dev, VIDIOC_QBUF, &buffer);
	if (res != 0) {
		return errno;
	}
	return 0;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getControl(JNIEnv *,
		jclass, jint dev, jint control) {
	struct v4l2_control control_s;
	control_s.id = control;
	jint res = ioctl(dev, VIDIOC_G_CTRL, &control_s);
	return control_s.value;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getFormat(JNIEnv *env,
		jclass, jint dev, jobject formatObj) {
	struct v4l2_format format;
	memset(&format, 0, sizeof(format));
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	jint res = ioctl(dev, VIDIOC_G_FMT, &format);

	if (res != 0) {
		return errno;
	}

	jassert(env, formatObj != NULL);

	jclass formatClass = env->GetObjectClass(formatObj);
	jassert(env, formatClass != NULL);

	jfieldID widthField = env->GetFieldID(formatClass, "width", "I");
	jassert(env, widthField != NULL);
	env->SetIntField(formatObj, widthField, format.fmt.pix.width);

	jfieldID heightField = env->GetFieldID(formatClass, "height", "I");
	jassert(env, heightField != NULL);
	env->SetIntField(formatObj, heightField, format.fmt.pix.height);

	jfieldID pixelformatField =
			env->GetFieldID(formatClass, "pixelFormat", "I");
	jassert(env, pixelformatField != NULL);
	env->SetIntField(formatObj, pixelformatField, format.fmt.pix.pixelformat);
	return 0;
}

JNIEXPORT
jlong JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getStandard(JNIEnv *,
		jclass, jint dev) {
	v4l2_std_id value;
	jint res = ioctl(dev, VIDIOC_G_STD, &value);
	assert(res == 0);
	return value;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getSupportedFormats(
		JNIEnv *env, jclass, jint dev, jobject collectionObj) {
	// TODO implement.
}

JNIEXPORT
jboolean JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1isSupportedControl(
		JNIEnv *, jclass, jint dev, jint control) {
	struct v4l2_queryctrl queryctrl;
	queryctrl.id = control;

	jint res = ioctl(dev, VIDIOC_QUERYCTRL, &queryctrl);
	if (res < 0) {
		return false;
	}

	if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED) {
		return false;
	}

	if (queryctrl.type & V4L2_CTRL_TYPE_BOOLEAN) {
		return true;
	}

	if (queryctrl.type & V4L2_CTRL_TYPE_INTEGER) {
		return true;
	}
	return false;
}

JNIEXPORT
jboolean JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1isSupportedFormat(
		JNIEnv *env, jclass, jint dev, jobject formatObj) {
	jassert(env, formatObj != NULL);

	jclass formatClass = env->GetObjectClass(formatObj);
	jassert(env, formatClass != NULL);

	jfieldID widthField = env->GetFieldID(formatClass, "width", "I");
	jassert(env, widthField != NULL);
	jint width = env->GetIntField(formatObj, widthField);

	jfieldID heightField = env->GetFieldID(formatClass, "height", "I");
	jassert(env, heightField != NULL);
	jint height = env->GetIntField(formatObj, heightField);

	jfieldID pixelformatField =
			env->GetFieldID(formatClass, "pixelFormat", "I");
	jassert(env, pixelformatField != NULL);
	jint pixelformat = env->GetIntField(formatObj, pixelformatField);

	struct v4l2_format format;
	memset(&format, 0, sizeof(format));
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	format.fmt.pix.field = V4L2_FIELD_NONE;
	format.fmt.pix.width = width;
	format.fmt.pix.height = height;
	format.fmt.pix.pixelformat = pixelformat;
	jint res = ioctl(dev, VIDIOC_TRY_FMT, &format);
	return res == 0;
}

JNIEXPORT
jobject JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1mmapBuffer(
		JNIEnv *env, jclass, jint dev, jint index) {
	struct v4l2_buffer buffer;
	memset(&buffer, 0, sizeof(buffer));
	buffer.index = index;
	buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buffer.memory = V4L2_MEMORY_MMAP;

	jint res;
	res = ioctl(dev, VIDIOC_QUERYBUF, &buffer);
	if (res < 0) {
		return NULL;
	}

#ifdef __DEBUG__
	fprintf(stderr, "buffer length:%u offset:%u\n", buffer.length, buffer.m.offset);
#endif

	void *ptr = mmap(NULL, buffer.length, PROT_READ, MAP_SHARED, dev,
			buffer.m.offset);
	if (ptr == MAP_FAILED) {
		return NULL;
	}
#ifdef __DEBUG__
	fprintf(stderr, "Buffer %d mapped %p\n", index, ptr);
#endif

	jobject bufferObj = env->NewDirectByteBuffer(ptr, buffer.length);
	jassert(env, bufferObj != NULL);
	return bufferObj;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1munmapBuffer(
		JNIEnv *env, jclass, jint, jobject buffer) {
	jassert(env, buffer != NULL);

	void *ptr = env->GetDirectBufferAddress(buffer);
	jassert(env, ptr != NULL);
	jlong length = env->GetDirectBufferCapacity(buffer);
	jassert(env, length != -1);

	jint res = munmap(ptr, length);
	return res;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1requestBuffers(
		JNIEnv *, jclass, jint dev, jint count) {
	struct v4l2_requestbuffers request;
	memset(&request, 0, sizeof(request));
	request.count = count;
	request.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	request.memory = V4L2_MEMORY_MMAP;

	jint res = ioctl(dev, VIDIOC_REQBUFS, &request);
	if (res < 0) {
		return res;
	}
	return request.count;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1setControl(JNIEnv *,
		jclass, jint dev, jint control, jint value) {
	struct v4l2_control control_s;
	control_s.id = control;
	control_s.value = value;
	jint res = ioctl(dev, VIDIOC_S_CTRL, &control_s);
	return res;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1setFormat(JNIEnv *env,
		jclass, jint dev, jobject formatObj) {
	jassert(env, formatObj != NULL);

	jclass formatClass = env->GetObjectClass(formatObj);
	jassert(env, formatClass != NULL);

	jfieldID widthField = env->GetFieldID(formatClass, "width", "I");
	jassert(env, widthField != NULL);
	jint width = env->GetIntField(formatObj, widthField);

	jfieldID heightField = env->GetFieldID(formatClass, "height", "I");
	jassert(env, heightField != NULL);
	jint height = env->GetIntField(formatObj, heightField);

	jfieldID pixelformatField =
			env->GetFieldID(formatClass, "pixelFormat", "I");
	jassert(env, pixelformatField != NULL);
	jint pixelformat = env->GetIntField(formatObj, pixelformatField);

	jint res;

	// Aldebaran's custom operation.
	v4l2_std_id esid0;
	res = ioctl(dev, VIDIOC_G_STD, &esid0);
	if (res != 0) {
		return res;
	}

	// SET video device STANDARD
	if (width == 640 && height == 480) {
		esid0 = 0x08000000UL; /*VGA*/
	} else if (width == 320 && height == 240) {
		esid0 = 0x04000000UL; /*QVGA*/
	}
	res = ioctl(dev, VIDIOC_S_STD, &esid0);
	if (res != 0) {
		return res;
	}

	struct v4l2_format format;
	memset(&format, 0, sizeof(format));
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	format.fmt.pix.field = V4L2_FIELD_NONE;
	format.fmt.pix.width = width;
	format.fmt.pix.height = height;
	format.fmt.pix.pixelformat = pixelformat;
	res = ioctl(dev, VIDIOC_S_FMT, &format);
	return res;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1setFPS(JNIEnv *,
		jclass, jint dev, jint fps) {
	struct v4l2_streamparm parm;

	parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	parm.parm.capture.timeperframe.numerator = 1;
	parm.parm.capture.timeperframe.denominator = fps;
	parm.parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	jint res = ioctl(dev, VIDIOC_S_PARM, &parm);
	return res;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1setStandard(JNIEnv *,
		jclass, jint dev, jlong jvalue) {
	v4l2_std_id value = jvalue;
	jint res = ioctl(dev, VIDIOC_S_STD, &value);
	return res;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1start(JNIEnv *, jclass,
		jint dev) {
	int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	jint res = ioctl(dev, VIDIOC_STREAMON, &type);
	return res;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1stop(JNIEnv *, jclass,
		jint dev) {
	int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	jint res = ioctl(dev, VIDIOC_STREAMOFF, &type);
	return res;
}

#ifdef __cplusplus
}
#endif

