#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/student_db.h"
#include "../core/token_manager.h"
#include "../core/log_manager.h"
#include "../core/location_validator.h"

void teacherMenu();
void studentMenu();

int main() {
    int mode;
    inithashTable();
    loadstudents("../data/students.txt");

    printf("Select mode: (1) Teacher  (2) Student: ");
    fflush(stdout);
    if (scanf("%d", &mode) != 1) {
        printf("Invalid input!\n");
        return 0;
    }

    if (mode == 1)
        teacherMenu();
    else if (mode == 2)
        studentMenu();
    else
        printf("Invalid choice!\n");

    return 0;
}

void teacherMenu() {
    int choice;
    char token[16];

    while (1) {
        printf("\n[Teacher Menu]\n");
        printf("1. Start Attendance Session\n");
        printf("2. View Attendance Log\n");
        printf("3. Exit\n");
        printf("> ");
        fflush(stdout);
        scanf("%d", &choice);

        if (choice == 1) {
            generateToken(token);
            saveToken("../data/sessions.txt", token, 30); // token valid 30s
            printf("\nSession started!\nToken: %s (valid 30s)\n", token);
        } 
        else if (choice == 2) {
            printf("\n--- Attendance Log ---\n");
            showAttendance("../data/attendance_log.txt");
        } 
        else if (choice == 3) {
            printf("Exiting Teacher Mode...\n");
            break;
        } 
        else {
            printf("Invalid choice.\n");
        }
    }
}

void studentMenu() {
    int rollNo;
    char token[16];
    double lat, lon;

    printf("Enter Roll No: ");
    scanf("%d", &rollNo);

    Student *s = searchStudent(rollNo);
    if (!s) {
        printf("Student not found in database!\n");
        return;
    }

    printf("Enter Token: ");
    scanf("%s", token);

    if (!validateToken("../data/sessions.txt", token)) {
        printf("❌ Invalid or expired token!\n");
        return;
    }

    printf("Enter Location (latitude longitude): ");
    scanf("%lf %lf", &lat, &lon);

    if (!validateLocation(lat, lon)) {
        printf("❌ Location outside classroom range!\n");
        return;
    }

    markAttendance("../data/attendance_log.txt", rollNo, lat, lon, "Present");
    printf("[INFO] Attendance marked successfully for Roll %d!\n", rollNo);
}
