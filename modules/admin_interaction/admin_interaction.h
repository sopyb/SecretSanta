/*****************************************************************************\
 !  admin_interaction module                                                 !
 !  This module handles the admin's interaction with the app                 !
 !  Copyright (C) 2022 Sopy                                                  !
 !  FILE: admin_interaction.h                                                !
 *                                                                           *
 *  AUTHOR: Sopy <contact@sopy.one>                                          *
 *  DESCRIPTION: Header file for admin_interaction.c                         *
 *  DEPENDENCIES: stdio.h, string.h, stdlib.h, time.h                        *
 *  LICENSE: GNU General Public License v3.0                                 *
 *                                                                           *
 *  CREATED: 2022-12-26                                                      *
 *  MODIFIED: 2023-01-09                                                     *
 *  VERSION: 1.0.6                                                           *
 ?  NOTES: 										                             ?
\*****************************************************************************/

#ifndef ADMIN_INTERACTION_H
#define ADMIN_INTERACTION_H

    // relevant header
    #include "../file_operations/file_operations.h"
    
    static const char *admin_password = "1234"; // the admin's password

    // function prototypes
    void adminLogin();
    void adminActivities();
    void assignRecipients();
    void displayParticipantsFull();

#endif // ADMIN_INTERACTION_H