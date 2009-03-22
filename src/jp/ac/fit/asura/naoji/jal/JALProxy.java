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

	native private long _create(long jalBrokerPtr);
}
