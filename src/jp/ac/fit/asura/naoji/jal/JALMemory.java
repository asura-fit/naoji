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

	native private long _create(long jalBrokerPtr);

	native public void defineKey(int id, String key);

	native public void undefineKey(int id);

	// ALModule methods.
	native protected boolean _wait(long objPtr, int taskId, int timeout);

	native protected boolean _isRunning(long objPtr, int taskId);
}
