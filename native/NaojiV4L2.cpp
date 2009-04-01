#include <iostream>
#include <cassert>

#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev.h>

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

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1createVideodev(JNIEnv *env,
		jclass, jstring deviceName) {
	const char *chars = env->GetStringUTFChars(deviceName, NULL);
	jint dev = open(chars, O_RDWR);
	env->ReleaseStringUTFChars(deviceName, chars);
	return dev;
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1destroy(
		JNIEnv *, jclass, jint dev) {
	close(dev);
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1dequeueBuffer(
		JNIEnv *, jclass, jint dev, jobject buffer) {
	//	struct v4l2_buffer buffer;
	//	memset(&buffer, 0, sizeof(buffer));
	//	buffer.index = index;
	//	buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	//	buffer.memory = V4L2_MEMORY_MMAP;
	//
	//	jint res = ioctl(dev, VIDIOC_DQBUF, &buffer);
	//	if (res < 0) {
	//		return res;
	//	}
	return 0;
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1enqueueBuffer(
		JNIEnv *, jclass, jint dev, jint index) {
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
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getSelectedCamera(
		JNIEnv *, jclass, jint);

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getControl(JNIEnv *,
		jclass, jint, jint);

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getFormat(JNIEnv *,
		jclass, jint, jobject);

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
jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1selectCamera(JNIEnv *,
		jclass, jint, jint);

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

