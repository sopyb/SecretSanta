#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

struct person {
    char full_name[75];
    char username[75];
    char password[25];
    char gift_preference[100];
    int recipient_id;
} participants[100];

int participant_count = 0;
    
bool recipients_have_been_assigned = false;

void welcome();

// admin functions
void adminLogin();
void adminActivities();
void assignRecipients();
void displayAllParticipants();

// participant functions
void addNewParticipant();
void participantLogin();
void participantActivities(int);
void checkRecipient(int);
void updateParticipant(int);

int main() {
    welcome();
    return 0;
}

void welcome() {
    printf("Welcome to the Secret Santa App! Please read all the instrucions carefully! Press \"ENTER\" or \"RETURN\" after every input. Are you a participant or an admin?\n");
    printf("1 - participant\n2 - admin\n3 - exit\n");
    printf("Type 1, 2 or 3:\n");
    int choice;
    scanf("%d", &choice);
    while(choice != 1 && choice != 2 && choice != 3) {
        printf("Invalid input! Try again:\n");
        scanf("%d", &choice);
    }
    while(choice != 3) {
        if(choice == 1) {
            printf("Are you a new participant or a returning one?\n");
            printf("1 - new\n2 - returning\n");
            printf("Type 1 or 2:\n");
            int new_or_returning;
            scanf("%d", &new_or_returning);
            while(new_or_returning != 1 && new_or_returning != 2) {
                printf("Invalid input! Try again:\n");
                scanf("%d", &new_or_returning);
            }
            if(new_or_returning == 1) {
                addNewParticipant();
            }
            if(new_or_returning == 2) {
                participantLogin();
            }
        }
        if(choice == 2) {
            adminLogin();
        }
        printf("1 - participant\n2 - admin\n3 - exit\n");
        printf("Type 1, 2 or 3:\n");
        scanf("%d", &choice);
    }
}

void adminLogin() {
    char login_password[25];
    printf("Type the admin password:\n");
    scanf(" ");
    gets(login_password);
    while(strcmp(login_password, "1234") != 0 && strcmp(login_password, "0") != 0) {
        printf("Wrong password! Try again, or type 0 to cancel\n");
        scanf(" ");
        gets(login_password);
    }
    if(strcmp(login_password, "1234") == 0) {
        adminActivities();
    }
}

void adminActivities() {
    printf("Welcome back, admin! What would you like to do?\n");
    printf("1 - assign recipients\n2 - see all participants\n3 - exit\n");
    printf("Type 1, 2 or 3:\n");
    int choice;
    scanf("%d", &choice);
    while(choice != 1 && choice != 2 && choice != 3) {
        printf("Invalid input! Try again:\n");
        scanf("%d", &choice);
    }
    while(choice != 3) {
        if(choice == 1) {
            assignRecipients();
        }
        if(choice == 2) {
            displayAllParticipants();
        }
        printf("1 - assign recipients\n2 - see all participants\n3 - exit\n");
        printf("Type 1, 2 or 3:\n");
        scanf("%d", &choice);
    }
}

void assignRecipients() {
    srand(time(NULL));
    recipients_have_been_assigned = false;
    while(!recipients_have_been_assigned) {
        int aux_array[100];
        int i = 0, j = 0;
        for(i = 0; i < participant_count; i ++) {
            aux_array[i] = i;
        }
        for(i = participant_count - 1; i >= 0 ; i --) {
            while(aux_array[i] == i) {
                j = rand() % participant_count;
                int x = aux_array[i];
                aux_array[i] = aux_array[j];
                aux_array[j] = x;
                printf("\t\tAAA\n");
            }
            printf("\t\tBBB\n");
        }
        recipients_have_been_assigned = true;
        for(i = 0; i < participant_count - 1; i ++) {
            for(j = i + 1; j < participant_count; j ++) {
                if(aux_array[i] == aux_array[j]) {
                    recipients_have_been_assigned = false;
                }
            }
        }
        for(i = 0; i < participant_count; i ++) {
            participants[i].recipient_id = aux_array[i];
        }
        printf("\t\tCCC\n");
    }
    printf("Successfully assigned gift recipients.\n");
}

void displayAllParticipants() {
    if(participant_count > 0) {
        printf("ID\tName\t\t\tUsername\t\tGift Preferences\t\t\t\tRecipient ID\n");
        int i;
        for(i = 0; i < participant_count; i ++) {
            printf("%d\t%s\t%s\t\t%s\t%d\n", i, participants[i].full_name, participants[i].username, participants[i].gift_preference, participants[i].recipient_id);
        }
    }
    else {
        printf("No participants have been added yet.\n");
    }
}

