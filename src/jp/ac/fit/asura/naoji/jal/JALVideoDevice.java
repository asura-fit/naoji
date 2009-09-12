/*
 * 作成日: 2009/06/30
 */
package jp.ac.fit.asura.naoji.jal;

import java.awt.Dimension;
import java.awt.geom.Point2D;

/**
 * @author sey
 *
 * @version $Id: $
 *
 */
public class JALVideoDevice extends JALModule {
	protected JALVideoDevice(JALBroker broker) {
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

	public boolean startFrameGrabber() {
		return _startFrameGrabber(objPtr);
	}

	public boolean stopFrameGrabber() {
		return _stopFrameGrabber(objPtr);
	}

	public String subscribe(String pGVMname, int pResolution, int pColorSpace,
			int pFps) {
		return _subscribe(objPtr, pGVMname, pResolution, pColorSpace, pFps);
	}

	public void unsubscribe(String pId) {
		_unsubscribe(objPtr, pId);
	}

	/**
	 * Caution! You shouldn't use this method through remote broker.
	 */
	public int getImageLocal(String pId, JALImage image) {
		int res = _getImageLocal(objPtr, pId, image);
		if (res == 0)
			return 0;
		assert image.getLength() <= image.getData().capacity();
		image.getData().position(0);
		image.getData().limit(image.getLength());
		return res;
	}

	public int releaseImage(String pId) {
		return _releaseImage(objPtr, pId);
	}

	public void getImageRemote(String pId, JALImage image) {
		_getImageRemote(objPtr, pId, image);
		assert image.getLength() <= image.getData().capacity();
		image.getData().position(0);
		image.getData().limit(image.getLength());
	}

	/**
	 * Caution! You shouldn't use this method through remote broker.
	 */
	public int getDirectRawImageLocal(String pId, JALImage image) {
		int res = _getDirectRawImageLocal(objPtr, pId, image);
		if (res == 0)
			return 0;
		assert image.getLength() <= image.getData().capacity();
		image.getData().position(0);
		image.getData().limit(image.getLength());
		return res;
	}

	public int releaseDirectRawImage(String pId) {
		return _releaseDirectRawImage(objPtr, pId);
	}

	public void getDirectRawImageRemote(String pId, JALImage image) {
		_getDirectRawImageRemote(objPtr, pId, image);
		assert image.getLength() <= image.getData().capacity();
		image.getData().position(0);
		image.getData().limit(image.getLength());
	}

	public boolean setResolution(String pId, int size) {
		return _setResolution(objPtr, pId, size);
	}

	public boolean setFrameRate(String pId, int fps) {
		return _setFrameRate(objPtr, pId, fps);
	}

	public boolean setColorSpace(String pId, int pColorSpace) {
		return _setColorSpace(objPtr, pId, pColorSpace);
	}

	public int getVIMResolution() {
		return _getVIMResolution(objPtr);
	}

	public int getVIMColorSpace() {
		return _getVIMColorSpace(objPtr);
	}

	public int getVIMFrameRate() {
		return _getVIMFrameRate(objPtr);
	}

	public int getGVMResolution(String pId) {
		return _getGVMResolution(objPtr, pId);
	}

	public int getGVMColorSpace(String pId) {
		return _getGVMColorSpace(objPtr, pId);
	}

	public int getGVMFrameRate(String pId) {
		return _getGVMFrameRate(objPtr, pId);
	}

	public void setParam(int pParam, int pNewValue) {
		_setParam(objPtr, pParam, pNewValue);
	}

	public void setParamDefault(int pParam) {
		_setParamDefault(objPtr, pParam);
	}

	public void getAngles(float xPos, float yPos, Point2D.Float angle) {
		_getAngles(objPtr, xPos, yPos, angle);
	}

	public void resolutionToSizes(int resolution, Dimension dim) {
		_resolutionToSizes(objPtr, resolution, dim);
	}

	public int sizesToResolution(int width, int height) {
		return _sizesToResolution(objPtr, width, height);
	}

	public boolean recordVideo(String pId, String pPath, int pTotalNumber,
			int pPeriod) {
		return _recordVideo(objPtr, pId, pPath, pTotalNumber, pPeriod);
	}

	public boolean stopVideo(String pId) {
		return _stopVideo(objPtr, pId);
	}

	public int getParam(int pParam) {
		return _getParam(objPtr, pParam);
	}

	native static private long _create(long jalBrokerPtr);

	native static private void _dispose(long objPtr);

	native static protected boolean _isRunning(long objPtr, int taskId);

	native static protected boolean _wait(long objPtr, int taskId, int timeout);

	native static private boolean _startFrameGrabber(long objPtr);

	native static private boolean _stopFrameGrabber(long objPtr);

	native static private String _subscribe(long objPtr, String pGVMname,
			int pResolution, int pColorSpace, int pFps);

	native static private void _unsubscribe(long objPtr, String pId);

	native static private int _getImageLocal(long objPtr, String pId,
			JALImage image);

	native static private int _releaseImage(long objPtr, String pId);

	native static private void _getImageRemote(long objPtr, String pId,
			JALImage image);

	native static private int _getDirectRawImageLocal(long objPtr, String pId,
			JALImage image);

	native static private int _releaseDirectRawImage(long objPtr, String pId);

	native static private void _getDirectRawImageRemote(long objPtr,
			String pId, JALImage image);

	native static private boolean _setResolution(long objPtr, String pId,
			int size);

	native static private boolean _setFrameRate(long objPtr, String pId, int fps);

	native static private boolean _setColorSpace(long objPtr, String pId,
			int pColorSpace);

	native static private int _getVIMResolution(long objPtr);

	native static private int _getVIMColorSpace(long objPtr);

	native static private int _getVIMFrameRate(long objPtr);

	native static private int _getGVMResolution(long objPtr, String pId);

	native static private int _getGVMColorSpace(long objPtr, String pId);

	native static private int _getGVMFrameRate(long objPtr, String pId);

	native static private void _setParam(long objPtr, int pParam, int pNewValue);

	native static private void _setParamDefault(long objPtr, int pParam);

	native static private void _getAngles(long objPtr, float xPos, float yPos,
			Point2D.Float angle);

	native static private void _resolutionToSizes(long objPtr, int resolution,
			Dimension dim);

	native static private int _sizesToResolution(long objPtr, int width,
			int height);

	native static private boolean _recordVideo(long objPtr, String pId,
			String pPath, int pTotalNumber, int pPeriod);

	native static private boolean _stopVideo(long objPtr, String pId);

	native static private int _getParam(long objPtr, int pParam);
}
