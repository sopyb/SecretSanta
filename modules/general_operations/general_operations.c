/************************************************************************\
 !                         general_operation.c                          !
 !         More information can be found in general_operation.h         !
\************************************************************************/

// dependencies
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// relevant headers
#include "general_operations.h"
#include "../admin_interaction/admin_interaction.h"
#include "../user_interaction/user_interaction.h"

int participant_count = 0; // the amount of participant profiles
struct user participants[100];
bool recipients_have_been_assigned = false;

// initial prompts
void startUp() {
    printf("Welcome to the Secret Santa App! Please read all the instructions carefully! Press \"ENTER\" or \"RETURN\" after every input. Are you a participant or an admin?\n");
    printf("1 - participant\n2 - admin\n3 - exit\n");
    printf("Type 1, 2 or 3:\n");
    int choice;; // the user's choice
    scanf("%d", &choice);
    while(choice != 1 && choice != 2 && choice != 3) {
        printf("Invalid input! Try again:\n");
        scanf("%d", &choice);
    }
    while(choice != 3) {
        // looping while the exit option hasn't been chosen
        if(choice == 1) {
            // the regular user creates or logs into their profile
            printf("Are you a new participant or a returning one?\n");
            printf("1 - new\n2 - returning\n");
            printf("Type 1 or 2:\n");
            int new_or_returning; // the user's choice
            scanf("%d", &new_or_returning);
            while(new_or_returning != 1 && new_or_returning != 2) {
                // checking if the choice belongs to the valid set
                printf("Invalid input! Try again:\n");
                scanf("%d", &new_or_returning);
            }
            if(new_or_returning == 1) {
                // the new user proceeds to create their participant profile
                addNewParticipant();
            }
            if(new_or_returning == 2) {
                //the returning user proceeds to log into their participant profile
                participantLogin();
            }
        }
        if(choice == 2) {
            // the admin proceed to log into their admin profile
            adminLogin();
        }

        // the user is prompted to choose again
        printf("1 - participant\n2 - admin\n3 - exit\n");
        printf("Type 1, 2 or 3:\n");
        scanf("%d", &choice);
    }
}

// Fisher-Yates algorithm for shuffling an array
void modifiedFisherYatesShuffle(int *array, int size) {
    int i, j;
    for(i = size - 1; i >= 0; i --) {
        // additional condition: elements keep being swapped until no element is equal to its index
        while(array[i] == i) {
            j = rand() % size; // a random number lower than size is generated
            // the current element is swapped with a random one
            int aux = array[i];
            array[i] = array[j];
            array[j] = aux;
        }
    }
}

// checking if a string has the desired length
void checkStringLength(char *string, int low_bound, int high_bound, char *name) {
    while(strlen(string) < low_bound || strlen(string) > high_bound) {
        // looping until the desired length condition is satisfied
        printf("The %s should have more than %d and less than %d characters. Try again.\n", name, low_bound, high_bound);
        scanf(" ");
        gets(string);
    }
}

// checking if any of the users have the provided username
void checkUsernames(int current_user) {bool taken = true;
    while(taken) {
        // looping until a new username is typed
        taken = false;
        int i;
        // the username is compared to the ones of the other participants to assure there are no duplicates
        for(i = 0; i < participant_count && !taken; i ++) {
            if(current_user != i && strcmp(participants[i].username, participants[current_user].username) == 0) {
                taken = true;
            }
        }
        if(taken) {
            printf("Someone else took that username already! Try another one. [less than 25 characters]\n");
            scanf(" ");
            gets(participants[current_user].username);

            checkStringLength(participants[current_user].username, 2, 75, "username");
        }
    }
}