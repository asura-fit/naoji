/*
 * 作成日: 2009/04/19
 */
package jp.ac.fit.asura.naoji;

import java.io.IOException;

import jp.ac.fit.asura.naoji.i2c.I2Cdev;
import jp.ac.fit.asura.naoji.i2c.I2CdevTest;
import jp.ac.fit.asura.naoji.robots.NaoV3R.Camera;
import jp.ac.fit.asura.naoji.v4l2.V4L2Control;
import jp.ac.fit.asura.naoji.v4l2.V4L2PixelFormat;
import jp.ac.fit.asura.naoji.v4l2.Videodev;
import jp.ac.fit.asura.naoji.v4l2.VideodevTest;
import junit.framework.TestCase;

/**
 * @author sey
 *
 * @version $Id: $
 *
 */
public class CameraTest extends TestCase {
	private Videodev video;
	private I2Cdev i2c;

	public void testSwitch() throws Exception {
		int res;

		res = i2c.init();
		assertEquals(0, res);

		res = i2c.getSelectedCamera();
		System.out.println("Current Camera:" + res);

		System.out.println("Select camera:" + Camera.TOP);
		res = i2c.selectCamera(Camera.TOP.getId());
		assertEquals(0, res);

		video.setControl(V4L2Control.V4L2_CID_CAM_INIT, 0);
		video.setControl(V4L2Control.V4L2_CID_HFLIP, 1);
		video.setControl(V4L2Control.V4L2_CID_VFLIP, 1);

		// set format
		V4L2PixelFormat format = new V4L2PixelFormat();
		format.setWidth(320);
		format.setHeight(240);
		format.setPixelFormat(V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode());
		res = video.setFormat(format);
		assertEquals(0, res);

		//
		res = video.setFPS(30);
		assertEquals(0, res);

		res = video.init();
		assertTrue("Result:" + res, res > 0);

		res = video.start();
		assertEquals(0, res);
		for (int i = 0; i < 3; i++) {
			VideodevTest._testRetrieveImage(video, true);
		}

		_testSwitchCamera2(Camera.BOTTOM);

		for (int i = 0; i < 3; i++) {
			VideodevTest._testRetrieveImage(video, true);
		}

		_testSwitchCamera1(Camera.TOP);
		for (int i = 0; i < 10; i++)
			VideodevTest._testRetrieveImage(video, false);
		_testSwitchCamera1(Camera.BOTTOM);
		for (int i = 0; i < 10; i++)
			VideodevTest._testRetrieveImage(video, false);
		_testSwitchCamera2(Camera.TOP);
		for (int i = 0; i < 10; i++)
			VideodevTest._testRetrieveImage(video, false);
		_testSwitchCamera2(Camera.BOTTOM);
		for (int i = 0; i < 10; i++)
			VideodevTest._testRetrieveImage(video, false);
		_testSwitchCamera3(Camera.TOP);
		for (int i = 0; i < 10; i++)
			VideodevTest._testRetrieveImage(video, false);
		_testSwitchCamera3(Camera.BOTTOM);
		for (int i = 0; i < 10; i++)
			VideodevTest._testRetrieveImage(video, false);

		res = video.stop();
		assertEquals(0, res);
	}

	/*
	 * もっとも慎重なカメラの切り替え. 3秒ぐらいかかる.
	 *
	 * それぞれのカメラでパラメータの設定(ホワイトバランスなど)が必要.
	 */
	private void _testSwitchCamera1(Camera camera) throws IOException {
		long beforeswitch = System.nanoTime();
		System.out.println("Switching camera...");

		int res = video.stop();
		assertEquals(0, res);

		video.dispose();

		System.out.println("Select camera:" + camera);
		i2c.selectCamera(camera.getId());

		video = VideodevTest.createDevice();

		video.setControl(V4L2Control.V4L2_CID_CAM_INIT, 0);

		V4L2PixelFormat format = new V4L2PixelFormat();
		format.setWidth(320);
		format.setHeight(240);
		format.setPixelFormat(V4L2PixelFormat.PixelFormat.V4L2_PIX_FMT_YUYV
				.getFourccCode());
		res = video.setFormat(format);
		assertEquals(0, res);

		//
		res = video.setFPS(30);
		assertEquals(0, res);

		res = video.init();
		assertTrue("Result:" + res, res > 0);

		res = video.start();
		assertEquals(0, res);

		long afterswitch = System.nanoTime();
		System.out.println("Camera switched. time:"
				+ (afterswitch - beforeswitch) / 1e6 + " [ms]");

	}

	/*
	 * かなり手を抜いたカメラの切り替え. 10msぐらいかかる.
	 *
	 * それぞれのカメラでパラメータの設定(ホワイトバランスなど)が必要.
	 */
	private void _testSwitchCamera2(Camera camera) throws IOException {
		long beforeswitch = System.nanoTime();
		System.out.println("Switching camera...");

		int res = video.stop();
		assertEquals(0, res);

		System.out.println("Select camera:" + camera);
		i2c.selectCamera(camera.getId());

		res = video.start();
		assertEquals(0, res);

		long afterswitch = System.nanoTime();
		System.out.println("Camera switched. time:"
				+ (afterswitch - beforeswitch) / 1e6 + " [ms]");
	}

	/*
	 * 手を抜きすぎなカメラの切り替え. 5msぐらいかかる.
	 *
	 * それぞれのカメラでパラメータの設定(ホワイトバランスなど)が必要.
	 *
	 * 切り替え直後の数フレームは切り替える前のカメラの画像がきたり、画像が乱れたりする.
	 */
	private void _testSwitchCamera3(Camera camera) throws IOException {
		long beforeswitch = System.nanoTime();
		System.out.println("Switching camera...");

		System.out.println("Select camera:" + camera);
		i2c.selectCamera(camera.getId());

		long afterswitch = System.nanoTime();
		System.out.println("Camera switched. " + camera + " time:"
				+ (afterswitch - beforeswitch) / 1e6 + " [ms]");
	}

	@Override
	protected void setUp() throws Exception {
		video = VideodevTest.createDevice();
		i2c = I2CdevTest.createDevice();
	}

	@Override
	protected void tearDown() throws Exception {
		video.dispose();
		i2c.dispose();
	}
}
