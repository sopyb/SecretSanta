// dependencies
#include <stdio.h>
#include <malloc.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// local includes
#include "DataStore/DataStore.h"
#include "PasswordManager/PasswordManager.h"
#include "colors.h"

// Constants
#define CONF_FILE "./config.conf"

// event function prototypes
void onInit(void);
void run(void);
void onExit(void);

// main function
int main() {
  // init event
  onInit();

  // run event
  run();

  // exit event
  onExit();
  return 0;
}

void onInit() {
  // setup config file
  //hacky way to define data arrays
  DataItem defaultConfig[] = {
	  {"__SIZE__", malloc(sizeof(int))},
	  {"admin_pass", "YWRtaW4="}, // admin
	  {"budget", "10"},
	  {"currency", "EUR"}
  };
  *(int *) defaultConfig[0].value = 3;

  initData(CONF_FILE, defaultConfig);

  //setup folder structures
  mkdir("./data", 0777);
  mkdir("./data/participants", 0777);

  // create password file
  FILE *passFile;
  if((passFile = fopen("./data/pass.txt", "r+")) == NULL) {
	  // if file doesn't exist, create it
	  passFile = fopen("./data/pass.txt", "w");
	  if(passFile == NULL) {
		  printf(RED "Critical error: Cannot create password file!" reset "\n");
		  exit(1);
	  }

	  fclose(passFile);
  }

  // warn if admin password is default
  if (strcmp(getKey("admin_pass", CONF_FILE), "YWRtaW4=") == 0) {
	printf(YELLOW "WARNING: The admin password is still the default. Please change it!" reset "\n");
  }
}

void run() {
  // main loop
  while (true) {
	printf(CLEARTERM);
	// print menu
	printf("Welcome to Secret Santa!\n"
		   "Please select an option:\n"
		   "1. Register\n"
		   "2. Login\n"
		   "3. List participants\n"
		   "\n"
		   "9. Session Settings\n"
		   "0. Exit\n"
		   ">> ");

	// get input
	char input[2];
	scanf("%s", input);
	if (strcmp(input, "0") == 0)
	  // exit
	  break;
  }
}

void onExit() {
  // if the admin password is still the default, warn the user
  if (strcmp(getKey("admin_pass", CONF_FILE), "YWRtaW4=") == 0) {
	printf(YELLOW "WARNING: The admin password is still the default. Please change it!" reset "\n");
  }
}
