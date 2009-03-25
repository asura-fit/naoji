/*
 * 作成日: 2009/03/21
 */
package jp.ac.fit.asura.naoji;

import jp.ac.fit.asura.naoji.jal.JALMotion;
import jp.ac.fit.asura.naoji.robots.NaoV3RoboCupEdition;
import jp.ac.fit.asura.naoji.robots.NaoV3RoboCupEdition.Joint;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class NaojiTest implements Naoji {
	public static class Factory implements NaojiFactory {
		public Naoji create() {
			return new NaojiTest();
		}
	}

	Thread mainThread;
	private NaojiContext context;
	private boolean isActive;
	private JALMotion motion;

	public void init(NaojiContext context) {
		System.err.println("NaojiTest init called.");
		this.context = context;
		motion = context.getParentBroker().createJALMotion();
		mainThread = new Thread() {
			public void run() {
				NaojiTest.this.run();
			}
		};
	}

	public void exit() {
	}

	public void start() {
		System.err.println("NaojiTest start called.");
		assert !isActive;
		assert !mainThread.isAlive();
		isActive = true;
		mainThread.run();

	}

	public void stop() {
		System.err.println("NaojiTest stop called.");
		assert isActive;
		assert mainThread.isAlive();
		isActive = false;
		try {
			mainThread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
			assert false;
		}
	}

	protected void run() {
		System.err.println("NaojiTest run called.");
		int frame = 0;
		while (isActive) {
			try {
				Thread.sleep(100);
				float headYaw = motion.getAngle(Joint.HeadYaw.getId());
				System.out.println("HeadYaw:" + headYaw);

				motion.gotoAngle(Joint.HeadYaw.getId(), (float) Math.sin(Math
						.toRadians(frame)), 0.125f, 1);
				frame++;
			} catch (InterruptedException e) {
				isActive = false;
				assert false;
			}
		}
	}
}
