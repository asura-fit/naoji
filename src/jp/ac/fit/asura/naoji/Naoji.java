/*
 * 作成日: 2009/03/15
 */
package jp.ac.fit.asura.naoji;

/**
 *
 * Naoji API. Naojiのモジュールインターフェイス.
 *
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public interface Naoji {
	/**
	 * Naojiの初期化時に呼び出されます.
	 *
	 * モジュールは必要に応じてリソースの確保など初期化処理を実行できます.
	 *
	 * @param o
	 */
	public void init(NaojiContext context);

	/**
	 * モジュールの開始時に呼び出されます.
	 *
	 * モジュールは現在のスレッドをブロックするべきではなく、必要に応じて処理スレッドを開始するべきです.
	 */
	public void start();

	/**
	 * モジュールの停止時に呼び出されます.
	 *
	 * このメソッドの呼び出しによって、モジュールは速やかに停止状態に移行しなければなりません.
	 * モジュールは停止状態に移行するまで現在のスレッドをブロックすることが許されていますが、可能な限り速やかに復帰するべきです.
	 *
	 * このメソッドの呼び出しの後、再びstart()によって処理を開始できることが推薦されます.
	 */
	public void stop();

	/**
	 * モジュールの終了時に呼び出されます.
	 */
	public void exit();
}
