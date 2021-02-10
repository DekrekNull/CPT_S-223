#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SLList.h"
#include "functions.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;


//LINKED LIST
//	Advantage: 	Reading from and writing to files in this case is very quick with
//			the use of the list becuase we are adding and removing from the front
//			every time.
//	Disadvantage:	Searching for nodes to avoid adding duplicates and searching for
// 			nodes takes more time than if it was an array.

//ARRAY
//	Advantage:	Updating the profiles scores and checking if there is already a profile
// 			with a given name is very quick.
//	Disadvantage:	Adding profiles to the front requires all other profiles in the array 
//			to be moved back one slot, which not only drops the last one if the
//			array is full, but also takes a lot of time to do.


int main() {

    //initialize files
    SLList<string> *List = getCommandsList();
    Profile profiles[maxProfiles];
    getProfiles(profiles);

    //Seed random with Time to creat pseudo random numbers
    srand(time(NULL));

    bool noExit = true; //Stays true until user chooses to exit the program
    char choice; //Stores the user's choice from the main menu options

    while(noExit){
        menu();
        cin >> choice;
        dash();
        switch (choice) {
            case'1': //Displays game rules
                gameRules();
                break;
            case '2': //Starts a game for a new profile
                playNewGame(List, profiles);
                break;
            case '3': //Starts a game with an existing profile
                loadPrevGame(List, profiles);
                break;
            case '4': //Prompts the user to add a new command to the command list
                addCommand(List);
                break;
            case '5': //Prompts the user to remove a command from the command list
                removeCommand(List);
                break;
            case '6': //Ends the menu loop to exit
                noExit = false;
                break;
            default: //When the user doesn't choose one of the listed options
                cout << "That isn't one of the options!" << endl;
                break;
        }
    }

    //Exits the program, deallocating all dynamic memory
    exitGame(List, profiles);

    return 0;
}
