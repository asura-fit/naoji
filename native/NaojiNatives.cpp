#include <iostream>
#include <cassert>

#include "alproxy.h"
#include "alptr.h"
#include "albroker.h"

#include "alerror.h"

#include <jni.h>       /* where everything is defined */

// include JNI Headers
#include "jp_ac_fit_asura_naoji_NaojiModule.h"

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

#ifdef __cplusplus
}
#endif

