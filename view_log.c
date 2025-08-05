#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "keypad.h"
#include "ds1307.h"
#include "ext_eeprom.h"

// Global variables to keep track of log position
char axis = 1;
char count = 1;
extern char clear_f;  // Flag to indicate if logs are cleared

// Function to view log entries
void view_log(char key) 
{
    int i = 0;        // Loop variable
    int s = 0;        // Variable to toggle between different states (if needed)
    char prev_key;    // Variable to store the previous key pressed
    int delay = 0;    // Variable to manage key press delay
    
    // Clear the display screen and print the header
    CLEAR_DISP_SCREEN; 
    clcd_print("VIEW LOGS", LINE1(3));

    while (1)
    {
        // Read the key press
        key = read_switches(LEVEL_CHANGE);
      
        // If any key is pressed
        if (key != ALL_RELEASED)
        {
            prev_key = key;  // Store the key pressed
            delay++;
            // If key is held for a short duration
            if (delay > 200)
                key = key + 10;  // Increase key value to indicate long press
            else
                key = 0;
        }
        // If key was released before the long press threshold
        else if (delay < 200 && delay != 0)
        {
            delay = 0;  // Reset delay
            key = prev_key;  // Use the previously pressed key
        }
        else
        {
            delay = 0;  // Reset delay if no key is pressed
        }
  
        char readdata[10];  // Buffer to store log data read from EEPROM
        extern char lap;    // External variable (if used elsewhere in the code)
        
        // Reset axis and count if the end of logs is reached
        if (axis >= 10)
        {
            axis = 1;
            count = 1;
        }
       
        // Check if logs are cleared
        if (clear_f)
        {
            clcd_print("(Empty)", LINE2(3));
        }
        else
        {
            // Read log data from external EEPROM
            for (int k = 0; k < 10; k++)
                readdata[k] = read_ext_eeprom((axis * 10) + k);

            // Display the log data
            clcd_putch(count + '0', LINE2(0));
            clcd_putch(readdata[0], LINE2(2));
            clcd_putch(readdata[1], LINE2(3));
            clcd_putch(':', LINE2(4));
            clcd_putch(readdata[2], LINE2(5));
            clcd_putch(readdata[3], LINE2(6));
            clcd_putch(':', LINE2(7));
            clcd_putch(readdata[4], LINE2(8));
            clcd_putch(readdata[5], LINE2(9));
            clcd_putch(' ', LINE2(10));
            clcd_putch(readdata[6], LINE2(11));
            clcd_putch(readdata[7], LINE2(12));
            clcd_putch(' ', LINE2(13));
            clcd_putch(readdata[8], LINE2(14));
            clcd_putch(readdata[9], LINE2(15));
        }
        
        // Navigate to the next log entry if key 6 (Down) is pressed
        if (key == 6)
        {
            axis++;
            count++;
        }
        
        // Exit the log view if key 16 (Back) is pressed
        if (key == 16)
        {
            extern char main_f;
            CLEAR_DISP_SCREEN;
            main_f = 2;  // Set main flag to indicate returning to the main menu
            break;  // Exit the while loop
        }
    }
    return;
}
