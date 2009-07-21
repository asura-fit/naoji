#include <iostream>
#include <cassert>

#include "alproxy.h"
#include "alptr.h"
#include "albroker.h"

#include "alerror.h"

#include "alvisiondefinitions.h"
#include "alvisionimage.h"

#include <jni.h>       /* where everything is defined */

// include JNI Headers
#include "jp_ac_fit_asura_naoji_NaojiModule.h"
#include "jp_ac_fit_asura_naoji_jal_JALVideoDevice.h"

#include "jni_utils.hpp"

#include "NaojiModule.hpp"
#include "NaojiNatives.hpp"

using namespace AL;
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

JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1create(
		JNIEnv *, jclass, jlong jbrokerPtr) {
	JALBroker *jbroker = reinterpret_cast<JALBroker*> (jbrokerPtr);
	assert(jbroker != NULL);
	JALVideoDevice *jvideo = new JALVideoDevice(jbroker);
	return reinterpret_cast<jlong> (jvideo);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1dispose(
		JNIEnv *, jclass, jlong objPtr) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	delete jvideo;
}

JNIEXPORT jboolean
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1isRunning(JNIEnv *,
		jclass, jlong objPtr, jint taskId) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<bool> ("isRunning", taskId);
}

JNIEXPORT jboolean
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1wait(JNIEnv *, jclass,
		jlong objPtr, jint taskId, jint timeout) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<bool> ("wait", taskId, timeout);
}

JNIEXPORT jboolean
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1startFrameGrabber(
		JNIEnv *, jclass, jlong objPtr) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("startFrameGrabber") != 0;
}

JNIEXPORT jboolean
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1stopFrameGrabber(
		JNIEnv *, jclass, jlong objPtr) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("stopFrameGrabber") != 0;
}

