#ifndef STUDENT_DB_H
#define STUDENT_DB_H
#define TABLE_SIZE 100
typedef struct Student {
    int rollno;
    char name[50];
    struct Student* next;
} Student;
void inithashtable();
void loadstudents(const char* filename);
Student* searchstudent(int rollNo);
void displaystudents();
#endif

