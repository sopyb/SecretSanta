/*****************************************************************************\
 !  UserInteraction module                                                   !
 !  This module handles the user's interaction with the app.                 !
 !  Copyright (C) 2022 Mihai Muresan                                         !
 !  FILE: UserInteraction.h                                                  !
 *                                                                           *
 *  AUTHOR: Mihai Muresan <mihaimuresan592003@gmail.com>                     *
 *  DESCRIPTION: Header file for UserInteraction.c                           *
 *  DEPENDENCIES: stdio.h, string.h, stdbool.h                               *
 *  LICENSE: GNU General Public License v3.0                                 *
 *                                                                           *
 *  CREATED: 2022-12-26                                                      *
 *  MODIFIED: 2023-01-08                                                     *
 *  VERSION: 1.0.4                                                           *
 ?  NOTES: 										                             ?
\*****************************************************************************/

#ifndef SECRETSANTA_USERINTERACTION_H
#define SECRETSANTA_USERINTERACTION_H
#include "../Admin/AdminInteraction.h"
#include <stdbool.h>

// structure handling the users' data
static struct user {
    char full_name[75];
    char username[75];
    char password[25];
    char gift_preference[100];
    int recipient_id;
} participants[100];

static int participant_count = 0; // the amount of participant profiles

static bool recipients_have_been_assigned = false; // whether or not recipients have been assigned

// function prototypes
void addNewParticipant();
void participantLogin();
void participantActivities(int);
void checkRecipient(int);
void updateParticipant(int);


#endif //SECRETSANTA_USERINTERACTION_H
