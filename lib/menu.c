/** 
 * @file menu.c
 * @brief Command-line Interface library source.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the menu.h file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mem-manager.h"
#include "class.h"
#include "convert.h"
#include "common.h"
#include "file.h"
#include "menu.h"

/**
 * @brief Global variable for the userfile pointer.
 *
 * @todo Description
 */
FILE* userfilePointer = NULL;

/**
 * @brief Global variable for the userfile path.
 * 
 * @todo Description
 */
char userfilePath[255] = "";

/**
 * @todo Brief
 * @todo Description
 */
Class* class = NULL;

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
        printf(" Choose one of the option (1-3): ");

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
            // Free all allocated memory
            freeMemManager();

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
            printf("| Size (bytes): %-46d |\n", fileSize(userfilePointer));
            printf("|--------------------------------------------------------------|\n");
            printf("| General Information:                                         |\n");
            printf("|                                                              |\n");
            printf("| Magic: 0x%.8X                                            |\n", class->magic);
            printf("| Minor version: %-45u |\n", class->minorVersion);
            printf("| Major version: %-45d |\n", class->majorVersion);
            printf("| Contant pool count: %-40d |\n", class->constantPoolCount);
            printf("| Access flags: 0x%.4X                                         |\n", class->accessFlags);
            printf("| This class: cp_info #%-39d |\n", class->thisClass);
            printf("| Super class: cp_info #%-38d |\n", class->superClass);
            printf("| Interfaces count: %-42d |\n", class->interfacesCount);
            printf("| Fields count: %-46d |\n", class->fieldsCount);
            printf("|                                                              |\n");
            printf("|--------------------------------------------------------------|\n");
            printf("| -1) Contant pool                                             |\n");
            printf("| -2) Interfaces                                               |\n");
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
        printf("Choose one of the options (1-3): ");

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
    clearScreen();

    switch(userOption) {
        case 1:
            chooseFile();
            break;
        case 2:
            jvm();
            break;
        case -1:
            if (userfilePointer != NULL && userfilePath[0] != '\0') {
                showConstantPool();
            } else {
                printf("Invalid option! Please choose a valid one.\n");
            }
            break;
        case -2:
            if (userfilePointer != NULL && userfilePath[0] != '\0') {
                showInterfaces();
            } else {
                printf("Invalid option! Please choose a valid one.\n");
            }
            break; 
        default:
            printf("Invalid option! Please choose a valid one.\n");
    }
}


void showConstantPool() {
    int userOption;

    if (class->constantPoolCount == 0) {
        printf("Empty array.\n");
        return;
    }

    forever {
        printf("|==============================================================|\n");
        printf("|                         Constant Pool                        |\n");
        printf("|==============================================================|\n");
        int cpIndex;
        for (cpIndex = 0; cpIndex < class->constantPoolCount - 1; cpIndex++) {
            switch(class->constantPool[cpIndex].tag) {
                case LARGE_NUMERIC_CONTINUED:
                    printf("| [%-3d] (large numeric continued)                              |\n", cpIndex + 1);
                    break;
                    
                case UTF8:
                    printf("| [%-3d] CONSTANT_Utf8_Info                                     |\n", cpIndex + 1);
                    break;

                case INTEGER:
                    printf("| [%-3d] CONSTANT_Integer_Info                                  |\n", cpIndex + 1);
                    break;

                case FLOAT:
                    printf("| [%-3d] CONSTANT_Float_Info                                    |\n", cpIndex + 1);
                    break;

                case LONG:
                    printf("| [%-3d] CONSTANT_Long_Info                                     |\n", cpIndex + 1);
                    break;

                case DOUBLE:
                    printf("| [%-3d] CONSTANT_Double_Info                                   |\n", cpIndex + 1);
                    break;

                case CLASS:
                    printf("| [%-3d] CONSTANT_Class_Info                                    |\n", cpIndex + 1);
                    break;

                case STRING:
                    printf("| [%-3d] CONSTANT_String_Info                                   |\n", cpIndex + 1);
                    break;

                case FIELD_REF:
                    printf("| [%-3d] CONSTANT_Fieldref_Info                                 |\n", cpIndex + 1);
                    break;

                case METHOD_REF:
                    printf("| [%-3d] CONSTANT_Methodref_Info                                |\n", cpIndex + 1);
                    break;

                case INTERFACE_METHOD_REF:
                    printf("| [%-3d] CONSTANT_InterfaceMethodref_Info                       |\n", cpIndex + 1);
                    break;

                case NAME_AND_TYPE:
                    printf("| [%-3d] CONSTANT_NameAndType_Info                              |\n", cpIndex + 1);
                    break;
            }
        }
        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Choose a constant                                         |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-2): ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');

        // Process user option
        if (userOption == 1) { // Option #1: Choose a contant
            forever {

                // Ask for the constant index
                int chosenConst;
                printf("Index: ");
                scanf("%d", &chosenConst);
                while(getchar() != '\n');

                // Verify index correctness
                if (chosenConst > 0 && chosenConst < (class->constantPoolCount)) {
                    clearScreen();
                    if (class->constantPool[chosenConst - 1].tag == LARGE_NUMERIC_CONTINUED) {
                        // Show the previous element, which has to be a long or a double
                        showConstant(class->constantPool[chosenConst - 2]);
                    }
                    showConstant(class->constantPool[chosenConst - 1]);
                    break;
                } else {
                    printf("Invalid option! Please choose a valid one.\n");
                }
            }
        } else if (userOption == 2) { // Option #2: Go back to previous page
            clearScreen();
            break;
        } else { // Invalid option
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }
    }
}

