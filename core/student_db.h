#ifndef STUDENT_DB_H
#define STUDENT_DB_H
#define TABLE_SIZE 100
typedef struct student {
int rollno;
int name[50];
struct student *next;   //this is i have made to avoid collision 
}Student ;
//functions
void inithashtable();
unsigned int hashfucntion(int rollno);
void addstudent(int rolllno,const char* name);
student* searchstudent(int rollno);
void displaystudents();
#endif

