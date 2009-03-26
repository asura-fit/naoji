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
public class NaoV3RoboCupEdition {
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
		LINEAR(0), INTERPOLATION_SMOOTH(1);

		private int id;

		private InterpolationType(int id) {
			this.id = id;
		}

		public int getId() {
			return id;
		}
	}

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
