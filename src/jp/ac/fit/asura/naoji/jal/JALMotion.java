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

	native private long _create(long jalBrokerPtr);
}
