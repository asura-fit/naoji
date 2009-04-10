/*
 * 作成日: 2009/04/01
 */
package jp.ac.fit.asura.naoji.v4l2;

import java.io.IOException;
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

	private Videodev createDevice() throws IOException {
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
			V4L2Buffer buffer = new V4L2Buffer();
			res = dev.retrieveImage(buffer);
			assertEquals(0, res);

			assertTrue("invalid length:" + buffer.getLength(), buffer
					.getLength() > 0);
			assertTrue("invalid timestamp:" + buffer.getTimestamp(), buffer
					.getTimestamp() > 0);

			ByteBuffer bb = buffer.getBuffer();
			assertNotNull(bb);
			assertTrue(bb.isDirect());
			assertEquals(0, bb.position());
			assertEquals(buffer.getLength(), bb.remaining());

			System.out.println("Retrieve image.");
			System.out.println("  index:" + buffer.getIndex());
			System.out.println("  length:" + buffer.getLength());
			System.out.println("  timestamp:" + buffer.getTimestamp());

			assertEquals(System.currentTimeMillis() * 1000, buffer
					.getTimestamp(), 100 * 1e3);
			dev.disposeImage(buffer);
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
		assertEquals(0, res);
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
		assertEquals(0, res);
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

	protected void setUp() throws Exception {
		dev = createDevice();
	}

	protected void tearDown() throws Exception {
		dev.dispose();
	}
}
