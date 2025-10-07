#include "log_manager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct attendancerecord *head = NULL;
int marked(int roll)
{
    struct attendancerecord*itr=head;
    while (itr!=NULL)
    {
        if (itr->roll_no ==roll)
        {
            return 1;
        }
        itr=itr->next;
    }
    return 0;
}
void mark_attendance(int roll,const char*token)
{
    // int a = valid_token(token);
    // if (a == 0)
    // {
    //     printf("Invalid token.\n");
    //     return;
    // }
    if (marked(roll))
    {
        printf("Attendance is already marked.\n");
        return;
    }
    time_t now = time(NULL);
    create_attendance_record(roll,now,"PRESENT");
    struct attendancerecord*itr=head;
    while (itr->next!=NULL){
        itr=itr->next;
    }
    save_attendance_record(itr);
    printf("Attendance is marked for roll_no %d.\n",roll);
}

void create_attendance_record(int roll,time_t timestamp,const char *status)
{
    struct attendancerecord* new =(struct attendancerecord*)malloc(sizeof(struct attendancerecord));
    if (new==NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    new->roll_no = roll;
    new->timestamp = timestamp;
    if(strcmp(status,"PRESENT")==0)
    {
        new->status=PRESENT;
    }
    else if(strcmp(status,"ABSENT")==0)
    {
        new->status=ABSENT;
    }
    else
    {
        new->status=ABSENT;
    }
    new->next=NULL;
    if (head==NULL)
        head=new;
    else
    {
        struct attendancerecord *itr=head;
        while (itr->next!=NULL)
            itr=itr->next;
        itr->next=new;
    }
}

void save_attendance_record(struct attendancerecord *record)
{
    FILE *fp=fopen("attendance_log.txt", "a");
    if (fp==NULL)
    {
        printf("Error opening attendance_log.txt for writing.\n");
        return;
    }
    fprintf(fp,"%s %d %ld %d\n",record->name,record->roll_no,record->timestamp,record->status);
    fclose(fp);
}
void load_attendance_log(const char *filename)
{
    FILE *fp = fopen(filename,"r");
    if (fp==NULL)
    {
        printf("Error opening %s for reading.\n",filename);
        return;
    }
    char name[50];
    int roll_no;
    long timestamp;
    int status;
    while (fscanf(fp,"%s %d %ld %d",name,&roll_no,&timestamp,&status) == 4)
    {
        create_attendance_record(roll_no,(time_t)timestamp,status==PRESENT?"PRESENT":"ABSENT");
    }
    fclose(fp);
}
void show_attendance(struct attendancerecord*head)
{
    struct attendancerecord *itr=head;
    if (itr == NULL)
    {
        printf("No attendancer records found.\n");
        return;
    }
    while (itr!=NULL)
    {
        print_attendance_record(itr);
        itr = itr->next;
    }
}
void free_attendance_list(struct attendancerecord *head)
{
    struct attendancerecord *itr = head;
    while (itr != NULL)
    {
        struct attendancerecord *temp = itr;
        itr = itr->next;
        free(temp);
    }
    head = NULL;
}
void print_attendance_record(const struct attendancerecord *record)
{
    // Convert timestamp to readable time string (HH:MM)
    char time_str[6];
    struct tm *tm_info = localtime(&record->timestamp);
    strftime(time_str, sizeof(time_str), "%H:%M", tm_info);

    printf("Roll No: %d, Time: %s, Status: %s\n",
           record->roll_no, time_str,
           record->status == PRESENT ? "Present" : "Absent");
}