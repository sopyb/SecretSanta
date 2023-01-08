/************************************************************************\
 !                             AdminInteraction.c                       !
 !           More information can be found in AdminInteraction.h        !
\************************************************************************/

// dependencies
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// corresponding header
#include "AdminInteraction.h"

// login using the established admin password
void adminLogin() {
    char login_password[25]; // the input password
    printf("Type the admin password:\n");
    scanf(" ");
    gets(login_password);
    while (strcmp(login_password, "1234") != 0 && strcmp(login_password, "0") != 0) {
        // checking is the password is correct or the login is cancelled
        printf("Wrong password! Try again, or type 0 to cancel\n");
        scanf(" ");
        gets(login_password);
    }
    if (strcmp(login_password, "0") != 0) {
        // the user proceeds to do their admin activities
        adminActivities();
    }
}

// providing the available activities to the admin
void adminActivities() {
    printf("Welcome back, admin! What would you like to do?\n");
    printf("1 - assign recipients\n2 - see all participants\n3 - exit\n");
    printf("Type 1, 2 or 3:\n");
    int choice; // the admin's choice
    scanf("%d", &choice);
    while (choice != 1 && choice != 2 && choice != 3) {
        // data validation
        printf("Invalid input! Try again:\n");
        scanf("%d", &choice);
    }
    while (choice != 3) {
        // looping while the exit option hasn't been chosen
        if (choice == 1) {
            // the admin can randomly assign recipients
            assignRecipients();
        }
        if (choice == 2) {
            // the admin can take a look at all the participant's data, except their passwords
            displayAllParticipants();
        }
        
        // the admin is prompted to choose again
        printf("1 - assign recipients\n2 - see all participants\n3 - exit\n");
        printf("Type 1, 2 or 3:\n");
        scanf("%d", &choice);
    }
}

// randomly assigning gift recipients
void assignRecipients() {
    srand(time(NULL)); // seeding the rand() function
    // recipients_have_been_assigned = false;
    /*
    while (!recipients_have_been_assigned) {
        // looping until the recipients have been correctly assigned
    */
        int aux_array[100]; // auxiliary array
        int i = 0, j = 0;
        for (i = 0; i < participant_count; i++) {
            // initializing the relevant array elements with the value of their index
            aux_array[i] = i;
        }
        for (i = participant_count - 1; i >= 0; i--) {
            // shuffling the auxiliary array using the Fisher-Yates method
            while (i == j) {
                // generating a random number until it's different to i
                j = rand() % participant_count;
            }
            // swapping the i'th and j'th elements of the auxiliary array
            int x = aux_array[i];
            aux_array[i] = aux_array[j];
            aux_array[j] = x;
        }
    // the recipients are considered correctly assigned for now
        
        /*
        // checking if multiple participants have been assigned the same recipient
        for (i = 0; i < participant_count - 1 && recipients_have_been_assigned == true; i++) {
            for (j = i + 1; j < participant_count && recipients_have_been_assigned == true; j++) {
                if (aux_array[i] == aux_array[j]) {
                    recipients_have_been_assigned = false;
                }
            }
        }
        */

        // assigning recipient IDs from the shuffled auxiliary array
        for (i = 0; i < participant_count; i++) {
            participants[i].recipient_id = aux_array[i];
        }
    /*
    }
    */
    printf("Successfully assigned gift recipients.\n");
}

// displaying the relevant participant data to the admin
void displayAllParticipants() {
    if (participant_count > 0) {
        // the relevant information is displayed in an informative table
        printf("ID\tName\t\t\tUsername\t\tGift Preferences\t\t\t\tRecipient ID\n");
        int i;
        for (i = 0; i < participant_count; i++) {
            printf("%d\t%s\t%s\t\t%s\t%d\n", i, participants[i].full_name, participants[i].username, participants[i].gift_preference, participants[i].recipient_id);
        }
    }
    else {
        // the admin is informed that no participants have been added
        printf("No participants have been added yet.\n");
    }
}
