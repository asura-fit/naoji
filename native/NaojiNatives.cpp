#include <iostream>
#include <cassert>

#include "alproxy.h"
#include "alptr.h"
#include "albroker.h"

#include "alerror.h"

#include <jni.h>       /* where everything is defined */

// include JNI Headers
#include "jp_ac_fit_asura_naoji_NaojiModule.h"
#include "jp_ac_fit_asura_naoji_jal_JALMemory.h"
#include "jp_ac_fit_asura_naoji_jal_JALMotion.h"
#include "jp_ac_fit_asura_naoji_jal_JALProxy.h"

#include "NaojiModule.hpp"
#include "NaojiNatives.hpp"

using namespace AL;
using namespace Naoji;

#ifdef __cplusplus
extern "C" {
#endif

/* Inaccessible static: factories */
/*
 * Class:     jp_ac_fit_asura_naoji_NaojiModule
 * Method:    _createJALBroker
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_NaojiModule__1createJALBroker(
		JNIEnv *, jobject, jlong naojiPtr) {
	NaojiModule *naoji = reinterpret_cast<NaojiModule*> (naojiPtr);
	assert(naoji != NULL);
	AL::ALPtr<AL::ALBroker> broker = naoji->getParentBroker();
	JALBroker *jbroker = new JALBroker(broker);
	return reinterpret_cast<jlong> (jbroker);
}

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMemory
 * Method:    _create
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1create(
		JNIEnv *, jobject, jlong jbrokerPtr) {
	JALBroker *jbroker = reinterpret_cast<JALBroker*> (jbrokerPtr);
	assert(jbroker != NULL);
	JALMemory *jmemory = new JALMemory(jbroker);
	return reinterpret_cast<jlong> (jmemory);
}

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _create
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1create(
		JNIEnv *, jobject, jlong jbrokerPtr) {
	JALBroker *jbroker = reinterpret_cast<JALBroker*> (jbrokerPtr);
	assert(jbroker != NULL);
	JALMotion *jmotion = new JALMotion(jbroker);
	return reinterpret_cast<jlong> (jmotion);
}

/* Inaccessible static: _00024assertionsDisabled */
/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALProxy
 * Method:    _create
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JALProxy__1create(
		JNIEnv *, jobject, jlong) {
	// not implemented.
	assert(false);
	return 0;
}

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getAngle
 * Signature: (JLjava/lang/String;)F
 */
JNIEXPORT jfloat JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getAngle(
		JNIEnv *env, jobject, jlong objPtr, jstring pJointName) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	// TODO caching JointName.
	const char *jointChars = env->GetStringUTFChars(pJointName, NULL);
	jfloat angle = jmotion->getProxy()->getAngle(jointChars);
	env->ReleaseStringUTFChars(pJointName, jointChars);

	return angle;
}

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoAngle
 * Signature: (JLjava/lang/String;FFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoAngle(
		JNIEnv *env, jobject, jlong objPtr, jstring pJointName,
		jfloat pAngle, jfloat pDuration, jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	// TODO caching JointName.
	const char *jointChars = env->GetStringUTFChars(pJointName, NULL);
	jint taskId = jmotion->getProxy()->post.gotoAngle(jointChars, pAngle, pDuration, pInterpolationType);
	env->ReleaseStringUTFChars(pJointName, jointChars);

	return taskId;
}

#ifdef __cplusplus
}
#endif

