/*
 * 作成日: 2009/07/01
 */
package jp.ac.fit.asura.naoji.jal;

import java.nio.ByteBuffer;

/**
 * @author sey
 *
 * @version $Id: $
 *
 */
public class JALImage {
	int width;
	int height;
	int nbLayers;
	int colorSpace;
	long timestamp;
	ByteBuffer data;

	private boolean isRemote;

	/**
	 *
	 */
	JALImage() {

	}

	/**
	 * @return colorSpace
	 */
	public int getColorSpace() {
		return colorSpace;
	}

	/**
	 * @return data
	 */
	public ByteBuffer getData() {
		return data;
	}

	/**
	 * @return height
	 */
	public int getHeight() {
		return height;
	}

	/**
	 * @return nbLayers
	 */
	public int getNbLayers() {
		return nbLayers;
	}

	/**
	 * @return timeStamp
	 */
	public long getTimestamp() {
		return timestamp;
	}

	/**
	 * @return width
	 */
	public int getWidth() {
		return width;
	}

	public int getLength() {
		return width * height * nbLayers;
	}
}