JNIEXPORT jstring
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1register(JNIEnv *env,
		jclass, jlong objPtr, jstring pGVMname, jint pResolution,
		jint pColorSpace, jint pFps) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	string pId = jvideo->getProxy()->call<string> ("register", toString(env,
			pGVMname), pResolution, pColorSpace, pFps);
	return env->NewStringUTF(pId.c_str());
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1unRegister(JNIEnv *env,
		jclass, jlong objPtr, jstring pId) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	jvideo->getProxy()->callVoid("unRegister", toString(env, pId));
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getImageLocal(
		JNIEnv *env, jclass, jlong objPtr, jstring pId, jobject imgObj) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	int res = jvideo->getProxy()->call<int> ("getImageLocal",
			toString(env, pId));
	if (res == 0)
		return 0;
	ALVisionImage* image = reinterpret_cast<ALVisionImage*> (res);

	jassert(env, imgObj != NULL);

	jclass imgClass = env->GetObjectClass(imgObj);
	jassert(env, imgClass != NULL);

	jfieldID widthField = env->GetFieldID(imgClass, "width", "I");
	jassert(env, widthField != NULL);

	jfieldID heightField = env->GetFieldID(imgClass, "height", "I");
	jassert(env, heightField != NULL);

	jfieldID nbLayersField = env->GetFieldID(imgClass, "nbLayers", "I");
	jassert(env, nbLayersField != NULL);

	jfieldID colorSpaceField = env->GetFieldID(imgClass, "colorSpace", "I");
	jassert(env, colorSpaceField != NULL);

	jfieldID timestampField = env->GetFieldID(imgClass, "timestamp", "J");
	jassert(env, timestampField != NULL);

	jfieldID dataField = env->GetFieldID(imgClass, "data",
			"Ljava/nio/ByteBuffer;");
	jassert(env, dataField != NULL);

	env->SetIntField(imgObj, widthField, image->fWidth);
	env->SetIntField(imgObj, heightField, image->fHeight);
	env->SetIntField(imgObj, nbLayersField, image->fNbLayers);
	env->SetIntField(imgObj, colorSpaceField, image->fColorSpace);
	env->SetLongField(imgObj, timestampField, image->fTimeStamp);

	jsize length = image->fWidth * image->fHeight * image->fNbLayers;

	jobject buf = env->NewDirectByteBuffer(image->getFrame(), length);
	jassert(env, buf != NULL);
	env->SetObjectField(imgObj, dataField, buf);
	return 1;
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1releaseImage(
		JNIEnv *env, jclass, jlong objPtr, jstring pId) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("releaseImage", toString(env, pId));
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getImageRemote(
		JNIEnv *env, jclass, jlong objPtr, jstring pId, jobject imgObj) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	jassert(env, imgObj != NULL);

	jclass imgClass = env->GetObjectClass(imgObj);
	jassert(env, imgClass != NULL);

	jfieldID widthField = env->GetFieldID(imgClass, "width", "I");
	jassert(env, widthField != NULL);

	jfieldID heightField = env->GetFieldID(imgClass, "height", "I");
	jassert(env, heightField != NULL);

	jfieldID nbLayersField = env->GetFieldID(imgClass, "nbLayers", "I");
	jassert(env, nbLayersField != NULL);

	jfieldID colorSpaceField = env->GetFieldID(imgClass, "colorSpace", "I");
	jassert(env, colorSpaceField != NULL);

	jfieldID timestampField = env->GetFieldID(imgClass, "timestamp", "J");
	jassert(env, timestampField != NULL);

	jfieldID dataField = env->GetFieldID(imgClass, "data",
			"Ljava/nio/ByteBuffer;");
	jassert(env, dataField != NULL);

	ALValue image;
	image.arraySetSize(7);
	image = jvideo->getProxy()->call<ALValue> ("getImageRemote", toString(env,
			pId));

	env->SetIntField(imgObj, widthField, image[0]);
	env->SetIntField(imgObj, heightField, image[1]);
	env->SetIntField(imgObj, nbLayersField, image[2]);
	env->SetIntField(imgObj, colorSpaceField, image[3]);

	// @FIXME According to the docment(Blue book), image[4] is highest 32bits and image[5] is lowest 32 bits.
	// But an example code in Red book, image[4] is microsecs and image[5] is secs.
	long long timestamp = ((int) image[4]) * 1000000LL + (int) image[5];
	env->SetLongField(imgObj, timestampField, timestamp);

	jclass bbClass = env->FindClass("java/nio/ByteBuffer");
	jassert(env, bbClass != NULL);
	jmethodID allocMid = env->GetStaticMethodID(bbClass, "allocateDirect",
			"(I)Ljava/nio/ByteBuffer;");
	jassert(env, allocMid != NULL);

	jsize length = image[6].getSize();
	jobject buf = env->CallStaticObjectMethod(bbClass, allocMid, length);
	jassert(env, buf != NULL);
	jassert(env, length == env->GetDirectBufferCapacity(buf));
	jassert(env, length == (int) image[0] * (int) image[1] * (int) image[2]);

	void *ptr = env->GetDirectBufferAddress(buf);
	jassert(env, ptr != NULL);
	const void* data = image[6].GetBinary();
	assert(data != NULL);
	memcpy(ptr, data, length);

	env->SetObjectField(imgObj, dataField, buf);
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getDirectRawImageLocal(
		JNIEnv *env, jclass, jlong objPtr, jstring pId, jobject imgObj) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	jassert(env, imgObj != NULL);

	int res = jvideo->getProxy()->call<int> ("getDirectRawImageLocal",
			toString(env, pId));

	if (res == 0)
		return 0;

	// TODO check validity of pointer 'res'
	ALVisionImage* image = reinterpret_cast<ALVisionImage*> (res);
	assert(image != NULL);

	jclass imgClass = env->GetObjectClass(imgObj);
	jassert(env, imgClass != NULL);

	jfieldID widthField = env->GetFieldID(imgClass, "width", "I");
	jassert(env, widthField != NULL);

	jfieldID heightField = env->GetFieldID(imgClass, "height", "I");
	jassert(env, heightField != NULL);

	jfieldID nbLayersField = env->GetFieldID(imgClass, "nbLayers", "I");
	jassert(env, nbLayersField != NULL);

	jfieldID colorSpaceField = env->GetFieldID(imgClass, "colorSpace", "I");
	jassert(env, colorSpaceField != NULL);

	jfieldID timestampField = env->GetFieldID(imgClass, "timestamp", "J");
	jassert(env, timestampField != NULL);

	jfieldID dataField = env->GetFieldID(imgClass, "data",
			"Ljava/nio/ByteBuffer;");
	jassert(env, dataField != NULL);

	env->SetIntField(imgObj, widthField, image->fWidth);
	env->SetIntField(imgObj, heightField, image->fHeight);
	env->SetIntField(imgObj, nbLayersField, image->fNbLayers);
	env->SetIntField(imgObj, colorSpaceField, image->fColorSpace);
	env->SetLongField(imgObj, timestampField, image->fTimeStamp);

	jsize length = image->fWidth * image->fHeight * image->fNbLayers;

	jobject buf = env->NewDirectByteBuffer(image->getFrame(), length);
	jassert(env, buf != NULL);
	env->SetObjectField(imgObj, dataField, buf);

	return 1;
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1releaseDirectRawImage(
		JNIEnv *env, jclass, jlong objPtr, jstring pId) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("releaseDirectRawImage", toString(
			env, pId));
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getDirectRawImageRemote(
		JNIEnv *env, jclass, jlong objPtr, jstring pId, jobject imgObj) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	jassert(env, imgObj != NULL);

	jclass imgClass = env->GetObjectClass(imgObj);
	jassert(env, imgClass != NULL);

	jfieldID widthField = env->GetFieldID(imgClass, "width", "I");
	jassert(env, widthField != NULL);

	jfieldID heightField = env->GetFieldID(imgClass, "height", "I");
	jassert(env, heightField != NULL);

	jfieldID nbLayersField = env->GetFieldID(imgClass, "nbLayers", "I");
	jassert(env, nbLayersField != NULL);

	jfieldID colorSpaceField = env->GetFieldID(imgClass, "colorSpace", "I");
	jassert(env, colorSpaceField != NULL);

	jfieldID timestampField = env->GetFieldID(imgClass, "timestamp", "J");
	jassert(env, timestampField != NULL);

	jfieldID dataField = env->GetFieldID(imgClass, "data",
			"Ljava/nio/ByteBuffer;");
	jassert(env, dataField != NULL);

	ALValue image;
	image.arraySetSize(7);
	image = jvideo->getProxy()->call<ALValue> ("getDirectRawImageRemote",
			toString(env, pId));

	env->SetIntField(imgObj, widthField, image[0]);
	env->SetIntField(imgObj, heightField, image[1]);
	env->SetIntField(imgObj, nbLayersField, image[2]);
	env->SetIntField(imgObj, colorSpaceField, image[3]);

	// @FIXME According to the docment(Blue book), image[4] is highest 32bits and image[5] is lowest 32 bits.
	// But an example code in Red book, image[4] is microsecs and image[5] is secs.
	long long timestamp = ((int) image[4]) * 1000000LL + (int) image[5];
	env->SetLongField(imgObj, timestampField, timestamp);

	jclass bbClass = env->FindClass("java/nio/ByteBuffer");
	jassert(env, bbClass != NULL);
	jmethodID allocMid = env->GetStaticMethodID(bbClass, "allocateDirect",
			"(I)Ljava/nio/ByteBuffer;");
	jassert(env, allocMid != NULL);

	jsize length = image[6].getSize();
	jobject buf = env->CallStaticObjectMethod(bbClass, allocMid, length);
	jassert(env, buf != NULL);
	jassert(env, length == env->GetDirectBufferCapacity(buf));
	jassert(env, length == (int) image[0] * (int) image[1] * (int) image[2]);

	void *ptr = env->GetDirectBufferAddress(buf);
	jassert(env, ptr != NULL);
	const void* data = image[6].GetBinary();
	assert(data != NULL);
	memcpy(ptr, data, length);

	env->SetObjectField(imgObj, dataField, buf);
}

