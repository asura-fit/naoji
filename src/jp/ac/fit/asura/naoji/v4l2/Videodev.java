/*
 * 作成日: 2009/03/30
 */
package jp.ac.fit.asura.naoji.v4l2;

import java.awt.Dimension;
import java.nio.ByteBuffer;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class Videodev {
	private int dev;
	private ByteBuffer[] buffers;

	/**
	 *
	 */
	public Videodev(String device) {
		dev = _createVideodev(device);
	}

	protected void finalize() throws Throwable {
		_destroy(dev);
	}

	public void init() {
		int count = _requestBuffers(dev, 5);
		buffers = new ByteBuffer[count];
		for(int i = 0;i < count; i++)
			buffers[i] = _queryBuffer(dev, i).asReadOnlyBuffer();
	}

	public void start() {
		_start(dev);
	}

	public void stop() {
		_stop(dev);
	}

	public void retrieveImage(V4L2Buffer buffer) {
		int res = _retrieveImage(dev, buffer);
		ByteBuffer bb = buffers[buffer.getIndex()];
		bb.position(0);
		bb.limit(buffer.getLength());
		buffer.setBuffer(bb);
	}

	public void disposeImage(V4L2Buffer buffer) {
		_disposeImage(dev, buffer.getIndex());
	}

	protected void disposeBuffers() {
		_disposeBuffers(dev);
		buffers = null;
	}

	public int getControl(int id) {
		return _getControl(dev, id);
	}

	public void getFormat(V4L2PixelFormat format) {
		_getFormat(dev, format);
	}

	public int getSelectedCamera() {
		return _getSelectedCamera(dev);
	}

	public boolean isSupportedControl(int id) {
		return _isSupportedControl(dev, id);
	}

	public boolean isSupportedFormat(Dimension dim, int pixelFormat) {
		return _isSupportedFormat(dev, dim.width, dim.height, pixelFormat);
	}

	public boolean isSupportedFPS(int fps) {
		return _isSupportedFPS(dev, fps);
	}

	public void selectCamera(int id) {
		_selectCamera(dev, id);
	}

	public void setFormat(V4L2PixelFormat format) {
		_setFormat(dev, format);
	}

	public void setFPS(int fps) {
		_setFPS(dev, fps);
	}

	public void setControl(int id, int value) {
		assert isSupportedControl(id);
		_setControl(dev, id, value);
	}

	private static native int _createVideodev(String device);

	private static native void _destroy(int dev);

	private static native void _disposeBuffers(int dev);

	private static native void _disposeImage(int dev, int index);

	private static native int _getSelectedCamera(int dev);

	private static native int _getControl(int dev, int key);

	private static native int _getFormat(int dev, V4L2PixelFormat format);

	private static native boolean _isSupportedControl(int dev, int id);

	private static native boolean _isSupportedFormat(int dev, int width,
			int height, int pixelFormat);

	private static native boolean _isSupportedFPS(int dev, int fps);

	private static native int _requestBuffers(int dev, int count);

	private static native ByteBuffer _queryBuffer(int dev, int index);

	private static native void _selectCamera(int dev, int id);

	private static native void _setControl(int dev, int key, int value);

	private static native void _setFormat(int dev, V4L2PixelFormat format);

	private static native void _setFPS(int dev, int fps);

	private static native void _start(int dev);

	private static native void _stop(int dev);

	private static native int _retrieveImage(int dev, V4L2Buffer buffer);

}
