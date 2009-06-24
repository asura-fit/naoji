/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jp_ac_fit_asura_naoji_jal_JALMotion */

#ifndef _Included_jp_ac_fit_asura_naoji_jal_JALMotion
#define _Included_jp_ac_fit_asura_naoji_jal_JALMotion
#ifdef __cplusplus
extern "C" {
#endif
/* Inaccessible static: _00024assertionsDisabled */
/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _create
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1create
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _isDefinedJoint
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1isDefinedJoint
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _dispose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1dispose
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setTimeSeparate
 * Signature: (J[F[II)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setTimeSeparate
  (JNIEnv *, jclass, jlong, jfloatArray, jintArray, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _isRunning
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1isRunning
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _wait
 * Signature: (JII)Z
 */
JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1wait
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _addTurn
 * Signature: (JFI)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addTurn
  (JNIEnv *, jclass, jlong, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _addWalkArc
 * Signature: (JFFI)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addWalkArc
  (JNIEnv *, jclass, jlong, jfloat, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _addWalkSideways
 * Signature: (JFI)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addWalkSideways
  (JNIEnv *, jclass, jlong, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _addWalkStraight
 * Signature: (JFI)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1addWalkStraight
  (JNIEnv *, jclass, jlong, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _changeAngle
 * Signature: (JIF)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeAngle
  (JNIEnv *, jclass, jlong, jint, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _changeBodyAngles
 * Signature: (J[F)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeBodyAngles
  (JNIEnv *, jclass, jlong, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _changeChainAngles
 * Signature: (JI[F)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeChainAngles
  (JNIEnv *, jclass, jlong, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _changeCom
 * Signature: (JFFF)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changeCom
  (JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _changePosition
 * Signature: (JIIFFFFFFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1changePosition
  (JNIEnv *, jclass, jlong, jint, jint, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _clearFootsteps
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1clearFootsteps
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _doMove
 * Signature: (J[I[[F[[FI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1doMove
  (JNIEnv *, jclass, jlong, jintArray, jobjectArray, jobjectArray, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _doMoveAll
 * Signature: (J[[F[[FI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1doMoveAll
  (JNIEnv *, jclass, jlong, jobjectArray, jobjectArray, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getAngle
 * Signature: (JI)F
 */
JNIEXPORT jfloat JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getAngle
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getAngleError
 * Signature: (JI)F
 */
JNIEXPORT jfloat JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getAngleError
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getBalanceMode
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBalanceMode
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getBodyAngleErrors
 * Signature: (J[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyAngleErrors
  (JNIEnv *, jclass, jlong, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getBodyAngles
 * Signature: (J[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyAngles
  (JNIEnv *, jclass, jlong, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getBodyCommandAngles
 * Signature: (J[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyCommandAngles
  (JNIEnv *, jclass, jlong, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getBodyJointNames
 * Signature: (J)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyJointNames
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getBodyLimits
 * Signature: (J[F[F[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyLimits
  (JNIEnv *, jclass, jlong, jfloatArray, jfloatArray, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getBodyStiffnesses
 * Signature: (J[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getBodyStiffnesses
  (JNIEnv *, jclass, jlong, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getChainAngleErrors
 * Signature: (JI[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainAngleErrors
  (JNIEnv *, jclass, jlong, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getChainAngles
 * Signature: (JI[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainAngles
  (JNIEnv *, jclass, jlong, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getChainCommandAngles
 * Signature: (JI[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainCommandAngles
  (JNIEnv *, jclass, jlong, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getChainLimits
 * Signature: (JI[F[F[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainLimits
  (JNIEnv *, jclass, jlong, jint, jfloatArray, jfloatArray, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getChainStiffnesses
 * Signature: (JI[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getChainStiffnesses
  (JNIEnv *, jclass, jlong, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getCom
 * Signature: (JI[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getCom
  (JNIEnv *, jclass, jlong, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getCommandAngle
 * Signature: (JI)F
 */
JNIEXPORT jfloat JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getCommandAngle
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getForwardTransform
 * Signature: (JII[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getForwardTransform
  (JNIEnv *, jclass, jlong, jint, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getJointLimits
 * Signature: (JI[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getJointLimits
  (JNIEnv *, jclass, jlong, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getJointStiffness
 * Signature: (JI)F
 */
JNIEXPORT jfloat JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getJointStiffness
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getJointSpeedParams
 * Signature: (JI[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getJointSpeedParams
  (JNIEnv *, jclass, jlong, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getPosition
 * Signature: (JII[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getPosition
  (JNIEnv *, jclass, jlong, jint, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getRemainingFootStepCount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getRemainingFootStepCount
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getSensorPosition
 * Signature: (JLjava/lang/String;I[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getSensorPosition
  (JNIEnv *, jclass, jlong, jstring, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getSupportMode
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getSupportMode
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getWalkArmsConfig
 * Signature: (J[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getWalkArmsConfig
  (JNIEnv *, jclass, jlong, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getWalkArmsEnable
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getWalkArmsEnable
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _getWalkConfig
 * Signature: (J[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1getWalkConfig
  (JNIEnv *, jclass, jlong, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoAngle
 * Signature: (JIFFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoAngle
  (JNIEnv *, jclass, jlong, jint, jfloat, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoAngles
 * Signature: (J[I[FFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoAngles
  (JNIEnv *, jclass, jlong, jintArray, jfloatArray, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoAnglesWithSpeed
 * Signature: (J[I[FII)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoAnglesWithSpeed
  (JNIEnv *, jclass, jlong, jintArray, jfloatArray, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoAngleWithSpeed
 * Signature: (JIFII)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoAngleWithSpeed
  (JNIEnv *, jclass, jlong, jint, jfloat, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoBodyAngles
 * Signature: (J[FFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoBodyAngles
  (JNIEnv *, jclass, jlong, jfloatArray, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoBodyAnglesWithSpeed
 * Signature: (J[FII)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoBodyAnglesWithSpeed
  (JNIEnv *, jclass, jlong, jfloatArray, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoBodyStiffness
 * Signature: (JFFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoBodyStiffness
  (JNIEnv *, jclass, jlong, jfloat, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoBodyStiffnesses
 * Signature: (J[FFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoBodyStiffnesses
  (JNIEnv *, jclass, jlong, jfloatArray, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoChainAngles
 * Signature: (JI[FFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoChainAngles
  (JNIEnv *, jclass, jlong, jint, jfloatArray, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoChainAnglesWithSpeed
 * Signature: (JI[FII)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoChainAnglesWithSpeed
  (JNIEnv *, jclass, jlong, jint, jfloatArray, jint, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoChainStiffness
 * Signature: (JIFFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoChainStiffness
  (JNIEnv *, jclass, jlong, jint, jfloat, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoChainStiffnesses
 * Signature: (JI[FFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoChainStiffnesses
  (JNIEnv *, jclass, jlong, jint, jfloatArray, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoCom
 * Signature: (JFFFFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoCom
  (JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoJointStiffness
 * Signature: (JIFFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoJointStiffness
  (JNIEnv *, jclass, jlong, jint, jfloat, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoJointStiffnesses
 * Signature: (J[I[FFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoJointStiffnesses
  (JNIEnv *, jclass, jlong, jintArray, jfloatArray, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoPosition
 * Signature: (JIIFFFFFFIFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoPosition
  (JNIEnv *, jclass, jlong, jint, jint, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jint, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _gotoTorsoOrientation
 * Signature: (JFFFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1gotoTorsoOrientation
  (JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _killAll
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1killAll
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _killTask
 * Signature: (JI)Z
 */
JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1killTask
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _openHand
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1openHand
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setAngle
 * Signature: (JIF)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setAngle
  (JNIEnv *, jclass, jlong, jint, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setBalanceMode
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setBalanceMode
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setBodyAngles
 * Signature: (J[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setBodyAngles
  (JNIEnv *, jclass, jlong, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setBodyStiffness
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setBodyStiffness
  (JNIEnv *, jclass, jlong, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setChainAngles
 * Signature: (JI[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setChainAngles
  (JNIEnv *, jclass, jlong, jint, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setChainStiffness
 * Signature: (JIF)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setChainStiffness
  (JNIEnv *, jclass, jlong, jint, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setCom
 * Signature: (JFFF)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setCom
  (JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setJointStiffness
 * Signature: (JIF)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setJointStiffness
  (JNIEnv *, jclass, jlong, jint, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setJointStiffnesses
 * Signature: (J[I[F)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setJointStiffnesses
  (JNIEnv *, jclass, jlong, jintArray, jfloatArray);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setJointSpeedParams
 * Signature: (JIFFF)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setJointSpeedParams
  (JNIEnv *, jclass, jlong, jint, jfloat, jfloat, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setPosition
 * Signature: (JIIFFFFFFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setPosition
  (JNIEnv *, jclass, jlong, jint, jint, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setSupportMode
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setSupportMode
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setTorsoOrientation
 * Signature: (JFF)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setTorsoOrientation
  (JNIEnv *, jclass, jlong, jfloat, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setWalkArmsConfig
 * Signature: (JFFFF)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setWalkArmsConfig
  (JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setWalkArmsEnable
 * Signature: (JZ)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setWalkArmsEnable
  (JNIEnv *, jclass, jlong, jboolean);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setWalkConfig
 * Signature: (JFFFFFF)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setWalkConfig
  (JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _setWalkExtraConfig
 * Signature: (JFFFF)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1setWalkExtraConfig
  (JNIEnv *, jclass, jlong, jfloat, jfloat, jfloat, jfloat);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _stop
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1stop
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _turn
 * Signature: (JFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1turn
  (JNIEnv *, jclass, jlong, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _waitUntilWalkIsFinished
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1waitUntilWalkIsFinished
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _walk
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1walk
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _walkArc
 * Signature: (JFFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1walkArc
  (JNIEnv *, jclass, jlong, jfloat, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _walkIsActive
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1walkIsActive
  (JNIEnv *, jclass, jlong);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _walkStraight
 * Signature: (JFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1walkStraight
  (JNIEnv *, jclass, jlong, jfloat, jint);

/*
 * Class:     jp_ac_fit_asura_naoji_jal_JALMotion
 * Method:    _walkSideways
 * Signature: (JFI)I
 */
JNIEXPORT jint JNICALL Java_jp_ac_fit_asura_naoji_jal_JALMotion__1walkSideways
  (JNIEnv *, jclass, jlong, jfloat, jint);

#ifdef __cplusplus
}
#endif
#endif
