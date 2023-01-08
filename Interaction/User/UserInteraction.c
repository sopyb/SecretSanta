/************************************************************************\
 !                             UserInteraction.c                        !
 !           More information can be found in UserInteraction.h         !
\************************************************************************/

// dependencies
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../../PasswordManager/PasswordManager.h"

// corresponding header
#include "UserInteraction.h"

// creation of a new participant profile
void addNewParticipant() {
    int current_user = participant_count; // the current user's ID
    // the user inputs their data
    printf("What's you full name? [between 2 and 75 characters]\n");
    scanf(" ");
    gets(participants[current_user].full_name);

    while (strlen(participants[current_user].full_name) < 2 || strlen(participants[current_user].full_name) > 75) {
        // data validation
        printf("The full names should have between 2 and 75 characters. Try again.\n");
        scanf(" ");
        gets(participants[current_user].full_name);
    }

    printf("Now type a username. You'll use it to log in. [between 2 and 25 characters]\n");
    scanf(" ");
    gets(participants[current_user].username);

    while (strlen(participants[current_user].username) < 2 || strlen(participants[current_user].username) > 25) {
        // data validation
        printf("The username should have between 2 and 25 characters. Try again.\n");
        scanf(" ");
        gets(participants[current_user].username);
    }

    // the username is compared to the ones of the other participants to assure there are no duplicates
    bool taken = true;
    while (taken) {
        taken = false;
        int i = 0;
        for (i = 0; i < participant_count && !taken; i++) {
            if (current_user != i && strcmp(participants[i].username, participants[current_user].username) == 0) {
                taken = true;
            }
        }

        if (taken) {
            printf("Someone else took that username already! Try another one. [less than 25 characters]\n");
            scanf(" ");
            gets(participants[current_user].username);

            while (strlen(participants[current_user].username) < 2 || strlen(participants[current_user].username) > 25) {
                // data validation
                printf("The username should have between 2 and 25 characters. Try again.\n");
                scanf(" ");
                gets(participants[current_user].username);
            }
        }
    }

    printf("Now type a password. [between 2 and 25 characters]\n");
    scanf(" ");
    gets(participants[current_user].password);

    while (strlen(participants[current_user].password) < 2 || strlen(participants[current_user].password) > 25) {
        // data validation
        printf("The password should have between 2 and 25 characters. Try again.\n");
        scanf(" ");
        gets(participants[current_user].password);
    }

    printf("Now, do you have any gift preferences? [between 2 and 100 characters]\n");
    scanf(" ");
    gets(participants[current_user].gift_preference);

    while (strlen(participants[current_user].gift_preference) < 2 || strlen(participants[current_user].gift_preference) > 100) {
        // data validation
        printf("The gift preferences should have between 2 and 100 characters. Try again.\n");
        scanf(" ");
        gets(participants[current_user].gift_preference);
    }

    participants[current_user].recipient_id = -1; // initially the participant doesn't have an assigned recipient

    printf("Succefully added new participant!\n");

    participant_count++; // the amount of participants is increased

    if (recipients_have_been_assigned) {
        // the new participant is warned if the recipients had been assigned before they created their profile
        printf("Warning! Recipients have already been assigned before you joined! Contact the admin for a reassignment!\n");
    }

    // the user proceeds to do their participant activities
    participantActivities(current_user);
}

// login of a returning participant
void participantLogin() {
    int login_id; // the participant's ID
    char login_username[25]; // the input username
    char login_password[25]; // the input password

    printf("Type your username:\n");

    // seek to the end of the input buffer
    fseek(stdin, 0, SEEK_END);
    scanf("%24s", login_username);

    gets(login_username);

    if(checkPassword(login_username, login_password)) {
        // the user proceeds to do their participant activities
        participantActivities(current_user);
    }
}

// providing the available activites to the user
void participantActivities(int current_user) {
    printf("Welcome, %s! What would you like to do?\n", participants[current_user].full_name);
    printf("1 - check who my gift recipient is\n2 - update my data\n3 - exit\n");
    printf("Type 1, 2 or 3:\n");
    int choice; // the user's choice
    scanf("%d", &choice);
    while (choice != 1 && choice != 2 && choice != 3) {
        // data validation
        printf("Invalid input! Try again:\n");
        scanf("%d", &choice);
    }
    while (choice != 3) {
        // looping while the exit option hasn't been chosen
        if (choice == 1) {
            // the user check's who they should give a gift to
            checkRecipient(current_user);
        }
        if (choice == 2) {
            // the user can update their data
            updateParticipant(current_user);
        }

        // the user is prompted to choose again
        printf("Is there anything else you'd like to do?\n");
        printf("1 - check who my gift recipient is\n2 - update my data\n3 - exit\n");
        printf("Type 1, 2 or 3:\n");
        scanf("%d", &choice);
    }
}

