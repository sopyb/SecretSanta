/************************************************************************\
 !                             GeneralInteraction.c                     !
 !          More information can be found in GeneralInteraction.h       !
\************************************************************************/

//dependencies
#include <stdio.h>

// corresponding header
#include "GeneralInteraction.h"

// relevant headers
#include "User/UserInteraction.h"
#include "Admin/AdminInteraction.h"

// initial prompts
void welcome() {
    printf("Welcome to the Secret Santa App! Please read all the instrucions carefully! Press \"ENTER\" or \"RETURN\" after every input. Are you a participant or an admin?\n");
    printf("1 - participant\n2 - admin\n3 - exit\n");
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
            // the regular user creates or logs into their profile
            printf("Are you a new participant or a returning one?\n");
            printf("1 - new\n2 - returning\n");
            printf("Type 1 or 2:\n");
            int new_or_returning; // the user's choice
            scanf("%d", &new_or_returning);
            while (new_or_returning != 1 && new_or_returning != 2) {
                // checking if the choice belongs to the valid set
                printf("Invalid input! Try again:\n");
                scanf("%d", &new_or_returning);
            }
            if (new_or_returning == 1) {
                // the new user proceeds to create their participant profile
                addNewParticipant();
            }
            if (new_or_returning == 2) {
                //the returning user proceeds to log into their participant profile
                participantLogin();
            }
        }
        if (choice == 2) {
            // the admin proceed to log into their admin profile
            adminLogin();
        }
        // the user is prompted to choose again
        printf("1 - participant\n2 - admin\n3 - exit\n");
        printf("Type 1, 2 or 3:\n");
        scanf("%d", &choice);
    }
}
