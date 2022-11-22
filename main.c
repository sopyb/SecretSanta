#include <stdio.h>
#include "DataStore/DataStore.h"

//import WebServer from WebServer;

int main() {
    //get an item from /home/sopy/CLionProjects/SecretSanta/testconfig.ss
    char *key = "test";
    char *value = getKey(key, "/home/sopy/CLionProjects/SecretSanta/testconfig.ss");
    printf("Key: %s, Value: %s\n", key, value);

    //get all items from /home/sopy/CLionProjects/SecretSanta/testconfig.ss
    DataItem *items = getAllKeys("/home/sopy/CLionProjects/SecretSanta/testconfig.ss");
    for (int i = 0; i < sizeof(items); i++) {
        DataItem item = items[i];
        printf("Key: %s, Value: %s\n", item.key, item.value);
    }

    return 0;
}
