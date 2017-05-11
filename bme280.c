/*
 *  bme280.c - Linux device driver for the bme280 humidity,
 *  temperature and barometric sensor.
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

static int bme280_probe(void){

}

static int bme280_remove(void){

}

static struct i2c_device_id bme280_idtable[] = {
	{ "bme280", 0},
	{ }
};

MODULE_DEVICE_TABLE(i2c, bme280_idtable);

static struct i2c_driver bme280_driver = {
	.driver = {
		    .name = "bme280",
		    .owner = THIS_MODULE,
		  },
	.probe = bme280_probe,
	.remove = bme280_remove,
	.id_table = bme280_idtable
};


static int __init bme280_init(void){
	return 0;
}

static void __exit bme280_exit(void){

}

module_init(bme280_init);
module_exit(bme280_exit);

MODULE_AUTHOR("Manuel Rodriguez <manuel2982@gmail.com>");
MODULE_DESCRIPTION("Driver for BME280 sensor");
MODULE_LICENSE("GPL");
