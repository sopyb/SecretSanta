/************************************************************************\
 !                          user_information.c                          !
 !          More information can be found in user_information.h         !
\************************************************************************/

// depenencies
#include <stdio.h>
#include <string.h>

// relevant headers
#include "user_interaction.h"
#include "../file_operations/file_operations.h"

// creation of a new participant profile
void addNewParticipant() {
    if(participant_count < 100) {
        int current_user = participant_count; // the current user's ID
        // the user inputs their data
        printf("What's you full name? [between 2 and 25 characters]\n");
        scanf(" ");
        gets(participants[current_user].full_name);

        // data validation
        checkStringLength(participants[current_user].full_name, 2, 25, "full name");

        printf("Now type a username. You'll use it to log in and won't be able to change it. [between 2 and 25 characters]\n");
        scanf(" ");
        gets(participants[current_user].username);

        // data validation
        checkStringLength(participants[current_user].username, 2, 25, "username");

        // the username is compared to the ones of the other participants to assure there are no duplicates
        checkUsernames(current_user);

        printf("Now type a password. [between 2 and 25 characters]\n");
        scanf(" ");
        gets(participants[current_user].password);

        // data validation
        checkStringLength(participants[current_user].password, 2, 25, "password");

        printf("Now, do you have any gift preferences? [between 2 and 100 characters]\n");
        scanf(" ");
        gets(participants[current_user].gift_preference);

        // data validation
        checkStringLength(participants[current_user].gift_preference, 2, 100, "gift preferences");

        participants[current_user].recipient_id = -1; // initially the participant doesn't have an assigned recipient
        participant_count ++; // the amount of participants is increased by one

        // the new user's data is written in a file
        writeUserData(current_user, participants[current_user]);

        // the vital data file is updated to reflect the increased amount of participants
        writeVitalData(participant_count, recipients_have_been_assigned);

        printf("Successfully added new participant!\n");

        if(recipients_have_been_assigned) {
            // the new participant is warned if the recipients had been assigned before they created their profile
            printf("Warning: Recipients have been assigned before you joined. Contact the admin for a reassignment!\n");
        }

        // the user proceeds to do their participant activities
        participantActivities(current_user);
    }
    else {
        printf("The limit of 100 participants has already been reached.");
    }
}

// login of a returning participant
void participantLogin() {
    int login_id; // the participant's ID
    char login_username[25]; // the input username
    char login_password[25]; // the input password

    printf("Type your username:\n");
    scanf(" ");
    gets(login_username);

    // the input username is compared to the ones of existing users to make sure the profile exists
    bool found = false;
    while (!found && strcmp(login_username,"0") != 0) {
        // looping until a matching username is found or the login is cancelled
        int i;
        for (i = 0; i < participant_count && !found; i++) {
            if (strcmp(participants[i].username, login_username) == 0) {
                found = true;
                login_id = i;// the ID of the matching user is stored for later
            }
        }
        if (!found) {
            printf("There's no participant with that username. Try again or type 0 to cancel.\n");
            scanf(" ");
            gets(login_username);
        }
    }

    // if the login hasn't been canceled, it continues
    if (strcmp(login_username, "0") != 0) {
        int current_user = login_id; // the index used to refer to the current user's field in the participants array

        printf("Type your password:\n");
        scanf(" ");
        gets(login_password);

        // checking if the password is correct or the login is cancelled
        while (strcmp(login_password, participants[current_user].password) != 0 && strcmp(login_password, "0") != 0) {
            printf("Wrong password! Try again, or type 0 to cancel\n");
            scanf(" ");
            gets(login_password);
        }
        if (strcmp(login_password, participants[current_user].password) == 0) {
            // the user proceeds to do their participant activities
            participantActivities(current_user);
        }
    }
}

// providing the available activites to the user
void participantActivities(int current_user) {
    printf("Welcome, %s! What would you like to do?\n", participants[current_user].full_name);
    printf("1 - check who my gift recipient is\n2 - update my data\n3 - look at the participant list\n4 - exit\n");
    printf("Type 1, 2, 3 or 4:\n");
    int choice; // the user's choice
    scanf("%d", &choice);
    while(choice != 1 && choice != 2 && choice != 3 && choice != 4) {
        // data validation
        printf("Invalid input! Try again:\n");
        scanf("%d", &choice);
    }
    while(choice != 4) {
        // looping while the exit option hasn't been chosen
        if(choice == 1) {
            // the user check's who they should give a gift to
            checkRecipient(current_user);
        }
        if(choice == 2) {
            // the user can update their data
            updateParticipant(current_user);
        }
        if(choice == 3) {
            // the user can look at the participants list
            displayParticipantsLimited();
        }

        // the user is prompted to choose again
        printf("Is there anything else you'd like to do?\n");
        printf("1 - check who my gift recipient is\n2 - update my data\n3 - look at the participant list\n4 - exit\n");
        printf("Type 1, 2, 3 or 4:\n");
        scanf("%d", &choice);
    }
}

