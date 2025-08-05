#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "keypad.h"
#include "ds1307.h"
#include "ext_eeprom.h"

void change_pass(char key) 
{
    CLEAR_DISP_SCREEN;
    long int wait = 0;
    int i = 0;
    char new_password[5];
    char confirm_password[5];
    int pwd_flag = 0;

    do
    {
        // Enter new password
        CLEAR_DISP_SCREEN;
        clcd_print("Enter New Password", LINE1(0));
        i = 0;
        while (i < 4) 
        {
            key = read_switches(STATE_CHANGE);
        
            if (wait++ < 2000)
                clcd_putch('_', LINE2(i));
            else if (wait > 2000 && wait < 4000)
                clcd_putch(' ', LINE2(i));
            else
                wait = 0;

            if (key == 5) 
            {
                clcd_putch('*', LINE2(i)); 
                new_password[i++] = '0';       
            } 
            else if (key == 6) 
            {
                clcd_putch('*', LINE2(i)); 
                new_password[i++] = '1';       
            }
        }
        new_password[i] = '\0';

        // Confirm new password
        CLEAR_DISP_SCREEN;
        clcd_print("Confirm Password", LINE1(0));
        i = 0;
        while (i < 4) 
        {
            key = read_switches(STATE_CHANGE);
        
            if (wait++ < 2000)
                clcd_putch('_', LINE2(i));
            else if (wait > 2000 && wait < 4000)
                clcd_putch(' ', LINE2(i));
            else
                wait = 0;

            if (key == 5) 
            {
                clcd_putch('*', LINE2(i)); 
                confirm_password[i++] = '0';       
            } 
            else if (key == 6) 
            {
                clcd_putch('*', LINE2(i)); 
                confirm_password[i++] = '1';       
            }
        }
        confirm_password[i] = '\0';
    
        // Check if new password and confirm password match
        if (strcmp(new_password, confirm_password) == 0)
        {
            // Write new password to EEPROM
            for (int p = 0; p < 4; p++)
            {
                write_ext_eeprom(p, new_password[p]);
            }

            pwd_flag = 1;

            if (pwd_flag) 
            {
                CLEAR_DISP_SCREEN;
                clcd_print("Change Password", LINE1(0));
                clcd_print("Successful!!", LINE2(2));
                for (long int k = 900000; k--;);
                extern char main_f;
                main_f = 2;
                CLEAR_DISP_SCREEN;
            }
        } 
        else 
        {
            CLEAR_DISP_SCREEN;
            clcd_print("Passwords Do Not", LINE1(0));
            clcd_print("Match", LINE2(3));
            for (long int k = 900000; k--;);
        }
    } while (!pwd_flag);
}
