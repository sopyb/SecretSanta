/*****************************************************************************\
 !  AdminInteraction module                                                  !
 !  This module handles the admin's interaction with the app.                !
 !  Copyright (C) 2022 Mihai Muresan                                         !
 !  FILE: AdminInteraction.h                                                 !
 *                                                                           *
 *  AUTHOR: Mihai Muresan <mihaimuresan592003@gmail.com>                     *
 *  DESCRIPTION: Header file for AdminInteraction.c                          *
 *  DEPENDENCIES: stdio.h, string.h, stdbool.h                               *
 *  LICENSE: GNU General Public License v3.0                                 *
 *                                                                           *
 *  CREATED: 2022-12-26                                                      *
 *  MODIFIED: 2023-01-08                                                     *
 *  VERSION: 1.0.3                                                           *
 ?  NOTES: 										                             ?
\*****************************************************************************/

#ifndef SECRETSANTA_ADMININTERACTION_H
#define SECRETSANTA_ADMININTERACTION_H
#include "../User/UserInteraction.h"
#include <stdbool.h>

// the amount of participant profiles

// whether or not recipients have been assigned

// function prototypes
void adminLogin();
void adminActivities();
void assignRecipients();
void displayAllParticipants();

#endif //SECRETSANTA_ADMININTERACTION_H