void addNewParticipant() {
    int current_user = participant_count;
    printf("What's you full name? [between 2 and 75 characters]\n");
    scanf(" ");
    gets(participants[current_user].full_name);

    while(strlen(participants[current_user].full_name) < 2 || strlen(participants[current_user].full_name) > 75) {
        printf("The full names should have between 2 and 75 characters. Try again.\n");
        scanf(" ");
        gets(participants[current_user].full_name);
    }

    printf("Now type a username. You'll use it to log in. [between 2 and 25 characters]\n");
    scanf(" ");
    gets(participants[current_user].username);

    while(strlen(participants[current_user].username) < 2 || strlen(participants[current_user].username) > 25) {
        printf("The username should have between 2 and 25 characters. Try again.\n");
        scanf(" ");
        gets(participants[current_user].username);
    }

    bool taken = true;
    while(taken) {
        taken = false;
        int i = 0;
        for(i = 0; i < participant_count && !taken; i ++) {
            if(current_user != i && strcmp(participants[i].username, participants[current_user].username) == 0) {
                taken = true;
            }
        }
        if(taken) {
            printf("Someone else took that username already! Try another one. [less than 25 characters]\n");
            scanf(" ");
            gets(participants[current_user].username);

            while(strlen(participants[current_user].username) < 2 || strlen(participants[current_user].username) > 25) {
                printf("The username should have between 2 and 25 characters. Try again.\n");
                scanf(" ");
                gets(participants[current_user].username);
            }
        }
    }

    printf("Now type a password. [between 2 and 25 characters]\n");
    scanf(" ");
    gets(participants[current_user].password);

    while(strlen(participants[current_user].password) < 2 || strlen(participants[current_user].password) > 25) {
        printf("The password should have between 2 and 25 characters. Try again.\n");
        scanf(" ");
        gets(participants[current_user].password);
    }

    printf("Now, do you have any gift preferences? [between 2 and 100 characters]\n");
    scanf(" ");
    gets(participants[current_user].gift_preference);

    while(strlen(participants[current_user].gift_preference) < 2 || strlen(participants[current_user].gift_preference) > 100) {
        printf("The gift preferences should have between 2 and 100 characters. Try again.\n");
        scanf(" ");
        gets(participants[current_user].gift_preference);
    }

    participants[current_user].recipient_id = -1;

    printf("Succefully added new participant!\n");

    participant_count ++;

    if(recipients_have_been_assigned) {
        printf("Warning! Recipients have already been assigned before you joined! Contact the admin for a reassignment!\n");
    }

    participantActivities(current_user);
}

void participantLogin() {
    int login_id;
    char login_username[25];
    char login_password[25];

    printf("Type your username:\n");
    scanf(" ");
    gets(login_username);

    bool found = false;
    while(!found) {
        int i = 0;
        for(i = 0; i < participant_count && !found; i ++) {
            if(strcmp(participants[i].username, login_username) == 0) {
                found = true;
                login_id = i;
            }
        }
        if(!found) {
            printf("There's no participant with that username. Try again.\n");
            scanf(" ");
            gets(login_username);
        }
    }

    int current_user = login_id;

    printf("Type your password:\n");
    scanf(" ");
    gets(login_password);
    printf("\t_%s =%s +%d\n", login_password, participants[current_user].password, strcmp(login_password, participants[current_user].password));
    while(strcmp(login_password, participants[current_user].password) != 0 && strcmp(login_password, "0") != 0) {
        printf("Wrong password! Try again, or type 0 to cancel\n");
        scanf(" ");
        gets(login_password);
    }
    if(strcmp(login_password, participants[current_user].password) == 0) {
        participantActivities(current_user);
    }

}

void participantActivities(int current_user) {
    printf("Welcome, %s! What would you like to do?\n", participants[current_user].full_name);
    printf("1 - check who my gift recipient is\n2 - update my data\n3 - exit\n");
    printf("Type 1, 2 or 3:\n");
    int choice;
    scanf("%d", &choice);
    while(choice != 1 && choice != 2 && choice != 3) {
        printf("Invalid input! Try again:\n");
        scanf("%d", &choice);
    }
    while(choice != 3) {
        if(choice == 1) {
            checkRecipient(current_user);
        }
        if(choice == 2) {
            updateParticipant(current_user);
        }
        printf("Is there anything else you'd like to do?\n");
        printf("1 - check who my gift recipient is\n2 - update my data\n3 - exit\n");
        printf("Type 1, 2 or 3:\n");
        scanf("%d", &choice);
    } 
}

