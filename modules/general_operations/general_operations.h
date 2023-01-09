/*****************************************************************************\
 !  general_operations module                                                !
 !  This module handles the general interaction with the app.                !
 !  Copyright (C) 2022 Mihai Muresan                                         !
 !  FILE: general_operations.h                                               !
 *                                                                           *
 *  AUTHOR: Mihai Muresan <mihaimuresan592003@gmail.com>                     *
 *  DESCRIPTION: Header file for general_operations.c                        *
 *  DEPENDENCIES: stdio.h, string.h, stdbool.h                               *
 *  LICENSE: GNU General Public License v3.0                                 *
 *                                                                           *
 *  CREATED: 2022-12-26                                                      *
 *  MODIFIED: 2023-01-08                                                     *
 *  VERSION: 1.0.2                                                           *
 ?  NOTES: 										                             ?
\*****************************************************************************/

#ifndef GENERAL_OPERATIONS_H
#define GENERAL_OPERATIONS_H

    #include <stdbool.h>

    // structure handling the users' data
    struct user {
        char full_name[25];
        char username[25];
        char password[25];
        char gift_preference[100];
        int recipient_id;
    };
    extern struct user participants[100];
    extern int participant_count;
    extern bool recipients_have_been_assigned; // whether recipients have been assigned

    // function prototypes
    void startUp();
    void modifiedFisherYatesShuffle(int*, int);
    void checkUsernames(int);
    void checkStringLength(char*, int, int, char*);

#endif // GENERAL_OPERATIONS_H