void showConstant(ConstPoolInfo cpInfo) {
    printf("|==============================================================|\n");
    switch(cpInfo.tag) {
        case UTF8:
            printf("|                      CONSTANT_Utf8_Info                      |\n");
            break;

        case INTEGER:
            printf("|                     CONSTANT_Integer_Info                    |\n");
            break;

        case FLOAT:
            printf("|                      CONSTANT_Float_Info                     |\n");
            break;

        case LONG:
            printf("|                      CONSTANT_Long_Info                      |\n");
            break;

        case DOUBLE:
            printf("|                     CONSTANT_Double_Info                     |\n");
            break;

        case CLASS:
            printf("|                      CONSTANT_Class_Info                     |\n");
            break;

        case STRING:
            printf("|                     CONSTANT_String_Info                     |\n");
            break;

        case FIELD_REF:
            printf("|                    CONSTANT_Fieldref_Info                    |\n");
            break;

        case METHOD_REF:
            printf("|                    CONSTANT_Methodref_Info                   |\n");
            break;

        case INTERFACE_METHOD_REF:
            printf("|               CONSTANT_InterfaceMethodref_Info               |\n");
            break;

        case NAME_AND_TYPE:
            printf("|                  CONSTANT_NameAndType_Info                   |\n");
            break;
    }
    printf("|==============================================================|\n");
    char* string = NULL;
    switch(cpInfo.tag) {
        case UTF8:
            string = utf8ToString(cpInfo.utf8Const.bytes, cpInfo.utf8Const.length);
            printf("| Length of bytes array: %-37d |\n", cpInfo.utf8Const.length);
            printf("| Length of string:      %-37zu |\n", strlen(string));
            printf("| String:                %-37s |\n", string);
            deallocate( (void**) &string );
            break;

        case INTEGER:
            printf("| Bytes:   0x%.8X                                          |\n", cpInfo.integerConst.bytes);
            printf("| Integer: %-51d |\n", cpInfo.integerConst.bytes);
            break;

        case FLOAT:
            printf("| Bytes: 0x%.8X                                            |\n", cpInfo.integerConst.bytes);
            printf("| Float: %-53f |\n", cpInfo.floatConst.value);
            break;

        case LONG:
            printf("| High bytes: 0x%.8X                                       |\n", cpInfo.longConst.bytes.highBytes);
            printf("| Low bytes:  0x%.8X                                       |\n", cpInfo.longConst.bytes.lowBytes);
            printf("| Long:       %-48ld |\n", cpInfo.longConst.value);
            break;

        case DOUBLE:
            printf("| High bytes: 0x%.8X                                       |\n", cpInfo.doubleConst.bytes.highBytes);
            printf("| Low bytes:  0x%.8X                                       |\n", cpInfo.doubleConst.bytes.lowBytes);
            printf("| Double:     %-48lf |\n", cpInfo.doubleConst.value);
            break;

        case CLASS:
            printf("| Class name: cp_info #%-39d |\n", cpInfo.classConst.nameIndex);
            break;

        case STRING:
            printf("| String: cp_info #%-43d |\n", cpInfo.stringConst.stringIndex);
            break;

        case FIELD_REF:
            printf("| Class name:    cp_info #%-36d |\n", cpInfo.fieldRefConst.classIndex);
            printf("| Name and type: cp_info #%-36d |\n", cpInfo.fieldRefConst.nameAndTypeIndex);
            break;

        case METHOD_REF:
            printf("| Class name:    cp_info #%-36d |\n", cpInfo.methodRefConst.classIndex);
            printf("| Name and type: cp_info #%-36d |\n", cpInfo.methodRefConst.nameAndTypeIndex);
            break;

        case INTERFACE_METHOD_REF:
            printf("| Class name:    cp_info #%-36d |\n", cpInfo.interfaceMethodRefConst.classIndex);
            printf("| Name and type: cp_info #%-36d |\n", cpInfo.interfaceMethodRefConst.nameAndTypeIndex);
            break;

        case NAME_AND_TYPE:
            printf("| Name:       cp_info #%-39d |\n", cpInfo.nameAndTypeConst.nameIndex);
            printf("| Descriptor: cp_info #%-39d |\n", cpInfo.nameAndTypeConst.descriptorIndex);
            break;
    }
    printf("|==============================================================|\n");
    printf("Press ENTER to return...");
    while(getchar() != '\n');
    clearScreen();
}

