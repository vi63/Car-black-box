#include <xc.h>
#include "main.h"
#include "uart.h"
#include "clcd.h"
#include "keypad.h"
#include "ds1307.h"
#include "ext_eeprom.h"

// External variables used in the program
extern char main_f;
extern char lap;

// Array to hold data read from EEPROM
char arr1[11];

// Function to download log data from EEPROM and send it over UART
void download_log(char key) 
{
    int k;
    static char index = 1;  // Static variable to keep track of the current index
    
    // Print success message
    puts("Downloaded Successful!");
    puts("\n\r");

    // Loop through the EEPROM memory and read log data
    for (int j = 1; j < 10; j++) {
        // Read 10 bytes of data from EEPROM into arr1
        for (k = 0; k < 10; k++)
            arr1[k] = read_ext_eeprom((j * 10) + k);
        
        // Print the data in the desired format HH:MM:SS XX YY
        putch(arr1[0]);
        putch(arr1[1]);
        putch(':');
        putch(arr1[2]);
        putch(arr1[3]);
        putch(':');
        putch(arr1[4]);
        putch(arr1[5]);
        putch(' ');
        putch(arr1[6]);
        putch(arr1[7]);
        putch(' ');
        putch(arr1[8]);
        putch(arr1[9]);
        puts("\n\r");
    }

    // Reset the index
    index = 1;
    
    // Set main_f to 2 to indicate the completion of the log download
    main_f = 2;
}
