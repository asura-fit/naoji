/*
 * 作成日: 2009/07/08
 */
package jp.ac.fit.asura.naoji.jal;

import java.awt.Dimension;
import java.nio.ByteBuffer;

import jp.ac.fit.asura.naoji.Naoji;
import jp.ac.fit.asura.naoji.NaojiContext;
import jp.ac.fit.asura.naoji.NaojiFactory;
import jp.ac.fit.asura.naoji.robots.NaoV3R;
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
		pId = video.register("testVideo1", NaoV3R.RESOLUTION_QVGA,
				NaoV3R.COLORSPACE_YUV422, 30);
		assertNotNull(pId);
		assertFalse(pId.isEmpty());

		assertEquals(NaoV3R.RESOLUTION_QVGA, video.getVIMColorSpace());
		assertEquals(NaoV3R.COLORSPACE_YUV422, video.getVIMColorSpace());
		assertEquals(30, video.getVIMFrameRate());

		assertEquals(NaoV3R.RESOLUTION_QVGA, video.getGVMColorSpace(pId));
		assertEquals(NaoV3R.COLORSPACE_YUV422, video.getGVMColorSpace(pId));
		assertEquals(30, video.getGVMFrameRate(pId));

		assertTrue(video.setResolution(pId, NaoV3R.RESOLUTION_QQVGA));
		assertTrue(video.setColorSpace(pId, NaoV3R.COLORSPACE_RGB));
		assertTrue(video.setFrameRate(pId, 10));

		assertEquals(NaoV3R.RESOLUTION_QQVGA, video.getGVMColorSpace(pId));
		assertEquals(NaoV3R.COLORSPACE_RGB, video.getGVMColorSpace(pId));
		assertEquals(10, video.getGVMFrameRate(pId));

		Dimension dim = new Dimension();
		video.resolutionToSizes(NaoV3R.RESOLUTION_QQVGA, dim);
		assertEquals(160, dim.width);
		assertEquals(120, dim.height);
		video.resolutionToSizes(NaoV3R.RESOLUTION_QVGA, dim);
		assertEquals(320, dim.width);
		assertEquals(240, dim.height);
		video.resolutionToSizes(NaoV3R.RESOLUTION_VGA, dim);
		assertEquals(640, dim.width);
		assertEquals(480, dim.height);
		video.resolutionToSizes(NaoV3R.RESOLUTION_VGA + 1, dim);
		assertEquals(-1, dim.width);
		assertEquals(-1, dim.height);

		assertEquals(NaoV3R.RESOLUTION_QQVGA, video.sizesToResolution(160, 120));
		assertEquals(NaoV3R.RESOLUTION_QVGA, video.sizesToResolution(320, 240));
		assertEquals(NaoV3R.RESOLUTION_VGA, video.sizesToResolution(640, 480));
		assertEquals(-1, video.sizesToResolution(1280, 960));

		video.unRegister(pId);
	}

	public void testGetDirectRawImageLocal() throws Exception {
		pId = video.register("testGetDirectRawImageLocal",
				NaoV3R.RESOLUTION_QVGA, NaoV3R.COLORSPACE_YUV422, 30);
		assertNotNull(pId);
		assertFalse(pId.isEmpty());

		JALImage image = new JALImage();
		assertTrue(video.getDirectRawImageLocal(pId, image) != 0);

		assertEquals(320, image.getWidth());
		assertEquals(240, image.getHeight());
		assertEquals(NaoV3R.COLORSPACE_YUV422, image.getColorSpace());
		assertEquals(2, image.getNbLayers());
		System.out.println("timestamp:" + image.timestamp);
		ByteBuffer buf = image.getData();
		assertNotNull(buf);

		assertEquals(320 * 240 * 2, buf.capacity());
		assertEquals(320 * 240 * 2, buf.remaining());
		assertEquals(0, buf.position());

		assertFalse(buf.get() == 0 && buf.get() == 0 && buf.get() == 0);

		assertEquals(1, video.releaseDirectRawImage(pId));

		video.unRegister(pId);
	}
}
