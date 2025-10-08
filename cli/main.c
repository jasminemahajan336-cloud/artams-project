#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/student_db.h"
#include "../core/token_manager.h"
#include "../core/log_manager.h"
#include "../core/location_validator.h"
#include "../core/utils.h"

void teacherMenu();
void studentMenu();
void mainMenu();

int main() {
    inithashTable();
    loadstudents("data/students.txt");
    
    // Initialize attendance log
    initAttendanceLog();
    loadAttendanceFromFile("data/attendance_log.txt");
    
    // Initialize token manager with Min-Heap and Hash Set
    initTokenManager();
    
    printf("=== ARTAMS - Attendance Management System ===\n");


    while (1) {
        mainMenu();
        
        // Ask user if they want to exit
        if (confirmExit()) {
            // Save attendance to file before exiting
            saveAttendanceToFile("data/attendance_log.txt");
            freeAttendanceList();
            
            // Cleanup token manager
            cleanupTokenManager();
            break;
        }
    }
    
    return 0;
}

void mainMenu() {
    int mode;

    printf("\n[MAIN MENU] Select mode:\n (1) Teacher  \n(2) Student  \n(3) Exit: ");
    fflush(stdout);
    
    if (scanf("%d", &mode) != 1) {
        printf("[ERROR] Invalid input!\n");
        clearInputBuffer();
        return;
    }

    if (mode == 1) {
        teacherMenu();
    }
    else if (mode == 2) {
        studentMenu();
        waitForUserInput();
    }
    else if (mode == 3) {
        return;
    }
    else {
        printf("[ERROR] Invalid choice! Please select 1, 2, or 3.\n");
    }
}

void teacherMenu() {
    int choice;
    double lat, lon;

    while (1) {
        printf("\n[Teacher Menu]\n");
        printf("1. Start Attendance Session\n");
        printf("2. View Attendance Log\n");
        printf("3. View Token Analytics\n");
        printf("4. Return to Main Menu\n");
        printf("> ");
        fflush(stdout);
        scanf("%d", &choice);

        if (choice == 1) {

            printf("\n=== Classroom Location Setup ===\n");
            printf("Enter classroom latitude: ");
            scanf("%lf", &lat);
            printf("Enter classroom longitude: ");
            scanf("%lf", &lon);

            setClassroomLocation(lat, lon);
            printf("[SUCCESS] Classroom location set to (%.6f, %.6f)\n", lat, lon);

            printf("[INFO] Starting auto-renewal session - tokens will regenerate every 32 seconds\n");
            printf("[INFO] Students must be within 100m of the classroom location\n");
            
            // Start auto-renewal session
            displayTokenWithAutoRenewal(30);
            waitForUserInput();
        }
        else if (choice == 2) {
            printf("\n--- Attendance Log ---\n");
            showAttendance(); // Use linked list display
            waitForUserInput();
        } 
        else if (choice == 3) {
            getTokenAnalytics("data/sessions.txt");
            waitForUserInput();
        }

        else if (choice == 4) {
            printf("[INFO] Returning to Main Menu...\n");
            break;
        } 
        else {
            printf("[ERROR] Invalid choice. Please select 1, 2, 3, or 4.\n");
        }
    }
}

void studentMenu() {
    int rollNo;
    char token[16];
    double lat, lon;
    double classroom_lat, classroom_lon;
    Student *s;
    int retry = 1;

    printf("\n=== Student Attendance Marking ===\n");
    
    // Get current classroom location for student reference
    getCurrentClassroomLocation(&classroom_lat, &classroom_lon);
    printf("[INFO] Current classroom location: (%.6f, %.6f)\n", classroom_lat, classroom_lon);
    printf("[INFO] You must be within 100 meters of this location\n");
    
    // Roll number input with retry
    while (retry) {
        printf("\nEnter Roll No: ");
        scanf("%d", &rollNo);

        s = searchStudent(rollNo);
        if (!s) {
            if (askRetry("[ERROR] Student not found in database!\n")) {
                continue;
            } else {
                printf("[INFO] Returning to main menu...\n");
                return;
            }
        } else {
            printf("[SUCCESS] Student found: %s\n", s->name);
            break;
        }
    }
    
    // Token input with retry
    retry = 1;
    while (retry) {
        printf("Enter Token: ");
        scanf("%s", token);

        if (!validateToken("data/sessions.txt", token)) {
            if (askRetry("[ERROR] Invalid or expired token!\n")) {
                continue;
            } else {
                printf("[INFO] Returning to main menu...\n");
                return;
            }
        } else {
            printf("[SUCCESS] Token validated successfully!\n");
            break;
        }
    }
    
    // Location input with retry
    retry = 1;
    while (retry) {
        printf("Enter Location (latitude longitude): ");
        printf("\n[Hint: Use coordinates near (%.6f, %.6f) for valid attendance]\n", classroom_lat, classroom_lon);
        printf("Latitude Longitude: ");
        scanf("%lf %lf", &lat, &lon);

        if (!validateLocation(lat, lon)) {
            printf("[ERROR] Location outside classroom range!\n");
            printf("[INFO] Your coordinates: (%.6f, %.6f)\n", lat, lon);
            printf("[INFO] Required coordinates: within 100m of (%.6f, %.6f)\n", classroom_lat, classroom_lon);
            if (askRetry("")) {
                continue;
            } else {
                printf("[INFO] Returning to main menu...\n");
                return;
            }
        } else {
            printf("[SUCCESS] Location validated successfully!\n");
            break;
        }
    }

    // Mark attendance using linked list
    markAttendance(rollNo, lat, lon, "Present");
    printf("[INFO] Your location: (%.6f, %.6f)\n", lat, lon);
    printf("[INFO] Returning to main menu...\n");
}
