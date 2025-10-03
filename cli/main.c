#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_db.h"

void teacherMode();
void studentMode();

int main() {
    initHashTable();
    loadStudentsFromFile("students.txt");

    int userType;
    while(1) {
        printf("\nSelect Mode:\n1. Teacher\n2. Student\nEnter choice: ");
        if(scanf("%d", &userType) != 1) {
            printf("Invalid input!\n");
            while(getchar() != '\n');
            continue;
        }

        if(userType == 1) {
            teacherMode();
            break;
        } else if(userType == 2) {
            studentMode();
            break;
        } else {
            printf("Enter 1 for Teacher or 2 for Student.\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void teacherMode() {
    char line[100];        // declare variables at the top
    FILE *log = fopen("attendance_log.txt", "r");

    if(log == NULL) {
        printf("No attendance log found.\n");
        return;
    }

    printf("Attendance Log:\n");
    while(fgets(line, sizeof(line), log)) {
        printf("%s", line);
    }

    fclose(log);
}

void studentMode() {
    int rollNo;
    char token[20];
    char gps[50];

    printf("Enter Roll Number: ");
    if(scanf("%d", &rollNo) != 1 || rollNo <= 0) {
        printf("Invalid roll number!\n"); exit(0);
    }

    if(!searchStudent(rollNo)) {
        printf("Roll number not found in database!\n"); exit(0);
    }

    printf("Enter Token: ");
    scanf("%s", token);

    // validate token
    char validToken[20];
    FILE *f = fopen("sessions.txt", "r");
    if(!f) { printf("No active session!\n"); return; }
    fscanf(f, "%s", validToken);
    fclose(f);

    if(strcmp(token, validToken) != 0) {
        printf("Invalid token!\n"); return;
    }

    printf("Enter GPS coordinates (mock): ");
    scanf(" %[^\n]", gps);  // simple input

    // append to attendance log
    FILE *log = fopen("attendance_log.txt", "a");
    if(log) {
        fprintf(log, "Roll: %d, GPS: %s\n", rollNo, gps);
        fclose(log);
        printf("Attendance recorded successfully!\n");
    } else {
        printf("Error writing attendance log.\n");
    }
}