// displaying the relevant recipient data to the user
void checkRecipient(int current_user) {
    if (recipients_have_been_assigned == true) {
        if (participants[current_user].recipient_id != -1) {
            // the relevant information is displayed, in a familiar sentence structure
            printf("Here's what you need to know about your recipient:\n");
            printf("Their full name is %s.\n", participants[participants[current_user].recipient_id].full_name);
            printf("Their username is %s.\n", participants[participants[current_user].recipient_id].username);
            printf("Their gift preferences are \"%s\".\n", participants[participants[current_user].recipient_id].gift_preference);
        }
        else {
            // the user is reminded that recipients have been assigned before they created their profile
            printf("Recipients have been assigned, but you don't have one. Contact the admin for a reassigment.\n");
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
    int choice = 5; // the user's choice
    printf("1 - full name\n2 - username\n3 - password\n4 - gift preferences\n5 - exit\n");
    printf("Type 1, 2, 3, 4 or 5:\n");
    scanf(" %d", &choice);
    while (choice != 5) {
        // looping while the exit option hasn't been chosen
        switch (choice) {
            case 1: {
                // updating the user's full name
                printf("Type your new full name. [between 2 and 75 characters]\n");
                scanf(" ");
                gets(participants[current_user].full_name);

                while (strlen(participants[current_user].full_name) < 2 || strlen(participants[current_user].full_name) > 75) {
                    // data validation
                    printf("The full names should have between 2 and 75 characters. Try again.\n");
                    scanf(" ");
                    gets(participants[current_user].full_name);
                }

                // the user is prompted to choose again
                printf("Full name successfully updated!\n");
                printf("1 - full name\n2 - username\n3 - password\n4 - gift preferences\n5 - exit");
                printf("If there's anything else you'd like to edit type 1, 2, 3, 4 or 5:\n");
                break;
            }
            case 2: {
                // updating the user's username or login name
                printf("Type your new username. [between 2 and 25 characters]\n");
                scanf(" ");
                gets(participants[current_user].username);

                while (strlen(participants[current_user].username) < 2 || strlen(participants[current_user].username) > 25) {
                    // data validation
                    printf("The username should have between 2 and 25 characters. Try again.\n");
                    scanf(" ");
                    gets(participants[current_user].username);
                }

                // the username is compared to the ones of the other participants to assure there are no duplicates
                bool taken = true;
                while (taken) {
                    taken = false;
                    int i = 0;
                    for (i = 0; i < participant_count && !taken; i++) {
                        if (i == current_user && strcmp(participants[i].username, participants[current_user].username) == 0) {
                            taken = true;
                        }
                    }
                    if (taken) {
                        printf("Someone else took that username already! Try another one.\n");
                        scanf(" ");
                        gets(participants[current_user].username);

                        while (strlen(participants[current_user].username) < 2 || strlen(participants[current_user].username) > 25) {
                            // data validation
                            printf("The username should have between 2 and 25 characters. Try again.\n");
                            scanf(" ");
                            gets(participants[current_user].username);
                        }
                    }
                }

                // the user is prompted to choose again
                printf("Username successfully updated!\n");
                printf("1 - full name\n2 - username\n3 - password\n4 - gift preferences\n");
                printf("If there's anything else you'd like to edit type 1, 2, 3 or 4 to edit one of the above, or 5 to exit:\n");
                break;
            }
            case 3: {
                // updating the user's password
                char old_password[25];
                char new_password[25];
                printf("Type your old password:\n");

                // seek to end of input buffer
                fseek(stdin, 0, SEEK_END);

                scanf("%24s", old_password);
                gets(old_password);

                printf("Type your new password:\n");

                // seek to end of input buffer
                fseek(stdin, 0, SEEK_END);

                scanf("%24s", new_password);
                gets(new_password);

                if(changePassword(participants[current_user].username, old_password, new_password) == 0) {
                    // the user is prompted to choose again
                    printf("Password successfully updated!\n");
                }
                printf("1 - full name\n2 - username\n3 - password\n4 - gift preferences\n");
                printf("If there's anything else you'd like to edit type 1, 2, 3 or 4 to edit one of the above, or 5 to exit:\n");
                break;
            }
            case 4: {
                // updating the user's gift preferences
                printf("Type your new gift preferences:\n");
                scanf(" ");
                gets(participants[current_user].gift_preference);

                while (strlen(participants[current_user].gift_preference) < 2 || strlen(participants[current_user].gift_preference) > 100) {
                    // data validation
                    printf("The gift preferences should have between 2 and 100 characters. Try again.\n");
                    scanf(" ");
                    gets(participants[current_user].gift_preference);
                }

                // the user is prompted to choose again
                printf("Gift preferences successfully updated!\n");
                printf("1 - full name\n2 - username\n3 - password\n4 - gift preferences\n");
                printf("If there's anything else you'd like to edit type 1, 2, 3 or 4 to edit one of the above, or 5 to exit:\n");
                break;
            }
            default: {
                // data validation
                printf("Invalid operation! Type 1, 2, 3, 4 or 5.\n");
                break;
            }
        }
        scanf(" %d", &choice);
    }
}
