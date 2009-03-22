/*
 * 作成日: 2009/03/15
 */
package jp.ac.fit.asura.naoji;

import java.util.ArrayList;
import java.util.List;

import jp.ac.fit.asura.naoji.jal.JALBroker;
import jp.ac.fit.asura.naoji.jal.JALModule;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class NaojiModule extends JALModule {
	private static List<NaojiFactory> factories = new ArrayList<NaojiFactory>();

	public static void addFactory(NaojiFactory factory) {
		factories.add(factory);
	}

	private JALBroker pBroker;

	private NaojiContext context;
	private List<Naoji> brothers;

	/**
	 *
	 */
	public NaojiModule(long ptr) {
		objPtr = ptr;
		long brokerPtr = _createJALBroker(objPtr);
		pBroker = new JALBroker(brokerPtr);
		brothers = new ArrayList<Naoji>(factories.size());
		for (NaojiFactory f : factories) {
			try {
				brothers.add(f.create());
			} catch (Exception e) {
			}
		}
	}

	public void init() {
		context = new NaojiContext(this);
		for (Naoji naoji : brothers) {
			try {
				naoji.init(context);
			} catch (Exception e) {
			}
		}
	}

	public void start() {
		for (Naoji naoji : brothers) {
			start(naoji);
		}
	}

	public void exit() {
		stop();
		for (Naoji naoji : brothers) {
			try {
				naoji.exit();
			} catch (Exception e) {
			}
		}
	}

	protected void start(final Naoji naoji) {
		try {
			naoji.start();
		} catch (Exception e) {
		}
	}

	/**
	 * すべてのスレッドを停止し、モジュールを終了可能状態にします.
	 *
	 * 呼び出しは終了可能状態になるまでブロックされます.
	 *
	 */
	protected void stop() {

	}

	public static void test() {
		System.out.println("Hello World from JNI!");
	}

	public static int testSquare(int i) {
		return i * i;
	}

	public JALBroker getParentBroker() {
		return pBroker;
	}

	native private long _createJALBroker(long objPtr);
}
