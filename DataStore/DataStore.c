#include "DataStore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int errorCode(int error) { return error - 10000; }

char* trimWhiteSpace(char *string) {
    //check if string is null or empty
    if (string == NULL || strlen(string) == 0) {
        return string;
    }

    char *end;

    // Trim leading space
    while(isspace((unsigned char)*string)) string++;

    if(*string == 0)  // All spaces?
        return string;

    // Trim trailing space
    end = string + strlen(string) - 1;
    while(end > string && (isspace((unsigned char)*end) || (unsigned char)*end == '\n')) end--;

    // Write new null terminator
    *(end+1) = '\0';

    return string;
}

//
// get all the items from the data file return array of DataItem
//
DataItem *getAllKeys(char *data_file) {
    FILE *fp; //file pointer
    char *line = NULL; //line buffer
    size_t len = 0; //line buffer size
    int i = 0; //line counter
    DataItem *dataItems = malloc(sizeof(DataItem) * 100); //array of DataItem

    //open the file
    fp = fopen(data_file, "r");
    // check if the file is open
    if (fp == NULL) {
        printf("Error opening file: %s", data_file);
        // exit with error
        exit(errorCode(-1));
    }

    // read the file line by line
    while (getline(&line, &len, fp) != -1) {
        // check if line is a comment
        if (line[0] == '#') {
            continue;
        }

        char *key = strtok(line, "="); //get the key
        key = trimWhiteSpace(key); //trim the key
        // get the value of key
        char *value = strtok(NULL, "=");
        // trim the whitespace
        value = trimWhiteSpace(value);x

        // copy the key into dataItems[i].key
        dataItems[i].key = malloc(strlen(key) + 1);
        strcpy(dataItems[i].key, key);

        // copy the value into dataItems[i].key
        dataItems[i].value = malloc(strlen(value) + 1);
        strcpy(dataItems[i].value, value);

        i++;
    }
    // close the file
    fclose(fp);

    // shrink the array to the correct size
    dataItems = realloc(dataItems, sizeof(DataItem) * i);

    // check if there is a line
    if (line) {
        // free the line buffer
        free(line);
    }

    // return the array of DataItem
    return dataItems;
}

//
// get key from data file
//
char* getKey(char* key, char* data_file)
{
    //open data file
    FILE* fp = fopen(data_file, "r");
    
    //check if file is open
    if (fp == NULL)
    {
        printf("Error: Cannot open data file %s", data_file);
        return NULL;
    }

    char* line = NULL; //line from data file
    size_t len = 0; //length of line
    char* value = NULL; //value of key

    // read each line from data file
    while (getline(&line, &len, fp) != -1)
    {
        //check if line is a key
        if (strstr(line, key) != NULL)
        {
            //remove everything before the =
            char* temp = strstr(line, "=");
            //remove the = and whitespace
            value = trimWhiteSpace(temp + 1);

            break;
        }
    }

    fclose(fp);

    //allocate memory for value
    char* result = malloc(sizeof(char) * strlen(value));
    //copy value to result
    strcpy(result, value);

    if (line)
        free(line);

    return result;
}

//
// Create data file if it doesn't exist with default values
//
void initData(char* data_file, DataItem* defaultItems)
{
    //open data file
    FILE* fp = fopen(data_file, "r");

    //check if file is open
    if (fp == NULL)
    {
        //create data file
        fp = fopen(data_file, "w");

        //check if file is open
        if (fp == NULL)
        {
            printf("Error: Cannot create data file %s", data_file);
            return;
        }

        //write default values to data file
        for (int i = 0; i < sizeof(defaultItems); i++)
        {
            // append key = value to data file
            fprintf(fp, "%s=%s", defaultItems[i].key, defaultItems[i].value);
        }
    }

    //close data file
    fclose(fp);
}

//
// update all entries in data file
//
void writeData(char* data_file, DataItem* items)
{
    //open data file
    FILE* fp = fopen(data_file, "w");

    //check if file is open
    if (fp == NULL)
    {
        printf("Error: Cannot open data file %s", data_file);
        return;
    }

    //clear all data in the fp stream
    fflush(fp);

    //write default values to data file
    for (int i = 0; i < sizeof(items); i++)
    {
        // append key = value to data file
        fprintf(fp, "%s=%s", items[i].key, items[i].value);
    }

    //close data file
    fclose(fp);
}


//
// update key in file
//
void updateKey(char* key, char* value, char* data_file)
{
    //open data file
    FILE* fp = fopen(data_file, "r");

    //check if file is open
    if (fp == NULL)
    {
        printf("Error: Cannot open data file %s", data_file);
        return;
    }

    char* line = NULL; //line from data file
    size_t len = 0; //length of line
    ssize_t read; //number of bytes read
    char* newData = NULL; //new data file

    // read each line from data file
    while ((read = getline(&line, &len, fp)) != -1)
    {
        //check if line is a comment
        if (line[0] == '#')
        {
            continue;
        }

        //check if line is a key
        if (strstr(line, key) != NULL)
        {
            // append key = value to new data file
            strcat(newData, key);
            strcat(newData, "=");
            strcat(newData, value);
        }
        else
        {
            // append line to new data file
            strcat(newData, line);
        }
    }

    fclose(fp);
    if (line)
        free(line);

    //open data file
    fp = fopen(data_file, "w");

    //check if file is open
    if (fp == NULL)
    {
        printf("Error: Cannot open data file %s", data_file);
        return;
    }

    //write new data file to data file
    fprintf(fp, "%s", newData);

    //close data file
    fclose(fp);
}