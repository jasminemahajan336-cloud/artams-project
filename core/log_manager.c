#include "log_manager.h"
#include "student_db.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static AttendanceRecord* head = NULL;

void initAttendanceLog() {
    head = NULL;
}

int isAlreadyMarked(int roll_no) {
    // Check if student is already marked TODAY
    char* todayDate = getCurrentDateString();
    char filename[100];
    snprintf(filename, sizeof(filename), "data/attendance_%s.txt", todayDate);
    
    FILE* file = fopen(filename, "r");
    if (file) {
        char line[200];
        int stored_roll;
        
        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "Roll: %d,", &stored_roll) == 1) {
                if (stored_roll == roll_no) {
                    fclose(file);
                    return 1; // Already marked today
                }
            }
        }
        fclose(file);
    }
    
    // Also check in-memory list (fallback)
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
    // Create new attendance record and persist it
    createAttendanceRecord(roll_no, student->name, current_time, lat, lon, status);
    
    // Save to main log file
    saveAttendanceToFile("data/attendance_log.txt"); 
    
    // DYNAMIC: Also save to date-specific file
    char* currentDate = getCurrentDateString();
    saveAttendanceByDate(currentDate);

    printf("Attendance marked for %s (Roll %d)\n", student->name, roll_no);
    printf("Saved to date file: attendance_%s.txt\n", currentDate);
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
        printf("Error- Could not save to file %s\n", filename);
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
        return;
    }
    
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        int roll_no;
        char name[50], time_str[20], status_str[10];
        double lat, lon;
        
        if (sscanf(line, "Roll: %d, Name: %49[^,], Time: %19[^,], Location: (%lf, %lf), Status: %9s",
                   &roll_no, name, time_str, &lat, &lon, status_str) == 6) {
            
            // Parse time string back to timestamp
            struct tm tm_time = {0};
            sscanf(time_str, "%d-%d-%d %d:%d:%d", 
                   &tm_time.tm_year, &tm_time.tm_mon, &tm_time.tm_mday,
                   &tm_time.tm_hour, &tm_time.tm_min, &tm_time.tm_sec);
            
            tm_time.tm_year -= 1900;  // Years since 1900
            tm_time.tm_mon -= 1;       // Months are 0-11
            tm_time.tm_isdst = -1;     // Let system determine DST
            
            time_t timestamp = mktime(&tm_time);
            
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
    
    printf("\n=== Attendance Records ===\n");
    AttendanceRecord* current = head;
    int count = 1;
    
    while (current != NULL) {
        printf("%d. ", count++);
        printAttendanceRecord(current);
        current = current->next;
    }
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
// Date-based functions implementation

void saveAttendanceByDate(const char* date) {
    char filename[100];
    snprintf(filename, sizeof(filename), "data/attendance_%s.txt", date);
    
    // Check if file exists, if not create it
    FILE* file = fopen(filename, "a"); // Append mode for dynamic creation
    if (!file) {
        printf("Error: Could not create/open %s\n", filename);
        return;
    }
    
    // Find the most recent attendance record (last one added)
    AttendanceRecord* current = head;
    AttendanceRecord* lastRecord = NULL;
    
    while (current != NULL) {
        lastRecord = current;
        current = current->next;
    }
    
    if (lastRecord != NULL) {
        // Write only the latest record to the date file
        struct tm* time_info = localtime(&lastRecord->timestamp);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
        
        fprintf(file, "Roll: %d, Name: %s, Time: %s, Location: (%.6f, %.6f), Status: %s\n",
                lastRecord->roll_no, lastRecord->name, time_str, 
                lastRecord->latitude, lastRecord->longitude,
                lastRecord->status == PRESENT ? "Present" : "Absent");
    }
    
    fclose(file);
}

void loadAttendanceByDate(const char* date) {
    char filename[100];
    snprintf(filename, sizeof(filename), "data/attendance_%s.txt", date);
    
    // Clear current attendance list first
    freeAttendanceList();
    initAttendanceLog();
    
    loadAttendanceFromFile(filename);
}

void showAttendanceByDate(const char* date) {
    char filename[100];
    snprintf(filename, sizeof(filename), "data/attendance_%s.txt", date);
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("No attendance records found for %s\n", date);
        return;
    }
    
    printf("\n=== Attendance Records for %s ===\n", date);
    char line[200];
    int count = 1;
    
    while (fgets(line, sizeof(line), file)) {
        printf("%d. %s", count++, line);
    }
    
    fclose(file);
}

char* getCurrentDateString() {
    static char dateStr[20];
    time_t now;
    struct tm *timeinfo;
    
    time(&now);
    timeinfo = localtime(&now);
    strftime(dateStr, sizeof(dateStr), "%d%b", timeinfo);
    
    // Convert to uppercase
    for(int i = 0; dateStr[i]; i++) {
        if(dateStr[i] >= 'a' && dateStr[i] <= 'z') {
            dateStr[i] = dateStr[i] - 'a' + 'A';
        }
    }
    
    return dateStr;
}

