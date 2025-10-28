#ifndef TOKEN_MANAGER_H
#define TOKEN_MANAGER_H

#include <time.h>

void generateToken(char* token);
void saveToken(const char* filename, const char* token, int validity_seconds);
int validateToken(const char* filename, const char* token);

#endif