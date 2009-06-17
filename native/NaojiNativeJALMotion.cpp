#include <iostream>
#include <cassert>

#include "alproxy.h"
#include "alptr.h"
#include "albroker.h"

#include "alerror.h"

#include <jni.h>       /* where everything is defined */

// include JNI Headers
#include "jp_ac_fit_asura_naoji_NaojiModule.h"
#include "jp_ac_fit_asura_naoji_jal_JALMotion.h"

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

JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1create(
		JNIEnv *, jclass, jlong jbrokerPtr) {
	JALBroker *jbroker = reinterpret_cast<JALBroker*> (jbrokerPtr);
	assert(jbroker != NULL);
	JALMotion *jmotion = new JALMotion(jbroker);
	return reinterpret_cast<jlong> (jmotion);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1dispose(
		JNIEnv *, jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	delete jmotion;
}

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1isDefinedJoint(
		JNIEnv *env, jclass, jlong objPtr, jint jointId) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->isDefinedJoint(jointId);
}

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1isRunning(
		JNIEnv *, jclass, jlong objPtr, jint taskId) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->isRunning(taskId);
}

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1wait(
		JNIEnv *, jclass, jlong objPtr, jint taskId, jint timeout) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->wait(taskId, timeout);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addWalkArc(
		JNIEnv *, jclass, jlong, jfloat, jfloat, jint);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addWalkSideways(
				JNIEnv *, jclass, jlong, jfloat, jint);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addWalkStraight(
				JNIEnv *, jclass, jlong, jfloat, jint);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeAngle(
		JNIEnv *, jclass, jlong, jint, jfloat);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeBodyAngles(
				JNIEnv *, jclass, jlong, jfloatArray);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeChainAngles(
				JNIEnv *, jclass, jlong, jint, jfloatArray);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeCom(
		JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changePosition(
				JNIEnv *, jclass, jlong, jint, jint, jfloat, jfloat, jfloat,
				jfloat, jfloat, jfloat, jint);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1clearFootsteps(
		JNIEnv *, jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->getProxy()->clearFootsteps();
}

void naoji_JALMotion_doMove_internal(JNIEnv *env, jobjectArray jangles,
		jobjectArray jdurations, ALValue& pAngles, ALValue& pDurations) {
	assert(env->GetArrayLength(jangles) == env->GetArrayLength(jdurations));
	jint jointNum = env->GetArrayLength(jangles);

	pAngles.arraySetSize(jointNum);
	pDurations.arraySetSize(jointNum);
	for (int i = 0; i < jointNum; i++) {
		// set angles each joint
		jfloatArray angleArray = (jfloatArray) env->GetObjectArrayElement(
				jangles, i);
		jint commandNum = env->GetArrayLength(angleArray);
		pAngles[i].arraySetSize(commandNum);

		jfloat* angles = (jfloat*) env->GetPrimitiveArrayCritical(angleArray,
				NULL);
		for (int j = 0; j < commandNum; j++) {
			pAngles[i][j] = angles[j];
		}
		env->ReleasePrimitiveArrayCritical(angleArray, angles, JNI_ABORT);

		// set durations each joint
		jfloatArray durationArray = (jfloatArray) env->GetObjectArrayElement(
				jdurations, i);
		// angle length and duration length must have the same size
		assert(commandNum == env->GetArrayLength(durationArray));
		pDurations[i].arraySetSize(commandNum);

		jfloat* durations = (jfloat*) env->GetPrimitiveArrayCritical(
				durationArray, NULL);
		for (int j = 0; j < commandNum; j++) {
			pDurations[i][j] = durations[j];
		}
		env->ReleasePrimitiveArrayCritical(durationArray, durations, JNI_ABORT);
	}
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1doMove(
		JNIEnv *env, jclass, jlong objPtr, jintArray jJointIdArray,
		jobjectArray jangles, jobjectArray jdurations, jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jint jointNum = env->GetArrayLength(jangles);
	assert(jointNum == env->GetArrayLength(jJointIdArray));
	assert(jointNum == env->GetArrayLength(jdurations));

	ALValue pJointNames;
	pJointNames.arraySetSize(jointNum);
	jint* jointIdArray = (jint*) env->GetPrimitiveArrayCritical(jJointIdArray,
			NULL);
	for (int i = 0; i < jointNum; i++) {
		pJointNames[i] = jmotion->getJointName(jointIdArray[i]);
	}
	env->ReleasePrimitiveArrayCritical(jJointIdArray, jointIdArray, JNI_ABORT);
	assert(pJointNames.getSize() == jointNum);

	// do copy values to ALValue
	ALValue pAngles;
	ALValue pDurations;

	naoji_JALMotion_doMove_internal(env, jangles, jdurations, pAngles,
			pDurations);
	return jmotion->getProxy()->post.doMove(pJointNames, pAngles, pDurations,
			pInterpolationType);
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1doMoveAll(
		JNIEnv *env, jclass, jlong objPtr, jobjectArray jangles,
		jobjectArray jdurations, jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jint jointNum = env->GetArrayLength(jangles);
	assert(jointNum == env->GetArrayLength(jdurations));

	ALValue pJointNames = jmotion->getBodyJointNames();
	assert(pJointNames.getSize() == jointNum);

	// do copy values to ALValue
	ALValue pAngles;
	ALValue pDurations;

	naoji_JALMotion_doMove_internal(env, jangles, jdurations, pAngles,
			pDurations);
	return jmotion->getProxy()->post.doMove(pJointNames, pAngles, pDurations,
			pInterpolationType);
}

JNIEXPORT jfloat JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getAngle(
		JNIEnv *, jclass, jlong objPtr, jint pJointId) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	// TODO caching JointName.
	string jointName = jmotion->getJointName(pJointId);
	jfloat angle = jmotion->getProxy()->getAngle(jointName);

	return angle;
}

JNIEXPORT jfloat
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getAngleError(
				JNIEnv *, jclass, jlong, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBalanceMode(
				JNIEnv *, jclass, jlong);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyAngleErrors(
				JNIEnv *, jclass, jlong, jfloatArray);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyAngles(
		JNIEnv *env, jclass, jlong objPtr, jfloatArray pAngles) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> angles(jmotion->getProxy()->getBodyAngles());
	jsize len = angles.size();
	env->SetFloatArrayRegion(pAngles, 0, len, &angles[0]);
}

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyCommandAngles(
				JNIEnv *, jclass, jlong, jfloatArray);

JNIEXPORT jobjectArray JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyJointNames(
		JNIEnv *env, jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<string> names(jmotion->getProxy()->getBodyJointNames());
	jclass stringClass = env->FindClass("java/lang/String");
	jobjectArray nameArray = env->NewObjectArray(names.size(), stringClass,
			NULL);
	for (int i = 0; i < names.size(); i++) {
		jstring name = env->NewStringUTF(names[i].c_str());
		env->SetObjectArrayElement(nameArray, i, name);
		env->DeleteLocalRef(name);
	}
	return nameArray;
}

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyLimits(
				JNIEnv *, jclass, jlong, jfloatArray, jfloatArray, jfloatArray);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyStiffnesses(
				JNIEnv *, jclass, jlong, jfloatArray);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainAngleErrors(
				JNIEnv *, jclass, jlong, jint, jfloatArray);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainAngles(
				JNIEnv *, jclass, jlong, jint, jfloatArray);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainCommandAngles(
				JNIEnv *, jclass, jlong, jint, jfloatArray);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainLimits(
				JNIEnv *, jclass, jlong, jint, jfloatArray, jfloatArray,
				jfloatArray);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainStiffnesses(
				JNIEnv *, jclass, jlong, jint, jfloatArray);

JNIEXPORT jfloat
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getCommandAngle(
				JNIEnv *, jclass, jlong, jint);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getForwardTransform(
				JNIEnv *, jclass, jlong, jint, jint, jfloatArray);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getJointLimits(
				JNIEnv *, jclass, jlong, jint, jfloatArray);

JNIEXPORT jfloat JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getJointStiffness(
		JNIEnv *, jclass, jlong objPtr, jint pJointId) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	jfloat stiffness = jmotion->getProxy()->getJointStiffness(jointName);
	return stiffness;
}

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getJointSpeedParams(
				JNIEnv *, jclass, jlong, jint, jfloatArray);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getPosition(
		JNIEnv *, jclass, jlong, jint, jint, jfloatArray);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getRemainingFootStepCount(
				JNIEnv *, jclass, jlong);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getSensorPosition(
				JNIEnv *, jclass, jlong, jstring, jint, jfloatArray);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getSupportMode(
				JNIEnv *, jclass, jlong);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getWalkArmsConfig(
				JNIEnv *, jclass, jlong, jfloatArray);

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getWalkArmsEnable(
		JNIEnv *, jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->getWalkArmsEnable();
}

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getWalkConfig(
				JNIEnv *, jclass, jlong, jfloatArray);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoAngle(
		JNIEnv *, jclass, jlong objPtr, jint pJointId, jfloat pAngle,
		jfloat pDuration, jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	return jmotion->getProxy()->post.gotoAngle(jointName, pAngle, pDuration,
			pInterpolationType);
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoAngles(
		JNIEnv *, jclass, jlong, jintArray, jfloatArray, jfloat, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoAnglesWithSpeed(
				JNIEnv *, jclass, jlong, jintArray, jfloatArray, jint, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoAngleWithSpeed(
				JNIEnv *, jclass, jlong, jint, jfloat, jint, jint);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoBodyAngles(
		JNIEnv *env, jclass, jlong objPtr, jfloatArray pAngles,
		jfloat pDuration, jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	// copy array.
	jsize len = env->GetArrayLength(pAngles);
	vector<jfloat> angleVector(len);
	env->GetFloatArrayRegion(pAngles, 0, len, &angleVector[0]);
	assert(angleVector.size() == len);
	return jmotion->getProxy()->post.gotoBodyAngles(angleVector, pDuration,
			pInterpolationType);
}

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoBodyAnglesWithSpeed(
				JNIEnv *, jclass, jlong, jfloatArray, jint, jint);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoBodyStiffness(
		JNIEnv *, jclass, jlong objPtr, jfloat pStiffness, jfloat pDuration,
		jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->post.gotoBodyStiffness(pStiffness, pDuration,
			pInterpolationType);
}

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoBodyStiffnesses(
				JNIEnv *, jclass, jlong, jfloatArray, jfloat, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoChainAngles(
				JNIEnv *, jclass, jlong, jint, jfloatArray, jfloat, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoChainAnglesWithSpeed(
				JNIEnv *, jclass, jlong, jint, jfloatArray, jint, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoChainStiffness(
				JNIEnv *, jclass, jlong, jint, jfloat, jfloat, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoChainStiffnesses(
				JNIEnv *, jclass, jlong, jint, jfloatArray, jfloat, jint);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoCom(
		JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat, jfloat, jint);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoJointStiffness(
		JNIEnv *, jclass, jlong objPtr, jint pJointId, jfloat pStiffness,
		jfloat pDuration, jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	return jmotion->getProxy()->post.gotoJointStiffness(jointName, pStiffness,
			pDuration, pInterpolationType);
}

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoJointStiffnesses(
				JNIEnv *, jclass, jlong, jintArray, jfloatArray, jfloat, jint);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoPosition(
		JNIEnv *, jclass, jlong, jint, jint, jfloat, jfloat, jfloat, jfloat,
		jfloat, jfloat, jint, jfloat, jint);

JNIEXPORT jint
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoTorsoOrientation(
				JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat, jint);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1killAll(
		JNIEnv *, jclass, jlong);

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1killTask(
		JNIEnv *, jclass, jlong, jint);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1openHand(
		JNIEnv *, jclass, jlong, jstring);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setAngle(
		JNIEnv *, jclass, jlong, jint, jfloat);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setBalanceMode(
				JNIEnv *, jclass, jlong, jint);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setBodyAngles(
				JNIEnv *, jclass, jlong, jfloatArray);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setBodyStiffness(
		JNIEnv *, jclass, jlong objPtr, jfloat pStiffness) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->getProxy()->setBodyStiffness(pStiffness);
}

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setChainAngles(
				JNIEnv *, jclass, jlong, jint, jfloatArray);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setChainStiffness(
				JNIEnv *, jclass, jlong, jint, jfloat);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setCom(
		JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setJointStiffness(
		JNIEnv *, jclass, jlong objPtr, jint pJointId, jfloat pStiffness) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	jmotion->getProxy()->setJointStiffness(jointName, pStiffness);
}

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setJointStiffnesses(
				JNIEnv *, jclass, jlong, jintArray, jfloatArray);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setJointSpeedParams(
				JNIEnv *, jclass, jlong, jint, jfloat, jfloat, jfloat);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setPosition(
		JNIEnv *, jclass, jlong, jint, jint, jfloat, jfloat, jfloat, jfloat,
		jfloat, jfloat, jint);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setSupportMode(
				JNIEnv *, jclass, jlong, jint);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setTorsoOrientation(
				JNIEnv *, jclass, jlong, jfloat, jfloat);

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setWalkArmsConfig(
				JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat, jfloat);

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setWalkArmsEnable(JNIEnv *,
		jclass, jlong objPtr, jboolean pArmsEnable) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->getProxy()->setWalkArmsEnable(pArmsEnable);
}

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setWalkArmsEnable(
				JNIEnv *, jclass, jlong, jboolean);

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setWalkConfig(JNIEnv *,
		jclass, jlong objPtr, jfloat pMaxStepLength, jfloat pMaxStepHeight,
		jfloat pMaxStepSide, jfloat pMaxStepTurn, jfloat pZmpOffsetX,
		jfloat pZmpOffsetY) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->getProxy()->setWalkConfig(pMaxStepLength, pMaxStepHeight,
			pMaxStepSide, pMaxStepTurn, pZmpOffsetX, pZmpOffsetY);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setWalkExtraConfig(JNIEnv *,
		jclass, jlong objPtr, jfloat pLHipRollBacklashCompensator,
		jfloat pRHipRollBacklashCompensator, jfloat pHipHeight,
		jfloat pTorsoYOrientation) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->getProxy()->setWalkExtraConfig(pLHipRollBacklashCompensator,
			pRHipRollBacklashCompensator, pHipHeight, pTorsoYOrientation);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1stop(
		JNIEnv *, jclass, jlong objPtr, jint taskId) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->getProxy()->stop(taskId);
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1turn(
		JNIEnv *, jclass, jlong objPtr, jfloat pAngle, jint pNumSamplesPerStep) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->post.turn(pAngle, pNumSamplesPerStep);
}

JNIEXPORT void
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1waitUntilWalkIsFinished(
				JNIEnv *, jclass, jlong);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1walk(
		JNIEnv *, jclass, jlong);

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1walkArc(
		JNIEnv *, jclass, jlong objPtr, jfloat pAngle, jfloat pRadius,
		jint pNumSamplesPerStep) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->post.walkArc(pAngle, pRadius,
			pNumSamplesPerStep);
}

JNIEXPORT jboolean
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1walkIsActive(JNIEnv *,
		jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->walkIsActive();
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1walkStraight(
		JNIEnv *, jclass, jlong objPtr, jfloat pDistance,
		jint pNumSamplesPerStep) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->post.walkStraight(pDistance, pNumSamplesPerStep);
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1walkSideways(
		JNIEnv *env, jclass, jlong objPtr, jfloat pDistance,
		jint pNumSamplesPerStep) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->post.walkSideways(pDistance, pNumSamplesPerStep);
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setTimeSeparate(JNIEnv *env,
		jclass, jlong objPtr, jfloatArray jvalueMatrix, jintArray jtimeArray,
		jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	ALValue pJointNames = jmotion->getBodyJointNames();
	jint jointNum = pJointNames.getSize();
	jint valueMatrixSize = env->GetArrayLength(jvalueMatrix);
	jint timeArraySize = env->GetArrayLength(jtimeArray);

	assert(valueMatrixSize == jointNum * timeArraySize);

	// do copy values to ALValue
	ALValue pAngles;
	ALValue pDurations;

	pAngles.arraySetSize(jointNum);
	pDurations.arraySetSize(jointNum);

	jint* timeArray = (jint*) env->GetPrimitiveArrayCritical(jtimeArray, NULL);
	ALValue pTimeArray;
	pTimeArray.arraySetSize(timeArraySize);
	for (int i = 0; i < timeArraySize; i++) {
		pTimeArray[i] = timeArray[i] / 1000.0f;
	}
	env->ReleasePrimitiveArrayCritical(jtimeArray, timeArray, JNI_ABORT);

	jfloat* values = (jfloat*) env->GetPrimitiveArrayCritical(jvalueMatrix,
			NULL);
	for (int i = 0; i < jointNum; i++) {
		// set angles each joint
		pAngles[i].arraySetSize(timeArraySize);
		for (int j = 0; j < timeArraySize; j++) {
			pAngles[i][j] = values[j * jointNum + i];
		}
		pDurations[i] = pTimeArray;
	}
	env->ReleasePrimitiveArrayCritical(jvalueMatrix, values, JNI_ABORT);

	return jmotion->getProxy()->post.doMove(pJointNames, pAngles, pDurations,
			pInterpolationType);
}

#ifdef __cplusplus
}
#endif

