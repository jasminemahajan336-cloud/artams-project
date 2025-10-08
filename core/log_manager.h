#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <time.h>  

#define PRESENT 1
#define ABSENT 0

typedef struct AttendanceRecord {
    int roll_no;
    char name[50];
    time_t timestamp;
    double latitude;
    double longitude;
    int status; // PRESENT or ABSENT
    struct AttendanceRecord* next;
} AttendanceRecord;

// Linked list functions
void initAttendanceLog();
int isAlreadyMarked(int roll_no);
void markAttendance(int roll_no, double lat, double lon, const char* status);
void createAttendanceRecord(int roll_no, const char* name, time_t timestamp, double lat, double lon, const char* status);
void saveAttendanceToFile(const char* filename);
void loadAttendanceFromFile(const char* filename);
void showAttendance();
void freeAttendanceList();
void printAttendanceRecord(const AttendanceRecord* record);

// File-based functions (for compatibility)
void showAttendanceFromFile(const char* filename);

#endif