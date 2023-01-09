// dependencies
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// include own header
#include "admin_interaction.h"

// login using the established admin password
void adminLogin() {
    // needed variables
    char login_password[25];
    // prompt for password
    printf("Type the admin password:\n");
    scanf(" ");
    gets(login_password);

    // check if the password is correct
    while(strcmp(login_password, admin_password) != 0 && strcmp(login_password, "0") != 0) {
        // announce the error
        printf("Wrong password! Try again, or type 0 to cancel\n");
        scanf(" ");
        gets(login_password);
    }

    // if the password is correct, proceed to the admin activities
    if(strcmp(login_password, "1234") == 0) {
        adminActivities();
    }
}

// providing the available activities to the admin
void adminActivities() {
    // print menu
    printf("Welcome back, admin! What would you like to do?\n");
    printf("1 - assign recipients\n2 - see all participants\n3 - clear all data\n4 - exit\n");
    printf("Type 1, 2, 3 or 4:\n");

    // get choice
    int choice;
    scanf("%d", &choice);
    // check if choice is valid
    while(choice != 1 && choice != 2 && choice != 3 && choice != 4) {
        // if not ask the user to try again
        printf("Invalid input! Try again:\n");
        scanf("%d", &choice);
    }

    // while the user hasn't chosen to exit
    while(choice != 4) {
        // check what the user wants to do
        if(choice == 1) {
            // assign recipients
            assignRecipients();
        }
        if(choice == 2) {
            // display all participants
            displayParticipantsFull();
        }
        if(choice == 3) {
            // clear all data

            // ask for confirmation
            printf("Are you sure you want to clear all data? This process is irreversible.\n");
            printf("1 - clear all data\n2 - cancel\n");

            // get choice
            int confirm;
            scanf("%d", &confirm);

            // check if choice is valid
            while(confirm != 1 && confirm != 2) {
                // if not ask the user to try again
                printf("Invalid input! Try again:\n");
                scanf("%d", &confirm);
            }

            // if user confirms
            if(confirm == 1) {
                // clear all data
                clearData();
                // confirm the action
                printf("Successfully cleared all data.\n");
            }
        }
        // print menu
        printf("1 - assign recipients\n2 - see all participants\n3 - clear all data\n4 - exit\n");
        printf("Type 1, 2, 3 or 4:\n");
        // get new choice
        scanf("%d", &choice);
    }
}

// assign gift recipients
void assignRecipients() {
    if(participant_count > 1) {
        // randomize the seed
        srand(time(NULL));

        // get the number of participants
        recipients_have_been_assigned = false;

        // while participants haven't all been assigned
        while(!recipients_have_been_assigned) {
            int aux_array[100]; // auxiliary array
            int i, j; // counters

            // fill the auxiliary array with numbers from 1 to the number of participants
            for(i = 0; i < participant_count; i ++) {
                aux_array[i] = i;
            }

            // shuffle
            modifiedFisherYatesShuffle(aux_array, participant_count);

            // stop loop if all users have a different recipient than themselves
            recipients_have_been_assigned = true;

            // check if all users have a different recipient than themselves
            for(i = 0; i < participant_count - 1; i ++) {
                for(j = i + 1; j < participant_count; j ++) {
                    // if a user has the same recipient as themselves
                    if(aux_array[i] == aux_array[j]) {
                        // loop again
                        recipients_have_been_assigned = false;
                    }
                }
            }

            // write data to file
            for(i = 0; i < participant_count; i ++) {
                // participant recipient set
                participants[i].recipient_id = aux_array[i];
                // write user data
                writeUserData(i, participants[i]);
            }
        }

        // update data file
        writeVitalData(participant_count, recipients_have_been_assigned);

        // confirm actions
        printf("Successfully assigned gift recipients.\n");
    }
    else {
        // if there is less than 2 participants recipients can't be assigned
        printf("There aren't enough participants to assign recipients. There should be at least two.\n");
    }
}

// display all users in a table
void displayParticipantsFull() {
    if(participant_count > 0) {
        // if there are participants print table header
        printf("%-3s | %-12s | %-25s | %-25s | %-100s\n", "ID", "Recipient ID", "Full Name", "Username", "Gift Preferences");

        int i; // counter

        // print separator between header and data
        printf("----|-"); // ID
        for(i = 0; i < 12; i ++) {
            printf("-"); // Recipient ID
        }
        printf("-|-");
        for(i = 0; i < 25; i ++) {
            printf("-"); // Full Name
        }
        printf("-|-");
        for(i = 0; i < 25; i ++) {
            printf("-"); // Username
        }
        printf("-|-");
        for(i = 0; i < 100; i ++) {
            printf("-"); // Gift Preferences
        }
        printf("\n");

        // for each participant
        for(i = 0; i < participant_count; i ++) {
            // print user data
            printf("%-3d | %-12d | %-25s | %-25s | %-100s\n", i, participants[i].recipient_id, participants[i].full_name, participants[i].username, participants[i].gift_preference);
        }
    }
    else {
        // if there are no participants
        printf("No participants have been added yet.\n");
    }
}
