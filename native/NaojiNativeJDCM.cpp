#include <iostream>
#include <cassert>

#include <boost/lexical_cast.hpp>

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

#ifndef AL_CATCH_ERR
#define AL_CATCH_ERR(CALLBACK) catch (AL::ALError err) { CALLBACK }
#endif

const int cDCMCommandDelay = 40;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1create(JNIEnv *,
		jclass, jlong jbrokerPtr) {
	JALBroker *jbroker = reinterpret_cast<JALBroker*> (jbrokerPtr);
	assert(jbroker != NULL);
	JDCM *jdcm = new JDCM(jbroker);
	return reinterpret_cast<jlong> (jdcm);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1dispose(JNIEnv *,
		jclass, jlong jdcmPtr) {
	JDCM *jdcm = reinterpret_cast<JDCM*> (jdcmPtr);
	assert(jdcm != NULL);

	delete jdcm;
}

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1isRunning(
		JNIEnv *, jclass, jlong objPtr, jint taskId) {
	JDCM *jdcm = reinterpret_cast<JDCM*> (objPtr);
	assert(jdcm != NULL);

	return jdcm->getProxy()->isRunning(taskId);
}

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1wait(JNIEnv *,
		jclass, jlong objPtr, jint taskId, jint timeout) {
	JDCM *jdcm = reinterpret_cast<JDCM*> (objPtr);
	assert(jdcm != NULL);

	return jdcm->getProxy()->wait(taskId, timeout);
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1createAlias(JNIEnv *env,
		jclass, jlong jdcmPtr, jobjectArray jstrings) {
	JDCM *jdcm = reinterpret_cast<JDCM*> (jdcmPtr);
	assert(jdcm != NULL);

	ALValue alias;
	alias.arraySetSize(2);

	jsize size = env->GetArrayLength(jstrings);
	int id = jdcm->aliases++;
	alias[0] = boost::lexical_cast<string>(id);
	alias[1].arraySetSize(size);
	for (int i = 0; i < size; i++) {
		jstring jstr = static_cast<jstring> (env->GetObjectArrayElement(
				jstrings, i));
		jassert(env, jstr != NULL);
		alias[1][i] = toString(env, jstr);
		env->DeleteLocalRef(jstr);
	}
	try {
		jdcm->getProxy()->createAlias(alias);
	}AL_CATCH_ERR(assert(false);)
	return id;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1getTime(JNIEnv *, jclass,
		jlong jdcmPtr) {
	JDCM *jdcm = reinterpret_cast<JDCM*> (jdcmPtr);
	assert(jdcm != NULL);

	return jdcm->getProxy()->getTime(cDCMCommandDelay);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1set(JNIEnv *env,
		jclass, jlong jdcmPtr, jstring key, jint mergeType,
		jfloatArray jvalues, jintArray jdurations) {
	JDCM *jdcm = reinterpret_cast<JDCM*> (jdcmPtr);
	assert(jdcm != NULL);

	jsize valueSize = env->GetArrayLength(jvalues);
	jsize durationsSize = env->GetArrayLength(jdurations);
	assert(valueSize == durationsSize);

	try {
		ALValue commands;

		commands.arraySetSize(3);
		commands[0] = toString(env, key);
		commands[1] = jdcm->getMergeType(mergeType);
		commands[2].arraySetSize(valueSize);

		jfloat* values =
				(jfloat*) env->GetPrimitiveArrayCritical(jvalues, NULL);
		jint* durations = (jint*) env->GetPrimitiveArrayCritical(jdurations,
				NULL);

		int baseTime = jdcm->getProxy()->getTime(cDCMCommandDelay);
		for (int i = 0; i < valueSize; i++) {
			commands[2][i].arraySetSize(2);
			commands[2][i][0] = values[i];
			commands[2][i][1] = durations[i];
		}

		jdcm->getProxy()->set(commands);
	}AL_CATCH_ERR(assert(false);)
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1setTimeMixed(
		JNIEnv *, jclass, jlong jdcmPtr, jint, jint, jfloatArray, jintArray);

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JDCM__1setTimeSeparate(JNIEnv *env,
		jclass, jlong jdcmPtr, jint aliasId, jint mergeType,
		jfloatArray jvalueMatrix, jintArray jdurations) {
	JDCM *jdcm = reinterpret_cast<JDCM*> (jdcmPtr);
	assert(jdcm != NULL);

	jsize valueMatrixSize = env->GetArrayLength(jvalueMatrix);
	jsize durationsSize = env->GetArrayLength(jdurations);
	assert(valueMatrixSize % durationsSize == 0);
	jint jointNum = valueMatrixSize / durationsSize;

	ALValue commands;
	commands.arraySetSize(6);
	commands[0] = boost::lexical_cast<string>(aliasId);
	commands[1] = jdcm->getMergeType(mergeType);
	commands[2] = string("time-separate");
	commands[3] = 0;

	commands[4].arraySetSize(durationsSize);

	jint* durations = (jint*) env->GetPrimitiveArrayCritical(jdurations, NULL);
	int baseTime = jdcm->getProxy()->getTime(cDCMCommandDelay);
	for (int i = 0; i < durationsSize; i++) {
		commands[4][i] = baseTime + durations[i];
	}
	env->ReleasePrimitiveArrayCritical(jdurations, durations, JNI_ABORT);

	commands[5].arraySetSize(jointNum);

	jfloat* valueMatrix = (jfloat*) env->GetPrimitiveArrayCritical(
			jvalueMatrix, NULL);
	for (int i = 0; i < jointNum; i++) {
		commands[5][i].arraySetSize(durationsSize);
		for (int j = 0; j < durationsSize; j++) {
			commands[5][i][j] = valueMatrix[i * durationsSize + j];
		}
	}
	env->ReleasePrimitiveArrayCritical(jvalueMatrix, valueMatrix, JNI_ABORT);
	try {
		jdcm->getProxy()->setAlias(commands);
	}AL_CATCH_ERR(assert(false);)
}

}
