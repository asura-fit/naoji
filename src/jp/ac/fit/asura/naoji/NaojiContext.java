/*
 * 作成日: 2009/03/22
 */
package jp.ac.fit.asura.naoji;

import jp.ac.fit.asura.naoji.jal.JALBroker;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class NaojiContext {
	private NaojiModule module;

	public NaojiContext(NaojiModule module) {
		this.module = module;
	}

	public JALBroker getParentBroker() {
		return module.getParentBroker();
	}

	public NaojiModule getNaojiModule() {
		return module;
	}
}
