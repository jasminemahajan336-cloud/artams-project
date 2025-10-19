#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_db.h"
Student *hashtable[TABLE_SIZE];

unsigned int hashfunction(int rollno)
{
    return rollno % TABLE_SIZE;
}

void inithashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
    }
}

static void addstudent(int rollno, const char *name)
{ // adding student(internally in hashtable)
    unsigned int index = hashfunction(rollno);
    Student *newstudent = (Student *)malloc(sizeof(Student));
    newstudent->rollno = rollno;
    strncpy(newstudent->name, name, 50);
    newstudent->name[49] = '\0';
    newstudent->next = hashtable[index];
    hashtable[index] = newstudent;
}

Student *searchStudent(int rollno)
{
    unsigned int index = hashfunction(rollno);
    Student *current = hashtable[index];
    while (current)
    {
        if (current->rollno == rollno)
            return current;
        current = current->next;
    }
    return NULL;
}

void displaystudents()   // abhi use nhi kiya hai to simplify - aage karenge
{
    printf("\n---ALL STUDENTS---\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Student *current = hashtable[i];
        while (current)
        {
            printf("Roll:%d, Name:%s\n", current->rollno, current->name);
            current = current->next;
        }
    }
}

void loadstudents(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf(" No students file found.\n");
        return;
    }
    int rollno;
    char name[50];
    while (fscanf(file, "%d,%49[^\n]\n", &rollno, name) == 2)
    {
        addstudent(rollno, name);
    }
    fclose(file);
}
