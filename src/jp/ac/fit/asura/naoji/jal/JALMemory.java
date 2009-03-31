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
public class JALMemory extends JALModule {
	protected JALMemory(JALBroker broker) {
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

	native static private long _create(long jalBrokerPtr);

	native static public void defineKey(int id, String key);

	native static private void _dispose(long objPtr);

	native static public void undefineKey(int id);

	// ALModule methods.
	native static protected boolean _wait(long objPtr, int taskId, int timeout);

	native static protected boolean _isRunning(long objPtr, int taskId);
}