// displaying the relevant recipient data to the user
void checkRecipient(int current_user) {
    if(recipients_have_been_assigned == true) {
        if(participants[current_user].recipient_id != -1)  {
            // the relevant information is displayed, in a familiar sentence structure
            printf("Here's what you need to know about your recipient:\n");
            printf("Their full name is %s.\n", participants[participants[current_user].recipient_id].full_name);
            printf("Their username is %s.\n", participants[participants[current_user].recipient_id].username);
            printf("Their gift preferences are \"%s\".\n", participants[participants[current_user].recipient_id].gift_preference);
        }
        else {
            // the user is reminded that recipients have been assigned before they created their profile
            printf("Recipients have been assigned before you joined. Contact the admin for a reassignment!\n");
        }
    }
    else {
        // the user is informed that recipients haven't been assigned
        printf("Recipients haven't been assigned yet. Check again later.\n");
    }
}

// updating various fields from the user's profile
void updateParticipant(int current_user) {
    printf("What information would you like to update?\n");
    int choice = 4; // the user's choice
    printf("1 - full name\n2 - password\n3 - gift preferences\n4 - exit\n");
    printf("Type 1, 2, 3 or 5:\n");
    scanf(" %d", &choice);
    while(choice != 4) {
        // looping while the exit option hasn't been chosen
        switch(choice) {
            case 1: {
                // updating the user's full name
                printf("Type your new full name. [between 2 and 25 characters]\n");
                scanf(" ");
                gets(participants[current_user].full_name);

                // data validation
                checkStringLength(participants[current_user].full_name, 2, 25, "full name");

                // the user is prompted to choose again
                printf("Full name successfully updated!\n");
                printf("1 - full name\n2 - password\n3 - gift preferences\n4 - exit\n");
                printf("Type 1, 2, 3 or 4:\n");
                break;
            }
            case 2: {
                // updating the user's password
                printf("Type your new password:\n");
                scanf(" ");
                gets(participants[current_user].password);

                // data validation
                checkStringLength(participants[current_user].password, 2, 25, "password");

                // the user is prompted to choose again
                printf("Password successfully updated!\n");
                printf("1 - full name\n2 - password\n3 - gift preferences\n4 - exit\n");
                printf("Type 1, 2, 3 or 4:\n");
                break;
            }
            case 3: {
                // updating the user's gift preferences
                printf("Type your new gift preferences:\n");
                scanf(" ");
                gets(participants[current_user].gift_preference);

                // data validation
                checkStringLength(participants[current_user].gift_preference, 2, 100, "gift preferences");

                // the user is prompted to choose again
                printf("Gift preferences successfully updated!\n");
                printf("1 - full name\n2 - password\n3 - gift preferences\n4 - exit\n");
                printf("Type 1, 2, 3 or 4:\n");
                break;
            }
            default: {
                printf("Invalid operation! Type 1, 2, 3 or 4.\n");
                break;
            }
        }
        // the user's file is updated
        writeUserData(current_user, participants[current_user]);

        scanf(" %d", &choice);
    }
}
// displaying the relevant participant data to the participant
void displayParticipantsLimited() {
    // the relevant information is displayed in an informative table
    printf("%-25s | %-25s | %-100s\n", "Full Name", "Username", "Gift Preferences");

    for(int i = 0; i < 25; i ++) {
        printf("-");
    }
    printf("-|-");
    for(int i = 0; i < 25; i ++) {
        printf("-");
    }
    printf("-|-");
    for(int i = 0; i < 100; i ++) {
        printf("-");
    }
    printf("\n");

    int i;
    for(i = 0; i < participant_count; i ++) {
        printf("%-25s | %-25s | %-100s\n", participants[i].full_name, participants[i].username, participants[i].gift_preference);
    }
}
