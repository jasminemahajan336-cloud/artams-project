#ifndef UTILS_H
#define UTILS_H

void clearInputBuffer();
int confirmExit();
void waitForUserInput();
int askRetry(const char* message);
void displayTokenWithAutoRenewal(int duration);

#endif