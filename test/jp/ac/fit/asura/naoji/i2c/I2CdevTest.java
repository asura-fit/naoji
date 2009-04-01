/*
 * 作成日: 2009/04/02
 */
package jp.ac.fit.asura.naoji.i2c;

import java.io.IOException;

import junit.framework.TestCase;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class I2CdevTest extends TestCase {
	private I2Cdev dev;

	private I2Cdev createDevice() throws IOException {
		String device = System.getProperty("jp.ac.fit.asura.naoji.i2c.DEVICE");
		if (device == null)
			device = "/dev/i2c-0";
		return new I2Cdev(device);
	}

	public void testSuite() throws Exception {
		int res;

		res = dev.init();
		assertEquals(0, res);

		res = dev.selectCamera(1);
		assertEquals(0, res);

		res = dev.getSelectedCamera();
		assertEquals(1, res);

		res = dev.selectCamera(0);
		assertEquals(0, res);

		res = dev.getSelectedCamera();
		assertEquals(0, res);
	}

	protected void setUp() throws Exception {
		dev = createDevice();
	}

	protected void tearDown() throws Exception {
		dev.dispose();
	}
}
