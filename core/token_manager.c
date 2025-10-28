#include "token_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateToken(char* token) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int length = 8;
    
    srand((unsigned int)time(NULL));
    
    for (int i = 0; i < length; i++) {
        token[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    token[length] = '\0';
}

void saveToken(const char* filename, const char* token, int validity_seconds) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not save token to %s\n", filename);
        return;
    }
    
    time_t current_time = time(NULL);
    time_t expiry_time = current_time + validity_seconds;
    
    fprintf(file, "%s %ld\n", token, expiry_time);
    fclose(file);
}

int validateToken(const char* filename, const char* token) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return 0;
    }
    
    char stored_token[16];
    time_t expiry_time;
    
    if (fscanf(file, "%15s %ld", stored_token, &expiry_time) != 2) {
        fclose(file);
        return 0;
    }
    fclose(file);
    
    time_t current_time = time(NULL);
    
    if (strcmp(token, stored_token) == 0 && current_time <= expiry_time) {
        return 1;
    }
    
    return 0;
}
