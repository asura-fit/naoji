/*
 * 作成日: 2009/03/22
 */
package jp.ac.fit.asura.naoji.jal;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class JALMotion extends JALModule {
	private int jointNum;

	protected JALMotion(JALBroker broker) {
		objPtr = _create(broker.getPtr());
		String[] jointNames = _getBodyJointNames(objPtr);
		assert jointNames != null;
		jointNum = jointNames.length;
	}

	public void dispose() {
		_dispose(objPtr);
	}

	public boolean isDefinedJoint(int id) {
		return _isDefinedJoint(objPtr, id);
	}

	/**
	 * {@link JDCM#setTimeSeparate(int, jp.ac.fit.asura.naoji.jal.JDCM.MergeType, float[], int[])}
	 * と 互換性のあるvalueMatrix, timeで関節の時系列指令を実行します.
	 *
	 * @param valueMatrix
	 * @param time
	 * @param pInterpolationType
	 * @return
	 */
	public int setTimeSeparate(float[] valueMatrix, int[] time,
			int pInterpolationType) {
		return _setTimeSeparate(objPtr, valueMatrix, time, pInterpolationType);
	}

	public boolean isRunning(int taskId) {
		return _isRunning(objPtr, taskId);
	}

	public void wait(int taskId, int timeout) {
		_wait(objPtr, taskId, timeout);
	}

	// ALMotion methods. see ALMotion Reference in Blue doc.

	public void addTurn(float pAngle, int pNumSamplesPerStep) {
		_addTurn(objPtr, pAngle, pNumSamplesPerStep);
	}

	public void addWalkArc(float pAngle, float pRadius, int pNumSamplesPerStep) {
		_addWalkArc(objPtr, pAngle, pRadius, pNumSamplesPerStep);
	}

	public void addWalkSideways(float pDistance, int pNumSamplesPerStep) {
		_addWalkSideways(objPtr, pDistance, pNumSamplesPerStep);
	}

	public void addWalkStraight(float pDistance, int pNumSamplesPerStep) {
		_addWalkStraight(objPtr, pDistance, pNumSamplesPerStep);
	}

	public int changeAngle(int pJointNameId, float pAngleChange) {
		return _changeAngle(objPtr, pJointNameId, pAngleChange);
	}

	public int changeBodyAngles(float[] pAngleChanges) {
		return _changeBodyAngles(objPtr, pAngleChanges);
	}

	public int changeChainAngles(int pChainNameId, float[] pAngleChanges) {
		return _changeChainAngles(objPtr, pChainNameId, pAngleChanges);
	}

	public int changeCom(float pXd, float pYd, float pZd) {
		return _changeCom(objPtr, pXd, pYd, pZd);
	}

	public int changePosition(int pChainNameId, int pSpace, float xd, float yd,
			float zd, float wxd, float wyd, float wzd, int pAxisMask) {
		return _changePosition(objPtr, pChainNameId, pSpace, xd, yd, zd, wxd,
				wyd, wzd, pAxisMask);
	}

	public void clearFootsteps() {
		_clearFootsteps(objPtr);
	}

	/**
	 * 複数の関節に対し、実行時間を指定して関節の時系列データを与え実行します.
	 *
	 * pAnglesとpDurationsはそれぞれの関節に対する時系列データを2次元配列で示します.
	 *
	 * 例えば次のデータは、pJointIdsで示す1番目の関節を0度, 90度, 0度と1秒ごとに遷移させます.
	 *
	 * <pre>
	 * pAngles[0][0] = 0.0f
	 * pAngles[0][1] = 1.57f
	 * pAngles[0][2] = 0.0f
	 * pDurations[0][0] = 1.0f
	 * pDurations[0][1] = 2.0f
	 * pDurations[0][2] = 3.0f
	 * </pre>
	 *
	 * @param pJointIds
	 * @param pAngles
	 * @param pDurations
	 * @param pInterpolationType
	 * @return taskId
	 */
	public int doMove(int[] pJointIds, float[][] pAngles, float[][] pDurations,
			int pInterpolationType) {
		assert pJointIds.length <= jointNum;
		for (int id : pJointIds)
			assert isDefinedJoint(id);
		return _doMove(objPtr, pJointIds, pAngles, pDurations,
				pInterpolationType);
	}

	public float getAngle(int pJointId) {
		assert isDefinedJoint(pJointId);
		return _getAngle(objPtr, pJointId);
	}

	public float getAngleError(int pJointId) {
		assert isDefinedJoint(pJointId);
		return _getAngleError(objPtr, pJointId);
	}

	public int getBalanceMode() {
		return _getBalanceMode(objPtr);
	}

	public void getBodyAngleErrors(float[] pAngles) {
		assert pAngles.length == jointNum;
		_getBodyAngleErrors(objPtr, pAngles);
	}

	public void getBodyAngles(float[] pAngles) {
		assert pAngles.length == jointNum;
		_getBodyAngles(objPtr, pAngles);
	}

	public void getBodyCommandAngles(float[] pAngles) {
		assert pAngles.length == jointNum;
		_getBodyCommandAngles(objPtr, pAngles);
	}

	public String[] getBodyJointNames() {
		return _getBodyJointNames(objPtr);
	}

	public void getBodyLimits(float[] matrixNx3) {
		assert matrixNx3.length == jointNum * 3;
		_getBodyLimits(objPtr, matrixNx3);
	}

	public void getBodyStiffnesses(float[] pStiffnesses) {
		assert pStiffnesses.length == jointNum;
		_getBodyStiffnesses(objPtr, pStiffnesses);
	}

	public void getChainAngleErrors(int pChainNameId, float[] pAngles) {
		_getChainAngleErrors(objPtr, pChainNameId, pAngles);
	}

	public void getChainAngles(int pChainNameId, float[] pAngles) {
		_getChainAngles(objPtr, pChainNameId, pAngles);
	}

	public void getChainCommandAngles(int pChainNameId, float[] pAngles) {
		_getChainCommandAngles(objPtr, pChainNameId, pAngles);
	}

	public void getChainLimits(int pChainNameId, float[] matrixNx3) {
		assert matrixNx3.length % 3 == 0;
		_getChainLimits(objPtr, pChainNameId, matrixNx3);
	}

	public void getChainStiffnesses(int pChainNameId, float[] pStiffnesses) {
		_getChainStiffnesses(objPtr, pChainNameId, pStiffnesses);
	}

	public void getCom(int pSpace, float[] vector3f) {
		_getCom(objPtr, pSpace, vector3f);
	}

	public float getCommandAngle(int pJointId) {
		assert isDefinedJoint(pJointId);
		return _getCommandAngle(objPtr, pJointId);
	}

	public void getForwardTransform(int pChainNameId, int pSpace,
			float[] matrix4f) {
		assert matrix4f.length == 16;
		_getForwardTransform(objPtr, pChainNameId, pSpace, matrix4f);
	}

	public void getJointLimits(int pJointId, float[] vector3f) {
		assert vector3f.length == 3;
		_getJointLimits(objPtr, pJointId, vector3f);
	}

	public float getJointStiffness(int pJointId) {
		assert isDefinedJoint(pJointId);
		return _getJointStiffness(objPtr, pJointId);
	}

	public void getJointSpeedParams(int pJointId, float[] vector3f) {
		assert vector3f.length == 3;
		_getJointSpeedParams(objPtr, pJointId, vector3f);
	}

	public void getPosition(int pChainNameId, int pSpace, float[] vector6f) {
		assert vector6f.length == 6;
		_getPosition(objPtr, pChainNameId, pSpace, vector6f);
	}

	public int getRemainingFootStepCount() {
		return _getRemainingFootStepCount(objPtr);
	}

	public void getSensorPosition(String pSensorName, int pSpace,
			float[] vector6f) {
		assert vector6f.length == 6;
		_getSensorPosition(objPtr, pSensorName, pSpace, vector6f);
	}

	public int getSupportMode() {
		return _getSupportMode(objPtr);
	}

	public void getWalkArmsConfig(float[] vector4f) {
		assert vector4f.length == 4;
		_getWalkArmsConfig(objPtr, vector4f);
	}

	public boolean getWalkArmsEnable() {
		return _getWalkArmsEnable(objPtr);
	}

	public void getWalkConfig(float[] vector6f) {
		assert vector6f.length == 6;
		_getWalkConfig(objPtr, vector6f);
	}

	public int gotoAngle(int pJointId, float pAngle, float pDuration,
			int pInterpolationType) {
		assert isDefinedJoint(pJointId);
		return _gotoAngle(objPtr, pJointId, pAngle, pDuration,
				pInterpolationType);
	}

	public int gotoAngles(int[] pJointIds, float[] pAngles, float pDuration,
			int pInterpolationType) {
		assert pJointIds.length == pAngles.length;
		return _gotoAngles(objPtr, pJointIds, pAngles, pDuration,
				pInterpolationType);
	}

	public int gotoAnglesWithSpeed(int[] pJointIds, float[] pAngles,
			int pSpeedPercent, int pInterpolationType) {
		assert pJointIds.length == pAngles.length;
		return _gotoAnglesWithSpeed(objPtr, pJointIds, pAngles, pSpeedPercent,
				pInterpolationType);
	}

	public int gotoAngleWithSpeed(int pJointId, float pAngle,
			int pSpeedPercent, int pInterpolationType) {
		assert isDefinedJoint(pJointId);
		return _gotoAngleWithSpeed(objPtr, pJointId, pAngle, pSpeedPercent,
				pInterpolationType);
	}

	public int gotoBodyAngles(float[] pAngles, float pDuration,
			int pInterpolationType) {
		assert pAngles.length == jointNum;
		return _gotoBodyAngles(objPtr, pAngles, pDuration, pInterpolationType);
	}

	public int gotoBodyAnglesWithSpeed(float[] pAngles, int pSpeedPercent,
			int pInterpolationType) {
		assert pAngles.length == jointNum;
		return _gotoBodyAnglesWithSpeed(objPtr, pAngles, pSpeedPercent,
				pInterpolationType);
	}

	public int gotoBodyStiffness(float pStiffness, float pDuration,
			int pInterpolationType) {
		return _gotoBodyStiffness(objPtr, pStiffness, pDuration,
				pInterpolationType);
	}

	public int gotoBodyStiffnesses(float[] pStiffnesses, float pDuration,
			int pInterpolationType) {
		return _gotoBodyStiffnesses(objPtr, pStiffnesses, pDuration,
				pInterpolationType);
	}

	public int gotoChainAngles(int pChainNameId, float[] pAngles,
			float pDuration, int pInterpolationType) {
		return _gotoChainAngles(objPtr, pChainNameId, pAngles, pDuration,
				pInterpolationType);
	}

	public int gotoChainAnglesWithSpeed(int pChainNameId, float[] pAngles,
			int pSpeedPercent, int pInterpolationType) {
		return _gotoChainAnglesWithSpeed(objPtr, pChainNameId, pAngles,
				pSpeedPercent, pInterpolationType);
	}

	public int gotoChainStiffness(int pChainNameId, float pStiffness,
			float pDuration, int pInterpolationType) {
		return _gotoChainStiffness(objPtr, pChainNameId, pStiffness, pDuration,
				pInterpolationType);
	}

	public int gotoChainStiffnesses(int pChainNameId, float[] pStiffnesses,
			float pDuration, int pInterpolationType) {
		return _gotoChainStiffnesses(objPtr, pChainNameId, pStiffnesses,
				pDuration, pInterpolationType);
	}

	public int gotoCom(float pX, float pY, float pZ, float pDuration,
			int pInterpolationType) {
		return _gotoCom(objPtr, pX, pY, pZ, pDuration, pInterpolationType);
	}

	public int gotoJointStiffness(int pJointId, float pStiffness,
			float pDuration, int pInterpolationType) {
		assert isDefinedJoint(pJointId);
		return _gotoJointStiffness(objPtr, pJointId, pStiffness, pDuration,
				pInterpolationType);
	}

	public int gotoJointStiffnesses(int[] pJointIds, float[] pStiffnesses,
			float pDuration, int pInterpolationType) {
		return _gotoJointStiffnesses(objPtr, pJointIds, pStiffnesses,
				pDuration, pInterpolationType);
	}

	public int gotoPosition(int pChainNameId, int pSpace, float x, float y,
			float z, float wx, float wy, float wz, int pAxisMask,
			float pDuration, int pInterpolationType) {
		return _gotoPosition(objPtr, pChainNameId, pSpace, x, y, z, wx, wy, wz,
				pAxisMask, pDuration, pInterpolationType);
	}

	public int gotoTorsoOrientation(float pX, float pY, float pDuration,
			int pInterpolationType) {
		return _gotoTorsoOrientation(objPtr, pX, pY, pDuration,
				pInterpolationType);
	}

	public void killAll() {
		_killAll(objPtr);
	}

	public boolean killTask(int pTaskID) {
		return _killTask(objPtr, pTaskID);
	}

	public int openHand(String pHandName) {
		return _openHand(objPtr, pHandName);
	}

	public void setAngle(int pJointId, float pAngle) {
		_setAngle(objPtr, pJointId, pAngle);
	}

	public void setBalanceMode(int pBalanceMode) {
		_setBalanceMode(objPtr, pBalanceMode);
	}

	public void setBodyAngles(float[] pAngles) {
		_setBodyAngles(objPtr, pAngles);
	}

	public void setBodyStiffness(float pStiffness) {
		_setBodyStiffness(objPtr, pStiffness);
	}

	public void setChainAngles(int pChainNameId, float[] pAngles) {
		_setChainAngles(objPtr, pChainNameId, pAngles);
	}

	public void setChainStiffness(int pChainNameId, float pStiffness) {
		_setChainStiffness(objPtr, pChainNameId, pStiffness);
	}

	public void setCom(float pX, float pY, float pZ) {
		_setCom(objPtr, pX, pY, pZ);
	}

	public void setJointStiffness(int pJointId, float pStiffness) {
		_setJointStiffness(objPtr, pJointId, pStiffness);
	}

	public void setJointStiffnesses(int[] pJointIds, float[] pStiffnesses) {
		_setJointStiffnesses(objPtr, pJointIds, pStiffnesses);
	}

	public void setJointSpeedParams(int pJointId, float pUserMaxSpeed,
			float pUserMaxAcceleration, float pUserMaxDecleration) {
		_setJointSpeedParams(objPtr, pJointId, pUserMaxSpeed,
				pUserMaxAcceleration, pUserMaxDecleration);
	}

	public int setPosition(int pChainNameId, int pSpace, float x, float y,
			float z, float wx, float wy, float wz, int pAxisMask) {
		return _setPosition(objPtr, pChainNameId, pSpace, x, y, z, wx, wy, wz,
				pAxisMask);
	}

	public void setSupportMode(int pSupportMode) {
		_setSupportMode(objPtr, pSupportMode);
	}

	public void setTorsoOrientation(float pTetaX, float pTetaY) {
		_setTorsoOrientation(objPtr, pTetaX, pTetaY);
	}

	public void setWalkArmsConfig(float pShoulderMedian,
			float pShoulderAmplitude, float pElbowMedian, float pElbowAmplitude) {
		_setWalkArmsConfig(objPtr, pShoulderMedian, pShoulderAmplitude,
				pElbowMedian, pElbowAmplitude);
	}

	public void setWalkArmsEnable(boolean pArmsEnable) {
		_setWalkArmsEnable(objPtr, pArmsEnable);
	}

	public void setWalkConfig(float pMaxStepLength, float pMaxStepHeight,
			float pMaxStepSide, float pMaxStepTurn, float pHipHeight,
			float pTorsoYOrientation) {
		_setWalkConfig(objPtr, pMaxStepLength, pMaxStepHeight, pMaxStepSide,
				pMaxStepTurn, pHipHeight, pTorsoYOrientation);
	}

	public void setWalkTrapezoidConfig(float pLHipRollBacklashCompensator,
			float pRHipRollBacklashCompensator) {
		_setWalkTrapezoidConfig(objPtr, pLHipRollBacklashCompensator,
				pRHipRollBacklashCompensator);
	}

	public void stop(int pBrokerTaskID) {
		_stop(objPtr, pBrokerTaskID);
	}

	public int turn(float pAngle, int pNumSamplesPerStep) {
		return _turn(objPtr, pAngle, pNumSamplesPerStep);
	}

	public void waitUntilWalkIsFinished() {
		_waitUntilWalkIsFinished(objPtr);
	}

	public int walk() {
		return _walk(objPtr);
	}

	public int walkArc(float pAngle, float pRadius, int pNumSamplesPerStep) {
		return _walkArc(objPtr, pAngle, pRadius, pNumSamplesPerStep);
	}

	public boolean walkIsActive() {
		return _walkIsActive(objPtr);
	}

	public int walkSideways(float pDistance, int pNumSamplesPerStep) {
		return _walkSideways(objPtr, pDistance, pNumSamplesPerStep);
	}

	public int walkStraight(float pDistance, int pNumSamplesPerStep) {
		return _walkStraight(objPtr, pDistance, pNumSamplesPerStep);
	}

	native static private long _create(long jalBrokerPtr);

	// Joint definitions.
	native static private boolean _isDefinedJoint(long objPtr, int id);

	native static private void _dispose(long objPtr);

	private int _getChainId(String chainName) {
		throw new UnsupportedOperationException();
	}

	private void _defineChain(int id, String chainName) {
		throw new UnsupportedOperationException();
	}

	private void _removeChain(int id) {
		throw new UnsupportedOperationException();
	}

	native static private int _setTimeSeparate(long objPtr,
			float[] valueMatrix, int[] time, int pInterpolationType);

	// ALModule methods.
	native static protected boolean _isRunning(long objPtr, int taskId);

	native static protected boolean _wait(long objPtr, int taskId, int timeout);

	// ALMotion methods.
	native static private void _addTurn(long objPtr, float pAngle,
			int pNumSamplesPerStep);

	native static private void _addWalkArc(long objPtr, float pAngle,
			float pRadius, int pNumSamplesPerStep);

	native static private void _addWalkSideways(long objPtr, float pDistance,
			int pNumSamplesPerStep);

	native static private void _addWalkStraight(long objPtr, float pDistance,
			int pNumSamplesPerStep);

	native static private int _changeAngle(long objPtr, int pJointNameId,
			float pAngleChange);

	native static private int _changeBodyAngles(long objPtr,
			float[] pAngleChanges);

	native static private int _changeChainAngles(long objPtr, int pChainNameId,
			float[] pAngleChanges);

	native static private int _changeCom(long objPtr, float pXd, float pYd,
			float pZd);

	native static private int _changePosition(long objPtr, int pChainNameId,
			int pSpace, float xd, float yd, float zd, float wxd, float wyd,
			float wzd, int pAxisMask);

	native static private void _clearFootsteps(long objPtr);

	native static private int _doMove(long objPtr, int[] pJointIds,
			float[][] pAngles, float[][] pDurations, int pInterpolationType);

	native static private float _getAngle(long objPtr, int pJointId);

	native static private float _getAngleError(long objPtr, int pJointId);

	native static private int _getBalanceMode(long objPtr);

	native static private void _getBodyAngleErrors(long objPtr, float[] pAngles);

	native static private void _getBodyAngles(long objPtr, float[] pAngles);

	native static private void _getBodyCommandAngles(long objPtr,
			float[] pAngles);

	native static private String[] _getBodyJointNames(long objPtr);

	native static private void _getBodyLimits(long objPtr, float[] matrixNx3f);

	native static private void _getBodyStiffnesses(long objPtr,
			float[] pStiffnesses);

	native static private void _getChainAngleErrors(long objPtr,
			int pChainNameId, float[] pAngles);

	native static private void _getChainAngles(long objPtr, int pChainNameId,
			float[] pAngles);

	native static private void _getChainCommandAngles(long objPtr,
			int pChainNameId, float[] pAngles);

	native static private void _getChainLimits(long objPtr, int pChainNameId,
			float[] matrixNx3f);

	native static private void _getChainStiffnesses(long objPtr,
			int pChainNameId, float[] pStiffnesses);

	native static private void _getCom(long objPtr, int pSpace, float[] vector3f);

	native static private float _getCommandAngle(long objPtr, int pJointId);

	native static private void _getForwardTransform(long objPtr,
			int pChainNameId, int pSpace, float[] matrix4f);

	native static private void _getJointLimits(long objPtr, int pJointId,
			float[] vector3f);

	native static private float _getJointStiffness(long objPtr, int pJointId);

	native static private void _getJointSpeedParams(long objPtr, int pJointId,
			float[] vector3f);

	native static private void _getPosition(long objPtr, int pChainNameId,
			int pSpace, float[] vector6f);

	native static private int _getRemainingFootStepCount(long objPtr);

	native static private void _getSensorPosition(long objPtr,
			String pSensorName, int pSpace, float[] vector6f);

	native static private int _getSupportMode(long objPtr);

	native static private void _getWalkArmsConfig(long objPtr, float[] vector4f);

	native static private boolean _getWalkArmsEnable(long objPtr);

	native static private void _getWalkConfig(long objPtr, float[] vector6f);

	native static private int _gotoAngle(long objPtr, int pJointId,
			float pAngle, float pDuration, int pInterpolationType);

	native static private int _gotoAngles(long objPtr, int[] pJointIds,
			float[] pAngles, float pDuration, int pInterpolationType);

	native static private int _gotoAnglesWithSpeed(long objPtr,
			int[] pJointIds, float[] pAngles, int pSpeedPercent,
			int pInterpolationType);

	native static private int _gotoAngleWithSpeed(long objPtr, int pJointId,
			float pAngle, int pSpeedPercent, int pInterpolationType);

	native static private int _gotoBodyAngles(long objPtr, float[] pAngles,
			float pDuration, int pInterpolationType);

	native static private int _gotoBodyAnglesWithSpeed(long objPtr,
			float[] pAngles, int pSpeedPercent, int pInterpolationType);

	native static private int _gotoBodyStiffness(long objPtr, float pStiffness,
			float pDuration, int pInterpolationType);

	native static private int _gotoBodyStiffnesses(long objPtr,
			float[] pStiffnesses, float pDuration, int pInterpolationType);

	native static private int _gotoChainAngles(long objPtr, int pChainNameId,
			float[] pAngles, float pDuration, int pInterpolationType);

	native static private int _gotoChainAnglesWithSpeed(long objPtr,
			int pChainNameId, float[] pAngles, int pSpeedPercent,
			int pInterpolationType);

	native static private int _gotoChainStiffness(long objPtr,
			int pChainNameId, float pStiffness, float pDuration,
			int pInterpolationType);

	native static private int _gotoChainStiffnesses(long objPtr,
			int pChainNameId, float[] pStiffnesses, float pDuration,
			int pInterpolationType);

	native static private int _gotoCom(long objPtr, float pX, float pY,
			float pZ, float pDuration, int pInterpolationType);

	native static private int _gotoJointStiffness(long objPtr, int pJointId,
			float pStiffness, float pDuration, int pInterpolationType);

	native static private int _gotoJointStiffnesses(long objPtr,
			int[] pJointIds, float[] pStiffnesses, float pDuration,
			int pInterpolationType);

	native static private int _gotoPosition(long objPtr, int pChainNameId,
			int pSpace, float x, float y, float z, float wx, float wy,
			float wz, int pAxisMask, float pDuration, int pInterpolationType);

	native static private int _gotoTorsoOrientation(long objPtr, float pX,
			float pY, float pDuration, int pInterpolationType);

	native static private void _killAll(long objPtr);

	native static private boolean _killTask(long objPtr, int pTaskID);

	native static private int _openHand(long objPtr, String pHandName);

	native static private void _setAngle(long objPtr, int pJointId, float pAngle);

	native static private void _setBalanceMode(long objPtr, int pBalanceMode);

	native static private void _setBodyAngles(long objPtr, float[] pAngles);

	native static private void _setBodyStiffness(long objPtr, float pStiffness);

	native static private void _setChainAngles(long objPtr, int pChainNameId,
			float[] pAngles);

	native static private void _setChainStiffness(long objPtr,
			int pChainNameId, float pStiffness);

	native static private void _setCom(long objPtr, float pX, float pY, float pZ);

	native static private void _setJointStiffness(long objPtr, int pJointId,
			float pStiffness);

	native static private void _setJointStiffnesses(long objPtr,
			int[] pJointIds, float[] pStiffnesses);

	native static private void _setJointSpeedParams(long objPtr, int pJointId,
			float pUserMaxSpeed, float pUserMaxAcceleration,
			float pUserMaxDecleration);

	native static private int _setPosition(long objPtr, int pChainNameId,
			int pSpace, float x, float y, float z, float wx, float wy,
			float wz, int pAxisMask);

	native static private void _setSupportMode(long objPtr, int pSupportMode);

	native static private void _setTorsoOrientation(long objPtr, float pTetaX,
			float pTetaY);

	native static private void _setWalkArmsConfig(long objPtr,
			float pShoulderMedian, float pShoulderAmplitude,
			float pElbowMedian, float pElbowAmplitude);

	native static private void _setWalkArmsEnable(long objPtr,
			boolean pArmsEnable);

	native static private void _setWalkConfig(long objPtr,
			float pMaxStepLength, float pMaxStepHeight, float pMaxStepSide,
			float pMaxStepTurn, float pHipHeight, float pTorsoYOrientation);

	native static private void _setWalkTrapezoidConfig(long objPtr,
			float pLHipRollBacklashCompensator,
			float pRHipRollBacklashCompensator);

	native static private void _stop(long objPtr, int pBrokerTaskID);

	native static private int _turn(long objPtr, float pAngle,
			int pNumSamplesPerStep);

	native static private void _waitUntilWalkIsFinished(long objPtr);

	native static private int _walk(long objPtr);

	native static private int _walkArc(long objPtr, float pAngle,
			float pRadius, int pNumSamplesPerStep);

	native static private boolean _walkIsActive(long objPtr);

	native static private int _walkStraight(long objPtr, float pDistance,
			int pNumSamplesPerStep);

	native static private int _walkSideways(long objPtr, float pDistance,
			int pNumSamplesPerStep);
}
