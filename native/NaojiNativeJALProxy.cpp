#include <iostream>
#include <cassert>

#include "alproxy.h"
#include "alptr.h"
#include "albroker.h"

#include "alerror.h"

#include <jni.h>       /* where everything is defined */

// include JNI Headers
#include "jp_ac_fit_asura_naoji_NaojiModule.h"
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

#ifdef __cplusplus
}
#endif

