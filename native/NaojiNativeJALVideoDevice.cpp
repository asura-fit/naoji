#include <iostream>
#include <cassert>

#include "alproxy.h"
#include "alptr.h"
#include "albroker.h"

#include "alerror.h"

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

	return jvideo->getProxy()->call<bool> ("startFrameGrabber");
}

JNIEXPORT jboolean
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1stopFrameGrabber(
		JNIEnv *, jclass, jlong objPtr) {
	JALVideoDevice *jvideo = reinterpret_cast<JALVideoDevice*> (objPtr);
	assert(jvideo != NULL);

	return jvideo->getProxy()->call<bool> ("stopFrameGrabber");
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

	jvideo->getProxy()->call<void> ("unRegister", toString(env, pId));
}

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getImageLocal
 * Signature: (JLjava/lang/String;Ljp/ac/fit/asura/naoji/jal/JALImage;)V
 */
JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getImageLocal(
				JNIEnv *, jclass, jlong, jstring, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _releaseImage
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1releaseImage(
				JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getImageRemote
 * Signature: (JLjava/lang/String;Ljp/ac/fit/asura/naoji/jal/JALImage;)Ljp/ac/fit/asura/naoji/jal/JALImage;
 */
JNIEXPORT jobject
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getImageRemote(
				JNIEnv *, jclass, jlong, jstring, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getDirectRawImageLocal
 * Signature: (JLjp/ac/fit/asura/naoji/jal/JALImage;)Ljp/ac/fit/asura/naoji/jal/JALImage;
 */
JNIEXPORT jobject
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getDirectRawImageLocal(
				JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _releaseDirectRawImage
 * Signature: (J)V
 */
JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1releaseDirectRawImage(
				JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getDirectRawImageRemote
 * Signature: (JLjp/ac/fit/asura/naoji/jal/JALImage;)Ljp/ac/fit/asura/naoji/jal/JALImage;
 */
JNIEXPORT jobject
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getDirectRawImageRemote(
				JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _setResolution
 * Signature: (JLjava/lang/String;I)Z
 */
JNIEXPORT jboolean
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1setResolution(
				JNIEnv *, jclass, jlong, jstring, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _setFrameRate
 * Signature: (JLjava/lang/String;I)Z
 */
JNIEXPORT jboolean
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1setFrameRate(
				JNIEnv *, jclass, jlong, jstring, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _setColorSpace
 * Signature: (JLjava/lang/String;I)Z
 */
JNIEXPORT jboolean
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1setColorSpace(
				JNIEnv *, jclass, jlong, jstring, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getVIMResolution
 * Signature: (J)I
 */
JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getVIMResolution(
				JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getVIMColorSpace
 * Signature: (J)I
 */
JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getVIMColorSpace(
				JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getVIMFrameRate
 * Signature: (J)I
 */
JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getVIMFrameRate(
				JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getGVMResolution
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getGVMResolution(
				JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getGVMColorSpace
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getGVMColorSpace(
				JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getGVMFrameRate
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getGVMFrameRate(
				JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _setParam
 * Signature: (JII)V
 */
JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1setParam(
				JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _setParamDefault
 * Signature: (JI)V
 */
JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1setParamDefault(
				JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getAngles
 * Signature: (JFFLjava/awt/geom/Point2D;)V
 */
JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getAngles(
				JNIEnv *, jclass, jlong, jfloat, jfloat, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _resolutionToSizes
 * Signature: (JILjava/awt/Dimension;)V
 */
JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1resolutionToSizes(
				JNIEnv *, jclass, jlong, jint, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _sizesToResolution
 * Signature: (JII)I
 */
JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1sizesToResolution(
				JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _recordVideo
 * Signature: (JLjava/lang/String;Ljava/lang/String;II)Z
 */
JNIEXPORT jboolean
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1recordVideo(
				JNIEnv *, jclass, jlong, jstring, jstring, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _stopVideo
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1stopVideo(
				JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALVideoDevice
 * Method:    _getParam
 * Signature: (JI)I
 */
JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALVideoDevice__1getParam(
				JNIEnv *, jclass, jlong, jint);

#ifdef __cplusplus
}
#endif
