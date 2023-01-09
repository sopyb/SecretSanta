/*****************************************************************************\
 !  user_interaction module                                                  !
 !  This module handles the user's interaction with the app.                 !
 !  Copyright (C) 2022 Mihai Muresan                                         !
 !  FILE: user_interaction.h                                                 !
 *                                                                           *
 *  AUTHOR: Mihai Muresan <mihaimuresan592003@gmail.com>                     *
 *  DESCRIPTION: Header file for user_interaction.c                          *
 *  DEPENDENCIES: stdio.h, string.h, stdbool.h                               *
 *  LICENSE: GNU General Public License v3.0                                 *
 *                                                                           *
 *  CREATED: 2022-12-26                                                      *
 *  MODIFIED: 2023-01-08                                                     *
 *  VERSION: 1.0.4                                                           *
 ?  NOTES: 										                             ?
\*****************************************************************************/

#ifndef USER_INTERACTION_H
#define USER_INTERACTION_H

    // function prototypes
    void addNewParticipant();
    void participantLogin();
    void participantActivities(int);
    void checkRecipient(int);
    void updateParticipant(int);
    void displayParticipantsLimited();

#endif //USER_INTERACTION_H
