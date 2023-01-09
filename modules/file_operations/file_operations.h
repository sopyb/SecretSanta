/*****************************************************************************\
 !  file_operations module                                                   !
 !  This module handles operations with the files.                           !
 !  Copyright (C) 2022 Sopy                                                  !
 !  FILE: file_operations.h                                                  !
 *                                                                           *
 *  AUTHOR: Sopy <contact@sopy.one>                                          *
 *  DESCRIPTION: Header file for file_operations.c                           *
 *  DEPENDENCIES: stdio.h, string.h, unistd.h, sys/stat.h                    *
 *  LICENSE: GNU General Public License v3.0                                 *
 *                                                                           *
 *  CREATED: 2022-12-26                                                      *
 *  MODIFIED: 2023-01-09                                                     *
 *  VERSION: 1.0.2                                                           *
 ?  NOTES: 										                             ?
\*****************************************************************************/

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

    #include "../general_operations/general_operations.h"

    // function prototypes
    void readUserData(int);
    void writeUserData(int, struct user);
    void readAllUserData(int);
    void readVitalData();
    void writeVitalData();
    void clearData();

#endif // FILE_OPERATIONS_H