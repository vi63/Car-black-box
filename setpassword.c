#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "keypad.h"
#include "ds1307.h"
#include "ext_eeprom.h"

// Function to handle password setting and validation
void setpassword(char key) 
{
    // Clear the display screen
    CLEAR_DISP_SCREEN; 
    
    int attempt = 2;  // Number of attempts allowed
    char trail[5];  // Array to store entered password
    int i = 0;  // Index for entering password
    long int count = 0;  // Counter for timeout
    long int wait = 0;  // Counter for blinking cursor
    
    while (1)
    {
        // Prompt user to enter password
        clcd_print("Enter Password", LINE1(0)); 
        
        // Timeout logic to exit the function if no input is received for a while
        if (count++ == 10000)
        {
            extern char main_f;
            main_f = 0;
            CLEAR_DISP_SCREEN; 
            break;
        }
        
        // Read key press
        key = read_switches(STATE_CHANGE);
        
        // Handle password input
        if (i < 4)
        {
            // Blinking cursor logic
            if (wait++ < 500)
            {
                clcd_putch('_', LINE2(i));
            }
            else if (wait > 500 && wait < 1000)
            {
                clcd_putch(' ', LINE2(i));
            }
            else
            {
                wait = 0;
            }
            
            // Update password entry based on key press
            if (key == 5)
            {
                clcd_putch('*', LINE2(i)); 
                trail[i++] = '0';
            }
            else if (key == 6)
            {
                clcd_putch('*', LINE2(i)); 
                trail[i++] = '1';
            }
            trail[i] = '\0';  // Null-terminate the password string
        }
        
        // Compare entered password with stored password in EEPROM
        int j;
        for (j = 0; j < 4; j++)
        {
            if (trail[j] != read_ext_eeprom(j))
                break;
        }
        
        // If password matches
        if (j == 4)
        {
            CLEAR_DISP_SCREEN;
            clcd_print("Successful", LINE1(0)); // Print success message
            for (long int k = 900000; k--;); // Delay to show success message
            extern char main_f;
            main_f = 2;  // Set main_f to indicate successful login
            break;
        }
        // If password does not match and attempts are left
        else if (i > 3)
        {
            CLEAR_DISP_SCREEN;
            clcd_print("Wrong password", LINE1(0));
            clcd_putch('0' + (attempt % 10), LINE2(0));
            clcd_print("Attempts Left", LINE2(3));
            for (long int i = 50000; i--;);  // Delay
            i = 0;  // Reset index for next attempt
            attempt--;

            // Add delay of before allowing new attempt
            for (long int delay = 80000; delay--;);  

            CLEAR_DISP_SCREEN;
        }
        // If no attempts are left
        else if (attempt == -1)
        {
            CLEAR_DISP_SCREEN;
            int sec = 180;  // Block time in seconds
            while (sec != 0)
            {
                clcd_print("blocked", LINE1(0));
                clcd_putch((sec / 100) + '0', LINE2(1));
                clcd_putch(((sec / 10) % 10) + '0', LINE2(2));
                clcd_putch(sec % 10 + '0', LINE2(3));
                clcd_print("sec left", LINE2(6));
                sec--;
                for (long int i = 500000; i--;);  // Delay
            }
            attempt = 2;  // Reset attempts
            CLEAR_DISP_SCREEN;        
        }
    }
    return;
}