void showInterfaces() {
    int interfacesIndex;

    if (class->interfacesCount == 0) {
        printf("Empty array.\n");
        return;
    }

    printf("|==============================================================|\n");
    printf("|                           Interfaces                         |\n");
    printf("|==============================================================|\n");

    for (interfacesIndex = 0; interfacesIndex < class->interfacesCount; interfacesIndex++) {
        printf("| cp_info #%-51d |\n", class->interfaces[interfacesIndex]);
    }
    printf("|==============================================================|\n");
    printf("Press enter to return...\n");
    while(getchar() != '\n');
    clearScreen();
}

void jvm() {
    int userOption;
    char* shortname = NULL;

    forever {

        // Get short name of the userfile path
        if (userfilePointer != NULL && userfilePath[0] != '\0') {
            shortname = getShortName();
        }

        printf("|==============================================================|\n");
        printf("|                       JVM Execution Menu                     |\n");
        printf("|==============================================================|\n");
        // Only the userfile path is sets prints the short name
        if (userfilePointer != NULL && userfilePath[0] != '\0') {

            printf("| Chosen file: %-47s |\n", shortname);
            printf("| Size (bytes): %-47d|\n", fileSize(userfilePointer));
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Choose another .class file                                |\n");
        
        } else {

            printf("| Chosen file: none                                            |\n");
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Choose a .class file                                      |\n");
        
        }
        printf("| 2) Run file                                                  |\n");
        printf("| 3) Classfile viewer                                          |\n");
        printf("| 4) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-4): ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');
        printf("\n");
        // Option #4: Go back to last page
        if (userOption == 4) {
            clearScreen();
            break;
        }
        // Process other options
        jvmOption(userOption);
    }
}

void jvmOption(int userOption) {
    clearScreen();

    switch(userOption) {
        case 1:
            chooseFile();
            break;
        case 2:
            printf("Not Implemented Yet\n");
            break;    
        case 3:
            viewer();
            break;
        default:
            printf("Invalid option! Please choose a valid one.\n");
    }
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
                // Close the previous file
                if (userfilePointer != NULL) {
                    closeFile(&userfilePointer);
                }
                // Update with new userfile reference and path
                userfilePointer = tempPointer;
                strcpy(userfilePath, tempPath);
                // Update classfile
                class = readClassfile(userfilePointer);
                // Return the previous menu
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