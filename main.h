

#define DASHBOARD               0
#define PASSWORD                1
#define MENU                    2
#define MENU_ENTER              3
#define VIEWLOG                 0
#define DOWNLOADLOG             1
#define CLEARLOG                2
#define SETTIME                 3
#define CHANGEPASS              4
#define TIME_ARR_SIZE          9
void dashboard(char key);               
void store_event(char key);
void setpassword(char key);
void menu(char key);
void view_log(char key);
void download_log(char key);
void clear_log(char key);
void settime(char key);
void change_pass(char key);
void save_time_to_RTC();

