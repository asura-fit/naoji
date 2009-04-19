/**
 * @author sey
 *
 * Version : $Id$
 */

#ifndef NaojiI2C_H
#define NaojiI2C_H

#include <cassert>

#include <errno.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <jni.h>       /* where everything is defined */

namespace Naoji {
inline jint I2Cdev_read_byte(int dev, __u8 command) {
	union i2c_smbus_data data;
	struct i2c_smbus_ioctl_data arg;
	arg.read_write = I2C_SMBUS_READ;
	arg.command = command;
	arg.size = I2C_SMBUS_BYTE_DATA;
	arg.data = &data;

	jint res = ioctl(dev, I2C_SMBUS, &arg);
	if (res == 0)
		return 0x0FF & data.byte;
	return res;
}

inline jint I2Cdev_write(int dev, __u8 command, int size, i2c_smbus_data *data) {
	struct i2c_smbus_ioctl_data arg;
	arg.read_write = I2C_SMBUS_WRITE;
	arg.command = command;
	arg.size = size;
	arg.data = data;

	jint res = ioctl(dev, I2C_SMBUS, &arg);
	return res;
}
}

#endif // NaojiI2C_H
