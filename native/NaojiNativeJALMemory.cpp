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
		// FIXME ???
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
		JNIEnv *env, jclass, jlong objPtr, jstring key) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (objPtr);
	assert(jmemory != NULL);

	string value = jmemory->getProxy()->getData(toString(env, key), 0);
	return env->NewStringUTF(value.c_str());
}

JNIEXPORT jstring
JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1getDataString__JI(
		JNIEnv *env, jclass, jlong objPtr, jint id) {
	JALMemory *jmemory = reinterpret_cast<JALMemory*> (objPtr);
	assert(jmemory != NULL);

	string value = jmemory->getProxy()->getData(jmemory->getKey(id), 0);
	return env->NewStringUTF(value.c_str());
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

	return reinterpret_cast<jlong> (query);
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1disposeQuery(
		JNIEnv *env, jclass, jlong queryPtr) {
	Query *query = reinterpret_cast<Query*> (queryPtr);
	assert(query != NULL);

	env->DeleteGlobalRef(query->bufferObj);
	query->bufferObj = NULL;

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

	query->bufferObj = env->NewGlobalRef(buffer);
	query->buffer.b = (jbyte*) ptr;
	query->bufferLength = length;
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1setQueryBufferString(
		JNIEnv *env, jclass, jlong queryPtr, jobjectArray jstrings) {
	Query *query = reinterpret_cast<Query*> (queryPtr);
	assert(query != NULL);

	query->bufferObj = env->NewGlobalRef(jstrings);
	query->buffer.s = (jobjectArray) query->bufferObj;
	query->bufferLength = -1;
}

JNIEXPORT
void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMemory__1updateFloatQuery(
		JNIEnv *, jclass, jlong queryPtr) {
	Query *query = reinterpret_cast<Query*> (queryPtr);
	assert(query != NULL);

	try {
		ALValue data = query->jmemory->getProxy()->getListData(query->names);
		int size = data.getSize();
		assert(query->names.getSize() == size);

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
		assert(query->names.getSize() == size);

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
		JNIEnv *env, jclass, jlong queryPtr) {
	Query *query = reinterpret_cast<Query*> (queryPtr);
	assert(query != NULL);

	try {
		ALValue data = query->jmemory->getProxy()->getListData(query->names);
		int size = data.getSize();
		assert(query->names.getSize() == size);

		for (int i = 0; i < size; i++) {
			env->SetObjectArrayElement(query->buffer.s, i, env->NewStringUTF(
					((string)data[i]).c_str()));
		}
	} catch (AL::ALError err) {
		std::cerr << err.toString() << std::endl;
		assert(false);
	}
}

#ifdef __cplusplus
}
#endif

