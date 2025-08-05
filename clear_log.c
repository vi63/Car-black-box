


#include <xc.h>
#include "clcd.h"
#include "keypad.h"



extern char clear_f;
extern char main_f;

void clear_log(char key) 
{
    extern char lap;
    lap = 1;
    clear_f = 1;
    
    int t = 0;
    int long_press_detected = 0;
    
    while (t < 3800) 
    { // Adjust this loop for your required delay
        clcd_print("Logs Cleared!!", LINE1(1));
        key = read_switches(LEVEL_CHANGE); // Check for switch 6
        
        if (key == 6) 
        {
            long_press_detected = 1;
            t++; // Increment the timer while switch 6 is pressed
        } 
        else 
        {
            long_press_detected = 0; // Reset long press flag if switch 6 is released
            t = 0; // Reset timer if switch 6 is released
        }
    }
    
    if (long_press_detected) 
    {
        main_f = 2; // Go back to menu after long press detected
    }
    
    return;
}
