/*   
 * Name : VIDYA V K
 * Register No : 23029_251
 * Project Title: Car Black Box
 */



#include <xc.h>
#include "clcd.h"
#include "adc.h"
#include "keypad.h"
#include "main.h"
#include "ds1307.h"
#include "i2c.h"
#include "ext_eeprom.h"
#include "uart.h"


char main_f = 0, menu_f = 0, key;
extern unsigned char time[9];
char h1, m1, s1;
char original[5] = "1110";
char clear_f = 0;

// Function to initialize peripherals
void inti_config() 
{
    init_adc();
    init_clcd();
    init_matrix_keypad();
    init_i2c();
    init_ds1307();
    init_uart();
    
}

void main(void)
{
    inti_config();

    // Store the default password in EEPROM
    for (int i = 0; i < 4; i++)
        write_ext_eeprom(i, original[i]);

    // Main loop
    while (1)
    {   
        key = read_switches(STATE_CHANGE);
        
        // Switch between different modes based on main_f
        if (main_f == DASHBOARD) 
        {
            CLEAR_DISP_SCREEN;
            dashboard(key);
        } 
        else if (main_f == PASSWORD) 
        {
            setpassword(key);
        } 
        else if (main_f == MENU) 
        {
            // Extract hours, minutes, and seconds from time array
            h1 = (((time[0] - 48) * 10) + (time[1] - 48)); 
            m1 = (((time[3] - 48) * 10) + (time[4] - 48)); 
            s1 = (((time[6] - 48) * 10) + (time[7] - 48)); 
            menu(key);
        } 
        else if (main_f == MENU_ENTER) 
        {
            // Handle different menu options
            if (menu_f == VIEWLOG)
            {
                view_log(key);
            } 
            else if (menu_f == DOWNLOADLOG) 
            {
                download_log(key);
            } 
            else if (menu_f == CLEARLOG) 
            {
                clear_log(key);
            } 
            else if (menu_f == SETTIME)
            {
                settime(key);
            } 
            else if (menu_f == CHANGEPASS) 
            {
                change_pass(key);
            }
        }
    }

    return;
}
