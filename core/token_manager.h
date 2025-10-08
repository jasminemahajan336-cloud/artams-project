#ifndef TOKEN_MANAGER_H
#define TOKEN_MANAGER_H

#include <time.h>

#define TOKEN_LENGTH 8

// Basic token functions
void generateToken(char* token);
void saveToken(const char* filename, const char* token, int validity_seconds);
int validateToken(const char* filename, const char* token);

// Token status functions
int getTokenStatus(const char* filename);
void checkTokenExpiry(const char* filename);
void displayTokenInfo(const char* filename);

// Initialization and cleanup
void initTokenManager();
void cleanupTokenManager();

// Analytics
void getTokenAnalytics(const char* filename);

#endif