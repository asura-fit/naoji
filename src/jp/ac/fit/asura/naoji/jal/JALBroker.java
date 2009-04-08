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
public class JALBroker {
	private long objPtr;

	public JALBroker(long brokerPtr) {
		this.objPtr = brokerPtr;
	}

	public JALMemory createJALMemory() {
		JALMemory mem = new JALMemory(this);
		return mem;
	}

	public JALMotion createJALMotion() {
		JALMotion mot = new JALMotion(this);
		return mot;
	}

	public JDCM createJDCM() {
		JDCM dcm = new JDCM(this);
		return dcm;
	}

	public void dispose() {
		_dispose(objPtr);
	}

	protected long getPtr() {
		return objPtr;
	}

	native static private void _dispose(long objPtr);
}
