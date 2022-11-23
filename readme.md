# Secret santa - C
[![CodeFactor](https://www.codefactor.io/repository/github/sopyb/secretsanta/badge/master)](https://www.codefactor.io/repository/github/sopyb/secretsanta/overview/master)
## So uhh what's this?
This is a secret santa program written in C. It's a simple program that takes a list of names and randomly assigns them to each other. 

The process is as follows:
 - Users register their name into the program
 - The admin executes the randomizer
 - Each user can log in and see who they have been assigned to

*oh btw this is a school project*
## How do I build this and use this?
* I am a linux nerd so here's the linux tutorial
```bash
# Clone the repo
$ git clone https://github.com/sopyb/SecretSanta.git
# cd into the directory
$ cd SecretSanta
# make build folder and cd into it
$ mkdir build && cd build
# compile the program with cmake into an executable\
$ cmake .. && make
# make the files executable
$ chmod +x SecretSanta
# run the program
$ ./SecretSanta
```