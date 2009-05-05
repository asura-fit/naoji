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

JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_NaojiModule__1createJALBroker(
		JNIEnv *, jclass, jlong naojiPtr) {
	NaojiModule *naoji = reinterpret_cast<NaojiModule*> (naojiPtr);
	assert(naoji != NULL);
	AL::ALPtr<AL::ALBroker> broker = naoji->getParentBroker();
	JALBroker *jbroker = new JALBroker(broker);
	return reinterpret_cast<jlong> (jbroker);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALBroker__1dispose(
		JNIEnv *, jclass, jlong objPtr) {
	JALBroker *jbroker = reinterpret_cast<JALBroker*> (objPtr);
	assert(jbroker != NULL);

	delete jbroker;
}

JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1create(
		JNIEnv *, jclass, jlong jbrokerPtr) {
	JALBroker *jbroker = reinterpret_cast<JALBroker*> (jbrokerPtr);
	assert(jbroker != NULL);
	JALMemory *jmemory = new JALMemory(jbroker);
	return reinterpret_cast<jlong> (jmemory);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1dispose(
		JNIEnv *, jclass, jlong objPtr) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (objPtr);
	assert(jmemory != NULL);

	delete jmemory;
}

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

JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JALProxy__1create(
		JNIEnv *, jclass, jlong) {
	// not implemented.
	assert(false);
	return 0;
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALProxy__1dispose(
		JNIEnv *, jclass, jlong objPtr) {
	// not implemented.
	assert(false);
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1defineKey(
		JNIEnv *env, jclass, jlong objPtr, jstring jstr) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (objPtr);
	assert(jmemory != NULL);

	return jmemory->defineKey(toString(env, jstr));
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1removeKey(
		JNIEnv *, jclass, jlong objPtr, jint id) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (objPtr);
	assert(jmemory != NULL);

	jmemory->removeKey(id);
}

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1wait(
		JNIEnv *, jclass, jlong, jint, jint);

JNIEXPORT jboolean
		JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1isRunning(JNIEnv *,
				jclass, jlong, jint);

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1waitNextCycle(
		JNIEnv *, jclass, jlong objPtr) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (objPtr);
	assert(jmemory != NULL);

	int value = jmemory->getProxy()->getData(string("DCM/Time"), 0);
	if (value == jmemory->getLastTime()) {
		value = jmemory->getProxy()->getDataOnChange(string("DCM/Time"), 0);
		jmemory->setLastTime(value);
	}
}

JNIEXPORT jint
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1getDataInt__JLjava_lang_String_2(
		JNIEnv *env, jclass, jlong objPtr, jstring key) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (objPtr);
	assert(jmemory != NULL);

	ALValue value = jmemory->getProxy()->getData(toString(env, key), 0);
	return value;
}

JNIEXPORT
jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1getDataInt__JI(
		JNIEnv *, jclass, jlong objPtr, jint id) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (objPtr);
	assert(jmemory != NULL);

	ALValue value = jmemory->getProxy()->getData(jmemory->getKey(id), 0);
	return value;
}

JNIEXPORT jfloat
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1getDataFloat__JLjava_lang_String_2(
		JNIEnv *env, jclass, jlong objPtr, jstring key) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (objPtr);
	assert(jmemory != NULL);

	ALValue value = jmemory->getProxy()->getData(toString(env, key), 0);
	return value;
}

JNIEXPORT
jfloat JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1getDataFloat__JI(
		JNIEnv *, jclass, jlong objPtr, jint id) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (objPtr);
	assert(jmemory != NULL);

	ALValue value = jmemory->getProxy()->getData(jmemory->getKey(id), 0);
	return value;
}

JNIEXPORT jstring
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1getDataString__JLjava_lang_String_2(
		JNIEnv *, jclass, jlong, jstring) {
	assert(false);
	return NULL;
}

JNIEXPORT jstring
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1getDataString__JI(
		JNIEnv *env, jclass, jlong, jint) {
	assert(false);
	return NULL;
}

JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1createQuery(
		JNIEnv *env, jclass, jlong jmemoryPtr, jobjectArray jstrings) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (jmemoryPtr);
	assert(jmemory != NULL);
	Query *query = new Query(jmemory);
	jsize size = env->GetArrayLength(jstrings);
	ALValue names;
	names.arraySetSize(size);
	for (int i = 0; i < size; i++) {
		jstring jstr = static_cast<jstring> (env->GetObjectArrayElement(
				jstrings, i));
		jassert(env, jstr != NULL);
		names[i] = toString(env, jstr);
		env->DeleteLocalRef(jstr);
	}
	query->names = names;
	query->size = size;

	return reinterpret_cast<jlong> (query);
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1disposeQuery(JNIEnv *,
		jclass, jlong queryPtr) {
	Query *query = reinterpret_cast<Query*> (queryPtr);
	assert(query != NULL);

	delete query;
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1setQueryBuffer(
		JNIEnv *env, jclass, jlong queryPtr, jobject buffer) {
	Query *query = reinterpret_cast<Query*> (queryPtr);
	assert(query != NULL);

	void *ptr = env->GetDirectBufferAddress(buffer);
	jassert(env, ptr != NULL);
	jlong length = env->GetDirectBufferCapacity(buffer);
	jassert(env, length != -1);

	query->buffer.b = (jbyte*) ptr;
	query->bufferLength = length;
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1setQueryBufferString(
		JNIEnv *, jclass, jlong, jobjectArray jstrings) {
	// TODO implement
	assert(false);
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1updateFloatQuery(
		JNIEnv *, jclass, jlong queryPtr) {
	Query *query = reinterpret_cast<Query*> (queryPtr);
	assert(query != NULL);

	try {
		ALValue data = query->jmemory->getProxy()->getListData(query->names);
		int size = data.getSize();
		assert(query->size == size);

		jfloat* buf = reinterpret_cast<jfloat*> (query->buffer.b);
		for (int i = 0; i < size; i++) {
			buf[i] = data[i];
		}
	} catch (AL::ALError err) {
		std::cerr << err.toString() << std::endl;
		assert(false);
	}

}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1updateIntQuery(
		JNIEnv *, jclass, jlong queryPtr) {
	Query *query = reinterpret_cast<Query*> (queryPtr);
	assert(query != NULL);

	try {
		ALValue data = query->jmemory->getProxy()->getListData(query->names);
		int size = data.getSize();
		assert(query->size == size);

		jint* buf = reinterpret_cast<jint*> (query->buffer.b);
		for (int i = 0; i < size; i++) {
			buf[i] = data[i];
		}
	} catch (AL::ALError err) {
		std::cerr << err.toString() << std::endl;
		assert(false);
	}
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1updateStringQuery(
		JNIEnv *, jclass, jlong queryPtr) {
	// TODO implement
	assert(false);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1defineJoint(
		JNIEnv *env, jclass, jlong objPtr, jint jointId, jstring jointName) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->defineJoint(jointId, toString(env, jointName));
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1removeJoint(
		JNIEnv *env, jclass, jlong objPtr, jint jointId) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->removeJoint(jointId);
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

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1clearFootsteps(
		JNIEnv *, jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->getProxy()->clearFootsteps();
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1doMove(
		JNIEnv *env, jclass, jlong objPtr, jintArray, jfloatArray, jfloatArray,
		jint) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	// TODO implement.
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1doMoveAll(
		JNIEnv *env, jclass, jlong objPtr, jfloatArray, jfloatArray, jint) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	// TODO implement.
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

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyAngles(
		JNIEnv *env, jclass, jlong objPtr, jfloatArray pAngles) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	vector<jfloat> angles(jmotion->getProxy()->getBodyAngles());
	jsize len = angles.size();
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

JNIEXPORT jfloat JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getJointStiffness(
		JNIEnv *, jclass, jlong objPtr, jint pJointId) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	jfloat stiffness = jmotion->getProxy()->getJointStiffness(jointName);
	return stiffness;
}

JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getWalkArmsEnable(
		JNIEnv *, jclass, jlong objPtr) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->getWalkArmsEnable();
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

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoBodyStiffness(
		JNIEnv *, jclass, jlong objPtr, jfloat pStiffness, jfloat pDuration,
		jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	return jmotion->getProxy()->post.gotoBodyStiffness(pStiffness, pDuration,
			pInterpolationType);
}

JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoJointStiffness(
		JNIEnv *, jclass, jlong objPtr, jint pJointId, jfloat pStiffness,
		jfloat pDuration, jint pInterpolationType) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	return jmotion->getProxy()->post.gotoJointStiffness(jointName, pStiffness,
			pDuration, pInterpolationType);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setBodyStiffness(
		JNIEnv *, jclass, jlong objPtr, jfloat pStiffness) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->getProxy()->setBodyStiffness(pStiffness);
}

JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setJointStiffness(
		JNIEnv *, jclass, jlong objPtr, jint pJointId, jfloat pStiffness) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	string jointName = jmotion->getJointName(pJointId);
	jmotion->getProxy()->setJointStiffness(jointName, pStiffness);
}

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

JNIEXPORT void
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setWalkArmsEnable(JNIEnv *,
		jclass, jlong objPtr, jboolean pArmsEnable) {
	JALMotion *jmotion = reinterpret_cast<JALMotion*> (objPtr);
	assert(jmotion != NULL);

	jmotion->getProxy()->setWalkArmsEnable(pArmsEnable);
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

#ifdef __cplusplus
}
#endif

