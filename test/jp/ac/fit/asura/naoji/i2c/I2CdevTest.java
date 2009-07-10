/*
 * 作成日: 2009/04/02
 */
package jp.ac.fit.asura.naoji.i2c;

import java.io.IOException;

import jp.ac.fit.asura.naoji.robots.NaoV3R;
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

		System.out.println("Select camera:" + NaoV3R.I2C_CAMERA_BOTTOM);
		res = dev.selectCamera(NaoV3R.I2C_CAMERA_BOTTOM);
		assertEquals(0, res);

		res = dev.getSelectedCamera();
		System.out.println("Current Camera:" + res);
		assertEquals(NaoV3R.I2C_CAMERA_BOTTOM, res);

		System.out.println("Select camera:" + NaoV3R.I2C_CAMERA_TOP);
		res = dev.selectCamera(NaoV3R.I2C_CAMERA_TOP);
		assertEquals(0, res);

		res = dev.getSelectedCamera();
		System.out.println("Current Camera:" + res);
		assertEquals(NaoV3R.I2C_CAMERA_TOP, res);
	}

	protected void setUp() throws Exception {
		dev = createDevice();
	}

	protected void tearDown() throws Exception {
		dev.dispose();
	}
}
