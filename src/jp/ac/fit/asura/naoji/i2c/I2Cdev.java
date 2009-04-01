/*
 * 作成日: 2009/04/02
 */
package jp.ac.fit.asura.naoji.i2c;

import java.io.IOException;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class I2Cdev {
	static {
		// Should i2c use another .so?
		System.err.println("Loading naojii2c library.");
		System.loadLibrary("naojiv4l2");
	}

	private int dev;

	/**
		 *
		 */
	public I2Cdev(String device) throws IOException {
		dev = _createI2Cdev(device);
		if (dev < 0)
			throw new IOException(device + " open() failed. code:" + dev);
	}

	public void dispose() {
		_destroy(dev);
	}

	public int init() {
		return _init(dev);
	}

	public int getSelectedCamera() {
		return _getSelectedCamera(dev);
	}

	public int selectCamera(int id) {
		return _selectCamera(dev, id);
	}

	private static native int _createI2Cdev(String device);

	private static native void _destroy(int dev);

	private static native int _getSelectedCamera(int dev);

	private static native int _init(int dev);

	private static native int _selectCamera(int dev, int id);

}
