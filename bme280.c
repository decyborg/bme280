/*
 *  bme280.c - Linux device driver for the bme280 humidity,
 *  temperature and barometric sensor.
 *
 *  This driver uses the I2C bus subsystem and creates a char device when
 *  probed to allow interaction with user space. For more details on use 
 *  and implementation please refer to the README file.
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * */

#include <linux/module.h> 
#include <linux/i2c.h>
#include "bme280.h"

#define DEVICE_NAME "bme280"

/* 
 * Structure that holds bme280 calibration data - this data is loaded into
 * the device at production and it is different for each device, this structure
 * is populated in the probe function. 
 * 
 * */
struct bme280_calibration{

};

/* Structure that holds bme280 configuration */
struct bme280_configuration{

};

/* Structure that holds configuration and client data for the device */
static struct bme280_data{
	struct i2c_client *client;
	struct bme280_calibration *cal_data;
	struct bme280_configuration *cfg_data;
};

/*
 * When the device is probed this function performs the following actions:
 *  -Reads device ID - NOTE: I2C Address should be configured in the device tree (or the method
 *                     used to register the device)
 *  -Reads calibration parameters
 *  -Configures device
 *  -Registers char device for user space communication
 * */
static int __devinit bme280_probe(struct i2c_client *client, const struct i2c_device_id *id){
	
	/* Check if adapter supports the functionality we need */

	/* Get chip_id */

	/* Get calibration parameters */

	/* Set configuration */

	/* Register char device */
}

static int __devexit bme280_remove(struct i2c_client *client){
	/* Unregister char device */
}

static struct i2c_device_id bme280_idtable[] = {
	{DEVICE_NAME, 0},
	{ }
};
MODULE_DEVICE_TABLE(i2c, bme280_idtable);

static struct i2c_driver bme280_driver = {
	.driver = {
		    .name = DEVICE_NAME,
		    .owner = THIS_MODULE,
		  },
	.probe = bme280_probe,
	.remove = bme280_remove,
	.id_table = bme280_idtable
};

/* Module init routine */
static int __init bme280_init(void){
	/* Register driver within I2C subsystem */
	int tmp;
	tmp = i2c_add_driver(&bme280_driver);
	if(tmp < 0){
		printk(KERN_INFO "%s: I2C subsystem registration failed.\n", DEVICE_NAME);
	}
	printk(KERN_INFO "%s: Device successfully registered to I2C subsystem.\n", DEVICE_INFO);
	return tmp;
}

/* Module exit routine */
static void __exit bme280_exit(void){

	/* Unregister driver from I2C subsystem */
	i2c_del_driver(&bme280_driver);
}

module_init(bme280_init);
module_exit(bme280_exit);

MODULE_AUTHOR("Manuel Rodriguez <manuel2982@gmail.com>");
MODULE_DESCRIPTION("Driver for BME280 sensor");
MODULE_LICENSE("GPL");
