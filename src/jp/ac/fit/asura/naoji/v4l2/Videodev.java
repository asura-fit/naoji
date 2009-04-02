/*
 * 作成日: 2009/03/30
 */
package jp.ac.fit.asura.naoji.v4l2;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class Videodev {
	static {
		System.err.println("Loading naojiv4l2 library.");
		System.loadLibrary("naojiv4l2");
	}

	private int dev;
	private ByteBuffer[] buffers;

	/**
	 *
	 */
	public Videodev(String device) throws IOException {
		dev = _createVideodev(device);
		if (dev < 0)
			throw new IOException(device + " open() failed. code:" + dev);
		buffers = null;
	}

	public void dispose() {
		disposeBuffers();
		_destroy(dev);
	}

	public int init() {
		int count = _requestBuffers(dev, 5);
		if (count < 0)
			return count;

		buffers = new ByteBuffer[count];
		for (int i = 0; i < count; i++) {
			buffers[i] = _mmapBuffer(dev, i);
			if (buffers[i] == null)
				return -255;
			buffers[i] = buffers[i].asReadOnlyBuffer();
			_enqueueBuffer(dev, i);
		}
		return count;
	}

	public int start() {
		int res = _start(dev);
		return res;
	}

	public int stop() {
		int res = _stop(dev);
		return res;
	}

	public int retrieveImage(V4L2Buffer buffer) {
		int res = _dequeueBuffer(dev, buffer);
		if (res < 0)
			return res;

		ByteBuffer bb = buffers[buffer.getIndex()];
		bb.position(0);
		bb.limit(buffer.getLength());
		buffer.setBuffer(bb);
		return res;
	}

	public int disposeImage(V4L2Buffer buffer) {
		int res = _enqueueBuffer(dev, buffer.getIndex());
		return res;
	}

	private void disposeBuffers() {
		if (buffers == null)
			return;

		for (int i = 0; i < buffers.length; i++) {
			assert buffers[i] != null;
			int res = _munmapBuffer(dev, buffers[i]);
			assert res >= 0 : res;
			buffers[i] = null;
		}
		buffers = null;
	}

	public int getControl(int id) {
		return _getControl(dev, id);
	}

	public int getFormat(V4L2PixelFormat format) {
		return _getFormat(dev, format);
	}

	public Collection<V4L2PixelFormat> getSupportedFormats() {
		List<V4L2PixelFormat> list = new ArrayList<V4L2PixelFormat>();
		_getSupportedFormats(dev, list);
		return list;
	}

	public boolean isSupportedControl(int id) {
		return _isSupportedControl(dev, id);
	}

	public boolean isSupportedFormat(V4L2PixelFormat format) {
		return _isSupportedFormat(dev, format);
	}

	public int setFormat(V4L2PixelFormat format) {
		return _setFormat(dev, format);
	}

	public int setFPS(int fps) {
		return _setFPS(dev, fps);
	}

	public int setControl(int id, int value) {
		assert isSupportedControl(id);
		return _setControl(dev, id, value);
	}

	private static native int _createVideodev(String device);

	private static native int _dequeueBuffer(int dev, V4L2Buffer buffer);

	private static native void _destroy(int dev);

	private static native int _enqueueBuffer(int dev, int index);

	private static native int _getControl(int dev, int key);

	private static native int _getFormat(int dev, V4L2PixelFormat format);

	private static native int _getSupportedFormats(int dev,
			Collection<V4L2PixelFormat> list);

	private static native boolean _isSupportedControl(int dev, int id);

	private static native boolean _isSupportedFormat(int dev,
			V4L2PixelFormat format);

	private static native int _requestBuffers(int dev, int count);

	private static native ByteBuffer _mmapBuffer(int dev, int index);

	private static native int _munmapBuffer(int dev, ByteBuffer buf);

	private static native int _setControl(int dev, int key, int value);

	private static native int _setFormat(int dev, V4L2PixelFormat format);

	private static native int _setFPS(int dev, int fps);

	private static native int _start(int dev);

	private static native int _stop(int dev);

}
