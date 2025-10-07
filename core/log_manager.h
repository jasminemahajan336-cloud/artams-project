#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <time.h>  
#define PRESENT 1
#define ABSENT 0
struct attendancerecord {
    char name[50];
    int roll_no;
    time_t timestamp;   
    int status; 
    struct attendancerecord *next;
};

void mark_attendance(int roll, const char *token);
void show_attendance(void);
void load_attendance_log(const char *filename);
void free_attendance_list(void);
int marked(int roll);
//int valid_token(const char* token);
void create_attendance_record(int roll, time_t timestamp, const char *status);
void save_attendance_record( struct attendancerecord *record);
void print_attendance_record(const struct attendancerecord *record);
#endif