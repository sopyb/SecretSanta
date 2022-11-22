#ifndef CONFIGMANAGER_DATASTORE_H
#define CONFIGMANAGER_DATASTORE_H

// structure to hold the configuration
typedef struct {
    char *key;
    char *value;
} DataItem;

// function prototypes
DataItem *getAllKeys(char *data_file);
char* getKey(char* key, char* data_file);
void initData(char* data_file, DataItem* defaultItems); // not tested
void writeData(char* data_file, DataItem* items); // not tested
void updateKey(char* key, char* value, char* data_file); // not tested

#endif //CONFIGMANAGER_DATASTORE_H
