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

void displaystudents() // abhi use nhi kiya hai to simplify - aage karenge
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

/* =======================================================
   🧑‍🏫 TEACHER FUNCTIONS
   These safely extend your system — no overwriting.
   ======================================================= */

// Add a new student (update hash table + file)
void add_student_teacher(const char *filename, int rollno, const char *name)
{
    if (searchStudent(rollno))
    {
        printf("⚠️ Student with roll %d already exists.\n", rollno);
        return;
    }

    // Add to in-memory hash table
    addstudent(rollno, name);

    // Add to file
    FILE *file = fopen(filename, "a");
    if (!file)
    {
        printf("Error: Could not open %s\n", filename);
        return;
    }
    fprintf(file, "%d,%s\n", rollno, name);
    fclose(file);

    printf("✅ Student added successfully: Roll %d, Name %s\n", rollno, name);
}

// Remove student (update hash table + file)
void remove_student_teacher(const char *filename, int rollno)
{
    unsigned int index = hashfunction(rollno);
    Student *current = hashtable[index];
    Student *prev = NULL;
    int found = 0;

    // Remove from hash table
    while (current)
    {
        if (current->rollno == rollno)
        {
            if (prev)
                prev->next = current->next;
            else
                hashtable[index] = current->next;

            free(current);
            found = 1;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found)
    {
        printf("⚠️ Student with roll %d not found.\n", rollno);
        return;
    }

    // Remove from file
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp)
    {
        printf("Error: Could not open file(s).\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    int roll;
    char name[50];
    while (fscanf(file, "%d,%49[^\n]\n", &roll, name) == 2)
    {
        if (roll != rollno)
            fprintf(temp, "%d,%s\n", roll, name);
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    printf("🗑️ Student with roll %d removed successfully.\n", rollno);
}
