/************************************************************************\
 !                           file_operations.c                          !
 !           More information can be found in file_operations.h         !
\************************************************************************/

// dependencies
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// unix specific (linux, mac, bsd, etc)
#if !defined(_WIN32)
#include <sys/stat.h>
#endif

// own header
#include "file_operations.h"

const char data_file[] = "./data/data.txt";
const char participant_path[] = "./data/participants/";

// read the data from the data file
void readVitalData() {
    // printf("Please wait for the data to load...\n");
    // make required folder if it doesn't exist
#if defined(_WIN32) // if windows compile
    mkdir("./data");
    mkdir(participant_path);
#else // if unix compile
    mkdir("./data", 0777);
        mkdir(participant_path, 0777);
#endif

    // open data file
    FILE *file_pointer = fopen(data_file, "r");

    // check if file is open
    if(file_pointer != NULL) {

        // read data from file
        fscanf(file_pointer, "%d %d", &participant_count, (int*)(&recipients_have_been_assigned));

        // close file
        fclose(file_pointer);

        // read users data
        readAllUserData(participant_count);
    }
    else {
        // create data file
        file_pointer = fopen(data_file, "w");
        // write default data
        fprintf(file_pointer, "0 0");
        // close file
        fclose(file_pointer);

        // store defaults in memory
        participant_count = 0;
        recipients_have_been_assigned = false;
    }
}

void writeVitalData() {
    // open data file
    FILE *file_pointer = fopen(data_file, "w");

    // write data to file
    fprintf(file_pointer, "%d %d", participant_count, (int)recipients_have_been_assigned);

    // close file
    fclose(file_pointer);
}

void writeUserData(int id, struct user participant) {
    // file path string
    char file_name[30];
    strcpy(file_name, participant_path);
    // buffer to help create the path
    char buffer[30];
    sprintf(buffer, "%d", id);

    // append the id to the path
    strcat(file_name, buffer);
    // append the file extension
    strcat(file_name, ".txt");

    // open file
    FILE *file_pointer;
    file_pointer = fopen(file_name, "w");

    // write data to file
    fprintf(file_pointer, "%s\n%s\n%s\n%s\n%d",
            participant.full_name,
            participant.username,
            participant.password,
            participant.gift_preference,
            participant.recipient_id);

    // close file
    fclose(file_pointer);
}

void readUserData(int current_user) {
    // file path string
    char file_name[30];
    strcpy(file_name, participant_path);

    // buffer to help create the path
    char buffer[30];
    sprintf(buffer, "%d", current_user);

    // append the id to the path
    strcat(file_name, buffer);
    // append the file extension
    strcat(file_name, ".txt");

    // open file
    FILE *file_pointer;
    file_pointer = fopen(file_name, "r");

    // read data from file
    fscanf(file_pointer, "%[a-zA-Z0-9 '\".,]", participants[current_user].full_name); //User's full name
    fscanf(file_pointer, " %[a-zA-Z0-9 '\".,]", participants[current_user].username); // User's username
    fscanf(file_pointer, " %[a-zA-Z0-9 '\".,]", participants[current_user].password); // User's password
    fscanf(file_pointer, " %[a-zA-Z0-9 '\".,]", participants[current_user].gift_preference); // User's gift preference
    fscanf(file_pointer, " %d", &participants[current_user].recipient_id); // User's gift recipient

    // close file
    fclose(file_pointer);
}

void readAllUserData(int count) {
    // loop through all users
    int i;
    for(i = 0; i < count; i ++) {
        // read user data at id i
        readUserData(i);
    }
}

void clearData() {
    // loop through participant data files
    int i;
    for(i = 0; i < participant_count; i ++) {
        // file path string
        char file_name[30];
        strcpy(file_name, participant_path);
        // buffer to help create the path
        char buffer[30];
        sprintf(buffer, "%d", i);

        // append the id to the path
        strcat(file_name, buffer);
        // append the file extension
        strcat(file_name, ".txt");
        // attempt to delete file
        remove(file_name);
    }

    // reset to defults
    participant_count = 0;
    recipients_have_been_assigned = false;

    // update data file
    writeVitalData();
}