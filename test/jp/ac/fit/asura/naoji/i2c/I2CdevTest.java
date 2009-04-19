/*
 * 作成日: 2009/04/02
 */
package jp.ac.fit.asura.naoji.i2c;

import java.io.IOException;
import java.util.Random;

import jp.ac.fit.asura.naoji.robots.NaoV3R.Camera;
import junit.framework.TestCase;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class I2CdevTest extends TestCase {
	private I2Cdev dev;

	public static I2Cdev createDevice() throws IOException {
		String device = System.getProperty("jp.ac.fit.asura.naoji.i2c.DEVICE");
		if (device == null)
			device = "/dev/i2c-0";
		return new I2Cdev(device);
	}

	public void testSelectCamera() throws Exception {
		int res;

		res = dev.init();
		assertEquals(0, res);

		res = dev.getSelectedCamera();
		System.out.println("Current Camera:" + res);

		System.out.println("Select camera:" + Camera.BOTTOM);
		res = dev.selectCamera(Camera.BOTTOM.getId());
		assertEquals(0, res);

		res = dev.getSelectedCamera();
		System.out.println("Current Camera:" + res);
		assertEquals(Camera.BOTTOM.getId(), res);

		System.out.println("Select camera:" + Camera.TOP.getId());
		res = dev.selectCamera(Camera.TOP.getId());
		assertEquals(0, res);

		res = dev.getSelectedCamera();
		System.out.println("Current Camera:" + res);
		assertEquals(Camera.TOP.getId(), res);

		Camera camera = Camera.values()[new Random()
				.nextInt(Camera.values().length)];
		System.out.println("Select camera:" + camera);
		res = dev.selectCamera(camera.getId());
		assertEquals(0, res);
		res = dev.getSelectedCamera();
		System.out.println("Camera selected:" + res);
		assertEquals(camera.getId(), res);
	}

	protected void setUp() throws Exception {
		dev = createDevice();
	}

	protected void tearDown() throws Exception {
		dev.dispose();
	}
}
