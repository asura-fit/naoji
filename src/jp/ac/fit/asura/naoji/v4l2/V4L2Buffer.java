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
	protected int index;
	protected int length;
	protected long timestamp;
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

	public long getTimestamp() {
		return timestamp;
	}

	protected void setBuffer(ByteBuffer buffer) {
		this.buffer = buffer;
	}
}
