/*
 * 作成日: 2009/04/09
 */
package jp.ac.fit.asura.naoji.jal;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class JDCM extends JALModule {
	public static enum MergeType {
		Merge, ClearAll, ClearAfter, ClearBefore
	}

	protected JDCM(JALBroker broker) {
		objPtr = _create(broker.getPtr());
	}

	public void dispose() {
		_dispose(objPtr);
	}

	public boolean isRunning(int taskId) {
		return _isRunning(objPtr, taskId);
	}

	public void wait(int taskId, int timeout) {
		_wait(objPtr, taskId, timeout);
	}

	public int createAlias(String[] deviceNames) {
		assert deviceNames != null;
		return _createAlias(objPtr, deviceNames);
	}

	/**
	 * set actuator value for single device with timed command.
	 *
	 * @param device
	 * @param value
	 * @param time
	 */
	public void set(String device, MergeType type, float[] value, int[] time) {
		assert value.length == time.length;
		_set(objPtr, device, type.ordinal(), value, time);
	}

	/**
	 * set actuator value for alias with time-separate command.
	 *
	 * aliasIdで指定したDCMエイリアスに対し、time-separateモードでコマンドを送信します.
	 *
	 * 各アクチュエータには、timeで示される時間ごとに同時にコマンドが送られます.
	 *
	 * valueMatrixは次の規則でアクチュエータの値の行列をコード化したものです.
	 *
	 * <pre>
	 * valueMatrix[x] = valueMatrix[actuatorNo][timeNo]
	 * </pre>
	 *
	 * @param device
	 * @param value
	 * @param time
	 */
	public void setTimeSeparate(int aliasId, MergeType type,
			float[] valueMatrix, int[] time) {
		assert valueMatrix.length >= time.length;
		assert valueMatrix.length % time.length == 0;
		_setTimeSeparate(objPtr, aliasId, type.ordinal(), valueMatrix, time);
	}

	public void setTimeMixed(int aliasId, MergeType type, float[] valueMatrix,
			int[] time) {
		assert valueMatrix.length == time.length;
		_setTimeMixed(objPtr, aliasId, type.ordinal(), valueMatrix, time);
	}

	public int getTime() {
		return _getTime(objPtr);
	}

	native static private long _create(long jalBrokerPtr);

	native static private void _dispose(long objPtr);

	// ALModule methods.
	native static protected boolean _isRunning(long objPtr, int taskId);

	native static protected boolean _wait(long objPtr, int taskId, int timeout);

	// DCM methods
	native static private int _createAlias(long objPtr, String[] deviceNames);

	native static private int _getTime(long objPtr);

	native static private void _set(long objPtr, String device, int mergeType,
			float[] value, int[] time);

	native static private void _setTimeMixed(long objPtr, int aliasId,
			int mergeType, float[] valueMatrix, int[] time);

	native static private void _setTimeSeparate(long objPtr, int aliasId,
			int mergeType, float[] valueMatrix, int[] time);
}
