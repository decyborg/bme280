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
struct bme280_calibration_t{
	unsigned short dig_T1;
      	signed short dig_T2;
	signed short dig_T3;
	unsigned short dig_P1;
	signed short dig_P2;
	signed short dig_P3;
	signed short dig_P4;
	signed short dig_P5;
	signed short dig_P6;
	signed short dig_P7;
	signed short dig_P8;
	signed short dig_P9;
	unsigned char dig_H1;
	signed short dig_H2;
	unsigned char dig_H3;
	signed short dig_H4;
	signed short dig_H5;
	signed char dig_H6;	
};

/* Structure that holds bme280 configuration */
struct bme280_configuration_t{
	unsigned char t_sb;
	unsigned char filter;
	unsigned char spi3w_en;
	unsigned char osrs_t;
	unsigned char osrs_p;
	unsigned char mode;
	unsigned char osrs_h;	
};

/* Structure that holds configuration and client data for the device */
struct bme280_data_t{
	struct i2c_client *client;
	struct bme280_calibration_t *cal_data;
	struct bme280_configuration_t *cfg_data;
};

/* Global variables */
static struct bme280_calibration_t bme280_calibration;
static struct bme280_configuration_t bme280_configuration =
					{
					.t_sb = 0,
					.filter = 0,
					.spi3w_en = 0,
					.osrs_t = 1,
					.osrs_p = 1,
					.mode = 0,
					.osrs_h = 1
					};
struct i2c_client *bme280_client = NULL;
static struct bme280_data_t bme280_data =
					{
					.client = NULL,
					.cal_data = &bme280_calibration,
					.cfg_data = &bme280_configuration
					};

/* Helper functions definitions */
static void bme280_get_calibration(struct bme280_calibration_t *calibration){

}

static void bme280_set_configuration(struct bme280_configuration_t *configuration){

}

/*
 * When the device is probed this function performs the following actions:
 *  -Reads device ID - NOTE: I2C Address should be configured in the device tree (or the method
 *                     used to register the device)
 *  -Reads calibration parameters
 *  -Configures device
 *  -Registers char device for user space communication
 * */
static int bme280_probe(struct i2c_client *client, const struct i2c_device_id *id){
	
	int tmp, client_id;
	struct i2c_adapter *adapter;
	
	/* Check if adapter supports the functionality we need */
	adapter = client->adapter;
	tmp = i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA);
	if(!tmp)
		goto err_out;

	/* Get chip_id */
	client_id = i2c_smbus_read_byte_data(client, R_BME280_CHIP_ID);
	if(client_id != BME280_CHIP_ID){
		printk(KERN_INFO "%s: Client ID (%x) does not match chip ID (%x)\n", 
			DEVICE_NAME, client_id, BME280_CHIP_ID);
		return tmp;
	}

	/* Get calibration parameters */
	bme280_get_calibration(bme280_data.cal_data);

	/* Set configuration */
	bme280_set_configuration(bme280_data.cfg_data);

	/* Register char device */

err_out:
	return tmp;
}

static int bme280_remove(struct i2c_client *client){
	/* Unregister char device */
	
	return 0;
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
	printk(KERN_INFO "%s: Device successfully registered to I2C subsystem.\n", DEVICE_NAME);
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
