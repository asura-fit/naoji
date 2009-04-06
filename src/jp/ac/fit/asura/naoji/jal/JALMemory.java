/*
 * 作成日: 2009/03/22
 */
package jp.ac.fit.asura.naoji.jal;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.List;

/**
 * @author $Author: sey $
 *
 * @version $Id: $
 *
 */
public class JALMemory extends JALModule {
	public static abstract class Query {
		long queryPtr;
		String[] keys;

		Query(long jmemoryPtr, List<String> keys) {
			this.keys = keys.toArray(new String[0]);
			queryPtr = _createQuery(jmemoryPtr, this.keys);
		}

		public void dispose() {
			_disposeQuery(queryPtr);
		}

		ByteBuffer allocateBuffer(int capacity) {
			ByteBuffer bb = ByteBuffer.allocateDirect(capacity);
			bb.order(ByteOrder.nativeOrder());
			_setBuffer(queryPtr, bb);
			return bb;
		}

		public abstract void update();
	}

	public static class FloatQuery extends Query {
		FloatBuffer buffer;

		FloatQuery(long jmemoryPtr, List<String> keys) {
			super(jmemoryPtr, keys);
			int cap = keys.size() * Float.SIZE / 8;
			ByteBuffer bb = allocateBuffer(cap);
			buffer = bb.asFloatBuffer();
		}

		public FloatBuffer getBuffer() {
			return buffer;
		}

		public void update() {
			_updateFloat(queryPtr);
		}
	}

	public static class IntQuery extends Query {
		IntBuffer buffer;

		IntQuery(long jmemoryPtr, List<String> keys) {
			super(jmemoryPtr, keys);
			int cap = keys.size() * Integer.SIZE / 8;
			ByteBuffer bb = allocateBuffer(cap);
			buffer = bb.asIntBuffer();
		}

		public IntBuffer getBuffer() {
			return buffer;
		}

		public void update() {
			_updateInt(queryPtr);
		}
	}

	public static class StringQuery extends Query {
		String[] buffer;

		StringQuery(long jmemoryPtr, List<String> keys) {
			super(jmemoryPtr, keys);
			buffer = new String[keys.size()];
			_setBufferString(queryPtr, buffer);
		}

		public String[] getBuffer() {
			return buffer;
		}

		public void update() {
			_updateString(queryPtr);
		}
	}

	protected JALMemory(JALBroker broker) {
		objPtr = _create(broker.getPtr());
	}

	public FloatQuery createFloatQuery(List<String> keys) {
		FloatQuery query = new FloatQuery(objPtr, keys);
		return query;
	}

	public IntQuery createIntQuery(List<String> keys) {
		IntQuery query = new IntQuery(objPtr, keys);
		return query;
	}

	public void dispose() {
		_dispose(objPtr);
	}

	public boolean isRunning(int taskId) {
		return _isRunning(objPtr, taskId);
	}

	public void wait(int taskId, int timeout) {
		_wait(objPtr, taskId, timeout);
	}

	public int defineKey(String key) {
		return _defineKey(key);
	}

	public void removeKey(int id) {
		_removeKey(id);
	}

	public int getDataInt(String key) {
		return _getDataInt(objPtr, key);
	}

	public int getDataInt(int id) {
		return _getDataInt(objPtr, id);
	}

	public float getDataFloat(String key) {
		return _getDataFloat(objPtr, key);
	}

	public float getDataFloat(int id) {
		return _getDataFloat(objPtr, id);
	}

	public String getDataString(String key) {
		return _getDataString(objPtr, key);
	}

	public String getDataString(int id) {
		return _getDataString(objPtr, id);
	}

	native static private long _create(long jalBrokerPtr);

	native static private void _dispose(long objPtr);

	native static private int _defineKey(String key);

	native static private void _removeKey(int id);

	// ALModule methods.
	native static protected boolean _wait(long objPtr, int taskId, int timeout);

	native static protected boolean _isRunning(long objPtr, int taskId);

	// getData methods.
	native static private int _getDataInt(long objPtr, String key);

	native static private int _getDataInt(long objPtr, int id);

	native static private float _getDataFloat(long objPtr, String key);

	native static private float _getDataFloat(long objPtr, int id);

	native static private String _getDataString(long objPtr, String key);

	native static private String _getDataString(long objPtr, int id);

	// JALMemory.Query methods.
	native static private long _createQuery(long jalMemory, String keys[]);

	native static private void _disposeQuery(long queryPtr);

	native static private void _setBuffer(long queryPtr, ByteBuffer buffer);

	native static private void _setBufferString(long queryPtr, String[] buffer);

	native static private void _updateFloat(long queryPtr);

	native static private void _updateInt(long queryPtr);

	native static private void _updateString(long queryPtr);
}
