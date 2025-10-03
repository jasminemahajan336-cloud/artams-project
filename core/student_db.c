#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "student_db.h"
Student *hashtable[TABLE_SIZE];
//here initialising the hash table
void inithashtable(){
    for(int i=0;i<TABLE_SIZE;i++){
        hashtable[i]=NULL;
    }
    
}