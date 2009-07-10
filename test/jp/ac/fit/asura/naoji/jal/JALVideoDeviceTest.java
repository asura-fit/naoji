/*
 * 作成日: 2009/07/08
 */
package jp.ac.fit.asura.naoji.jal;

import java.awt.Dimension;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;

import jp.ac.fit.asura.naoji.Naoji;
import jp.ac.fit.asura.naoji.NaojiContext;
import jp.ac.fit.asura.naoji.NaojiFactory;
import jp.ac.fit.asura.naoji.robots.NaoV3R.Camera;
import junit.framework.TestCase;
import junit.textui.TestRunner;

/**
 * @author sey
 *
 * @version $Id: $
 *
 */
public class JALVideoDeviceTest extends TestCase {
	JALVideoDevice video;

	public static class Factory implements NaojiFactory {
		public Naoji create() {
			return NaojiImpl.getInstance();
		}
	}

	private static class NaojiImpl implements Naoji {
		static NaojiImpl instance = null;
		JALVideoDevice video;
		Thread mainThread;

		private NaojiImpl() {
		}

		public void init(NaojiContext context) {
			video = context.getParentBroker().createJALVideoDevice();

			mainThread = new Thread() {
				public void run() {
					try {
						TestRunner.run(JALVideoDeviceTest.class);
					} catch (RuntimeException e) {
						e.printStackTrace();
					}
				}
			};
		}

		public void exit() {
		}

		public void start() {
			System.err.println("NaojiTest start called.");
			mainThread.start();
		}

		public void stop() {
			System.err.println("NaojiTest stop called.");
			try {
				mainThread.join();
			} catch (InterruptedException e) {
				e.printStackTrace();
				assert false;
			}
		}

		public static NaojiImpl getInstance() {
			if (instance == null)
				instance = new NaojiImpl();
			return instance;
		}
	}

	String pId;

	protected void setUp() throws Exception {
		super.setUp();
		video = NaojiImpl.getInstance().video;
	}

	protected void tearDown() throws Exception {
		super.tearDown();
	}

	public void testVideo1() throws Exception {
		System.out.println("begin testVideo1.");
		pId = video.register("testVideo1", Camera.RESOLUTION_QVGA,
				Camera.COLORSPACE_YUV422Interlaced, 30);
		assertNotNull(pId);
		assertFalse(pId.isEmpty());

		System.out.println(" test get methods");
		assertEquals(Camera.RESOLUTION_QVGA, video.getVIMResolution());
		assertEquals(Camera.COLORSPACE_YUV422Interlaced, video
				.getVIMColorSpace());
		assertEquals(30, video.getVIMFrameRate());

		assertEquals(Camera.RESOLUTION_QVGA, video.getGVMResolution(pId));
		assertEquals(Camera.COLORSPACE_YUV422Interlaced, video
				.getGVMColorSpace(pId));
		assertEquals(30, video.getGVMFrameRate(pId));

		System.out.println(" test set methods");
		assertTrue(video.setResolution(pId, Camera.RESOLUTION_QQVGA));
		assertTrue(video.setColorSpace(pId, Camera.COLORSPACE_RGB));
		assertTrue(video.setFrameRate(pId, 10));

		assertEquals(Camera.RESOLUTION_QQVGA, video.getGVMResolution(pId));
		assertEquals(Camera.COLORSPACE_RGB, video.getGVMColorSpace(pId));
		assertEquals(10, video.getGVMFrameRate(pId));

		System.out.println(" test resolutionToSizes methods");
		Dimension dim = new Dimension();
		video.resolutionToSizes(Camera.RESOLUTION_QQVGA, dim);
		assertEquals(160, dim.width);
		assertEquals(120, dim.height);
		video.resolutionToSizes(Camera.RESOLUTION_QVGA, dim);
		assertEquals(320, dim.width);
		assertEquals(240, dim.height);
		video.resolutionToSizes(Camera.RESOLUTION_VGA, dim);
		assertEquals(640, dim.width);
		assertEquals(480, dim.height);
		video.resolutionToSizes(Camera.RESOLUTION_VGA + 1, dim);
		assertEquals(-1, dim.width);
		assertEquals(-1, dim.height);

		assertEquals(Camera.RESOLUTION_QQVGA, video.sizesToResolution(160, 120));
		assertEquals(Camera.RESOLUTION_QVGA, video.sizesToResolution(320, 240));
		assertEquals(Camera.RESOLUTION_VGA, video.sizesToResolution(640, 480));
		assertEquals(-1, video.sizesToResolution(1280, 960));

		System.out.println(" test setParam/getParam methods");
		video.setParam(Camera.PARAM_AEC, 0);
		video.setParam(Camera.PARAM_AWC, 0);
		video.setParam(Camera.PARAM_AGC, 0);

		video.setParam(Camera.PARAM_Brightness, 64);
		video.setParam(Camera.PARAM_Contrast, 0);
		video.setParam(Camera.PARAM_Saturation, 0);
		video.setParam(Camera.PARAM_Hue, 0);
		video.setParam(Camera.PARAM_RedChroma, 0);
		video.setParam(Camera.PARAM_BlueChroma, 0);
		video.setParam(Camera.PARAM_Gain, 0);
		video.setParam(Camera.PARAM_HFlip, 0);
		video.setParam(Camera.PARAM_VFlip, 0);
		video.setParam(Camera.PARAM_CorrectionLensX, 0);
		video.setParam(Camera.PARAM_CorrectionLensY, 0);
		video.setParam(Camera.PARAM_Exposure, 0);
		video.setParam(Camera.PARAM_ExposureCorrection, 0);
		video.setParam(Camera.PARAM_FPS, 30);

		assertEquals(0, video.getParam(Camera.PARAM_AEC));
		assertEquals(0, video.getParam(Camera.PARAM_AWC));
		assertEquals(0, video.getParam(Camera.PARAM_AGC));

		assertEquals(64, video.getParam(Camera.PARAM_Brightness));
		assertEquals(0, video.getParam(Camera.PARAM_Contrast));
		assertEquals(0, video.getParam(Camera.PARAM_Saturation));
		assertEquals(0, video.getParam(Camera.PARAM_Hue));
		assertEquals(0, video.getParam(Camera.PARAM_RedChroma));
		assertEquals(0, video.getParam(Camera.PARAM_BlueChroma));
		assertEquals(0, video.getParam(Camera.PARAM_Gain));
		assertEquals(0, video.getParam(Camera.PARAM_HFlip));
		assertEquals(0, video.getParam(Camera.PARAM_VFlip));
		assertEquals(0, video.getParam(Camera.PARAM_CorrectionLensX));
		assertEquals(0, video.getParam(Camera.PARAM_CorrectionLensY));
		assertEquals(0, video.getParam(Camera.PARAM_Exposure));
		assertEquals(0, video.getParam(Camera.PARAM_ExposureCorrection));
		assertEquals(30, video.getParam(Camera.PARAM_FPS));

		video.setParam(Camera.PARAM_Resolution, Camera.RESOLUTION_VGA);
		assertEquals(Camera.RESOLUTION_VGA, video
				.getParam(Camera.PARAM_Resolution));

		video.setParam(Camera.PARAM_Resolution, Camera.RESOLUTION_QVGA);
		assertEquals(Camera.RESOLUTION_QVGA, video
				.getParam(Camera.PARAM_Resolution));

		video.setParam(Camera.PARAM_CameraSelect, Camera.CAMERA_SELECT_BOTTOM);
		assertEquals(Camera.CAMERA_SELECT_BOTTOM, video
				.getParam(Camera.PARAM_CameraSelect));

		video.unRegister(pId);
		System.out.println("end testVideo1.");
	}

