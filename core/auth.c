#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h"
#include "student_db.h"

#define TEACHER_FILE "data/teachers.txt"

// Simple teacher login system
int teacherLogin() {
    char username[50], password[50], stored_user[50], stored_pass[50];
    FILE *file = fopen(TEACHER_FILE, "r");
    if (!file) {
        printf("⚠️ Error: Could not open %s\n", TEACHER_FILE);
        return 0;
    }

    printf("\n=== Teacher Login ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    int success = 0;
    while (fscanf(file, "%49[^,],%49[^\n]\n", stored_user, stored_pass) == 2) {
        if (strcmp(username, stored_user) == 0 && strcmp(password, stored_pass) == 0) {
            success = 1;
            break;
        }
    }

    fclose(file);

    if (success) {
        printf("✅ Login successful! Welcome, %s\n", username);
        return 1;
    } else {
        printf("❌ Invalid credentials. Access denied.\n");
        return 0;
    }
}

// Student "login" simply checks roll and name
int studentLogin() {
    int rollno;
    char name[50];
    Student *s;

    printf("\n=== Student Login ===\n");
    printf("Enter Roll Number: ");
    scanf("%d", &rollno);
    getchar();

    printf("Enter Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    s = searchStudent(rollno);
    if (s && strcmp(s->name, name) == 0) {
        printf("✅ Welcome %s!\n", s->name);
        return 1;
    } else {
        printf("❌ Invalid roll number or name.\n");
        return 0;
    }
}
