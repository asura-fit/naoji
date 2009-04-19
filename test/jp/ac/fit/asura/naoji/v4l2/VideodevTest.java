/*
 * 作成日: 2009/04/01
 */
package jp.ac.fit.asura.naoji.v4l2;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;

import junit.framework.TestCase;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class VideodevTest extends TestCase {
	private Videodev dev;

	public static Videodev createDevice() throws IOException {
		String device = System.getProperty("jp.ac.fit.asura.naoji.v4l2.DEVICE");
		if (device == null)
			device = "/dev/video0";
		return new Videodev(device);
	}

	public void testSuite() throws Exception {
		int res;

		// set format
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.width = 640;
		format.height = 480;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals(0, res);

		//
		res = dev.setFPS(30);
		assertEquals(0, res);

		res = dev.init();
		assertTrue("Result:" + res, res > 0);

		res = dev.start();
		assertEquals(0, res);

		for (int i = 0; i < 10; i++) {
			// retrieves
			_testRetrieveImage(dev, false);
		}

		res = dev.stop();
		assertEquals(0, res);
	}

	public void testSizeFormat() throws Exception {
		int res;

		// Test QVGA
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.width = 320;
		format.height = 240;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals(0, res);

		// Test get format
		V4L2PixelFormat format2 = new V4L2PixelFormat();
		res = dev.getFormat(format2);
		assertEquals(0, res);
		assertEquals(format.width, format2.width);
		assertEquals(format.height, format2.height);
		assertEquals(format.pixelFormat, format2.pixelFormat);

		// Test VGA
		format = new V4L2PixelFormat();
		format.width = 640;
		format.height = 480;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals(0, res);

		// Test QCIF
		format = new V4L2PixelFormat();
		format.width = 176;
		format.height = 144;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals(0, res);

		// Test CIF
		format = new V4L2PixelFormat();
		format.width = 352;
		format.height = 288;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals(0, res);
	}

	public void testPixelFormatYUYV() throws Exception {
		int res;

		// Nao実機で使用できる.
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.width = 640;
		format.height = 480;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals(0, res);
	}

	public void testPixelFormatUYVY() throws Exception {
		int res;

		// Nao実機では使えない.
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.width = 640;
		format.height = 480;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_UYVY
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals("This test will fail on NaoV3R.", 0, res);
	}

	public void testPixelFormatYUV422P() throws Exception {
		int res;

		// Nao実機では使えない.
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.width = 640;
		format.height = 480;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUV422P
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals("This test will fail on NaoV3R.", 0, res);
	}

	public void testFPS() throws Exception {
		int res;
		res = dev.setFPS(10);
		assertEquals(0, res);
		res = dev.setFPS(15);
		assertEquals(0, res);
		res = dev.setFPS(30);
		assertEquals(0, res);
	}

	public void testToControlId() throws Exception {
		assertEquals(0x00980900, dev
				.toControlId(V4L2Control.V4L2_CID_BRIGHTNESS));
	}

	public void testControls() {
		assertTrue(dev.isSupportedControl(V4L2Control.V4L2_CID_AUDIO_MUTE));
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
				+ (current - buffer.getTimestamp() / 1e3));

		assertEquals(current, buffer.getTimestamp() / 1e3, 1000);

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

	protected void setUp() throws Exception {
		dev = createDevice();
	}

	protected void tearDown() throws Exception {
		dev.dispose();
	}
}
