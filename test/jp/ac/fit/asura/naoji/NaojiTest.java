/*
 * 作成日: 2009/03/21
 */
package jp.ac.fit.asura.naoji;

import jp.ac.fit.asura.naoji.jal.JALMotion;
import jp.ac.fit.asura.naoji.jal.JDCM;
import jp.ac.fit.asura.naoji.jal.JDCM.MergeType;
import jp.ac.fit.asura.naoji.robots.NaoV3R.InterpolationType;
import jp.ac.fit.asura.naoji.robots.NaoV3R.Joint;

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
	private JDCM dcm;
	private int bodyAliasId;

	public void init(NaojiContext context) {
		System.err.println("NaojiTest init called.");
		this.context = context;
		motion = context.getParentBroker().createJALMotion();
		dcm = context.getParentBroker().createJDCM();

		String[] joints = { "LShoulderPitch/Position/Actuator/Value",
				"LShoulderRoll/Position/Actuator/Value",
				"LElbowYaw/Position/Actuator/Value",
				"LElbowRoll/Position/Actuator/Value",
				"LHipYawPitch/Position/Actuator/Value",
				"LHipRoll/Position/Actuator/Value",
				"LHipPitch/Position/Actuator/Value",
				"LKneePitch/Position/Actuator/Value",
				"LAnklePitch/Position/Actuator/Value",
				"LAnkleRoll/Position/Actuator/Value",
				"RHipYawPitch/Position/Actuator/Value",
				"RHipRoll/Position/Actuator/Value",
				"RHipPitch/Position/Actuator/Value",
				"RKneePitch/Position/Actuator/Value",
				"RAnklePitch/Position/Actuator/Value",
				"RAnkleRoll/Position/Actuator/Value",
				"RShoulderPitch/Position/Actuator/Value",
				"RShoulderRoll/Position/Actuator/Value",
				"RElbowYaw/Position/Actuator/Value",
				"RElbowRoll/Position/Actuator/Value" };
		bodyAliasId = dcm.createAlias(joints);

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
		mainThread.start();
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

		int taskId = motion.gotoBodyStiffness(0.25f, 0.5f,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);

		while (isActive) {
			try {
				Thread.sleep(10);

				if (frame < 10) {
					float headYaw = motion.getAngle(Joint.HeadYaw.getId());

					if (frame % 100 == 0)
						System.out.println("frame " + frame + " HeadYaw:"
								+ headYaw);

					taskId = motion.gotoAngle(Joint.HeadYaw.getId(),
							(float) Math.sin(Math.toRadians(frame)), 0.125f, 1);
					motion.wait(taskId, 10000);
				} else if (frame == 10) {
					taskId = motion.setTimeSeparate(MOTION_TEST1_ANGLES,
							MOTION_TEST1_DURATIONS, InterpolationType.LINEAR
									.getId());
					motion.wait(taskId, 10000);
				} else if (frame == 11) {
					Thread.sleep(5000);
					dcm.setTimeSeparate(bodyAliasId, MergeType.ClearAll,
							MOTION_TEST1_ANGLES, MOTION_TEST1_DURATIONS);
					Thread.sleep(10000);
				} else {
					frame = 0;
				}
				frame++;
			} catch (InterruptedException e) {
				isActive = false;
				assert false;
			}
		}
		motion.gotoBodyStiffness(0.0f, 0.5f, InterpolationType.LINEAR.getId());
	}

	static final float[] MOTION_TEST1_ANGLES = { //
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			//
			1.57f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.57f, 0, 0, 0,
			//
			-1.57f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1.57f, 0, 0,
			0,
			//
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	};
	static final int[] MOTION_TEST1_DURATIONS = { 2500, 2500, 2500, 2500 };
}
