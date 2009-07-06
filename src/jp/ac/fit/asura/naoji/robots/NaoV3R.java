/*
 * 作成日: 2009/03/25
 */
package jp.ac.fit.asura.naoji.robots;

/**
 * @author sey
 *
 * @version $Id: $
 *
 */
public class NaoV3R {
	public enum Joint {
		HeadYaw, HeadPitch, LShoulderPitch, LShoulderRoll, LElbowYaw, LElbowRoll, LHipYawPitch, LHipRoll, LHipPitch, LKneePitch, LAnklePitch, LAnkleRoll, RHipYawPitch, RHipRoll, RHipPitch, RKneePitch, RAnklePitch, RAnkleRoll, RShoulderPitch, RShoulderRoll, RElbowYaw, RElbowRoll;

		public int getId() {
			return this.ordinal();
		}

		public String getName() {
			return this.name();
		}

		public Chain getChain() {
			switch (this) {
			case HeadYaw:
			case HeadPitch:
				return Chain.Head;
			case LShoulderPitch:
			case LShoulderRoll:
			case LElbowRoll:
			case LElbowYaw:
				return Chain.LArm;
			case LHipYawPitch:
			case LHipRoll:
			case LHipPitch:
			case LKneePitch:
			case LAnklePitch:
			case LAnkleRoll:
				return Chain.LLeg;
			case RShoulderPitch:
			case RShoulderRoll:
			case RElbowRoll:
			case RElbowYaw:
				return Chain.RArm;
			case RHipYawPitch:
			case RHipRoll:
			case RHipPitch:
			case RKneePitch:
			case RAnklePitch:
			case RAnkleRoll:
				return Chain.RLeg;
			default:
				assert false : this;
				return null;
			}
		}
	}

	public enum Chain {
		Head, LArm, RArm, LLeg, RLeg;

		public int getId() {
			return this.ordinal();
		}

		public String getName() {
			return this.name();
		}
	}

	public enum InterpolationType {
		LINEAR(0), SMOOTH(1);

		private int id;

		private InterpolationType(int id) {
			this.id = id;
		}

		public int getId() {
			return id;
		}
	}

	public enum Camera {
		TOP(1), BOTTOM(2);

		private int id;

		private Camera(int id) {
			this.id = id;
		}

		/**
		 * I2Cdevで使用するカメラIDを返します.
		 *
		 * @return id
		 */
		public int getId() {
			return id;
		}

		@Override
		public String toString() {
			return "NaoV3R Camera id:" + getId() + " name:" + name();
		}
	}

	public enum CameraParam {
		Brightness(0), Contrast(1), Saturation(2), Hue(3), RedChroma(4), BlueChroma(
				5), Gain(6), HFlip(7), VFlip(8), CorrectionLensX(9), CorrectionLensY(
				10), AEC(11), AWC(12), AGC(13), Exposure(17), ExposureCorrection(
				21), FPS(15), Resolution(14), CameraSelect(18);

		private int id;

		private CameraParam(int id) {
			this.id = id;
		}

		public int getId() {
			return id;
		}
	}

	public static int AXIS_MASK_X = 0x01;
	public static int AXIS_MASK_Y = 0x02;
	public static int AXIS_MASK_Z = 0x04;
	public static int AXIS_MASK_WX = 0x08;
	public static int AXIS_MASK_WY = 0x10;
	public static int AXIS_MASK_WZ = 0x20;
	public static int AXIS_MASK_ALL = 0x3F;
	public static int AXIS_MASK_VEL = 0x07;
	public static int AXIS_MASK_ROT = 0x38;

	public static int BALANCE_MODE_OFF = 0;
	public static int BALANCE_MODE_AUTO = 1;
	public static int BALANCE_MODE_COM_CONTROL = 2;

	public static int COLORSPACE_YUV = 0;
	public static int COLORSPACE_RGB = 1;
	public static int COLORSPACE_YUV422 = 2;

	public static int RESOLUTION_QQVGA = 0;
	public static int RESOLUTION_QVGA = 1;
	public static int RESOLUTION_VGA = 2;

	public static int SPACE_BODY = 0;
	public static int SPACE_SUPPORT_LEG = 1;

	public static int SUPPORT_MODE_LEFT = 0;
	public static int SUPPORT_MODE_DOUBLE_LEFT = 1;
	public static int SUPPORT_MODE_RIGHT = 2;
	public static int SUPPORT_MODE_DOUBLE_RIGHT = 3;

	// public static void defineJoints(JALMotion jmotion) {
	// for (Joint j : Joint.values()) {
	// jmotion.defineJoint(j.getId(), j.getName());
	// }
	// }

	// public static void defineChains(JALMotion jmotion) {
	// for (Chain c : Chain.values()) {
	// jmotion.defineJoint(c.getId(), c.getName());
	// }
	// }
}
