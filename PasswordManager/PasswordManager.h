/*****************************************************************************\
 !  DataStore module                                                         !
 !  This module is used to store and retrieve data from files.               !
 !  Copyright (C) 2022 Sopy                                                  !
 !  FILE: PasswordManager.h                                                  !
 *                                                                           *
 *  AUTHOR: Sopy <contact@sopy.one>                                          *
 *  DESCRIPTION: Header file for PasswordManager.c                           *
 *  DEPENDENCIES: stdio.h, string.h, malloc.h, DataStore.h                   *
 *  LICENSE: GNU General Public License v3.0                                 *
 *                                                                           *
 *  CREATED: 2022-11-23                                                      *
 *  MODIFIED: 2022-11-24                                                     *
 *  VERSION: 1.1.0                                                           *
 ?  NOTES: I didn't overcomplicate this one, but I still think it's pretty   ?
 ?         cool.                                                             ?
\*****************************************************************************/

#ifndef PASSWORDMANAGER_PASSWORDMANAGER_H
#define PASSWORDMANAGER_PASSWORDMANAGER_H

int registerPassword(char *user, char *password);
int checkPassword(char *user, char *password);
int changePassword(char *user, char *oldPassword, char *newPassword);

#endif //PASSWORDMANAGER_PASSWORDMANAGER_H
