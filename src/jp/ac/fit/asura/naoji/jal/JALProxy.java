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
public class JALProxy extends JALModule {
	protected JALProxy(JALBroker broker) {
		// objPtr = _create(broker.getPtr());
		// TODO implement JALProxy
		assert false;
		throw new UnsupportedOperationException();
	}

	public void wait(int taskId, int timeout) {
		_wait(objPtr, taskId, timeout);
	}

	public boolean isRunning(int taskId) {
		return _isRunning(objPtr, taskId);
	}

	native static private long _create(long jalBrokerPtr);

	// ALModule methods.
	native static protected boolean _isRunning(long objPtr, int taskId);

	native static protected boolean _wait(long objPtr, int taskId, int timeout);
}
