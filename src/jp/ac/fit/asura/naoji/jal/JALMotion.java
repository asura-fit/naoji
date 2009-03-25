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
	private String[] jointNames;
	private int jointNum;

	protected JALMotion(JALBroker broker) {
		objPtr = _create(broker.getPtr());
		jointNames = _getBodyJointNames(objPtr);
		assert jointNames != null;
		for (int i = 0; i < jointNames.length; i++) {
			_defineJoint(objPtr, i, jointNames[i]);
		}
		jointNum = jointNames.length;
	}

	public boolean isDefinedJoint(int id) {
		return _isDefinedJoint(objPtr, id);
	}

	// ALMotion methods. see ALMotion Reference in Blue doc.

	public void clearFootsteps() {
		_clearFootsteps(objPtr);
	}

	/**
	 * 複数の関節に対し、実行時間を指定して関節の時系列データを与え実行します.
	 *
	 * pAnglesとpDurationsは1次元配列にパックされた行列(Matrix)です. i,j番目の要素は次のように表現されます.
	 *
	 * <pre>
	 * matrix[i][j] == packed[pJointIds.length*i + j].
	 * </pre>
	 *
	 * @param pJointIds
	 * @param pAngles
	 *            matrix of angles
	 * @param pDurations
	 *            matrix of durations
	 * @param pInterpolationType
	 * @return taskId
	 */
	public int doMove(int[] pJointIds, float[] pAngles, float[] pDurations,
			int pInterpolationType) {
		assert pJointIds.length <= jointNum;
		for (int id : pJointIds)
			assert isDefinedJoint(id);
		return _doMove(objPtr, pJointIds, pAngles, pDurations,
				pInterpolationType);
	}

	/**
	 * すべての関節に対し動作指令を与えます. 関節の順番は#getJointNames()で与えられるものと同じ順番です.
	 *
	 * その他の事柄は#doMove()と同じです.
	 *
	 * @param pAngles
	 * @param pDurations
	 * @param pInterpolationType
	 * @return taskId
	 */
	public int doMoveAll(float[] pAngles, float[] pDurations,
			int pInterpolationType) {
		return _doMoveAll(objPtr, pAngles, pDurations, pInterpolationType);
	}

	public float getAngle(int pJointId) {
		assert isDefinedJoint(pJointId);
		return _getAngle(objPtr, pJointId);
	}

	public void getBodyAngles(float[] pAngles) {
		assert pAngles.length == jointNum;
		_getBodyAngles(objPtr, pAngles);
	}

	public float getJointStiffness(int pJointId) {
		assert isDefinedJoint(pJointId);
		return _getJointStiffness(objPtr, pJointId);
	}

	public int gotoAngle(int pJointId, float pAngle, float pDuration,
			int pInterpolationType) {
		assert isDefinedJoint(pJointId);
		return _gotoAngle(objPtr, pJointId, pAngle, pDuration,
				pInterpolationType);
	}

	public int gotoBodyAngles(float[] pAngles, float pDuration,
			int pInterpolationType) {
		assert pAngles.length == jointNum;
		return _gotoBodyAngles(objPtr, pAngles, pDuration, pInterpolationType);
	}

	public int gotoBodyStiffness(float pStiffness, float pDuration,
			int pInterpolationType) {
		return _gotoBodyStiffness(objPtr, pStiffness, pDuration,
				pInterpolationType);
	}

	public int gotoJointStiffness(int pJointId, float pStiffness,
			float pDuration, int pInterpolationType) {
		assert isDefinedJoint(pJointId);
		return _gotoJointStiffness(objPtr, pJointId, pStiffness, pDuration,
				pInterpolationType);
	}

	public void setBodyStiffness(float pStiffness) {
		_setBodyStiffness(objPtr, pStiffness);
	}

	public void setJointStiffness(int pJointId, float pStiffness) {
		_setJointStiffness(objPtr, pJointId, pStiffness);
	}

	public void stop(int pBrokerTaskID) {
		_stop(objPtr, pBrokerTaskID);
	}

	// Walking commands
	public int turn(float pAngle, int pNumSamplesPerStep) {
		return _turn(objPtr, pAngle, pNumSamplesPerStep);
	}

	public int walkArc(float pAngle, float pRadius, int pNumSamplesPerStep) {
		return _walkArc(objPtr, pAngle, pRadius, pNumSamplesPerStep);
	}

	public boolean walkIsActive() {
		return _walkIsActive(objPtr);
	}

	public int walkStraight(float pDistance, int pNumSamplesPerStep) {
		return _walkStraight(pNumSamplesPerStep, pDistance, pNumSamplesPerStep);
	}

	public int walkSideways(float pDistance, int pNumSamplesPerStep) {
		return _walkSideways(objPtr, pDistance, pNumSamplesPerStep);
	}

	public void setWalkConfig(float pMaxStepLength, float pMaxStepHeight,
			float pMaxStepSide, float pMaxStepTurn, float pZmpOffsetX,
			float pZmpOffsetY) {
		_setWalkConfig(objPtr, pMaxStepLength, pMaxStepHeight, pMaxStepSide,
				pMaxStepTurn, pZmpOffsetX, pZmpOffsetY);
	}

	public void setWalkExtraConfig(float pLHipRollBacklashCompensator,
			float pRHipRollBacklashCompensator, float pHipHeight,
			float pTorsoYOrientation) {
		_setWalkExtraConfig(objPtr, pLHipRollBacklashCompensator,
				pRHipRollBacklashCompensator, pHipHeight, pTorsoYOrientation);
	}

	native private long _create(long jalBrokerPtr);

	// Joint definitions.
	native private boolean _isDefinedJoint(long objPtr, int id);

	native private void _defineJoint(long objPtr, int id, String jointName);

	native private void _removeJoint(long objPtr, int id);

	// Chain definitions, not implemented.
	private boolean _isDefinedChain(int id) {
		return false;
	}

	private int _getChainId(String chainName) {
		throw new UnsupportedOperationException();
	}

	private void _defineChain(int id, String chainName) {
		throw new UnsupportedOperationException();
	}

	private void _removeChain(int id) {
		throw new UnsupportedOperationException();
	}

	// ALModule methods.
	native protected boolean _isRunning(long objPtr, int taskId);

	native protected boolean _wait(long objPtr, int taskId, int timeout);

	// ALMotion methods.
	native private void _clearFootsteps(long objPtr);

	native private int _doMove(long objPtr, int[] pJointIds, float[] pAngles,
			float[] pDurations, int pInterpolationType);

	native private int _doMoveAll(long objPtr, float[] pAngles,
			float[] pDurations, int pInterpolationType);

	native private float _getAngle(long objPtr, int pJointId);

	native private void _getBodyAngles(long objPtr, float[] pAngles);

	native private String[] _getBodyJointNames(long objPtr);

	native private float _getJointStiffness(long objPtr, int pJointId);

	native private int _gotoAngle(long objPtr, int pJointId, float pAngle,
			float pDuration, int pInterpolationType);

	native private int _gotoBodyAngles(long objPtr, float[] pAngles,
			float pDuration, int pInterpolationType);

	native private int _gotoBodyStiffness(long objPtr, float pStiffness,
			float pDuration, int pInterpolationType);

	native private int _gotoJointStiffness(long objPtr, int pJointId,
			float pStiffness, float pDuration, int pInterpolationType);

	native private void _setBodyStiffness(long objPtr, float pStiffness);

	native private void _setJointStiffness(long objPtr, int pJointId,
			float pStiffness);

	native private void _setWalkConfig(long objPtr, float pMaxStepLength,
			float pMaxStepHeight, float pMaxStepSide, float pMaxStepTurn,
			float pZmpOffsetX, float pZmpOffsetY);

	native private void _setWalkExtraConfig(long objPtr,
			float pLHipRollBacklashCompensator,
			float pRHipRollBacklashCompensator, float pHipHeight,
			float pTorsoYOrientation);

	native void _stop(long objPtr, int pBrokerTaskID);

	// Walking commands
	native private int _turn(long objPtr, float pAngle, int pNumSamplesPerStep);

	native private int _walkArc(long objPtr, float pAngle, float pRadius,
			int pNumSamplesPerStep);

	native private boolean _walkIsActive(long objPtr);

	native private int _walkStraight(long objPtr, float pDistance,
			int pNumSamplesPerStep);

	native private int _walkSideways(long objPtr, float pDistance,
			int pNumSamplesPerStep);
}
