/** 
 * @file menu.h
 * @brief Command-line Interface library header.
 * @authors Ismael Coelho Medeiros (14/0083162)
 *
 * This file contains all the function signatures used in the menus
 * and in the user choices processing.
 */

#ifndef _MENU_H
#define _MENU_H

#include <stdio.h>
#include "class.h"

/** 
 * @brief Shows the JVM main menu.
 * 
 * Shows the application main menu as CLI and gets the user option to do some 
 * action. The available options are "JVM", "Classfile Viewer" and "Quit".
 */
void menu();

/**
 * @brief Process the user's option received on the main menu.
 * 
 * Process the option received by the user. The valid options are
 * 1-2 to open JVM and .class viewer, respectively.
 * @param userOption The user's option to be processed.
 */
void menuOption(int userOption);

/**
 * @brief Shows the .class viewer menu.
 *
 * Shows the Classfile Viewer menu after the user chooses the 
 * option in the main menu. Here, the user can choose to set a .class file
 * and after this, the class file structure is shown in this menu. The user
 * also has the option to go to the JVM execution menu through the second 
 * option, if the .class file is already setted, the JVM loads the same
 * file. The 3rd option is to go back to the previous menu.
 */
void viewer();

/**
 * @brief Process the user's option received on the .class viewer menu.
 * 
 * @todo Description
 */
void viewerOption(int userOption);

/**
 * @todo Brief
 * @todo Description
 */
void showConstantPool();

/**
 * @todo Brief
 * @todo Description
 */
void showContant(ConstPoolInfo cpInfo);

/**
 * @todo Brief
 * @todo Description
 */

void showMethods();

void showInterfaces();

/**
 * @brief Shows JVM execution menu.
 * 
 * @todo Description
 */
void jvm();

/**
 * @brief Process the user's option received on the JVM execution menu.
 *
 * @todo Description
 */
void jvmOption(int userOption);

/**
 * @brief Shows the menu that let the user to choose some .class file.
 * 
 * @todo Description
 */
void chooseFile();

/**
 * @brief Gets the short name of the local userfilePath.
 * 
 * @todo Description
 */
char* getShortName();

/**
 * @brief Clears the current screen.
 * 
 * @todo Description
 */
void clearScreen();

#endif //_MENU_H