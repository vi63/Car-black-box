# 1 "ds1307.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "ds1307.c" 2

# 1 "./ds1307.h" 1
# 17 "./ds1307.h"
void init_ds1307(void);
void write_ds1307(unsigned char address1, unsigned char data);
unsigned char read_ds1307(unsigned char address1);
# 2 "ds1307.c" 2

# 1 "./i2c.h" 1




void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);
# 3 "ds1307.c" 2

# 1 "./main.h" 1
# 13 "./main.h"
void dashboard(char key);
void store_event(char key);
void setpassword(char key);
void menu(char key);
void view_log(char key);
void download_log(char key);
void clear_log(char key);
void settime(char key);
void change_pass(char key);
void save_time_to_RTC();
# 4 "ds1307.c" 2








void init_ds1307(void)
{
 unsigned char dummy;


 dummy = read_ds1307(0x00);
 write_ds1307(0x00, dummy & 0x7F);


 dummy = read_ds1307(0x02);
 write_ds1307(0x02, dummy & 0xBF);
# 44 "ds1307.c"
}

void write_ds1307(unsigned char address, unsigned char data)
{
 i2c_start();
 i2c_write(0xD0);
 i2c_write(address);
 i2c_write(data);
 i2c_stop();
}

unsigned char read_ds1307(unsigned char address)
{
 unsigned char data;

 i2c_start();
 i2c_write(0xD0);
 i2c_write(address);
 i2c_rep_start();
 i2c_write(0xD1);
 data = i2c_read();
 i2c_stop();

 return data;
}
