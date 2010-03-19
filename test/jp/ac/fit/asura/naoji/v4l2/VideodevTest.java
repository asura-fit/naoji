/*
 * 作成日: 2009/04/01
 */
package jp.ac.fit.asura.naoji.v4l2;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;

import jp.ac.fit.asura.naoji.Naoji;
import jp.ac.fit.asura.naoji.NaojiContext;
import jp.ac.fit.asura.naoji.NaojiFactory;
import junit.framework.TestCase;
import junit.textui.TestRunner;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class VideodevTest extends TestCase {
	private Videodev dev;

	public static class Factory implements NaojiFactory {
		public Naoji create() {
			return new NaojiImpl();
		}
	}

	private static class NaojiImpl implements Naoji {
		Thread mainThread;

		public NaojiImpl() {
		}

		public void init(NaojiContext context) {
			mainThread = new Thread() {
				public void run() {
					try {
						Thread.sleep(10000);
						TestRunner.run(VideodevTest.class);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			};
		}

		public void exit() {
		}

		public void start() {
			System.err.println("VideodevTest start called.");
			mainThread.start();
		}

		public void stop() {
			System.err.println("VideodevTest stop called.");
			try {
				mainThread.join();
			} catch (InterruptedException e) {
				e.printStackTrace();
				assert false;
			}
		}
	}

	public static Videodev createDevice() throws IOException {
		String device = System.getProperty("jp.ac.fit.asura.naoji.v4l2.DEVICE");
		if (device == null)
			device = "/dev/video0";
		return new Videodev(device);
	}

	public void testSuite() throws Exception {
		int res;

		// init camera
		System.out.println("init camera");
		res = dev.setControl(V4L2Control.V4L2_CID_CAM_INIT, 0);
		assertEquals(0, res);

		// set format
		System.out.println("set format");
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.setWidth(320);
		format.setHeight(240);
		format.setPixelFormat(V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode());
		res = dev.setFormat(format);
		assertEquals(0, res);

		//
		System.out.println("set fps");
		res = dev.setFPS(30);
		assertEquals(0, res);

		// NaoQi 1.3.17以降では3以上でないと使えない?
		System.out.println("init buffers(3)");
		res = dev.init(3);
		assertEquals("Result:" + res, 3, res);

		System.out.println("start");
		res = dev.start();
		assertEquals(0, res);

		for (int i = 0; i < 10; i++) {
			// retrieves
			System.out.println("_testRetrieveImage " + i);
			_testRetrieveImage(dev, false);
		}

		System.out.println("_testRetrieveImageLoop");
		_testRetrieveImageLoop(dev);

		System.out.println("stop");
		res = dev.stop();
		assertEquals(0, res);
		System.out.println("end");
	}

	public void testSizeFormat() throws Exception {
		int res;
		System.out.println("testSizeFormat");

		// Test QVGA
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.setWidth(320);
		format.setHeight(240);
		format.setPixelFormat(V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode());
		res = dev.setFormat(format);
		assertEquals(0, res);

		// Test get format
		V4L2PixelFormat format2 = new V4L2PixelFormat();
		res = dev.getFormat(format2);
		assertEquals(0, res);
		assertEquals(format.getWidth(), format2.getWidth());
		assertEquals(format.getHeight(), format2.getHeight());
		assertEquals(format.getPixelFormat(), format2.getPixelFormat());

		// Test VGA
		format = new V4L2PixelFormat();
		format.setWidth(640);
		format.setHeight(480);
		format.setPixelFormat(V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode());
		res = dev.setFormat(format);
		assertEquals(0, res);

		// Test QCIF
		format = new V4L2PixelFormat();
		format.setWidth(176);
		format.setHeight(144);
		format.setPixelFormat(V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode());
		res = dev.setFormat(format);
		assertEquals(0, res);

		// Test CIF
		format = new V4L2PixelFormat();
		format.setWidth(352);
		format.setHeight(288);
		format.setPixelFormat(V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode());
		res = dev.setFormat(format);
		assertEquals(0, res);
	}

	public void testPixelFormatYUYV() throws Exception {
		int res;

		// Nao実機で使用できる.
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.setWidth(640);
		format.setHeight(480);
		format.setPixelFormat(V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode());
		res = dev.setFormat(format);
		assertEquals(0, res);
	}

	public void testPixelFormatUYVY() throws Exception {
		int res;

		// Nao実機では使えない.
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.setWidth(640);
		format.setHeight(480);
		format.setPixelFormat(V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_UYVY
				.getFourccCode());
		res = dev.setFormat(format);
		assertEquals("This test will fail on NaoV3R.", -1, res);
	}

	public void testPixelFormatYUV422P() throws Exception {
		int res;

		// Nao実機では使えない.
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.setWidth(640);
		format.setHeight(480);
		format.setPixelFormat(V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUV422P
				.getFourccCode());
		res = dev.setFormat(format);
		assertEquals("This test will fail on NaoV3R.", -1, res);
	}

	public void testFPS() throws Exception {
		int res;
		System.out.println("testFPS");
		res = dev.setFPS(10);
		assertEquals(0, res);
		res = dev.setFPS(15);
		assertEquals(0, res);
		res = dev.setFPS(30);
		assertEquals(0, res);
	}

	//
	// public void testToControlId() throws Exception {
	// assertEquals(0x00980900, dev
	// .toControlId(V4L2Control.V4L2_CID_BRIGHTNESS));
	// }

	public void testControls() {
		System.out.println("testControls");
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_AUTOEXPOSURE));
		assertTrue(dev
				.isSupportedControl(V4L2Control.V4L2_CID_AUTO_WHITE_BALANCE));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_AUTOGAIN));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_BLUE_BALANCE));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_BRIGHTNESS));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_CAM_INIT));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_CONTRAST));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_EXPOSURE));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_GAIN));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_HCENTER));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_HFLIP));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_HUE));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_RED_BALANCE));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_SATURATION));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_VCENTER));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_VFLIP));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_AEC_ALGORITHM));
		assertTrue(dev
				.isSupportedControl(V4L2Control.V4L2_CID_EXPOSURE_CORRECTION));
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_SHARPNESS));
	}

	public static void _testRetrieveImage(Videodev video, boolean doSaveImage)
			throws IOException {
		V4L2Buffer buffer = new V4L2Buffer();
		long current = System.currentTimeMillis();
		int res = video.retrieveImage(buffer);
		assertEquals(0, res);

		assertTrue("invalid length:" + buffer.getLength(),
				buffer.getLength() > 0);
		assertTrue("invalid timestamp:" + buffer.getTimestamp(), buffer
				.getTimestamp() > 0);

		ByteBuffer bb = buffer.getBuffer();
		assertNotNull(bb);
		assertTrue(bb.isDirect());
		assertEquals(0, bb.position());
		assertEquals(buffer.getLength(), bb.remaining());

		System.out.println("Retrieve image.");
		System.out.println("  length:" + buffer.getLength());
		System.out.println("  timestamp:" + buffer.getTimestamp());
		System.out.println("  used time:"
				+ (current - buffer.getTimestamp() / 1000L));

		assertEquals(current, buffer.getTimestamp() / 1000L, 1000L);

		if (doSaveImage) {
			OutputStream os = new FileOutputStream("image"
					+ buffer.getTimestamp() + ".raw");
			byte[] buf = new byte[4096];
			while (bb.hasRemaining()) {
				int len = buf.length;
				if (bb.remaining() < buf.length)
					len = bb.remaining();
				buffer.getBuffer().get(buf, 0, len);
				os.write(buf, 0, len);
			}
			os.close();
		}

		video.disposeImage(buffer);
	}

	public static void _testRetrieveImageLoop(Videodev video)
			throws IOException {
		V4L2Buffer buffer = new V4L2Buffer();

		long beginTime = System.nanoTime();
		for (int i = 0; i < 100; i++) {
			video.retrieveImage(buffer);
			video.disposeImage(buffer);
		}
		long time2 = System.nanoTime();
		for (int i = 0; i < 100; i++) {
			video.retrieveImage(buffer);
			video.disposeImage(buffer);
		}
		long time3 = System.nanoTime();

		System.out.println(" Loop time1:" + (time2 - beginTime) / 1.0e6 / 100);
		System.out.println(" Loop time2:" + (time3 - time2) / 1.0e6 / 100);
	}

	protected void setUp() throws Exception {
		dev = createDevice();
	}

	protected void tearDown() throws Exception {
		dev.dispose();
	}
}
