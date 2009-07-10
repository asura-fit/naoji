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
		Head, LArm, LLeg, RLeg, RArm;

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

	public static final class Camera {
		public static final int PARAM_Brightness = 0;
		public static final int PARAM_Contrast = 1;
		public static final int PARAM_Saturation = 2;
		public static final int PARAM_Hue = 3;
		public static final int PARAM_RedChroma = 4;
		public static final int PARAM_BlueChroma = 5;
		public static final int PARAM_Gain = 6;
		public static final int PARAM_HFlip = 7;
		public static final int PARAM_VFlip = 8;
		public static final int PARAM_CorrectionLensX = 9;
		public static final int PARAM_CorrectionLensY = 10;
		public static final int PARAM_AEC = 11;
		public static final int PARAM_AWC = 12;
		public static final int PARAM_AGC = 13;
		public static final int PARAM_Exposure = 17;
		public static final int PARAM_ExposureCorrection = 21;
		public static final int PARAM_FPS = 15;
		public static final int PARAM_Resolution = 14;
		public static final int PARAM_CameraSelect = 18;

		public static final int CAMERA_SELECT_TOP = 0;
		public static final int CAMERA_SELECT_BOTTOM = 1;

		public static final int COLORSPACE_Yuv = 0;
		public static final int COLORSPACE_yUv = 1;
		public static final int COLORSPACE_yuV = 2;
		public static final int COLORSPACE_Rgb = 3;
		public static final int COLORSPACE_rGb = 4;
		public static final int COLORSPACE_rgB = 5;
		public static final int COLORSPACE_Hsv = 6;
		public static final int COLORSPACE_hSv = 7;
		public static final int COLORSPACE_hsV = 8;
		public static final int COLORSPACE_YUV422Interlaced = 9;
		public static final int COLORSPACE_YUV = 10;
		public static final int COLORSPACE_RGB = 11;
		public static final int COLORSPACE_HSV = 12;
		public static final int COLORSPACE_BGR = 13;
		public static final int COLORSPACE_YYCbCr = 14;
		public static final int COLORSPACE_H2RGB = 15;
		public static final int COLORSPACE_HSMixed = 16;

		public static final int RESOLUTION_QQVGA = 0;
		public static final int RESOLUTION_QVGA = 1;
		public static final int RESOLUTION_VGA = 2;

	}

	public static final int AXIS_MASK_X = 0x01;
	public static final int AXIS_MASK_Y = 0x02;
	public static final int AXIS_MASK_Z = 0x04;
	public static final int AXIS_MASK_WX = 0x08;
	public static final int AXIS_MASK_WY = 0x10;
	public static final int AXIS_MASK_WZ = 0x20;
	public static final int AXIS_MASK_ALL = 0x3F;
	public static final int AXIS_MASK_VEL = 0x07;
	public static final int AXIS_MASK_ROT = 0x38;

	public static final int BALANCE_MODE_OFF = 0;
	public static final int BALANCE_MODE_AUTO = 1;
	public static final int BALANCE_MODE_COM_CONTROL = 2;

	public static final int I2C_CAMERA_TOP = 1;
	public static final int I2C_CAMERA_BOTTOM = 2;

	public static final int SPACE_BODY = 0;
	public static final int SPACE_SUPPORT_LEG = 1;

	public static final int SUPPORT_MODE_LEFT = 0;
	public static final int SUPPORT_MODE_DOUBLE_LEFT = 1;
	public static final int SUPPORT_MODE_RIGHT = 2;
	public static final int SUPPORT_MODE_DOUBLE_RIGHT = 3;

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
