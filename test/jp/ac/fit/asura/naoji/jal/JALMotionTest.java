/*
 * 作成日: 2009/06/30
 */
package jp.ac.fit.asura.naoji.jal;

import java.util.Arrays;

import jp.ac.fit.asura.naoji.robots.NaoV3R;
import jp.ac.fit.asura.naoji.robots.NaoV3R.Chain;
import jp.ac.fit.asura.naoji.robots.NaoV3R.InterpolationType;
import jp.ac.fit.asura.naoji.robots.NaoV3R.Joint;
import junit.framework.TestCase;

/**
 * @author sey
 *
 * @version $Id: $
 *
 */
public class JALMotionTest extends TestCase {
	JALMotion motion;

	/**
	 *
	 */
	public JALMotionTest() {
	}

	protected void setUp() throws Exception {
		motion.setBodyStiffness(0.35f);
		super.setUp();
	}

	protected void tearDown() throws Exception {
		super.tearDown();
		motion.setBodyStiffness(0.0f);
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#isDefinedJoint(int)}
	 * のためのテスト・メソッド。
	 */
	public void testIsDefinedJoint() {
		for (Joint j : NaoV3R.Joint.values())
			assertTrue(j.name(), motion.isDefinedJoint(j.getId()));
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#setTimeSeparate(float[], int[], int)}
	 * のためのテスト・メソッド。
	 */
	public void testSetTimeSeparate() {
		float[] MOTION_TEST1_ANGLES = { //
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0,
				//
				1.57f, 0.25f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.57f,
				-0.25f, 0, 0,
				//
				-1.57f, -0.25f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				-1.57f, 0.25f, 0, 0,
				//
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

		};
		int[] MOTION_TEST1_DURATIONS = { 500, 2000, 3500, 5000 };
		System.out.println("begin setTimeSeparate()");
		int taskId = motion.setTimeSeparate(MOTION_TEST1_ANGLES,
				MOTION_TEST1_DURATIONS, InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);
		System.out.println("end setTimeSeparate()");
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#isRunning(int)},
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#wait(int, int)} のためのテスト・メソッド。
	 */
	public void testIsRunningAndWait() {
		int taskId = motion.gotoAngle(Joint.HeadPitch.getId(), 0.5f, 1.0f,
				InterpolationType.LINEAR.getId());
		assertTrue(motion.isRunning(taskId));
		motion.wait(taskId, 200);
		assertTrue(motion.isRunning(taskId));
		motion.wait(taskId, 0);
		assertFalse(motion.isRunning(taskId));
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#changeCom(float, float, float)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getCom(int, float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#gotoCom(float, float, float, float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#setCom(float, float, float)}
	 * のためのテスト・メソッド。
	 */
	public void testCom() {
		int taskId;
		taskId = motion.gotoCom(0, 0, 0.25f, 2.5f, InterpolationType.LINEAR
				.getId());
		motion.wait(taskId, 0);
		float[] com = new float[3];
		// SPACE_BODY = 0, SPACE_SUPPORT_LEG = 1
		motion.getCom(1, com);
		assertEquals(0, com[0], 0.03125f);
		assertEquals(0, com[1], 0.03125f);
		assertEquals(0.25f, com[2], 0.03125f);

		taskId = motion.changeCom(0.05f, 0, 0);
		motion.wait(taskId, 0);
		taskId = motion.changeCom(0, 0.05f, 0);
		motion.wait(taskId, 0);
		taskId = motion.changeCom(0, 0, 0.05f);
		motion.wait(taskId, 0);

		motion.setCom(0, 0, 0.25f);
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#changePosition(int, int, float, float, float, float, float, float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getPosition(int, int, float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getSensorPosition(String, int, float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#gotoPosition(int, int, float, float, float, float, float, float, int, float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#setPosition(int, int, float, float, float, float, float, float, int)}
	 *
	 * のためのテスト・メソッド。
	 */
	public void testPosition() {
		int taskId;

		float[] pos = new float[6];
		motion.getSensorPosition("CameraTop", NaoV3R.SPACE_BODY, pos);
		assertTrue(pos[0] != 0);

		motion.getPosition(Chain.RArm.getId(), NaoV3R.SPACE_BODY, pos);
		assertTrue(pos[0] != 0);

		taskId = motion.changePosition(Chain.RArm.getId(),
				NaoV3R.SPACE_SUPPORT_LEG, 0.5f, 0, 0, 0, 0, 0,
				NaoV3R.AXIS_MASK_VEL);
		motion.wait(taskId, 0);

		taskId = motion.gotoPosition(Chain.RArm.getId(),
				NaoV3R.SPACE_SUPPORT_LEG, pos[0], pos[1], pos[2], pos[3],
				pos[4], pos[5], NaoV3R.AXIS_MASK_VEL, 0.5f,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);

		motion.setPosition(Chain.RArm.getId(), NaoV3R.SPACE_SUPPORT_LEG,
				pos[0], pos[1], pos[2], pos[3], pos[4], pos[5],
				NaoV3R.AXIS_MASK_VEL);
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#doMove(int[], float[][], float[][], int)}
	 * のためのテスト・メソッド。
	 */
	public void testDoMove() {
		fail("まだ実装されていません");
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getBalanceMode()}
	 * のためのテスト・メソッド。
	 */
	public void testBalanceMode() {
		motion.setBalanceMode(NaoV3R.BALANCE_MODE_AUTO);
		assertEquals(NaoV3R.BALANCE_MODE_AUTO, motion.getBalanceMode());

		motion.setBalanceMode(NaoV3R.BALANCE_MODE_OFF);
		assertEquals(NaoV3R.BALANCE_MODE_OFF, motion.getBalanceMode());
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getBodyJointNames()}
	 * のためのテスト・メソッド。
	 */
	public void testGetBodyJointNames() {
		String[] names = motion.getBodyJointNames();
		assertTrue(Arrays.equals(new String[] { "HeadYaw", "HeadPitch",
				"LShoulderPitch", "LShoulderRoll", "LElbowYaw", "LElbowRoll",
				"LHipYawPitch", "LHipRoll", "LHipPitch", "LKneePitch",
				"LAnklePitch", "LAnkleRoll", "RHipYawPitch", "RHipRoll",
				"RHipPitch", "RKneePitch", "RAnklePitch", "RAnkleRoll",
				"RShoulderPitch", "RShoulderRoll", "RElbowYaw", "RElbowRoll" },
				names));
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getBodyLimits(float[], float[], float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getChainLimits(int, float[], float[], float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getJointLimits(int, float[])}
	 * のためのテスト・メソッド。
	 */
	public void testLimits() {
		float[] minAngle1 = new float[22];
		float[] maxAngle1 = new float[22];
		float[] maxChangePerCycle1 = new float[22];
		motion.getBodyLimits(minAngle1, maxAngle1, maxChangePerCycle1);
		System.out.println("getBodyLimits minAngle: "
				+ Arrays.toString(minAngle1) + " maxAngle: "
				+ Arrays.toString(maxAngle1) + " maxChangePerCycle: "
				+ Arrays.toString(maxChangePerCycle1));

		float[] minAngle2 = new float[6];
		float[] maxAngle2 = new float[6];
		float[] maxChangePerCycle2 = new float[6];
		motion.getChainLimits(Chain.RLeg.getId(), minAngle2, maxAngle2,
				maxChangePerCycle2);
		System.out.println("getChainLimits RLeg minAngle: "
				+ Arrays.toString(minAngle2) + " maxAngle: "
				+ Arrays.toString(maxAngle2) + " maxChangePerCycle: "
				+ Arrays.toString(maxChangePerCycle2));

		float[] limits = new float[3];
		motion.getJointLimits(Joint.HeadYaw.getId(), limits);
		System.out.println("getJointLimits HeadYaw minAngle: " + limits[0]
				+ " maxAngle: " + limits[1] + " maxChangePerCycle: "
				+ limits[2]);
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getAngle(int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getAngleError(int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getCommandAngle(int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getJointSpeedParams(int, float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getJointStiffness(int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#gotoAngle(int, float, float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#gotoAngleWithSpeed(int, float, int, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#gotoJointStiffness(int, float, float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#setAngle(int, float)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#setJointSpeedParams(int, float, float, float)
	 * {
	 *
	 * @link jp.ac.fit.asura.naoji.jal.JALMotion#setJointStiffness(int, float)}
	 *       , のためのテスト・メソッド。
	 */
	public void testJoint() {
		int taskId;

		System.out.println("HeadYaw gotoJointStiffness 1.0f");
		taskId = motion.gotoJointStiffness(Joint.HeadYaw.getId(), 1.0f, 0.5f,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);
		assertEquals(1.0f, motion.getJointStiffness(Joint.HeadYaw.getId()),
				0.0625f);

		System.out.println("HeadYaw gotoAngle -0.5f with SMOOTH");
		taskId = motion.gotoAngle(Joint.HeadYaw.getId(), -0.5f, 3.0f,
				InterpolationType.SMOOTH.getId());
		assertEquals(-0.5f, motion.getCommandAngle(Joint.HeadYaw.getId()),
				0.0625f);
		motion.wait(taskId, 0);
		assertEquals(-0.5f, motion.getAngle(Joint.HeadYaw.getId()), 0.0625f);

		System.out.println("HeadYaw gotoAngleWithSpeed 0.5 with SLOWLY(10%)");
		taskId = motion.gotoAngleWithSpeed(Joint.HeadYaw.getId(), 0f, 10,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);
		assertEquals(0.0f, motion.getAngle(Joint.HeadYaw.getId()), 0.0625f);

		System.out.println("HeadYaw changeAngle +0.5f");
		taskId = motion.changeAngle(Joint.HeadYaw.getId(), 0.5f);
		assertEquals(0.5f, motion.getAngleError(Joint.HeadYaw.getId()), 0.125f);
		motion.wait(taskId, 0);
		assertEquals(0.5f, motion.getAngle(Joint.HeadYaw.getId()), 0.0625f);

		System.out.println("HeadYaw setJointSpeedParams 0.05f, 0.006f, 0.006f");
		motion
				.setJointSpeedParams(Joint.HeadYaw.getId(), 0.05f, 0.006f,
						0.006f);

		float[] speedParams = new float[3];
		motion.getJointSpeedParams(Joint.HeadYaw.getId(), speedParams);
		assertEquals(0.05f, speedParams[0], 0.03125f);
		assertEquals(0.006f, speedParams[1], 0.03125f);
		assertEquals(0.006f, speedParams[2], 0.03125f);

		System.out.println("HeadYaw setJointStiffness 0.0f");
		motion.setJointStiffness(Joint.HeadYaw.getId(), 0.0f);
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getBodyAngles(float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getBodyCommandAngles(float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getBodyStiffnesses(float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getBodyAngleErrors(float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#changeBodyAngles(float[])},
	 * のためのテスト・メソッド。
	 */
	public void testBody() {
		int taskId;
		float[] angles = new float[22];
		float[] stiffnesses = new float[22];

		System.out.println("testBody");

		System.out.println("setBodyStiffness");
		motion.setBodyStiffness(0.0f);

		System.out.println("gotoBodyStiffness");
		taskId = motion.gotoBodyStiffness(1.0f, 2.0f, InterpolationType.LINEAR
				.getId());
		motion.wait(taskId, 0);

		System.out.println("getBodyStiffnesses");
		motion.getBodyStiffnesses(stiffnesses);
		assertEquals(1.0f, stiffnesses[0], 0.03125f);

		System.out.println("gotoBodyStiffnesses");
		taskId = motion.gotoBodyStiffnesses(stiffnesses, 2.0f,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);
		assertEquals(1.0f, stiffnesses[0], 0.03125f);

		System.out.println("gotoBodyAngles");
		angles[0] = 0.5f;
		taskId = motion.gotoBodyAngles(angles, 2.0f, InterpolationType.LINEAR
				.getId());
		motion.wait(taskId, 0);

		System.out.println("getBodyAngles");
		motion.getBodyAngles(angles);
		assertEquals(0.5f, angles[0], 0.03125f);

		System.out.println("getBodyAngleErrors");
		motion.getBodyAngleErrors(angles);
		assertEquals(0.0f, angles[0], 0.03125f);

		System.out.println("getBodyCommandAngles");
		motion.getBodyCommandAngles(angles);
		assertEquals(0.5f, angles[0], 0.03125f);

		System.out.println("changeBodyAngles +0.5f");
		taskId = motion.changeBodyAngles(new float[] { 0.5f, 0.5f, 0.5f, 0.5f,
				0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
				0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f });
		motion.wait(taskId, 0);

		System.out.println("gotoBodyAnglesWithSpeed");
		taskId = motion.gotoBodyAnglesWithSpeed(angles, 10,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);

		System.out.println("setBodyAngles");
		motion.setBodyAngles(new float[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getChainAngleErrors(int, float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getChainAngles(int, float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getChainCommandAngles(int, float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getChainLimits(int, float[], float[], float[])}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getChainStiffnesses(int, float[])}
	 * のためのテスト・メソッド。
	 */
	public void testChain() {
		int taskId;
		float[] angles = new float[2];
		float[] stiffnesses = new float[2];

		System.out.println("testChain");

		System.out.println("setChainStiffness");
		motion.setChainStiffness(Chain.Head.getId(), 0.0f);

		System.out.println("gotoChainStiffness");
		taskId = motion.gotoChainStiffness(Chain.Head.getId(), 1.0f, 2.0f,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);

		System.out.println("getChainStiffnesses");
		motion.getChainStiffnesses(Chain.Head.getId(), stiffnesses);
		assertEquals(1.0f, stiffnesses[0], 0.03125f);

		System.out.println("gotoChainStiffnesses");
		taskId = motion.gotoChainStiffnesses(Chain.Head.getId(), stiffnesses,
				2.0f, InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);
		assertEquals(1.0f, stiffnesses[0], 0.03125f);

		System.out.println("changeChainAngles -0.5f");
		System.out.println("Head");
		taskId = motion.changeChainAngles(Chain.Head.getId(), new float[] {
				-0.5f, -0.5f });
		motion.wait(taskId, 0);
		System.out.println("RArm");
		taskId = motion.changeChainAngles(Chain.RArm.getId(), new float[] {
				-0.5f, -0.5f, -0.5f, -0.5f });
		motion.wait(taskId, 0);
		System.out.println("RLeg");
		taskId = motion.changeChainAngles(Chain.RLeg.getId(), new float[] {
				-0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f });
		motion.wait(taskId, 0);
		System.out.println("LArm");
		taskId = motion.changeChainAngles(Chain.LArm.getId(), new float[] {
				-0.5f, -0.5f, -0.5f, -0.5f });
		motion.wait(taskId, 0);
		System.out.println("LLeg");
		taskId = motion.changeChainAngles(Chain.LLeg.getId(), new float[] {
				-0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f });
		motion.wait(taskId, 0);

		System.out.println("gotoChainAngles");
		angles[0] = 0.5f;
		taskId = motion.gotoChainAngles(Chain.Head.getId(), angles, 2.0f,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);

		System.out.println("getChainAngles");
		motion.getChainAngles(Chain.Head.getId(), angles);
		assertEquals(0.5f, angles[0], 0.03125f);

		System.out.println("getChainAngleErrors");
		motion.getChainAngleErrors(Chain.Head.getId(), angles);
		assertEquals(0.0f, angles[0], 0.03125f);

		System.out.println("getChainCommandAngles");
		motion.getChainCommandAngles(Chain.Head.getId(), angles);
		assertEquals(0.5f, angles[0], 0.03125f);

		System.out.println("gotoChainAnglesWithSpeed");
		taskId = motion.gotoChainAnglesWithSpeed(Chain.Head.getId(), angles,
				10, InterpolationType.LINEAR.getId());
		motion.wait(taskId, 0);

		System.out.println("setChainAngles");
		motion.setChainAngles(Chain.Head.getId(), new float[] { 0, 0 });
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getForwardTransform(int, int, float[])}
	 * のためのテスト・メソッド。
	 */
	public void testGetForwardTransform() {
		float[] m = new float[4 * 4];
		motion.getForwardTransform(Chain.Head.getId(), NaoV3R.SPACE_BODY, m);
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getSupportMode()}
	 * のためのテスト・メソッド。
	 */
	public void testSupportMode() {
		int mode = motion.getSupportMode();
		motion.setSupportMode(NaoV3R.SUPPORT_MODE_DOUBLE_LEFT);
		assertEquals(NaoV3R.SUPPORT_MODE_DOUBLE_LEFT, motion.getSupportMode());
		motion.setSupportMode(mode);
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#killAll()} のためのテスト・メソッド。
	 */
	public void testKill() {
		int taskId = motion.gotoAngle(Joint.HeadYaw.getId(), 3.14f / 2, 5.0f,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 1000);
		motion.killTask(taskId);

		taskId = motion.gotoAngle(Joint.HeadYaw.getId(), -3.14f / 2, 5.0f,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 2000);
		motion.killAll();
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#openHand(java.lang.String)}
	 * のためのテスト・メソッド。
	 */
	public void testHand() {
		fail("まだ実装されていません");
		// not implemented
		// motion.openHand("");
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#setTorsoOrientation(float, float)}
	 * のためのテスト・メソッド。
	 */
	public void testTorsoOrientation() {
		int taskId;
		taskId = motion.gotoTorsoOrientation(0.25f, 0.25f, 3.0f,
				InterpolationType.LINEAR.getId());
		motion.wait(taskId, 2000);
		motion.setTorsoOrientation(0.0f, 0.0f);
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#getRemainingFootStepCount()}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#waitUntilWalkIsFinished()}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#stop(int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#walkIsActive()}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#walk()}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#addTurn(float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#addWalkArc(float, float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#addWalkSideways(float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#addWalkStraight(float, int) }
	 * のためのテスト・メソッド。
	 */
	public void testWalk() {
		System.out.println("walk begin");
		motion.addWalkStraight(0.4f, 40);
		motion.addWalkSideways(0.25f, 40);
		motion.addWalkArc(0.5f, 0.5f, 40);
		motion.addTurn(0.5f, 40);
		int taskId = motion.walk();
		assertTrue(motion.getRemainingFootStepCount() > 0);
		assertTrue(motion.walkIsActive());
		System.out.println("walk waitUntilWalkIsFinished");
		motion.waitUntilWalkIsFinished();
		assertTrue(motion.getRemainingFootStepCount() == 0);
		assertFalse(motion.walkIsActive());
		System.out.println("walk end");
	}

	/**
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#setWalkArmsConfig(float, float, float, float)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#setWalkArmsEnable(boolean)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#setWalkConfig(float, float, float, float, float, float)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#setWalkExtraConfig(float, float, float, float)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#clearFootsteps()}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#turn(float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#walkArc(float, float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#walkSideways(float, int)}
	 * {@link jp.ac.fit.asura.naoji.jal.JALMotion#walkStraight(float, int)}
	 * のためのテスト・メソッド。
	 */
	public void testWalk2() {
		int taskId;
		System.out.println("walkStraight");
		taskId = motion.walkStraight(1.0f, 40);
		motion.wait(taskId, 3000);
		System.out.println("clearFootsteps");
		motion.clearFootsteps();
		System.out.println("waitUntilWalkIsFinished");
		motion.waitUntilWalkIsFinished();
		assertFalse(motion.walkIsActive());

		System.out.println("walkSideways");
		taskId = motion.walkSideways(1.0f, 40);
		motion.wait(taskId, 3000);
		System.out.println("stop");
		motion.stop(taskId);
		System.out.println("waitUntilWalkIsFinished");
		motion.waitUntilWalkIsFinished();
		assertFalse(motion.walkIsActive());

		System.out.println("walkArc");
		taskId = motion.walkArc(0.5f, 1.0f, 40);
		motion.wait(taskId, 2000);
		System.out.println("killTask");
		motion.killTask(taskId);
		System.out.println("waitUntilWalkIsFinished");
		motion.waitUntilWalkIsFinished();
		assertFalse(motion.walkIsActive());

		taskId = motion.turn(0.5f, 40);
		motion.wait(taskId, 0);
		assertFalse(motion.walkIsActive());
	}

}
