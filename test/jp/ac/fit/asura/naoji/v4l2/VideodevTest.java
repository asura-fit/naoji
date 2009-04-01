/*
 * 作成日: 2009/04/01
 */
package jp.ac.fit.asura.naoji.v4l2;

import java.io.IOException;

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
		format.width = 160;
		format.height = 120;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_UYVY
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals(0, res);

		//
		res = dev.setFPS(10);
		assertEquals(0, res);

		res = dev.init();
		assertTrue("Result:" + res, res > 0);

		res = dev.start();
		assertEquals(0, res);

		// retrieves

		res = dev.stop();
		assertEquals(0, res);

		dev.dispose();
	}

	public void testFormat() throws Exception {
		int res;
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.width = 160;
		format.height = 120;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_UYVY
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals(0, res);

		V4L2PixelFormat format2 = new V4L2PixelFormat();
		res = dev.getFormat(format2);
		assertEquals(0, res);
		assertEquals(format.width, format2.width);
		assertEquals(format.height, format2.height);
		assertEquals(format.pixelFormat, format2.pixelFormat);

		format = new V4L2PixelFormat();
		format.width = 320;
		format.height = 240;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_UYVY
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals(0, res);

		format = new V4L2PixelFormat();
		format.width = 640;
		format.height = 480;
		format.pixelFormat = V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_UYVY
				.getFourccCode();
		res = dev.setFormat(format);
		assertEquals(0, res);

		dev.dispose();
	}

	public void testFPS() throws Exception {
		int res;
		res = dev.setFPS(10);
		assertEquals(0, res);
		res = dev.setFPS(15);
		assertEquals(0, res);
		res = dev.setFPS(30);
		assertEquals(0, res);

		dev.dispose();
	}

	protected void setUp() throws Exception {
		dev = createDevice();
	}

	protected void tearDown() throws Exception {
		dev.dispose();
	}
}
