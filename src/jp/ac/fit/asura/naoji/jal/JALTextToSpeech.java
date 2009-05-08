/*
 * 作成日: 2009/05/09
 */
package jp.ac.fit.asura.naoji.jal;

/**
 * @author sey
 *
 * @version $Id: $
 *
 */
public class JALTextToSpeech extends JALModule {
	protected JALTextToSpeech(JALBroker broker) {
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

	public int say(String pStringToSay) {
		return _say(objPtr, pStringToSay);
	}

	native static private long _create(long jalBrokerPtr);

	native static private void _dispose(long objPtr);

	native static protected boolean _isRunning(long objPtr, int taskId);

	native static protected boolean _wait(long objPtr, int taskId, int timeout);

	native static private int _say(long objPtr, String pStringToSay);
}
