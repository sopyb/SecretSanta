#include <stdio.h>
#include <malloc.h>
#include <sys/stat.h>
#include "DataStore/DataStore.h"


// Constants
#define CONF_FILE "./config.conf"

// function prototypes
void init(void);

int main() {
  //run initialization procedure
  init();

  return 0;
}

void init() {
  // setup config file
  //hacky way to define data arrays
  DataItem defaultConfig[3] = {
	  {"__SIZE__", malloc(sizeof(int))},
	  {"admin_pass", "PLEASECHANGETHIS"}};
  *(int *) defaultConfig[0].value = 1;

  initData(CONF_FILE, defaultConfig);

  //setup folder structures
  mkdir("./data", 0777);
  mkdir("./data/participants", 0777);
}
