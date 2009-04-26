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
	private static int[] controlIdMap;

	static {
		System.err.println("Loading naojiv4l2 library.");
		System.loadLibrary("naojiv4l2");

		__init();

		V4L2Control[] ctrls = V4L2Control.values();
		controlIdMap = new int[ctrls.length];
		for (V4L2Control c : ctrls)
			controlIdMap[c.ordinal()] = __getIntConst(c.name());
	}

	private int dev;
	private ByteBuffer[] buffers;

	/**
	 * Open V4L2 device.
	 *
	 * @param device
	 *            V4L2 Device to open. ex. "/dev/video0"
	 * @throws IOException
	 *             if open() system call is failed.
	 */
	public Videodev(String device) throws IOException {
		dev = _createVideodev(device);
		if (dev < 0)
			throw new IOException(device + " open() failed. code:" + dev);
		buffers = null;
	}

	/**
	 * Dispose all buffers and close V4L2 device.
	 *
	 * @see http://v4l2spec.bytesex.org/spec/r14037.htm
	 * @see
	 */
	public void dispose() {
		disposeBuffers();
		_destroy(dev);
	}

	/**
	 * do request V4L2 buffers and mmap().
	 *
	 * @param bufferNum
	 *            mmaped buffer size.
	 * @return > 0 allocated buffer size. <= 0 on error
	 * @see http://v4l2spec.bytesex.org/spec/r13696.htm
	 * @see http://v4l2spec.bytesex.org/spec/r13889.htm
	 */
	public int init(int bufferNum) {
		int count = _requestBuffers(dev, bufferNum);
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

	/**
	 * start video stream. do call VIDIOC_STREAMON.
	 *
	 * @see http://v4l2spec.bytesex.org/spec/r13817.htm
	 * @return 0 if succeeded. < 0 on error
	 */
	public int start() {
		int res = _start(dev);
		return res;
	}

	/**
	 * stop video stream. do call VIDIOC_STREAMOFF.
	 *
	 * @see http://v4l2spec.bytesex.org/spec/r13817.htm
	 * @return 0 if succeeded. < 0 on error
	 */
	public int stop() {
		int res = _stop(dev);
		return res;
	}

	/**
	 * retrieve one buffer and store in V4L2Buffer.
	 *
	 * It calls VIDIOC_DQBUF.
	 *
	 * @param buffer
	 * @return 0 if succeeded. < 0 on error
	 * @see http://v4l2spec.bytesex.org/spec/r12878.htm
	 */
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

	/**
	 * Dispose buffer that described by V4L2Buffer.
	 *
	 * It calls VIDIOC_QBUF.
	 *
	 * @param buffer
	 * @return
	 * @see http://v4l2spec.bytesex.org/spec/r12878.htm
	 */
	public int disposeImage(V4L2Buffer buffer) {
		int res = _enqueueBuffer(dev, buffer.getIndex());
		return res;
	}

	/**
	 * Dispose all buffers.
	 *
	 * It calls munmap for all buffers.
	 *
	 * @see http://v4l2spec.bytesex.org/spec/r14037.htm
	 */
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

	public int getControl(V4L2Control control) {
		return getControl(toControlId(control));
	}

	public int getControl(int id) {
		return _getControl(dev, id);
	}

	public int getFormat(V4L2PixelFormat format) {
		return _getFormat(dev, format);
	}

	public long getStandard() {
		return _getStandard(dev);
	}

	public Collection<V4L2PixelFormat> getSupportedFormats() {
		List<V4L2PixelFormat> list = new ArrayList<V4L2PixelFormat>();
		_getSupportedFormats(dev, list);
		return list;
	}

	public boolean isSupportedControl(V4L2Control control) {
		return isSupportedControl(toControlId(control));
	}

	public boolean isSupportedControl(int id) {
		return _isSupportedControl(dev, id);
	}

	public boolean isSupportedFormat(V4L2PixelFormat format) {
		return _isSupportedFormat(dev, format);
	}

	public int setControl(V4L2Control control, int value) {
		return setControl(toControlId(control), value);
	}

	public int setControl(int id, int value) {
		assert isSupportedControl(id) : toControl(id);
		return _setControl(dev, id, value);
	}

	public int setFormat(V4L2PixelFormat format) {
		return _setFormat(dev, format);
	}

	public int setFPS(int fps) {
		return _setFPS(dev, fps);
	}

	public int setStandard(long value) {
		return _setStandard(dev, value);
	}

	int toControlId(V4L2Control control) {
		return controlIdMap[control.ordinal()];
	}

	V4L2Control toControl(int controlId) {
		for (int i = 0; i < controlIdMap.length; i++)
			if (controlId == controlIdMap[i])
				return V4L2Control.values()[i];
		return null;
	}

	private static native void __init();

	private static native int __getIntConst(String str);

	private static native int _createVideodev(String device);

	private static native int _dequeueBuffer(int dev, V4L2Buffer buffer);

	private static native void _destroy(int dev);

	private static native int _enqueueBuffer(int dev, int index);

	private static native int _getControl(int dev, int id);

	private static native int _getFormat(int dev, V4L2PixelFormat format);

	private static native long _getStandard(int dev);

	private static native int _getSupportedFormats(int dev,
			Collection<V4L2PixelFormat> list);

	private static native boolean _isSupportedControl(int dev, int id);

	private static native boolean _isSupportedFormat(int dev,
			V4L2PixelFormat format);

	private static native int _requestBuffers(int dev, int count);

	private static native ByteBuffer _mmapBuffer(int dev, int index);

	private static native int _munmapBuffer(int dev, ByteBuffer buf);

	private static native int _setControl(int dev, int id, int value);

	private static native int _setFormat(int dev, V4L2PixelFormat format);

	private static native int _setFPS(int dev, int fps);

	private static native int _setStandard(int dev, long value);

	private static native int _start(int dev);

	private static native int _stop(int dev);

}
