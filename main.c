#include <stdio.h>
#include <malloc.h>
//#include "DataStore/DataStore.h"
#include "WebServer/WebServer.h"

int main() {
    Server();

//    //hacky way to define data file
//    DataItem defaultItems[3] = {
//            {"__SIZE__", malloc(sizeof(int))},
//            {"key1", "value1"},
//            {"key2", "value2"}
//    };
//    *(int *) defaultItems[0].value = 2;
//
//    // way of alocating memory and assigning value at the same time
//
//    //init to /home/sopy/CLionProjects/SecretSanta/testconfig.conf with default items = items
//    initData("/home/sopy/CLionProjects/SecretSanta/testconfig.ss", defaultItems);
//
//
//    //get an item from /home/sopy/CLionProjects/SecretSanta/testconfig.ss
//    char *key = "test";
//    char *value = getKey(key, "/home/sopy/CLionProjects/SecretSanta/testconfig.ss");
//    printf("Key: %s, Value: %s\n", key, value);
//
//    //get all items from /home/sopy/CLionProjects/SecretSanta/testconfig.ss
//    DataItem *items = getAllKeys("/home/sopy/CLionProjects/SecretSanta/testconfig.ss");
//
//    printf("All items count: %d\n", *(int *) items[0].value);
//    for (int i = 1; i <= *(int *) items[0].value; i++) {
//        DataItem item = items[i];
//        printf("Key: %s, Value: %s\n", item.key, item.value);
//    }
//
//    //init to /home/sopy/CLionProjects/SecretSanta/testconfig.conf with default items = items
//    initData("/home/sopy/CLionProjects/SecretSanta/testconfig.conf", items);
//
//    //write a new item to /home/sopy/CLionProjects/SecretSanta/testconfig.conf
//    writeData("/home/sopy/CLionProjects/SecretSanta/testconfig.conf", items);
//
//    //insert a new item to /home/sopy/CLionProjects/SecretSanta/testconfig.conf
//    insertKey("somethingreallyCool", "f", "/home/sopy/CLionProjects/SecretSanta/testconfig.conf");
//    insertKey("somethingreallycool", "qweasdzxc", "/home/sopy/CLionProjects/SecretSanta/testconfig.conf");
//
//    //update a key in /home/sopy/CLionProjects/SecretSanta/testconfig.conf
//    DataItem updateItem = {"test", "test2"};
//    updateKey(updateItem.key, updateItem.value, "/home/sopy/CLionProjects/SecretSanta/testconfig.conf");
//
//    //delete a key in /home/sopy/CLionProjects/SecretSanta/testconfig.conf
//    deleteKey("somethingreallyCool", "/home/sopy/CLionProjects/SecretSanta/testconfig.conf");

    return 0;
}
