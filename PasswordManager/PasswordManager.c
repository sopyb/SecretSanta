// Dependencies
#include <stdio.h>
#include <string.h>
#include "../DataStore/DataStore.h"

// Include own header
#include "PasswordManager.h"

// Constants
#define CONF_FILE "./config.conf"
#define PASS_FILE "./data/pass.txt"

//
// register an account with password
//
void registerPassword(char* user, char* password) {
    //check if user exists or user == "admin"
    if (getKey(user, PASS_FILE) != NULL || strcmp(user, "admin") == 0) {
        printf("Username already exists or is reserved!");
        return;
    }

    //check if user is not empty
    if (strcmp(user, "") == 0) {
        printf("Username cannot be empty!");
        return;
    }

    //check if password is defined
    if (password == NULL) {
        printf("Password is not defined!");
        return;
    }

    //check if password is strong enough
    if (strlen(password) < 8) {
        printf("Password is too short!");
        return;
    }

    // ! in the real world you'd want to hash the password before storing it
    // ! but because I am lazy, we'll just store it as plain text

    //store password
    insertKey(user, password, PASS_FILE);
}

int checkPassword(char* user, char* password) {
    //check if user exists
    if (getKey(user, PASS_FILE) == NULL) {
        // if user is admin check admin password
        if (strcmp(user, "admin") == 0) {
            return  strcmp(getKey("admin_pass", CONF_FILE), password) == 0;
        }
        printf("Username does not exist!");
        return 0;
    }

    //check if password is defined
    if (password == NULL) {
        printf("Password is not defined!");
        return 0;
    }

    //check if password is correct
    if (strcmp(getKey(user, PASS_FILE), password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void changePassword(char* user, char* oldPassword, char* newPassword) {
    //check if user exists
    if (getKey(user, PASS_FILE) == NULL) {
        printf("Username does not exist!");
        return;
    }

    //check if old password is correct
    if (strcmp(getKey(user, PASS_FILE), oldPassword) != 0) {
        printf("Old password is incorrect!");
        return;
    }

    //check if new password is defined
    if (newPassword == NULL) {
        printf("New password is not defined!");
        return;
    }

    //check if new password is strong enough
    if (strlen(newPassword) < 8) {
        printf("New password is too short!");
        return;
    }

    // ! in the real world you'd want to hash the password before storing it
    // ! but because I am lazy, we'll just store it as plain text

    //store password
    updateKey(user, newPassword, PASS_FILE);
}
