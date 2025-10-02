#ifndef STUDENT_DB_H
#define STUDENT_DB_H

typedef struct Student {
    int rollNo;
    char name[50];
} Student;

void initHashTable();
void addStudent(int rollNo, char* name);
Student* searchStudent(int rollNo);
void displayStudents();

#endif
