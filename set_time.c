#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "keypad.h"
#include "ds1307.h"

extern char time[TIME_ARR_SIZE];
extern char menu_f;
extern char main_f;

int field_flag = 0; //Flag variable to blink the selected field
int long_press_S5 = 0; //Variable for long press of Switch 5
int long_press_S6 = 0; //Variable for long press of Switch 6
int flick = 0;  //Variable for delay in blinking the field
int value; //Temporary variable to store the value of time

//Function to set the time
void settime(char key)
{
    clcd_print("    SET TIME    ", LINE1(0));
    
    //get_time();
    int hour = (time[0]-48)*10+(time[1]-48);
    int minute = (time[3]-48)*10+(time[4]-48);
    int second = (time[6]-48)*10+(time[7]-48); //Variables to store the time data;
    
    //Printing the time with blinking
    clcd_putch(time[2], LINE2(6)); //Printing the colons
    clcd_putch(time[5], LINE2(9));
    
    clcd_print("    ", LINE2(0)); //Clearing the remaining part of the display
    clcd_print("    ", LINE2(12));
    
    //Blinking the field to be edited
    if( field_flag == 0 )
    {
        //Editing the second field
        if( flick == 200 )
        {
            clcd_putch(time[6], LINE2(10));
            clcd_putch(time[7], LINE2(11));
        }
        else if( flick == 400 )
        {
            flick = 0;
            clcd_putch(' ', LINE2(10));
            clcd_putch(' ', LINE2(11));
        }
        clcd_putch(time[0], LINE2(4)); //Hour
        clcd_putch(time[1], LINE2(5));
        clcd_putch(time[3], LINE2(7)); //Minute
        clcd_putch(time[4], LINE2(8));
    }
    else if( field_flag == 1 )
    {
        //Editing the minute field
        if( flick == 200 )
        {
            clcd_putch(time[3], LINE2(7));
            clcd_putch(time[4], LINE2(8));
        }
        else if( flick == 400 )
        {
            flick = 0;
            clcd_putch(' ', LINE2(7));
            clcd_putch(' ', LINE2(8));
        }
        clcd_putch(time[0], LINE2(4)); //Hour
        clcd_putch(time[1], LINE2(5));
        clcd_putch(time[6], LINE2(10)); //Seconds
        clcd_putch(time[7], LINE2(11));
    }
    else if( field_flag == 2 )
    {
        //Editing the hour field
        if( flick == 200 )
        {
            clcd_putch(time[0], LINE2(4));
            clcd_putch(time[1], LINE2(5));
        }
        else if( flick == 400 )
        {
            flick = 0;
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
        }
        clcd_putch(time[3], LINE2(7)); //Minute
        clcd_putch(time[4], LINE2(8));
        clcd_putch(time[6], LINE2(10)); //Second
        clcd_putch(time[7], LINE2(11));
    }
    flick++;
    
     key = read_switches(LEVEL_CHANGE); //Reading the key from the user
    
    if( key == MK_SW5 )
    {
        long_press_S5++;
        
        /* Logic to go back to the main menu, store the 
         updated time to RTC and store event */
        if( long_press_S5 > 800 )
        {
            long_press_S5 = 0;
            for( int wait = 3000 ; wait-- ; )
            {
                clcd_print("    SUCCESS     ", LINE2(0));
            }
            save_time_to_RTC();
            store_event(10); //Storing to external EEPROM
            main_f = MENU;
            menu_f = -1;
            CLEAR_DISP_SCREEN;
            //Display success message
        }
    }
    else if( long_press_S5 > 0 && long_press_S5 < 800 )
    {
        //Logic for incrementing the value of the index
        long_press_S5 = 0;
        if( field_flag == 0 )
        {
            //Change the second
            second++;
            if( second == 60 )
            {
                second = 0;
            }
            
            //Storing back the updated value to time array
            time[6] = (second/10)+48;
            time[7] = (second%10)+48;
        }
        else if( field_flag == 1 )
        {
            //Change the minute
            minute++;
            if( minute == 60 )
            {
                minute = 0;
            }
            //Storing back the updated value to time array
            time[3] = (minute/10)+48;
            time[4] = (minute%10)+48;
        }
        else if( field_flag == 2 )
        {
            //Change the hour
            hour++;
            if( hour == 24 )
            {
                hour = 0;
            }
            //Storing back the updated value to time array
            time[0] = (hour/10)+48;
            time[1] = (hour%10)+48;
        }
    }
    else
    {
        long_press_S5 = 0;
    }
    
    if( key == MK_SW6 )
    {
        long_press_S6++;
        
        /* Logic to go back to main menu without saving updated time to RTC */
        //Display failure message
        if( long_press_S6 > 800)
        {
            
            main_f = MENU;
            menu_f = -1;
            CLEAR_DISP_SCREEN;
        }
    }
    else if( long_press_S6 > 0 && long_press_S6 < 800 )
    {
        long_press_S6 = 0;
        
        
        long_press_S6 = 0;
        field_flag++;
        if( field_flag == 3 )
        {
            field_flag = 0;
        }
    }
    else 
    {
        long_press_S6 = 0;
    }
    
}