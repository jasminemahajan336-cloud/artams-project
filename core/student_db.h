#ifndef STUDENT_DB_H
#define STUDENT_DB_H

#define TABLE_SIZE 100

typedef struct Student {
    int rollNo;
    char name[50];
    struct Student* next;
} Student;

// Hash table functions
void initHashTable();
unsigned int hashFunction(int rollNo);

// File + database functions
void loadStudentsFromFile(const char* filename);
void saveStudentToFile(const char* filename, int rollNo, const char* name);
void addStudent(int rollNo, const char* name);
Student* searchStudent(int rollNo);
void displayStudents();

#endif

