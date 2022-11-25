/*********************************************************************\
 !                         PasswordManager.c                         !
 !            Check the header file for more information.            !
\*********************************************************************/

// Dependencies
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../DataStore/DataStore.h"

// Include own header
#include "PasswordManager.h"

// Constants
#define CONF_FILE "./config.conf"
#define PASS_FILE "./data/pass.txt"

char *base64(char *string) {
  // Base64 encoding
  // >.> thanks stackoverflow for the explanation
  // https://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c
  char *base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  int len = strlen(string); // length of string
  int len2 = 4 * ((len + 2) / 3); // length of base64 string
  // explanation of len2: 4 bytes for every 3 bytes of input, plus padding
  char *res = malloc(len2 + 1); // allocate memory for base64 string
  res[len2] = '\0'; // null terminate string

  for (int i = 0; i < len; i += 3) {
	// explaination of the bit shifting (for later me):
	// n = 00000011 - 11110000 - 00111111 (n is composed of 3 8 bit ascii characters)
	// n64[0] = 000000; n64[1] = 111111; n64[2] = 000000; n64[3] = 111111
	// n64[0-3] are the 6 bit values of the base64 characters in the table)

	// read 3 characters from a string
	int n = (string[i] << 16) + (string[i + 1] << 8) + string[i + 2];

	// get the 6 bit values of the base64 characters
	int n64[] = {
		(n >> 18) & 63,
		(n >> 12) & 63,
		(n >> 6) & 63,
		n & 63
	};

	// convert to base64
	for (int j = 0; j < 4; j++) {
	  if (i + j > len) {
		// pad with = if string is not a multiple of 3
		res[i * 4 / 3 + j] = '=';
	  } else {
		res[i * 4 / 3 + j] = base64_table[n64[j]];
	  }
	}
  }

  return res;
}

DataItem *defaultUserData() {
  DataItem data[] = {
	  {"__SIZE__", malloc(sizeof(int))},
	  {"Name", "unknown"},
	  {"GiftTo", "undefined"},
	  {"Location", "Not set"}
  };
  *(int *) data[0].value = 3;

  return data;
}

//
// register an account with password
//
int registerPassword(char *user, char *password) {

  //check if user exists or user == "admin"
  if (getKey(user, PASS_FILE) != NULL
	  || strcmp(user, "admin") == 0
	  || strcmp(user, "unknown") == 0
	  || strcmp(user, "undefined") == 0) {
	printf("Username already exists or is reserved!\n");
	return 0;
  }

  //check if user is not empty
  if (strcmp(user, "") == 0) {
	printf("Username cannot be empty!\n");
	return 0;
  }

  //check if password is defined
  if (password == NULL) {
	printf("Password is not defined!\n");
	return 0;
  }

  //check if password is strong enough
  if (strlen(password) < 8) {
	printf("Password is too short!\n");
	return 0;
  }

  // ! in the real world you'd want to hash the password before storing it
  // ! but base64 is good enough for this project
  // ! because I don't want to implement a hash function
  // ! nor do I want to use a library for it

  //encode password
  password = base64(password);

  //store password
  insertKey(user, password, PASS_FILE);

  //create user data
  DataItem *data = defaultUserData();

  // define file name ./data/participants/$user.txt
  char *file = malloc(strlen(user) + 20);
  strcpy(file, "./data/participants/");
  strcat(file, user);
  strcat(file, ".txt");

  // store data
  initData(file, data);

  return 1;
}

int checkPassword(char *user, char *password) {
  // encode password
  password = base64(password);

  //check if user exists
  if (getKey(user, PASS_FILE) == NULL) {
	// if user is admin check admin password
	if (strcmp(user, "admin") == 0) {
	  return strcmp(getKey("admin_pass", CONF_FILE), password) == 0;
	}
	printf("Username does not exist!\n");
	return 0;
  }

  //check if password is correct
  if (strcmp(getKey(user, PASS_FILE), password) == 0) {
	return 1;
  } else {
	printf("Password is incorrect!\n");
	return 0;
  }
}

int changePassword(char *user, char *oldPassword, char *newPassword) {
  // encode old password
  oldPassword = base64(oldPassword);

  //check if user exists
  if (getKey(user, PASS_FILE) == NULL) {
	printf("Username does not exist!\n");
	return 0;
  }

  //check if old password is correct
  if (strcmp(getKey(user, PASS_FILE), oldPassword) != 0) {
	printf("Old password is incorrect!\n");
	return 0;
  }

  //check if new password is defined
  if (newPassword == NULL) {
	printf("New password is not defined!\n");
	return 0;
  }

  //check if new password is strong enough
  if (strlen(newPassword) < 8) {
	printf("New password is too short!\n");
	return 0;
  }

  // ! in the real world you'd want to hash the password before storing it
  // ! but base64 is good enough for this project
  // ! because I don't want to implement a hash function
  // ! nor do I want to use a library for it

  //encode new password
  newPassword = base64(newPassword);

  //store password
  if (strcmp(user, "admin") == 0) {
	// if user is admin change admin password
	updateKey("admin_pass", newPassword, CONF_FILE);
  } else {
	// else change user password
	updateKey(user, newPassword, PASS_FILE);
  }

  return 1;
}

// ! SHOULD  ONLY BE CALLED BY AUTHENTICATED USERS ON THEIR OWN ACCOUNTS
// ! OR BY THE ADMIN USER
int deleteUser(char *user) {
  //check if user exists
  if (getKey(user, PASS_FILE) == NULL) {
	printf("Username does not exist!\n");
	return 0;
  }

  //delete user
  deleteKey(user, PASS_FILE);

  // define file name ./data/participants/$user.txt
  char *file = malloc(strlen(user) + 20);
  strcpy(file, "./data/participants/");
  strcat(file, user);
  strcat(file, ".txt");

  // delete data
  dropData(file);

  return 1;
}