	public void testGetDirectRawImageLocal() throws Exception {
		System.out.println("begin testGetDirectRawImageLocal.");
		pId = video.register("testGetDirectRawImageLocal",
				Camera.RESOLUTION_QVGA, Camera.COLORSPACE_YUV422Interlaced, 30);
		assertNotNull(pId);
		assertFalse(pId.isEmpty());

		JALImage image = new JALImage();
		assertTrue(video.getDirectRawImageLocal(pId, image) != 0);

		System.out.println("  checking a image....");
		assertEquals(320, image.getWidth());
		assertEquals(240, image.getHeight());
		assertEquals(Camera.COLORSPACE_YUV422Interlaced, image.getColorSpace());
		assertEquals(2, image.getNbLayers());
		System.out.println("timestamp:" + image.getTimestamp());
		ByteBuffer buf = image.getData();
		assertNotNull(buf);

		assertEquals(320 * 240 * 2, buf.capacity());
		assertEquals(320 * 240 * 2, buf.remaining());
		assertEquals(0, buf.position());

		assertFalse(buf.get() == 0 && buf.get() == 0 && buf.get() == 0);

		try {
			StringBuilder path = new StringBuilder(System
					.getProperty("java.io.tmpdir"));
			path.append("/" + getName() + System.currentTimeMillis() + ".img");
			OutputStream os = new FileOutputStream(path.toString());
			byte[] b = new byte[4096];
			while (buf.hasRemaining()) {
				int len = Math.min(4096, buf.remaining());
				buf.get(b, 0, len);
				os.write(b, 0, len);
			}
			os.close();
		} catch (Exception e) {
		}

		assertEquals(1, video.releaseDirectRawImage(pId));

		video.unRegister(pId);
	}

	public void testCameraSelect() throws Exception {
		pId = video.register("testCameraSelect", Camera.RESOLUTION_QVGA,
				Camera.COLORSPACE_YUV422Interlaced, 30);
		assertNotNull(pId);
		assertFalse(pId.isEmpty());
		video.setParam(Camera.PARAM_CameraSelect, Camera.CAMERA_SELECT_BOTTOM);
		video.unRegister(pId);
	}
}
