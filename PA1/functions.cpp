#include "functions.h"
#include "SLList.cpp"
#include <string>


using std::cout;
using std::endl;
using std::cin;

//-----------------------------------------Print functions-------------------------------------------------------

//prints the main menu
void menu() {
    dash();
    cout << "Menu" << endl;
    cout << tab << "1. Game Rules" << endl;
    cout << tab << "2. Play Game" << endl;
    cout << tab << "3. Load Previous Game" << endl;
    cout << tab << "4. Add Command" << endl;
    cout << tab << "5. Remove Command" << endl;
    cout << tab << "6. Exit" << endl << endl;
    dash();
    cout << "Choice: ";
}

//prints the rules
void gameRules() {
    cout << "Game Rules: " << endl << endl;
    cout << tab << "Match the proper description to the given linux command and recieve 1 point." << endl;
    cout << tab << "If you guess incorrectly you lose a point instead! Rack up as many points you can," << endl;
    cout << tab << "there is no limit to how many rounds you can play and you score carries over!"<< endl;
}

//prints a dashed line, just to help keep the terminal neater and easier to follow along with
void dash(){
    cout << "--------------------------------------------------------------------------------" << endl;
}


//----------------------------------------Command List Functions-------------------------------------------------

//Reads the file with commands and adds them to a list one at a time
SLList<std::string> *getCommandsList() {
    //Open the file
    std::ifstream file;
    file.open("../commands.csv");
    std::string line;

    //Reads the first line and initializes the list object
    getline(file,line);
    int x = line.find(',');//finds the comma that splits the command and description
    std::string command = line.substr(0, x);//takes the command out of the line
    std::string description = line.substr(x + 2, line.length());//takes the description out of the line
    description.pop_back();//gets rid of the lingering comma
    auto *CommandList = new SLList<std::string>(command, description);

    //iterates over the rest of the file repeating the above process but adding new nodes to the existing list
    if (file.is_open()) {
        while (getline(file,line)){
            x = line.find(',');
            command = line.substr(0, x);
            description = line.substr(x + 2, line.length());
            description.pop_back();
            CommandList->addNode(command, description);
        }
        file.close();//closes file once all the lines are read
    }
    return CommandList;//returns the list of commands
}
//prompts the user for a new command to add to the list
//  List - the list of commands
void addCommand(SLList<std::string>* List) {
    std::string command;
    std::string description;
    bool complete = false;//stays false until either a new command is added or the user chooses to exit

    while (!complete) {
        //promt the user for input
        cout << "What command would you like to add?: ";
        cin >> command;
        cin.ignore();//ignores the exit character from pressing enter so that getline doesn't take it and finish
        cout << "How would you describe this command?: ";
        getline(cin, description);
        //attempts to add the command, if it already exists then it will return false and not leave the loop
        complete = List->insertAtFront(command, description);
        //if the adding fails, prompt the user to try again or exit
        if (!complete) {
            char yn;
            cout << "Would you like to try a different command (y/n)?: ";
            cin >> yn;
            if (yn != 'y' && yn != 'Y') {
                complete = true;
                cout << "Returning to main menu." << endl;
            }
        }
    }
}
//prompts the user for a command to remove
void removeCommand(SLList<std::string>* List) {
    std::string command;
    bool complete = false;
    //continues to prompt the user for a command until they enter one that exists
    while (!complete) {
        cout << "What command would you like to remove?: ";
        cin >> command;
        //attempts to remove the command, if it returns false then it continues the loop
        complete = List->removeNode(command);
        //if it fails, prompt the user to try again or exit
        if(!complete) {
            char yn;
            cout << "That command does not exist and therefore cannot be removed." << endl;
            cout << "Would you like to try a different command (y/n)?: ";
            cin >> yn;
            if (yn != 'y' && yn != 'Y') {
                complete = true;
                cout << "Returning to main menu." << endl;
            }
        }
        cout << "Command removed successfully!" << endl;
    }
}


//------------------------------------------Profile functions-----------------------------------------------------

//Takes user or file input to add a new Profile to the profiles array at the front
//  profiles - Profile array
//  name - name of the profile
//  score - current score of the user
void addProfile(Profile *profiles, std::string name, int score) {
    //iterates over the Profile array bumping all existing profiles back one to open the front for the new profile
    for (int i = maxProfiles - 1; i > 0; i--){
        (profiles + i)->name = (profiles + i - 1)->name;
        (profiles + i)->score = (profiles + i - 1)->score;
    }
    //changes the values of the now empty front slot of the Profile array
    profiles->name = name;
    profiles->score = score;
}

//Finds the position of the profile of the given name in the given Profile array
//  profiles - Profile array
//  name - name of the profile being searched for
//If the profile is found it will return the position in the array as an int value (0 - profiles.size())
//If the profile is not found it will return -1
int profilePosition(Profile* profiles, std::string name){
    for(int i = 0; i < maxProfiles; i++) {
        if((profiles + i)->name == name) return i;
    }
    return -1;
}

