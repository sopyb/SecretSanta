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
void initData(char* data_file, DataItem* defaultItems);
void writeData(char* data_file, DataItem* items);
void deleteData(char* data_file);
void insertKey(char* key, char* value, char* data_file);
void updateKey(char* key, char* value, char* data_file);
void deleteKey(char* key, char* data_file);

#endif //CONFIGMANAGER_DATASTORE_H
