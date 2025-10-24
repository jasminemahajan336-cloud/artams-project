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
    
    // Load classroom location from file (for cross-process sharing)
    loadClassroomLocation();
    
    // Token manager requires no explicit initialization
    
    printf("=== ARTAMS - Attendance Management System ===\n");


    while (1) {
        mainMenu();
        
        // Ask user if they want to exit
        if (confirmExit()) {

            freeAttendanceList();
            break;
        }
    }
    
    return 0;
}

// ---------------------------MAIN MENU FUNCTIONS ---------------------------

void mainMenu() {
    int mode;

    printf("\n=== Main Menu ===\n");

    printf("\n Select mode:\n"
        "    (1) Teacher\n"
        "    (2) Student\n"
        "    (3) Exit: \n");
    
    printf("> ");  // ye style ke liye hai prompt ka
    fflush(stdout); // It is to ensure prompt is displayed before input ( maltab upar wala printf stays in buffer otherwise)
    
    scanf("%d", &mode);

    if (mode == 1) {
        teacherMenu();
    }
    else if (mode == 2) {
        studentMenu();
    }
    else if (mode == 3) {
        return;
    }
    else {
        printf("Invalid choice! Please select 1, 2, or 3.\n");
    }
}

// ----------------------------TEACHER MENU FUNCTIONS ---------------------------

void teacherMenu() {
    int choice;
    double lat, lon;

    while (1) {
        printf("\n----Teacher Menu----\n");
        printf("1. Start Attendance Session\n");
        printf("2. View Attendance Log\n");
        printf("3. Return to Main Menu\n");
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
            printf("Classroom location set to (%.6f, %.6f) successfully\n", lat, lon);
            
            // Start auto-renewal session
            displayTokenWithAutoRenewal(30);
            
            waitForUserInput(); // Pause before returning to menu
        }
        else if (choice == 2) {
            printf("\n--- Attendance Log ---\n");
            loadAttendanceFromFile("data/attendance_log.txt");
            showAttendance(); // Use linked list display
            waitForUserInput(); // Pause before returning to menu   
        } 
        else if (choice == 3) {
            break;
        } 
        else {
            printf("Invalid choice. Please select 1, 2, or 3.\n");
        }
    }
}


// ----------------------------STUDENT MENU FUNCTIONS ---------------------------

void studentMenu() {
    int rollNo;
    char token[16];
    double lat, lon;
    double classroom_lat, classroom_lon;
    Student *s;

    printf("\n=== Student Attendance Marking ===\n");
    
    // Get current classroom location for student reference
    getCurrentClassroomLocation(&classroom_lat, &classroom_lon);
    printf("Current classroom location: (%.6f, %.6f)\n", classroom_lat, classroom_lon);
    printf("You must be within 100 meters of this location\n");

    // Roll number input with retry
    while (1) {
        printf("\nEnter Roll No: ");
        scanf("%d", &rollNo);

        s = searchStudent(rollNo);
        if (!s) {
            char choice;
            printf("Student not found in database!\n");
            printf("Do you want to try again? (y/n): ");
            fflush(stdout);
            clearInputBuffer();
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                continue;
            } else {
                printf("Returning to main menu...\n");
                return;
            }
        } else {
            printf("Student found: %s\n", s->name);
            break;
        }
    }
    
    // Token input with retry
    while (1) {
        printf("Enter Token: ");
        scanf("%s", token);

        if (!validateToken("data/sessions.txt", token)) {
            char choice;
            printf("Invalid or expired token!\n");
            printf("Do you want to try again? (y/n): ");
            fflush(stdout);
            clearInputBuffer();
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                continue;
            } else {
                printf("Returning to main menu...\n");
                return;
            }
        } else {
            printf("Token validated successfully!\n");
            break;
        }
    }
    
    // Location input with retry
    while (1) {
        printf("\nEnter Location (latitude longitude): ");
        printf("\nUse coordinates near (%.6f, %.6f) for valid attendance", classroom_lat, classroom_lon);
        printf("\nEnter both values on the same line, separated by space");
        printf("\nLatitude Longitude: ");
        scanf("%lf %lf", &lat, &lon);

        if (!validateLocation(lat, lon)) {
            char choice;
            double distance = getDistanceFromClassroom(lat, lon);
            printf("\nERROR: Location outside classroom range!\n");
            printf("Your coordinates: (%.6f, %.6f)\n", lat, lon);
            printf("Classroom location: (%.6f, %.6f)\n", classroom_lat, classroom_lon);
            printf("Distance: %.2f km (max allowed: 0.1 km or 100 meters)\n", distance);
            printf("\nDo you want to try again? (y/n): ");
            fflush(stdout);
            clearInputBuffer();
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                continue;
            } else {
                printf("Returning to main menu...\n");
                return;
            }
        } else {
            printf("\nLocation validated successfully!\n");
            break;
        }
    }

    // Mark attendance using linked list
    markAttendance(rollNo, lat, lon, "Present");

    printf("Your location: (%.6f, %.6f)\n", lat, lon);
    printf("Returning to main menu...\n");
}
