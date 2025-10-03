#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_db.h"

Student* hashTable[TABLE_SIZE];

void initHashTable() {
    for(int i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = NULL;
}

unsigned int hashFunction(int rollNo) {
    return rollNo % TABLE_SIZE;
}

void addStudent(int rollNo, const char* name) {
    unsigned int index = hashFunction(rollNo);

    // Create new node
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->rollNo = rollNo;
    strncpy(newStudent->name, name, 50);
    newStudent->name[49] = '\0';
    newStudent->next = hashTable[index];
    hashTable[index] = newStudent;
}

Student* searchStudent(int rollNo) {
    unsigned int index = hashFunction(rollNo);
    Student* current = hashTable[index];

    while(current != NULL) {
        if(current->rollNo == rollNo)
            return current;
        current = current->next;
    }
    return NULL;
}

void displayStudents() {
    printf("\n===== ALL STUDENTS =====\n");
    for(int i = 0; i < TABLE_SIZE; i++) {
        Student* current = hashTable[i];
        while(current != NULL) {
            printf("Roll: %d, Name: %s\n", current->rollNo, current->name);
            current = current->next;
        }
    }
}

// Load from file into hash table
void loadStudentsFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        printf("No student file found, starting fresh.\n");
        return;
    }

    int rollNo;
    char name[50];
    while(fscanf(file, "%d %[^\n]", &rollNo, name) == 2) {
        addStudent(rollNo, name);
    }

    fclose(file);
}

// Append new student to file
void saveStudentToFile(const char* filename, int rollNo, const char* name) {
    FILE* file = fopen(filename, "a");
    if(file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%d %s\n", rollNo, name);
    fclose(file);
}
