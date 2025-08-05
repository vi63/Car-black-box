#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "keypad.h"
#include "ds1307.h"
#include "ext_eeprom.h"

// Gear state array
unsigned char *gear[] = {"ON", "GR", "GN", "G1", "G2", "G3", "-C"};

// Clock register and time array
unsigned char clock_reg[3];
unsigned char time[9];
char arr[10];
char lap = 1;
long int adc_v;
unsigned int i = 0;

// Function to store events in EEPROM
void store_event(char key) 
{
    extern unsigned int i;
    // Copy time and gear state into arr
    arr[0] = time[0];
    arr[1] = time[1];
    arr[2] = time[3];
    arr[3] = time[4];
    arr[4] = time[6];
    arr[5] = time[7];
    arr[6] = gear[i][0];
    arr[7] = gear[i][1];
    arr[8] = ((adc_v / 10 % 10) + 48);
    arr[9] = ((adc_v % 10) + 48);
    
    // Write arr to EEPROM
    for (char i = 0; i < 10; i++)
        write_ext_eeprom((lap * 10) + i, arr[i]);
    
    // Increment lap and wrap around after 10 laps
    lap++;
    if (lap == 11) 
    {
        lap = 1;
    }
}

// Function to display speed
void speed(void) 
{
    extern long int adc_v;
    // Read ADC value from channel 4
    adc_v = read_adc(CHANNEL4);
    // Display speed if within range
    if (adc_v <= 1000) 
    {
        clcd_putch('0' + (adc_v / 100), LINE2(12));
        int r = adc_v % 100;
        clcd_putch('0' + (r / 10), LINE2(13));
    }
}

// Function to display time on the LCD
void display_time(void)
{
    clcd_print(time, LINE2(0));
}

// Function to get time from DS1307
static void get_time(void) 
{
    // Read hours, minutes, and seconds from DS1307
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    // Format hours
    if (clock_reg[0] & 0x40) 
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    } 
    else 
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    
    // Format minutes and seconds
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0';
}

// Dashboard function to display and handle user input
void dashboard(char key) 
{
    while (1) 
    {
        // Read key presses
        key = read_switches(STATE_CHANGE);
        
        // Display labels on LCD
        clcd_print("TIME", LINE1(2));
        clcd_print("EV", LINE1(9));
        clcd_print("SP", LINE1(12));

        // Update and display time and speed
        get_time();
        display_time();
        speed();

        // Handle gear changes
        if (key == 2)
        {
            extern char clear_f;
            clear_f = 0;
            store_event(key);
            if (i >= 0 && i < 5)
                i++;
        }
        if (key == 3) 
        {
            extern char clear_f;
            clear_f = 0;
            store_event(key);
            if (i > 1 && i < 6)
                i--;
        }
        if (key == 1) 
        {
            extern char clear_f;
            clear_f = 0;
            store_event(key);
            i = 6;
        }
        if (i == 6 && (key == 2 || key == 3))
            i = 2;
        
        // Display current gear state
        clcd_print(gear[i], LINE2(9));

        // Exit dashboard if key 5 is pressed
        if (key == 5) 
        {
            extern char main_f;
            main_f = 1;
            break;
        }
    }

    return;
}
