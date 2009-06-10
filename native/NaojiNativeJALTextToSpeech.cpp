#include <iostream>
#include <cassert>

#include "alproxy.h"
#include "alptr.h"
#include "albroker.h"

#include "alerror.h"

#include <jni.h>       /* where everything is defined */

// include JNI Headers
#include "jp_ac_fit_asura_naoji_NaojiModule.h"
#include "jp_ac_fit_asura_naoji_jal_JALTextToSpeech.h"

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

JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JALTextToSpeech__1create(
		JNIEnv *, jclass, jlong jbrokerPtr) {
	JALBroker *jbroker = reinterpret_cast<JALBroker*> (jbrokerPtr);
	assert(jbroker != NULL);
	JALTextToSpeech *jtts = new JALTextToSpeech(jbroker);
	return reinterpret_cast<jlong> (jtts);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALTextToSpeech__1dispose(
		JNIEnv *, jclass, jlong objPtr) {
	JALTextToSpeech *jtts = reinterpret_cast<JALTextToSpeech*> (objPtr);
	assert(jtts != NULL);

	delete jtts;
}

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALTextToSpeech__1isRunning(
		JNIEnv *, jclass, jlong objPtr, jint taskId) {
	JALTextToSpeech *jtts = reinterpret_cast<JALTextToSpeech*> (objPtr);
	assert(jtts != NULL);

	// return jtts->getProxy()->isRunning(taskId);
	return jtts->getProxy()->call<bool> ("isRunning", taskId);
}

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALTextToSpeech__1wait(
		JNIEnv *, jclass, jlong objPtr, jint taskId, jint timeout) {
	JALTextToSpeech *jtts = reinterpret_cast<JALTextToSpeech*> (objPtr);
	assert(jtts != NULL);

	return jtts->getProxy()->wait(taskId, timeout);
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALTextToSpeech__1say(
		JNIEnv *env, jclass, jlong objPtr, jstring pStringToSay) {
	JALTextToSpeech *jtts = reinterpret_cast<JALTextToSpeech*> (objPtr);
	assert(jtts != NULL);

	return jtts->getProxy()->post.say(toString(env, pStringToSay));
}

#ifdef __cplusplus
}
#endif

