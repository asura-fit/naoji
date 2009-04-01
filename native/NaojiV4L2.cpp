#include <iostream>
#include <cassert>

#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev.h>
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

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_i2c_I2Cdev__1init(JNIEnv *, jclass,
		jint dev) {

	jint res;
	res = ioctl(dev, I2C_SLAVE, DSPIC_I2C_ADDR);

	int val = i2c_smbus_read_byte_data(dev, DSPIC_VERSION_REG);
	if (val == -1) {
		return -1;
	}
	if (val < 2) {
		return -2;
	}
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_i2c_I2Cdev__1getSelectedCamera(
		JNIEnv *, jclass, jint dev) {
	jint res = i2c_smbus_read_byte_data(dev, DSPIC_SWITCH_REG);
	return res;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_i2c_I2Cdev__1selectCamera(JNIEnv *,
		jclass, jint dev, jint id) {
	unsigned char cmd[2];
	// select camera
	cmd[0] = (unsigned char) id;
	cmd[1] = 0;
	int res = i2c_smbus_write_block_data(dev, DSPIC_SWITCH_REG, 1, cmd);
	if (res == -1)
		return -1;
	return 0;
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

	jfieldID timestampField = env->GetFieldID(bufferClass, "timestamp", "J");
	jassert(env, timestampField != NULL);

	jfieldID lengthField = env->GetFieldID(bufferClass, "length", "I");
	jassert(env, lengthField != NULL);

	jlong timestamp = (jlong) buffer.timestamp.tv_sec * 1000000
			+ buffer.timestamp.tv_usec;

	env->SetLongField(bufferObj, timestampField, timestamp);
	env->SetIntField(bufferObj, lengthField, buffer.bytesused);

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
#ifdef __DEBUG__
	fprintf(stderr, "Buffer %d queued\n", index);
#endif
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

	if (queryctrl.flags & V4L2_CTRL_TYPE_BOOLEAN) {
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

	struct v4l2_format format;
	memset(&format, 0, sizeof(format));
	format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	format.fmt.pix.field = V4L2_FIELD_NONE;
	format.fmt.pix.width = width;
	format.fmt.pix.height = height;
	format.fmt.pix.pixelformat = pixelformat;
	jint res = ioctl(dev, VIDIOC_S_FMT, &format);
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