//Reads the file the profiles are stored in and writes the to a Profile array
void getProfiles(Profile *profiles) {
    //open the file
    std::ifstream file;
    file.open("../profiles.csv");
    std::string line;

    //iterate over the file line by line
    if (file.is_open()) {
        while(getline(file, line)){
            int x = line.find(',');//finds the split between the profile name and score
            std::string player = line.substr(0, x);//takes just the profile name
            int score = stoi(line.substr(x + 1, line.length() - 1));//takes just the score as an int
            addProfile(profiles, player, score); //adds new profile to array
        }
        file.close();//closes file
    }
}


//-------------------------------------------Game functions-----------------------------------------------------------

//plays a single round of the game using a given profile
//  List - the list of commands
//  profiles - the Profile array, needs to be updated after the round completes
//  playerName - name of the current profile
//  score - the profiles initial score
void game(SLList<std::string> *List, Profile* profiles, std::string playerName, int score) {
    //makes a copy of the commands list to keep track of the used commands already used and avoid repeats
    SLList<std::string>* unusedCommands = List->clone();

    int rounds;//number of commands the user will guess

    //prompts user for a number of commands to guess until they give a valid input
    while(true) {
        cout << "How many rounds would you like to play? (5 - " + std::to_string(List->getLength()) + "): ";
        cin >> rounds;
        if (rounds >= 5 && rounds <= List->getLength()){
            break;
        }else cout << "That input is invalid, please try again!" << endl;
    }
    //repeatedly displays the commands and prompts the guess for the given number of times
    for (int i = 0; i < rounds; i++) {
        dash();
        //retrieves a command from the clone list as the correct answer
        Node<std::string> *correctCommand = unusedCommands->getAndRemoveRandomCommand();
        cout << correctCommand->command + ":" << endl;
        //determines in which position the correct answer will be displayed
        int answerPosition = rand() % 4 + 1;

        //Prints all four possible descriptions
        for(int k = 1; k <= 4; k++) {
            cout << tab << std::to_string(k) + ".";
            if (k == answerPosition){//prints the correct answer in the randomly determined place
                cout << correctCommand->description;
            }else cout << List->getRandomDescription(correctCommand->command);//retrieves a random false answer
            cout << endl;
        }
        //prompts user for a guess
        cout << endl << "Your answer:";
        int userAnswer;
        cin >> userAnswer;
        cout << endl;
        //inform the user whether they were correct or not
        if(userAnswer == answerPosition) {
            score++;
            cout << "That's correct! ";
        }else {
            score--;
            cout << "That's incorrect! ";
        }
        //provide an updated score to the user
        cout << playerName + "'s score is now: " + std::to_string(score) + "." << endl;
        delete correctCommand;//node no longer needed and memory needs to be freed up
    }
    //at the end announce the final score
    cout << "Game complete! " + playerName + "'s final score is: " + std::to_string(score) + "." << endl;
    //update the profile's score in the array
    profiles[profilePosition(profiles, playerName)].score = score;
}

//Starts a new game and prompts for a new profile name
//  List - the list of commands
//  profiles - the Profile array
void playNewGame(SLList<std::string> *List, Profile* profiles) {
    std::string playerName;

    //promt user for a new profile name until one is entered that doesn't already exist
    while(true){
        cout << "Enter a new profile name: ";
        cin >> playerName;
        if(profilePosition(profiles, playerName) == -1) {
            addProfile(profiles, playerName, 0);
            break;
        }
        else {
            cout << "That profile already exists!" << endl;
        }
    }
    //starts a new game with the newly given profile name and a fresh score
    game(List, profiles, playerName, 0);
}

//Starts a new game and prompts the user for an already existing profile name
//  List - the list of commands
//  profiles- the Profile array
void loadPrevGame(SLList<std::string> *List, Profile* profiles) {
    std::string playerName;
    int score;
    //prompts the user for an already existing profile name
    while(true) {
        cout << "Enter an existing profile name (enter ""exit"" to return to menu): ";
        cin >> playerName;
        if (playerName == "exit") return;
        int position = profilePosition(profiles, playerName);
        if( position >= 0) {
            score = (profiles + position)->score;
            break;
        }
        else {
            cout << "That profile does not exist!" << endl;
        }
    }
    //displays the profiles previous total score
    cout << "Continuing " + playerName + "'s game. Score: " << score << endl;
    //starts the new game with the given profile
    game(List, profiles, playerName, score);
}

//prints the final list of commands and array of Profiles to their existing files and deallocates the used memory
void exitGame(SLList<std::string>* List, Profile* profiles) {
    //open the file for the profiles to be written to
    std::ofstream file("../profiles.csv");

    //repeats for every profile and writes it to the file in the proper format
    for (int i = 0; i < maxProfiles; i ++) {
        if ((profiles + i)->name.length() > 0) {
            file << (profiles + i)->name + "," + std::to_string((profiles + i)->score) + "\n";
        }
    }
    file.close();//closes file
    delete List;//deconstructor to deallocate memory
    cout << "Progress saved successfully. Thank you for playing!" << endl;
}



