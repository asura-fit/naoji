#ifndef jni_utils_H
#define jni_utils_H

#include <boost/current_function.hpp>

#include <jni.h>       /* where everything is defined */
#include <string>
#include <iostream>
#include <sstream>

inline void jassertion_failed(JNIEnv *env, char const * expr, char const * function,
		char const * file, long line) {
	env->ExceptionDescribe();
	std::ostringstream stream;
	stream << file << ":" << line << ": " << function << ": Assertion `"
			<< expr << "' failed.";
	std::string result = stream.str();
	env->FatalError(result.c_str());
}

#ifndef NDEBUG
#define jassert( env, expr) ((expr)? ((void)0) : jassertion_failed(env, #expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#else
#define jassert( env, expr)
#endif

inline std::string toString(JNIEnv* env, jstring jStr) {
	const char *chars = env->GetStringUTFChars(jStr, NULL);
	std::string str(chars);
	env->ReleaseStringUTFChars(jStr, chars);
	return str;
}

#endif // jni_utils_H
