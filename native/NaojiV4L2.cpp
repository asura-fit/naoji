#include <iostream>
#include <cassert>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/videodev.h>

#include <jni.h>       /* where everything is defined */

// include JNI Headers

#include "NaojiV4L2.hpp"

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
		JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1createVideodev(
				JNIEnv *, jclass, jstring);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1destroy(
		JNIEnv *, jclass, jint);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1disposeBuffers(
				JNIEnv *, jclass, jint);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1disposeImage(
		JNIEnv *, jclass, jint, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getSelectedCamera(
				JNIEnv *, jclass, jint);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getControl(
		JNIEnv *, jclass, jint, jint);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getFormat(
		JNIEnv *, jclass, jint, jobject);

JNIEXPORT jboolean
		JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1isSupportedControl(
				JNIEnv *, jclass, jint, jint);

JNIEXPORT jboolean
		JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1isSupportedFormat(
				JNIEnv *, jclass, jint, jint, jint, jint);

JNIEXPORT jboolean
		JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1isSupportedFPS(
				JNIEnv *, jclass, jint, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1requestBuffers(
				JNIEnv *, jclass, jint, jint);

JNIEXPORT jobject
		JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1queryBuffer(
				JNIEnv *, jclass, jint, jint);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1selectCamera(
		JNIEnv *, jclass, jint, jint);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1setControl(
		JNIEnv *, jclass, jint, jint, jint);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1setFormat(
		JNIEnv *, jclass, jint, jobject);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1setFPS(
		JNIEnv *, jclass, jint, jint);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1start(
		JNIEnv *, jclass, jint);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1stop(
		JNIEnv *, jclass, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1retrieveImage(
				JNIEnv *, jclass, jint, jobject);

#ifdef __cplusplus
}
#endif

