
#include "SLList.h"
#ifndef PA1_FUNCTIONS_H
#define PA1_FUNCTIONS_H

const int maxProfiles = 5; //maximum number of profiles allowed since we are using an array for storing them
const static std::string tab = "\t\t"; //just used to help keep both the code and terminal output neater



//Struct for the profile info
struct Profile
{
    std::string name;
    int score;
};

//File reading
SLList<std::string>* getCommandsList();

//Profile array functions
void addProfile(Profile* profiles, std::string name, int score);
int profilePosition(Profile* profiles, std::string name);
void getProfiles(Profile* profiles);

//print functions
void menu();
void gameRules();
void dash();

//gameplay functions
void game(SLList<std::string> *List, Profile* profiles, std::string playerName, int score);
void playNewGame(SLList<std::string> *List, Profile* profiles);
void loadPrevGame(SLList<std::string> *List, Profile* profiles);

//add and remove functions
void addCommand(SLList<std::string>* List);
void removeCommand(SLList<std::string>* List);

//exit function
void exitGame(SLList<std::string>* List, Profile* profiles);

#endif //PA1_FUNCTIONS_H