void checkRecipient(int current_user) {
    if(recipients_have_been_assigned == true) {
        if(participants[current_user].recipient_id != -1)  {
            printf("Here's what you need to know about your recipient:\n");
            printf("Their full name is %s.\n", participants[participants[current_user].recipient_id].full_name);
            printf("Their username is %s.\n", participants[participants[current_user].recipient_id].username);
            printf("Their gift preferences are \"%s\".\n", participants[participants[current_user].recipient_id].gift_preference);
        }
        else {
            printf("Recipients have been assigned, but you don't have one. Contact the admin for a reassigment.\n");
        }
    }
    else {
        printf("Recipients haven't been assigned yet. Check again later.\n");
    }
}

void updateParticipant(int current_user) {
    printf("What information would you like to update?\n");
    int choice = 5;
    printf("1 - full name\n2 - username\n3 - password\n4 - gift preferences\n5 - exit\n");
    printf("Type 1, 2, 3, 4 or 5:\n");
    scanf(" %d", &choice);
    while(choice != 5) {
        switch(choice) {
            case 1: {
                printf("Type your new full name. [between 2 and 75 characters]\n");
                scanf(" ");
                gets(participants[current_user].full_name);

                while(strlen(participants[current_user].full_name) < 2 || strlen(participants[current_user].full_name) > 75) {
                    printf("The full names should have between 2 and 75 characters. Try again.\n");
                    scanf(" ");
                    gets(participants[current_user].full_name);
                }

                printf("Full name successfully updated!\n");
                printf("1 - full name\n2 - username\n3 - password\n4 - gift preferences\n5 - exit");
                printf("If there's anything else you'd like to edit type 1, 2, 3, 4 or 5:\n");
                break;
            }
            case 2: {
                printf("Type your new username. [between 2 and 25 characters]\n");
                scanf(" ");
                gets(participants[current_user].username);

                while(strlen(participants[current_user].username) < 2 || strlen(participants[current_user].username) > 25) {
                    printf("The username should have between 2 and 25 characters. Try again.\n");
                    scanf(" ");
                    gets(participants[current_user].username);
                }

                bool taken = true;
                while(taken) {
                    taken = false;
                    int i = 0;
                    for(i = 0; i < participant_count && !taken; i ++) {
                        if(i == current_user && strcmp(participants[i].username, participants[current_user].username) == 0) {
                            taken = true;
                        }
                    }
                    if(taken) {
                        printf("Someone else took that username already! Try another one.\n");
                        scanf(" ");
                        gets(participants[current_user].username);
                        
                        while(strlen(participants[current_user].username) < 2 || strlen(participants[current_user].username) > 25) {
                            printf("The username should have between 2 and 25 characters. Try again.\n");
                            scanf(" ");
                            gets(participants[current_user].username);
                        }
                    }
                }
                printf("Username successfully updated!\n");
                printf("1 - full name\n2 - username\n3 - password\n4 - gift preferences\n");
                printf("If there's anything else you'd like to edit type 1, 2, 3 or 4 to edit one of the above, or 5 to exit:\n");
                break;
            }
            case 3: {
                printf("Type your new password:\n");
                scanf(" ");
                gets(participants[current_user].password);

                while(strlen(participants[current_user].password) < 2 || strlen(participants[current_user].password) > 25) {
                    printf("The password should have between 2 and 25 characters. Try again.\n");
                    scanf(" ");
                    gets(participants[current_user].password);
                }

                printf("Password successfully updated!\n");
                printf("1 - full name\n2 - username\n3 - password\n4 - gift preferences\n");
                printf("If there's anything else you'd like to edit type 1, 2, 3 or 4 to edit one of the above, or 5 to exit:\n");
                break;
            }
            case 4: {
                printf("Type your new gift preferences:\n");
                scanf(" ");
                gets(participants[current_user].gift_preference);

                while(strlen(participants[current_user].gift_preference) < 2 || strlen(participants[current_user].gift_preference) > 100) {
                    printf("The gift preferences should have between 2 and 100 characters. Try again.\n");
                    scanf(" ");
                    gets(participants[current_user].gift_preference);
                }

                printf("Gift preferences successfully updated!\n");
                printf("1 - full name\n2 - username\n3 - password\n4 - gift preferences\n");
                printf("If there's anything else you'd like to edit type 1, 2, 3 or 4 to edit one of the above, or 5 to exit:\n");
                break;
            }
            default: {
                printf("Invalid operation! Type 1, 2, 3, 4 or 5.\n");
                break;
            }
        }
        scanf(" %d", &choice);
    }
}
