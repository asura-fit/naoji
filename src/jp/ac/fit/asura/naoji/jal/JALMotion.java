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
	protected JALMotion(JALBroker broker) {
		objPtr = _create(broker.getPtr());
	}

	public int doMove(String[] pJointNames, float[][] pAngles,
			float[][] pDurations, int pInterpolationType) {
		return _doMove(objPtr, pJointNames, pAngles, pDurations,
				pInterpolationType);
	}

	public float getAngle(String pJointName) {
		return _getAngle(objPtr, pJointName);
	}

	public float getJointStiffness(String pJointName) {
		return _getJointStiffness(objPtr, pJointName);
	}

	public int gotoAngle(String pJointName, float pAngle, float pDuration,
			int pInterpolationType) {
		return _gotoAngle(objPtr, pJointName, pAngle, pDuration,
				pInterpolationType);
	}

	public void getBodyAngles(float[] pAngles) {
		_getBodyAngles(objPtr, pAngles);
	}

	public int gotoBodyAngles(float[] pAngles, float pDuration,
			int pInterpolationType) {
		return _gotoBodyAngles(objPtr, pAngles, pDuration, pInterpolationType);
	}

	public void setBodyAngles(float[] pAngles) {
		_setBodyAngles(objPtr, pAngles);
	}

	public int setBodyStiffness(float pStiffness) {
		return _setBodyStiffness(objPtr, pStiffness);
	}

	public void setJointStiffness(String pJointName, float pStiffness) {
		_setJointStiffness(objPtr, pJointName, pStiffness);
	}

	// Walking commands
	public int turn(float pAngle, int pNumSamplesPerStep) {
		return _turn(objPtr, pAngle, pNumSamplesPerStep);
	}

	public int walkArc(float pAngle, float pRadius, int pNumSamplesPerStep) {
		return _walkArc(objPtr, pAngle, pRadius, pNumSamplesPerStep);
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

	native public int _doMove(long objPtr, String[] pJointNames,
			float[][] pAngles, float[][] pDurations, int pInterpolationType);

	native public float _getAngle(long objPtr, String pJointName);

	native public float _getJointStiffness(long objPtr, String pJointName);

	native public int _gotoAngle(long objPtr, String pJointName, float pAngle,
			float pDuration, int pInterpolationType);

	native public void _getBodyAngles(long objPtr, float[] pAngles);

	native public int _gotoBodyAngles(long objPtr, float[] pAngles,
			float pDuration, int pInterpolationType);

	native void _setBodyAngles(long objPtr, float[] pAngles);

	native public int _setBodyStiffness(long objPtr, float pStiffness);

	native void _setJointStiffness(long objPtr, String pJointName,
			float pStiffness);

	// Walking commands
	native public int _turn(long objPtr, float pAngle, int pNumSamplesPerStep);

	native public int _walkArc(long objPtr, float pAngle, float pRadius,
			int pNumSamplesPerStep);

	native public int _walkStraight(long objPtr, float pDistance,
			int pNumSamplesPerStep);

	native public int _walkSideways(long objPtr, float pDistance,
			int pNumSamplesPerStep);

	native public void _setWalkConfig(long objPtr, float pMaxStepLength,
			float pMaxStepHeight, float pMaxStepSide, float pMaxStepTurn,
			float pZmpOffsetX, float pZmpOffsetY);

	native public void _setWalkExtraConfig(long objPtr,
			float pLHipRollBacklashCompensator,
			float pRHipRollBacklashCompensator, float pHipHeight,
			float pTorsoYOrientation);

}
