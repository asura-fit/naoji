/*
 * 作成日: 2009/03/31
 */
package jp.ac.fit.asura.naoji.v4l2;

/**
 * @author sey
 *
 * @version $Id: $
 *
 */
public class V4L2PixelFormat {
	public enum PixelFormat {
		V4L2_PIX_FMT_UYVY('Y', 'U', 'Y', 'V');

		private int fourcc;

		/**
	 *
	 */
		private PixelFormat(byte chr1, byte chr2, byte chr3, byte chr4) {
			fourcc = v4l2_fourcc(chr1, chr2, chr3, chr4);
		}

		private PixelFormat(char chr1, char chr2, char chr3, char chr4) {
			fourcc = v4l2_fourcc((byte) chr1, (byte) chr2, (byte) chr3,
					(byte) chr4);
		}

		public int getFourccCode() {
			return fourcc;
		}

		public static int v4l2_fourcc(byte chr1, byte chr2, byte chr3, byte chr4) {
			return ((int) (chr1) << 0) | ((int) (chr2) << 8)
					| ((int) (chr3) << 16) | ((int) (chr4) << 24);
		}
	}

	private int width;
	private int height;
	private int pixelFormat;

	public int getWidth() {
		return width;
	}

	public int getHeight() {
		return height;
	}

	public int getPixelFormat() {
		return pixelFormat;
	}

	public void setWidth(int width) {
		assert width >= 0;
		this.width = width;
	}

	public void setHeight(int height) {
		assert height >= 0;
		this.height = height;
	}

	public void setPixelFormat(int pixelFormat) {
		this.pixelFormat = pixelFormat;
	}
}
