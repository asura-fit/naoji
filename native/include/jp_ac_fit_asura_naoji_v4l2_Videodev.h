/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jp_ac_fit_asura_naoji_v4l2_Videodev */

#ifndef _Included_jp_ac_fit_asura_naoji_v4l2_Videodev
#define _Included_jp_ac_fit_asura_naoji_v4l2_Videodev
#ifdef __cplusplus
extern "C" {
#endif
/* Inaccessible static: _00024assertionsDisabled */
/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _createVideodev
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1createVideodev
  (JNIEnv *, jclass, jstring);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _dequeueBuffer
 * Signature: (ILjp/ac/fit/asura/naoji/v4l2/V4L2Buffer;)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1dequeueBuffer
  (JNIEnv *, jclass, jint, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _destroy
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1destroy
  (JNIEnv *, jclass, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _enqueueBuffer
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1enqueueBuffer
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _getControl
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getControl
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _getFormat
 * Signature: (ILjp/ac/fit/asura/naoji/v4l2/V4L2PixelFormat;)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getFormat
  (JNIEnv *, jclass, jint, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _getSelectedCamera
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getSelectedCamera
  (JNIEnv *, jclass, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _getSupportedFormats
 * Signature: (ILjava/util/Collection;)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1getSupportedFormats
  (JNIEnv *, jclass, jint, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _isSupportedControl
 * Signature: (II)Z
 */
JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1isSupportedControl
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _isSupportedFormat
 * Signature: (ILjp/ac/fit/asura/naoji/v4l2/V4L2PixelFormat;)Z
 */
JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1isSupportedFormat
  (JNIEnv *, jclass, jint, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _requestBuffers
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1requestBuffers
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _mmapBuffer
 * Signature: (II)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1mmapBuffer
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _munmapBuffer
 * Signature: (ILjava/nio/ByteBuffer;)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1munmapBuffer
  (JNIEnv *, jclass, jint, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _selectCamera
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1selectCamera
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _setControl
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1setControl
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _setFormat
 * Signature: (ILjp/ac/fit/asura/naoji/v4l2/V4L2PixelFormat;)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1setFormat
  (JNIEnv *, jclass, jint, jobject);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _setFPS
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1setFPS
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _start
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1start
  (JNIEnv *, jclass, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_v4l2_Videodev
 * Method:    _stop
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_v4l2_Videodev__1stop
  (JNIEnv *, jclass, jint);

#ifdef __cplusplus
}
#endif
#endif
