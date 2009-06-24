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

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addTurn(
		JNIEnv *, jclass, jlong objPtr, jfloat pAngle, jint pNumSamplesPerStep) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->addTurn(pAngle, pNumSamplesPerStep);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addWalkArc(
		JNIEnv *, jclass, jlong objPtr, jfloat pAngle, jfloat pRadius,
		jint pNumSamplesPerStep) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->addWalkArc(pAngle, pRadius, pNumSamplesPerStep);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addWalkSideways(JNIEnv *,
		jclass, jlong objPtr, jfloat pDistance, jint pNumSamplesPerStep) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->addWalkSideways(pDistance, pNumSamplesPerStep);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addWalkStraight(JNIEnv *,
		jclass, jlong objPtr, jfloat pDistance, jint pNumSamplesPerStep) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->addWalkStraight(pDistance, pNumSamplesPerStep);
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeAngle(
		JNIEnv *, jclass, jlong objPtr, jint pJointId, jfloat pAngleChange) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	return jmotion->getProxy()->post.changeAngle(jointName, pAngleChange);
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeBodyAngles(
		JNIEnv *env, jclass, jlong objPtr, jfloatArray pAngleChanges) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	// copy array.
	jsize len = env->GetArrayLength(pAngleChanges);
	vector<jfloat> angleVector(len);
	env->GetFloatArrayRegion(pAngleChanges, 0, len, &angleVector[0]);
	return jmotion->getProxy()->post.changeBodyAngles(angleVector);
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeChainAngles(
		JNIEnv *env, jclass, jlong objPtr, jint pChainId,
		jfloatArray pAngleChanges) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	// copy array.
	jsize len = env->GetArrayLength(pAngleChanges);
	vector<jfloat> angleVector(len);
	env->GetFloatArrayRegion(pAngleChanges, 0, len, &angleVector[0]);
	return jmotion->getProxy()->post.changeChainAngles(jmotion->getChainName(
			pChainId), angleVector);
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeCom(
		JNIEnv *env, jclass, jlong objPtr, jfloat pXd, jfloat pYd, jfloat pZd) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->post.changeCom(pXd, pYd, pZd);
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changePosition(JNIEnv *env,
		jclass, jlong objPtr, jint pChainId, jint pSpace, jfloat xd, jfloat yd,
		jfloat zd, jfloat wxd, jfloat wyd, jfloat wzd, jint pAxisMask) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<float> position(6);
	position[0] = xd;
	position[1] = yd;
	position[2] = zd;
	position[3] = wxd;
	position[4] = wyd;
	position[5] = wzd;
	return jmotion->getProxy()->post.changePosition(jmotion->getChainName(
			pChainId), pSpace, position, pAxisMask);
}

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

	ALValue pJointNames = jmotion->getHeadlessJointNames();
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

	string jointName = jmotion->getJointName(pJointId);
	jfloat angle = jmotion->getProxy()->getAngle(jointName);

	return angle;
}

