#include "HelloWorldJNI.h"
JNIEXPORT jstring JNICALL 
             Java_HelloWorldJNI_sayHelloWorld (JNIEnv *env, 
                                               jobject obj ) {
    return env->NewStringUTF("Hello World");
}
