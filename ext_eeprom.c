#include <xc.h>

#include "i2c.h"
#include "ext_eeprom.h"

/* 
 * A0  -  Write Mode
 * A1  -  Read Mode
 */

void write_ext_eeprom(unsigned char address, unsigned char data)  //write operation
{
	i2c_start();
	i2c_write(SLAVE_WRITE_E);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
        for(int i=3000;i--;);
}

unsigned char read_ext_eeprom(unsigned char address)  //read operation
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE_E);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ_E);
	data = i2c_read();
	i2c_stop();

	return data;
}