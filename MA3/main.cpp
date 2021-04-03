#include <map>
#include "TwitterData.hpp"

using namespace std;

void printFindAndDelete(map<string,TwitterData>* map, string k){
    for(auto & it : *map) {
        cout << "\t" << it.first << ": " << it.second.print() << endl;
    }
    auto found = map->find(k);
    cout << "\n\tFind and remove " + k + ": "+ found->second.print() + "\n\n";
    map->erase(found);
    cout << "\tAfter Removed:\n\n";
    for(auto & it : *map) {
        cout << "\t" << it.first << ": " << it.second.print() << endl;
    }
}

int main(int argc, char* argv[])
{
    // Schema: UserName,Last,First,Email,NumTweets,MostViewedCategory
    string raw_data[5][6] = {{"rangerPower","Smit","Rick","smitRick@gmail.com","1117","power lifting"},
                             {"kittyKat72","Smith","Kathryn","kat@gmail.com","56","health"},
                             {"lexi5","Anderson","Alexis","lexi5@gmail.com","900","education"},
                             {"savage1","Savage","Ken","ksavage@gmail.com","17","president"},
                             {"smithMan","Smith","Rick","rick@hotmail.com","77","olympics"}};
    auto *twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i) {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }

    auto *unMap = new map<string,TwitterData>;
    auto *emailMap = new map<string,TwitterData>;

    for(int i = 0;i < 5; i++) {
        unMap->insert(pair<string,TwitterData>(twitter_data[i].getUserName(), twitter_data[i]));
        emailMap->insert(pair<string,TwitterData>(twitter_data[i].getEmail(), twitter_data[i]));
    }
    cout << "UserName Map" << endl;
    printFindAndDelete(unMap, "savage1");
    cout << endl << "Email Map" << endl;
    printFindAndDelete(emailMap, "kat@gmail.com");


    return 0;
}