JNIEXPORT jfloat
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getAngleError(JNIEnv *,
		jclass, jlong objPtr, jint pJointId) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	jfloat angle = jmotion->getProxy()->getAngleError(jointName);

	return angle;
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBalanceMode(JNIEnv *,
		jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->getBalanceMode();
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyAngleErrors(
		JNIEnv *env, jclass, jlong objPtr, jfloatArray pAngles) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> angles(jmotion->getProxy()->getBodyAngleErrors());
	jsize len = angles.size();
	assert(len == env->GetArrayLength(pAngles));
	env->SetFloatArrayRegion(pAngles, 0, len, &angles[0]);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyAngles(
		JNIEnv *env, jclass, jlong objPtr, jfloatArray pAngles) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> angles(jmotion->getProxy()->getBodyAngles());
	jsize len = angles.size();
	assert(len == env->GetArrayLength(pAngles));
	env->SetFloatArrayRegion(pAngles, 0, len, &angles[0]);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyCommandAngles(
		JNIEnv *env, jclass, jlong objPtr, jfloatArray pAngles) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> angles(jmotion->getProxy()->getBodyAngles());
	jsize len = angles.size();
	assert(len == env->GetArrayLength(pAngles));
	env->SetFloatArrayRegion(pAngles, 0, len, &angles[0]);
}

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
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyLimits(JNIEnv *env,
		jclass, jlong objPtr, jfloatArray jMinAngle, jfloatArray jMaxAngle,
		jfloatArray jMaxChangePerCycle) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	ALValue ret = jmotion->getProxy()->getBodyLimits();

	jint jointNum = env->GetArrayLength(jMinAngle);
	assert(jointNum == env->GetArrayLength(jMaxAngle));
	assert(jointNum == env->GetArrayLength(jMaxChangePerCycle));

	// minAngle
	jfloat* minAngle =
			(jfloat*) env->GetPrimitiveArrayCritical(jMinAngle, NULL);
	for (int i = 0; i < jointNum; i++) {
		minAngle[i] = ret[0][i];
	}
	env->ReleasePrimitiveArrayCritical(jMinAngle, minAngle, 0);

	// maxAngle
	jfloat* maxAngle =
			(jfloat*) env->GetPrimitiveArrayCritical(jMaxAngle, NULL);
	for (int i = 0; i < jointNum; i++) {
		maxAngle[i] = ret[1][i];
	}
	env->ReleasePrimitiveArrayCritical(jMaxAngle, maxAngle, 0);

	// maxChangePerCycle
	jfloat* maxChangePerCycle = (jfloat*) env->GetPrimitiveArrayCritical(
			jMaxChangePerCycle, NULL);
	for (int i = 0; i < jointNum; i++) {
		maxChangePerCycle[i] = ret[0][i];
	}
	env->ReleasePrimitiveArrayCritical(jMaxChangePerCycle, maxChangePerCycle, 0);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyStiffnesses(
		JNIEnv *env, jclass, jlong objPtr, jfloatArray pStiffnesses) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> stiffnesses(jmotion->getProxy()->getBodyStiffnesses());
	jsize len = stiffnesses.size();
	assert(len == env->GetArrayLength(pStiffnesses));
	env->SetFloatArrayRegion(pStiffnesses, 0, len, &stiffnesses[0]);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainAngleErrors(
		JNIEnv *env, jclass, jlong objPtr, jint pChainId,
		jfloatArray pChainAngleErrors) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> errors(jmotion->getProxy()->getChainAngleErrors(
			jmotion->getChainName(pChainId)));
	jsize len = errors.size();
	assert(len == env->GetArrayLength(pChainAngleErrors));
	env->SetFloatArrayRegion(pChainAngleErrors, 0, len, &errors[0]);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainAngles(JNIEnv *env,
		jclass, jlong objPtr, jint pChainId, jfloatArray pChainAngles) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> angles(jmotion->getProxy()->getChainAngles(
			jmotion->getChainName(pChainId)));
	jsize len = angles.size();
	assert(len == env->GetArrayLength(pChainAngles));
	env->SetFloatArrayRegion(pChainAngles, 0, len, &angles[0]);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainCommandAngles(
		JNIEnv *env, jclass, jlong objPtr, jint pChainId,
		jfloatArray pChainCommandAngles) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> angles(jmotion->getProxy()->getChainCommandAngles(
			jmotion->getChainName(pChainId)));
	jsize len = angles.size();
	assert(len == env->GetArrayLength(pChainCommandAngles));
	env->SetFloatArrayRegion(pChainCommandAngles, 0, len, &angles[0]);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainLimits(JNIEnv *env,
		jclass, jlong objPtr, jint pChainId, jfloatArray jMinAngle,
		jfloatArray jMaxAngle, jfloatArray jMaxChangePerCycle) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	ALValue ret = jmotion->getProxy()->getChainLimits(jmotion->getChainName(
			pChainId));

	jint jointNum = env->GetArrayLength(jMinAngle);
	assert(jointNum == env->GetArrayLength(jMaxAngle));
	assert(jointNum == env->GetArrayLength(jMaxChangePerCycle));

	// minAngle
	jfloat* minAngle =
			(jfloat*) env->GetPrimitiveArrayCritical(jMinAngle, NULL);
	for (int i = 0; i < jointNum; i++) {
		minAngle[i] = ret[0][i];
	}
	env->ReleasePrimitiveArrayCritical(jMinAngle, minAngle, 0);

	// maxAngle
	jfloat* maxAngle =
			(jfloat*) env->GetPrimitiveArrayCritical(jMaxAngle, NULL);
	for (int i = 0; i < jointNum; i++) {
		maxAngle[i] = ret[1][i];
	}
	env->ReleasePrimitiveArrayCritical(jMaxAngle, maxAngle, 0);

	// maxChangePerCycle
	jfloat* maxChangePerCycle = (jfloat*) env->GetPrimitiveArrayCritical(
			jMaxChangePerCycle, NULL);
	for (int i = 0; i < jointNum; i++) {
		maxChangePerCycle[i] = ret[0][i];
	}
	env->ReleasePrimitiveArrayCritical(jMaxChangePerCycle, maxChangePerCycle, 0);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainStiffnesses(
		JNIEnv *env, jclass, jlong objPtr, jint pChainId,
		jfloatArray pStiffnesses) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> stiffnesses(jmotion->getProxy()->getChainStiffnesses(
			jmotion->getChainName(pChainId)));
	jsize len = stiffnesses.size();
	assert(len == env->GetArrayLength(pStiffnesses));
	env->SetFloatArrayRegion(pStiffnesses, 0, len, &stiffnesses[0]);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getCom(
		JNIEnv *env, jclass, jlong objPtr, jint pSpace, jfloatArray vector3f) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> com(jmotion->getProxy()->getCom(pSpace));
	jsize len = com.size();
	assert(len == env->GetArrayLength(vector3f));
	env->SetFloatArrayRegion(vector3f, 0, len, &com[0]);
}

