/*
 * 作成日: 2009/04/01
 */
package jp.ac.fit.asura.naoji.v4l2;

import java.nio.ByteBuffer;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class V4L2Buffer {
	int index;
	int length;
	long timestamp;
	private ByteBuffer buffer;

	public V4L2Buffer() {
	}

	public ByteBuffer getBuffer() {
		return buffer;
	}

	public int getLength() {
		return length;
	}

	protected int getIndex() {
		return index;
	}

	/**
	 * この画像を取得した時刻を返します.
	 *
	 * @return 取得した時刻(マイクロ秒)
	 */
	public long getTimestamp() {
		return timestamp;
	}

	void setBuffer(ByteBuffer buffer) {
		this.buffer = buffer;
	}
}
