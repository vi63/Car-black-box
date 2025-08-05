#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "keypad.h"
#include "ds1307.h"

// Menu options
char *vmenu[] = {"View log", "Download log", "Clear log", "Set time", "Change password"};

// Function to handle the menu navigation and selection
void menu(char key) 
{
    int i = 0;      // Index for menu items
    int s = 0;      // Toggle between line1 and line2 for highlighting
    char prev_key;  // Previous key pressed
    int delay = 0;  // Delay counter for key press
    int blink = 0;  // Counter for blinking effect

    // Clear the display screen
    CLEAR_DISP_SCREEN; 
    
    while (1) 
    {
        // Read key pressed
        key = read_switches(LEVEL_CHANGE);
        
        // If any key is pressed
        if (key != ALL_RELEASED) 
        {
            prev_key = key;  // Store the key pressed
            delay++;
            // If key is held for a long time, increase key value to indicate long press
            if (delay > 1000)
                key = key + 10;
            else
                key = 0;
        } 
        // If key was released before the long press threshold
        else if (delay < 1000 && delay != 0) 
        {
            delay = 0;  // Reset delay
            key = prev_key;  // Use the previously pressed key
        } 
        else 
        {
            delay = 0;  // Reset delay if no key is pressed
        }
        
        // Key navigation logic
        if (key == 5) 
        {  // If key 5 (Up) is pressed
            if (s == 1)
                s = 0;
            else if (i > 0) 
            {
                i--;  // Move up in the menu
                CLEAR_DISP_SCREEN;
            }
        }
        
        if (key == 6) 
        {  // If key 6 (Down) is pressed
            if (s == 0)
                s = 1;
            else if (i >= 0 && i < 3) 
            {
                i++;  // Move down in the menu
                CLEAR_DISP_SCREEN;
            }
        }
        
        // Blinking star logic
        blink++;
        if (blink < 500) 
        {
            if (s == 0) 
            {
                clcd_putch('*', LINE1(0));  
                clcd_putch(' ', LINE2(0));  
            } 
            else 
            {
                clcd_putch(' ', LINE1(0));  
                clcd_putch('*', LINE2(0));  
            }
        } 
        else if (blink >= 500 && blink < 1000) 
        {
            if (s == 0) 
            {
                clcd_putch(' ', LINE1(0));  
                clcd_putch(' ', LINE2(0));  
            } 
            else 
            {
                clcd_putch(' ', LINE1(0));  
                clcd_putch(' ', LINE2(0));  
            }
        } 
        else 
        {
            blink = 0;  // Reset the blink counter
        }
        
        // Print the current and next menu items
        clcd_print(vmenu[i], LINE1(1)); 
        clcd_print(vmenu[i + 1], LINE2(1));
        
        // Menu option selection logic
        if (key == 15) 
        {  // If key 15 (Select) is pressed
            extern char main_f;
            extern char menu_f;
            CLEAR_DISP_SCREEN;
            main_f = 3;
            
            // Determine which menu option is selected
            if (i == 0 && s == 0) 
            {
                menu_f = 0;  // View log
            } 
            else if ((i == 0 && s == 1) || (i == 1 && s == 0)) 
            {
                menu_f = 1;  // Download log
            } 
            else if ((i == 1 && s == 1) || (i == 2 && s == 0)) 
            {
                
                menu_f = 2;  // Clear log
            } 
            else if ((i == 2 && s == 1) || (i == 3 && s == 0)) 
            {
                menu_f = 3;  // Set time
            } 
            else if ((i == 3 && s == 1)) 
            {
                menu_f = 4;  // Change password
            }
            break;  // Exit the menu loop
        }
        
        // If key 6 (Back) is pressed, exit the menu
        if (key == 16) 
        {
            extern char main_f;
            CLEAR_DISP_SCREEN;
            main_f = 0; 
            break;
        }
    }  
    return;
}

