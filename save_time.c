#include <xc.h>
#include "main.h"
#include "i2c.h"
#include "ds1307.h"

extern char time[TIME_ARR_SIZE];

//Function to store the time to RTC after updating
void save_time_to_RTC()
{
    char temp = 0;
    
    temp = temp | (time[6]-48) << 4; //Storing the updated second data
    temp = temp | (time[7]-48);
    write_ds1307(SEC_ADDR, temp); //Writing the updated second data to register of RTC
    temp = 0;
    
    temp = temp | (time[3]-48) << 4; //Storing the updated minute data
    temp = temp | (time[4]-48);
    write_ds1307(MIN_ADDR, temp); //Writing the updated minute data to the register of RTC
    temp = 0;
    
    temp = temp | (time[0]-48) << 4;
    temp = temp | (time[1]-48);
    write_ds1307(HOUR_ADDR, temp); //Writing the updated hour data to the register of RTC
}