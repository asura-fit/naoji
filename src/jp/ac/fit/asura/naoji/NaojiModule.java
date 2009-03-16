/*
 * 作成日: 2009/03/15
 */
package jp.ac.fit.asura.naoji;

import java.util.ArrayList;
import java.util.List;

import jp.ac.fit.asura.naoji.al.ALMemory;
import jp.ac.fit.asura.naoji.al.ALMotion;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class NaojiModule {
	private static List<NaojiFactory> factories = new ArrayList<NaojiFactory>();

	public static void addFactory(NaojiFactory factory) {
		factories.add(factory);
	}

	private List<Naoji> brothers;

	/**
	 *
	 */
	public NaojiModule() {
		brothers = new ArrayList<Naoji>(factories.size());
		for (NaojiFactory f : factories) {
			try {
				brothers.add(f.create());
			} catch (Exception e) {
			}
		}
	}

	public void init() {
		for (Naoji naoji : brothers) {
			try {
				naoji.init(null);
			} catch (Exception e) {
			}
		}
	}

	public void exit() {
		for (Naoji naoji : brothers) {
			try {
				naoji.exit();
			} catch (Exception e) {
			}
		}
	}

	public static void test() {
		System.out.println("Hello World from JNI!");
	}

	public static int testSquare(int i) {
		return i * i;
	}

	public void read() {

	}

	private native void _read();

	private native long getProxy(String moduleName);
}
