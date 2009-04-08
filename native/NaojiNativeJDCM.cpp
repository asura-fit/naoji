#include <iostream>
#include <cassert>

#include "alproxy.h"
#include "alptr.h"
#include "albroker.h"

#include "alerror.h"

#include <jni.h>       /* where everything is defined */

// include JNI Headers
#include "jp_ac_fit_asura_naoji_jal_JDCM.h"

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

JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1create(JNIEnv *,
		jclass, jlong);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1dispose(JNIEnv *,
		jclass, jlong);

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1isRunning(
		JNIEnv *, jclass, jlong, jint);

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1wait(JNIEnv *,
		jclass, jlong, jint, jint);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1createAlias(
		JNIEnv *, jclass, jlong, jobjectArray);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1getTime(JNIEnv *,
		jclass, jlong);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1set(JNIEnv *,
		jclass, jlong, jstring, jint, jfloatArray, jintArray);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1setTimeMixed(
		JNIEnv *, jclass, jlong, jint, jint, jfloatArray, jintArray);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1setTimeSeparate(
		JNIEnv *, jclass, jlong, jint, jint, jfloatArray, jintArray);
}