JNIEXPORT jboolean
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1setResolution(
		JNIEnv *env, jclass, jlong objPtr, jstring pId, jint pSize) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<bool> ("setResolution", toString(env, pId),
			pSize);
}

JNIEXPORT jboolean
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1setFrameRate(
		JNIEnv *env, jclass, jlong objPtr, jstring pId, jint frameRate) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<bool> ("setFrameRate", toString(env, pId),
			frameRate);
}

JNIEXPORT
jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1setColorSpace(
		JNIEnv *env, jclass, jlong objPtr, jstring pId, jint pColorSpace) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<bool> ("setColorSpace", toString(env, pId),
			pColorSpace);
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getVIMResolution(
		JNIEnv *, jclass, jlong objPtr) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("getVIMResolution");
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getVIMColorSpace(
		JNIEnv *, jclass, jlong objPtr) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("getVIMColorSpace");
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getVIMFrameRate(
		JNIEnv *, jclass, jlong objPtr) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("getVIMFrameRate");
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getGVMResolution(
		JNIEnv *env, jclass, jlong objPtr, jstring pId) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("getGVMResolution",
			toString(env, pId));
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getGVMColorSpace(
		JNIEnv *env, jclass, jlong objPtr, jstring pId) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("getGVMColorSpace",
			toString(env, pId));
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getGVMFrameRate(
		JNIEnv *env, jclass, jlong objPtr, jstring pId) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("getGVMFrameRate", toString(env, pId));
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1setParam(
		JNIEnv *env, jclass, jlong objPtr, jint pParam, jint pNewValue) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	jvideo->getProxy()->callVoid("setParam", pParam, pNewValue);
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1setParamDefault(
		JNIEnv *env, jclass, jlong objPtr, jint pParam) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	jvideo->getProxy()->callVoid("setParamDefault", pParam);
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getAngles(
		JNIEnv *env, jclass, jlong objPtr, jfloat posX, jfloat posY,
		jobject pointObj) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	jclass pointClass = env->GetObjectClass(pointObj);
	jassert(env, pointClass != NULL);

	jfieldID xField = env->GetFieldID(pointClass, "x", "I");
	jassert(env, xField != NULL);

	jfieldID yField = env->GetFieldID(pointClass, "y", "I");
	jassert(env, yField != NULL);

	ALValue pos;
	pos.arraySetSize(2);
	pos[0] = posX;
	pos[1] = posY;
	ALValue angle = jvideo->getProxy()->call<ALValue> ("getAngles", pos);
	env->SetIntField(pointObj, xField, angle[0]);
	env->SetIntField(pointObj, yField, angle[1]);
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1resolutionToSizes(
		JNIEnv *env, jclass, jlong objPtr, jint resolution, jobject dimObj) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	jclass dimClass = env->GetObjectClass(dimObj);
	jassert(env, dimClass != NULL);

	jfieldID widthField = env->GetFieldID(dimClass, "width", "I");
	jassert(env, widthField != NULL);

	jfieldID heightField = env->GetFieldID(dimClass, "height", "I");
	jassert(env, heightField != NULL);

	ALValue size = jvideo->getProxy()->call<ALValue> ("resolutionToSizes",
			resolution);
	env->SetIntField(dimObj, widthField, size[0]);
	env->SetIntField(dimObj, heightField, size[1]);
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1sizesToResolution(
		JNIEnv *env, jclass, jlong objPtr, jint width, jint height) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("sizesToResolution", width, height);
}

JNIEXPORT
jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1recordVideo(
		JNIEnv *, jclass, jlong objPtr, jstring pId, jstring pPath,
		jint pTotalNumber, jint pPeriod) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<bool> ("recordVideo", pId, pPath,
			pTotalNumber, pPeriod);
}

JNIEXPORT
jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1stopVideo(
		JNIEnv *, jclass, jlong objPtr, jstring pId) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<bool> ("stopVideo", pId);
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getParam(JNIEnv *,
		jclass, jlong objPtr, jint pParam) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<int> ("getParam", pParam);
}

#ifdef __cplusplus
}
#endif