JNIEXPORT jfloat
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getCommandAngle(JNIEnv *,
		jclass, jlong objPtr, jint pJointId) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	return jmotion->getProxy()->getCommandAngle(jointName);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getForwardTransform(
		JNIEnv *env, jclass, jlong objPtr, jint pChainId, jint pSpace,
		jfloatArray matrix4f) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> forwardTransform(jmotion->getProxy()->getForwardTransform(
			jmotion->getChainName(pChainId), pSpace));
	jsize len = forwardTransform.size();
	assert(len == env->GetArrayLength(matrix4f));
	env->SetFloatArrayRegion(matrix4f, 0, len, &forwardTransform[0]);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getJointLimits(JNIEnv *env,
		jclass, jlong objPtr, jint pJointId, jfloatArray pJointLimits) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	vector<jfloat> jointLimits(jmotion->getProxy()->getJointLimits(jointName));
	jsize len = jointLimits.size();
	assert(len == env->GetArrayLength(pJointLimits));
	env->SetFloatArrayRegion(pJointLimits, 0, len, &jointLimits[0]);
}

JNIEXPORT jfloat JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getJointStiffness(
		JNIEnv *, jclass, jlong objPtr, jint pJointId) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	return jmotion->getProxy()->getJointStiffness(jointName);
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getJointSpeedParams(
		JNIEnv *env, jclass, jlong objPtr, jint pJointId,
		jfloatArray pJointSpeedParams) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	vector<jfloat> jointLimits(jmotion->getProxy()->getJointSpeedParams(
			jointName));
	jsize len = jointLimits.size();
	assert(len == env->GetArrayLength(pJointSpeedParams));
	env->SetFloatArrayRegion(pJointSpeedParams, 0, len, &jointLimits[0]);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getPosition(
		JNIEnv *env, jclass, jlong objPtr, jint pChainId, jint pSpace,
		jfloatArray vector6f) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> position(jmotion->getProxy()->getPosition(
			jmotion->getChainName(pChainId), pSpace));
	jsize len = position.size();
	assert(len == env->GetArrayLength(vector6f));
	env->SetFloatArrayRegion(vector6f, 0, len, &position[0]);
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getRemainingFootStepCount(
		JNIEnv *, jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->getRemainingFootStepCount();
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getSensorPosition(
		JNIEnv *env, jclass, jlong objPtr, jstring pSensorName, jint pSpace,
		jfloatArray pSensorPosition) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> position(jmotion->getProxy()->getSensorPosition(toString(
			env, pSensorName), pSpace));
	jsize len = position.size();
	assert(len == env->GetArrayLength(pSensorPosition));
	env->SetFloatArrayRegion(pSensorPosition, 0, len, &position[0]);
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getSupportMode(JNIEnv *,
		jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->getSupportMode();
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getWalkArmsConfig(
		JNIEnv *env, jclass, jlong objPtr, jfloatArray pWalkArmsConfig) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> config(jmotion->getProxy()->getWalkArmsConfig());
	jsize len = config.size();
	assert(len == env->GetArrayLength(pWalkArmsConfig));
	env->SetFloatArrayRegion(pWalkArmsConfig, 0, len, &config[0]);
}

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getWalkArmsEnable(
		JNIEnv *, jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->getWalkArmsEnable();
}

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getWalkConfig(JNIEnv *env,
		jclass, jlong objPtr, jfloatArray pWalkConfig) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> config(jmotion->getProxy()->getWalkConfig());
	jsize len = config.size();
	assert(len == env->GetArrayLength(pWalkConfig));
	env->SetFloatArrayRegion(pWalkConfig, 0, len, &config[0]);
}

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
		JNIEnv *env, jclass, jlong objPtr, jintArray pJointIds,
		jfloatArray pTargetAngles, jfloat pDuration, jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jsize len = env->GetArrayLength(pJointIds);
	assert(len == env->GetArrayLength(pTargetAngles));

	ALValue pJointNames;
	pJointNames.arraySetSize(len);
	jint* jointIds = (jint*) env->GetPrimitiveArrayCritical(pJointIds, NULL);
	for (int i = 0; i < len; i++) {
		pJointNames[i] = jmotion->getJointName(jointIds[i]);
	}
	env->ReleasePrimitiveArrayCritical(pJointIds, jointIds, JNI_ABORT);

	// copy array.
	vector<jfloat> angleVector(len);
	env->GetFloatArrayRegion(pTargetAngles, 0, len, &angleVector[0]);
	assert(angleVector.size() == len);
	return jmotion->getProxy()->post.gotoAngles(pJointNames, angleVector,
			pDuration, pInterpolationType);
}

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

	ALValue pJointNames = jmotion->getHeadlessJointNames();
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

