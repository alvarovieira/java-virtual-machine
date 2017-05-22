/** 
 * @file menu.c
 * @brief Command-line Interface library source.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * @description This file contains all the function source codes which has the
 * signatures declared on the menu.h file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "file.h"
#include "menu.h"

FILE* userfilePointer = NULL;
char userfilePath[255] = "";

void menu() {
    int userOption;

    forever {
        userOption = -1; // Always initialize option with -1 (invalid option)

        printf("|==============================================================|\n");
        printf("|                     Java Virtual Machine                     |\n");
        printf("|==============================================================|\n");
        printf("| 1) JVM                                                       |\n");
        printf("| 2) Classfile Viewer                                          |\n");
        printf("| 3) Quit                                                      |\n");
        printf("|==============================================================|\n");
        printf(" Choose some option: ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');
        printf("\n");
        // Option #3: Quit menu close program
        if (userOption == 3) { 
            // Close file and erase userfile path
            strcpy(userfilePath, "");
            if (userfilePointer != NULL) {
                closeFile(&userfilePointer);
            }

            break;
        }
        // Process other options
        menuOption(userOption);
    }
}

void menuOption(int userOption) {
    clearScreen();

    switch(userOption) {
        // Option #1: Open JVM
        case 1:
            jvm();
            break;
        // Option #2: Open .class viewer    
        case 2:
            viewer();
            break;
        // Invalid option    
        default:
            printf("Invalid option! Please choose a valid one.\n");
    }
}

void viewer() {
    int userOption;
    char* shortname = NULL;

    clearScreen();
    forever {

        // Get short name of the userfile path
        if (userfilePointer != NULL && userfilePath[0] != '\0') {
            shortname = getShortName();
        }

        printf("|==============================================================|\n");
        printf("|                       Classfile Viewer                       |\n");
        printf("|==============================================================|\n");
        // Only the userfile path is sets prints the short name
        if (userfilePointer != NULL && userfilePath[0] != '\0') {

            printf("| Chosen file: %-47s |\n", shortname);
            printf("|--------------------------------------------------------------|\n");
            printf("| Class:                                                       |\n");
            // TODO: Create the logic of this viewer
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Choose another .class file                                |\n");
        
        } else {

            printf("| Chosen file: none                                            |\n");
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Choose a .class file                                      |\n");
        
        }
        printf("| 2) Open JVM                                                  |\n");
        printf("| 3) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the following options: ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');
        printf("\n");
        // Option #3: Go back to last page
        if (userOption == 3) {
            clearScreen();
            break;
        }
        // Process other options
        viewerOption(userOption);
    }
}
    
void viewerOption(int userOption) {
    switch(userOption) {
        case 1:
            clearScreen();
            chooseFile();
            break;
        case 2:
            clearScreen();
            jvm();
            break;
        default:
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
    }
}

void jvm() {
    printf("JVM-Not Implemeted Yet\n");
}

void chooseFile() {
    char tempPath[255], confirmation;
    FILE* tempPointer = NULL;

    forever {
        printf("|==============================================================|\n");
        printf("|                     Choose a .class file                     |\n");
        printf("|==============================================================|\n");
        printf("Set the path (\"none\" to return): ");
        scanf("%s", tempPath);
        while(getchar() != '\n');

        if (strcmp(tempPath, "none") == 0) {
            clearScreen();
            break;
        }

        tempPointer = openFile(tempPath, "rb");
        if (tempPointer == NULL) {
            clearScreen();
            printf("Please choose a valid path!\n");
            strcpy(tempPath, "");
            continue;
        }

        forever {
            printf("Are you sure (Y-y or N-n)? ");
            scanf("%c", &confirmation);
            while(getchar() != '\n');

            if (confirmation == 'Y' || confirmation == 'y') {
                clearScreen();
                userfilePointer = tempPointer;
                strcpy(userfilePath, tempPath);
                goto fileAccepted;
            } else if (confirmation == 'N' || confirmation == 'n') {
                clearScreen();
                strcpy(tempPath, "");
                closeFile(&tempPointer);
                goto fileDeclined;
            } else {
                printf("Invalid option!\n");
                continue;
            }
        }

        fileDeclined:
            continue;

        fileAccepted:
            break;  
    }
}

char* getShortName() {
    int lastBar, i;
    for (i = 0; userfilePath[i] != '\0'; i++) {
        if (userfilePath[i] == '/') {
            lastBar = i;
        }
    }
    return &userfilePath[lastBar+1];
}

void clearScreen() {
    system("cls||clear");
}