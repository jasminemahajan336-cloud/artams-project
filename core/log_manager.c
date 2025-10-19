#include "log_manager.h"
#include "student_db.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Global head pointer for the linked list
static AttendanceRecord* head = NULL;

void initAttendanceLog() {
    head = NULL;
}

int isAlreadyMarked(int roll_no) {
    AttendanceRecord* current = head;
    while (current != NULL) {
        if (current->roll_no == roll_no) {
            return 1; // Already marked
        }
        current = current->next;
    }
    return 0; // Not marked
}

void markAttendance(int roll_no, double lat, double lon, const char* status) {
    // Check if student exists
    Student* student = searchStudent(roll_no);
    
    if (!student) {   // waise iski jarurat nhi hai but safety ke liye okay ( hum confirm kr chuke hai ki student exist krta hai ki nahi)

        printf("Student with roll number %d not found!\n", roll_no);
        return;
    }
    
    // Check if already marked
    if (isAlreadyMarked(roll_no)) {
        printf("Attendance already marked for %s (Roll %d)\n", student->name, roll_no);
        return;
    }
    
    // Create new attendance record
    time_t current_time = time(NULL);
    createAttendanceRecord(roll_no, student->name, current_time, lat, lon, status);
    
    // Save to file
    saveAttendanceToFile("data/attendance_log.txt");

    printf("Attendance marked for %s (Roll %d)\n", student->name, roll_no);
}


// isko use kiya hai humne inside markAttendance function me and 
void createAttendanceRecord(int roll_no, const char* name, time_t timestamp, double lat, double lon, const char* status) {
    // Allocate memory for new record
    AttendanceRecord* newRecord = (AttendanceRecord*)malloc(sizeof(AttendanceRecord));
    if (newRecord == NULL) {
        printf("ERROR: Memory allocation failed!\n");
        return;
    }
    
    // Fill record data
    newRecord->roll_no = roll_no;
    strncpy(newRecord->name, name, 49);
    newRecord->name[49] = '\0';
    newRecord->timestamp = timestamp;
    newRecord->latitude = lat;
    newRecord->longitude = lon;
    
    // Set status
    if (strcmp(status, "Present") == 0 || strcmp(status, "PRESENT") == 0) {
        newRecord->status = PRESENT;
    } else {
        newRecord->status = ABSENT;
    }
    
    newRecord->next = NULL;
    
    // Add to end of linked list (chronological order)
    if (head == NULL) {
        head = newRecord;
    } else {
        AttendanceRecord* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newRecord;
    }
}

void saveAttendanceToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("[ERROR] Could not save to file %s\n", filename);
        return;
    }
    
    AttendanceRecord* current = head;
    while (current != NULL) {
        struct tm* time_info = localtime(&current->timestamp);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
        
        fprintf(file, "Roll: %d, Name: %s, Time: %s, Location: (%.6f, %.6f), Status: %s\n",
                current->roll_no, current->name, time_str, 
                current->latitude, current->longitude,
                current->status == PRESENT ? "Present" : "Absent");
        
        current = current->next;
    }
    
    fclose(file);
}

void loadAttendanceFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return; // File doesn't exist yet
    }
    
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        int roll_no;
        char name[50], time_str[20], status_str[10];
        double lat, lon;
        
        if (sscanf(line, "Roll: %d, Name: %49[^,], Time: %19[^,], Location: (%lf, %lf), Status: %9s",
                   &roll_no, name, time_str, &lat, &lon, status_str) == 6) {
            
            // Convert time string back to timestamp
            time_t timestamp = time(NULL); // For now, use current time
            
            createAttendanceRecord(roll_no, name, timestamp, lat, lon, status_str);
        }
    }
    
    fclose(file);
}

void showAttendance() {
    if (head == NULL) {
        printf("No attendance records found.\n");
        return;
    }
    
    printf("\n=== Attendance Records (Chronological Order) ===\n");
    AttendanceRecord* current = head;
    int count = 1;
    
    while (current != NULL) {
        printf("%d. ", count++);
        printAttendanceRecord(current);
        current = current->next;
    }
    printf("===============================================\n");
}

// used in showAttendance function
void printAttendanceRecord(const AttendanceRecord* record) {
    struct tm* time_info = localtime(&record->timestamp);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    
    printf("Roll: %d, Name: %s, Time: %s, Location: (%.6f, %.6f), Status: %s\n",
           record->roll_no, record->name, time_str,
           record->latitude, record->longitude,
           record->status == PRESENT ? "Present" : "Absent");
}

void freeAttendanceList() {
    AttendanceRecord* current = head;
    while (current != NULL) {
        AttendanceRecord* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}
