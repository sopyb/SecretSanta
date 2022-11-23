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
        key = trimWhiteSpace(key); //trim whitespace - key

        char *value = strtok(NULL, "="); // get the value of key
        value = trimWhiteSpace(value); // trim the whitespace - value

        // copy the key into dataItems[i].key
        dataItems[i].key = malloc(strlen(key) + 1);
        strcpy(dataItems[i].key, key);

        // copy the value into dataItems[reali].key
        dataItems[i].value = malloc(strlen(value) + 1);
        strcpy(dataItems[i].value, value);

        i++;
    }

    // create result array copying the dataItems array at an offset of 1
    DataItem *result = malloc((i + 1) * sizeof(DataItem));

    // allocate result[0] to hold the size of the array with key "__size__" and value int i
    result[0].key = malloc(strlen("__size__") + 1);
    strcpy(result[0].key, "__size__");
    result[0].value = malloc(sizeof(int));
    *(int *) result[0].value = i;

    // copy the dataItems array into the result array
    for (int j = 1; j <= i; j++) {
        result[j] = dataItems[j - 1];
    }

    // close the file
    fclose(fp);

    // check if there is a line
    if (line) {
        // free the line buffer
        free(line);
    }

    // return the array of DataItem
    return result;
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

    char* result;
    //check if value is null
    if (value == NULL)
    {
        result = NULL;
    } else {
        //allocate memory for value
        result = malloc(sizeof(char) * strlen(value));
        //copy value to result
        strcpy(result, value);
    }

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
        for (int i = 1; i <=  *(int *) defaultItems[0].value; i++)
        {
            // append key = value to data file
            fprintf(fp, "%s=%s\n", defaultItems[i].key, defaultItems[i].value);
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

    //write default values to data file
    for (int i = 1; i <= *(int *) items[0].value; i++)
    {
        // append key = value to data file
        fprintf(fp, "%s=%s\n", items[i].key, items[i].value);
    }

    //close data file
    fclose(fp);
}

//
// delete data file
//
void deleteData(char* data_file)
{
    //delete data file
    remove(data_file);
}


//
// insert key into file
// if key exists, don't change value
//
void insertKey(char* key, char* value, char* data_file)
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
    char* temp = NULL; //temp string
    char* result = NULL; //result string

    // read each line from data file
    while (getline(&line, &len, fp) != -1)
    {
        //check if line is a key
        if (strstr(line, key) != NULL)
        {
            //remove everything before the =
            temp = strstr(line, "=");
            //remove the = and whitespace
            result = trimWhiteSpace(temp + 1);

            break;
        }
    }

    //check if key exists
    if (result == NULL)
    {
        //reopen data file
        freopen(data_file, "a", fp);

        //append key = value to data file
        fprintf(fp, "%s=%s\n", key, value);

        //close data file
        fclose(fp);
    }
}

//
// update key in file
// if key doesn't exist, create it
//
void updateKey(char* key, char* value, char* data_file)
{
    int updated = 0; //check if key is updated
    //open data file
    FILE* fp = fopen(data_file, "r");

    //check if file is open
    if (fp == NULL)
    {
        printf("Error: Cannot open data file %s", data_file);
        return;
    }

    //create temp file stream in memory
    FILE* temp = tmpfile();

    //check if file is open
    if (temp == NULL)
    {
        printf("Error: Cannot create temp file");
        return;
    }

    //read each line from data file
    char* line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != -1)
    {
        //check if line is a key
        if (strstr(line, key) != NULL)
        {
            fprintf(temp, "%s=%s\n", key, value);
            updated = 1;
        }
        else
        {
            //write line to temp file
            fprintf(temp, "%s", line);
        }
    }

    if(!updated)
    {
        fprintf(temp, "%s=%s\n", key, value);
    }

    line = NULL;
    len = 0;

    //reopen data file
    freopen(data_file, "w", fp);

    //write temp file to datafile path
    rewind(temp);
    while (getline(&line, &len, temp) != -1)
    {
        fprintf(fp, "%s", line);
    }

    //close files
    fclose(fp);
    fclose(temp);
}

//
// remove key from data file
//
void deleteKey(char* key, char* data_file) {
    //open data file
    FILE* fp = fopen(data_file, "r");

    //check if file is open
    if (fp == NULL)
    {
        printf("Error: Cannot open data file %s", data_file);
        return;
    }

    //create temp file stream in memory
    FILE* temp = tmpfile();

    //check if file is open
    if (temp == NULL)
    {
        printf("Error: Cannot create temp file");
        return;
    }

    //read each line from data file
    char* line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != -1)
    {
        //check if line is a key
        if (strstr(line, key) == NULL)
        {
            //write line to temp file
            fprintf(temp, "%s", line);
        }
    }

    //reopen data file
    freopen(data_file, "w", fp);

    //write temp file to datafile path
    rewind(temp);
    while (getline(&line, &len, temp) != -1)
    {
        fprintf(fp, "%s", line);
    }

    //close files
    fclose(fp);
    fclose(temp);
}