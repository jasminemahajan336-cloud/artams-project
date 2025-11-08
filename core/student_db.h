#ifndef STUDENT_DB_H
#define STUDENT_DB_H

#define TABLE_SIZE 100

typedef struct Student {
    int rollno;
    char name[50];
    struct Student *next;
} Student;

extern Student *hashtable[TABLE_SIZE];

unsigned int hashfunction(int rollno);
void inithashTable();
void loadstudents(const char *filename);
Student *searchStudent(int rollno);
void displaystudents();

// ==============================================
// 🧑‍🏫 Teacher Functions (Enhancement)
// ==============================================
void add_student_teacher(const char *filename, int rollno, const char *name);
void remove_student_teacher(const char *filename, int rollno);

#endif
