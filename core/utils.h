#ifndef UTILS_H
#define UTILS_H

void clearInputBuffer();
void displayWelcomeMessage();
int confirmExit();
void waitForUserInput();
int askRetry(const char* message);
void displayTokenWithTimer(const char* token, int duration);
void displayTokenWithAutoRenewal(int duration);

#endif