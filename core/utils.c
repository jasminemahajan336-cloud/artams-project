#include "utils.h"
#include "../core/token_manager.h"
#include <stdio.h>
#include <ctype.h>


#ifdef _WIN32
#include <windows.h>
#include <conio.h>

#define SLEEP(x) Sleep(x * 1000)  // ye aapka displayTokenWithAutoRenewal function me time delay ke liye hai

#define KBHIT() _kbhit()
#else
#include <unistd.h>
#define SLEEP(x) sleep(x)
// KBHIT macro not needed on non-Windows
#endif

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int confirmExit() {
    char choice;
    printf("\nDo you want to exit the application? (y/n): ");
    fflush(stdout);
    
    clearInputBuffer(); // Clear any previous input
    scanf("%c", &choice);
    
    choice = tolower(choice);
    
    if (choice == 'y') {
        printf("Thank you for using ARTAMS! Goodbye!\n");
        return 1; // Exit confirmed
    } else {
        printf("Returning to main menu...\n");
        return 0; // Don't exit
    }
}

void waitForUserInput() {
    printf("\nPress Enter to continue...");
    clearInputBuffer();
    getchar();
}

void displayTokenWithAutoRenewal(int duration) {
    char token[16];
    int session_count = 1;
    
    printf("Press 'q' and Enter to stop the session\n");
    
    while (1) {
        
        // Generate new token
        generateToken(token);
        saveToken("data/sessions.txt", token, duration);
        
        printf("\n[SESSION %d] New token generated: %s\n", session_count, token);
        
        // Display countdown with key check
        for (int i = duration; i > 0; i--) {
            printf("\r[TOKEN] %s (expires in %d seconds) - Press 'q' + Enter to stop   ", token, i);
            fflush(stdout);
            
            // Check for user input (Windows only for now)
            #ifdef _WIN32
            if (KBHIT()) {
                char ch = _getch();
                if (ch == 'q' || ch == 'Q') {
                    printf("\nSession stopped by user.\n");
                    return;
                }
            }
            #endif
            
            SLEEP(1);
        }
        
        printf("\r Token %s has expired! Generating new token...     \n", token);
        session_count++;
        
        // Small delay before next token
        SLEEP(1);
    }
}