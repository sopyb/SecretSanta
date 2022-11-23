/*****************************************************************************\
 *  DataStore module                                                         *
 *  Copyright (C) 2022 Sopy                                                  *
 *  FILE: DataStore.h                                                        *
 *                                                                           *
 *  AUTHOR: Sopy <contact@sopy.one>                                          *
 *  DESCRIPTION: Header file for DataStore.c                                 *
 *  DEPENDENCIES: stdio.h, stdlib.h, string.h, ctype.h                       *
 *  LICENSE: GNU General Public License v3.0                                 *
 *                                                                           *
 *  CREATED: 2022-11-22                                                      *
 *  MODIFIED: 2022-11-23                                                     *
 *  VERSION: 1.0.0                                                           *
 *  NOTES: Why do I always overcomplicate stuff?                             *
\*****************************************************************************/

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
void dropData(char* data_file);
void insertKey(char* key, char* value, char* data_file);
void updateKey(char* key, char* value, char* data_file);
void deleteKey(char* key, char* data_file);

#endif //CONFIGMANAGER_DATASTORE_H
