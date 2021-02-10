#include <fstream>
#include "SLList.h"
#include "functions.h"

using std::cout;
using std::endl;

//-------------------------------------------------Node-----------------------------------------------------------
template<class T>
Node<T>::Node(T cmd, T desc) {
    command = cmd;
    description = desc;
    next = nullptr;
}

//-------------------------------------------------List------------------------------------------------------------
//----------------------------------------------Constructor--------------------------------------------------------
template<class T>
SLList<T>::SLList(T cmd, T desc) {
    head = new Node<T>(cmd, desc);
    n = 1;
}
//----------------------------------------------Deconstructor-------------------------------------------------------
//writes the final command list to the commands file and deallocates all of the memory used by the list
template<class T>
SLList<T>::~SLList() {
    //opens file for writing
    std::ofstream file("../commands.csv");
    //writes each command description pair one by one
    while (head != nullptr) {
        Node<T>* temp = head->next;
        file << head->command + ",\"" + head->description + "\"\n";
        delete head;//deletes node
        head = temp;
    }
}

//---------------------------------------------Private Methods------------------------------------------------------
//Returns true if the given command exists in the list
template<class T>
bool SLList<T>::contains(T cmd) {
    Node<T>* temp = head;
    while(temp != nullptr) {
        if (temp->command == cmd) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

//----------------------------------------------Public Methods------------------------------------------------------
//Returns a complete copy of this list
template<class T>
SLList<T>* SLList<T>::clone(){
    Node<T> *temp = head;
    auto *newList = new SLList(temp->command,temp->description);
    for(int i = 0; i < n - 1; i++){
        temp = temp->next;
        newList->addNode(temp->command, temp->description);
    }
    return newList;
}
//Adds a new command and accompanying description to the front of the List
template<class T>
void SLList<T>::addNode(T cmd, T desc) {
        auto* newHead = new Node<T>(cmd, desc);
        newHead->next = head;
        head = newHead;
        n++;
}
//Determines if a command can be added to the list or not
//If the given command is already in the list it returns false
//If not then it adds it to the list and returns true
template<class T>
bool SLList<T>::insertAtFront(T cmd, T desc) {
    if (head == nullptr) {
        head = new Node<T>(cmd, desc);
    }else if (contains(cmd)) {
        cout << "That command is already accounted for!" << endl;
        return false;
    }else {
        addNode(cmd, desc);
        n++;
        cout << "Command successfully added!" << endl;
        return true;
    }
}
//determines if given command is in the list, and if so removes it
//if it removes the node of the command it returns true, otherwise it returns false
template<class T>
bool SLList<T>::removeNode(T cmd) {
    Node<T>* temp1 = head;
    Node<T>* temp2 = temp1;
    while(temp2 != nullptr) {
        if (temp2->command == cmd) {
            if (temp2 == head){
                head = temp2->next;
            }else temp1->next = temp2->next;
            delete temp2;//free up memory since node will Inaccessible
            n--;
            return true;
        }
        temp1 = temp2;
        temp2 = temp2->next;
    }
    return false;
}
//Finds and returns a description for a random command that is not the one given
//  cmd - a command that the description should not be returned
template<class T>
T SLList<T>::getRandomDescription(T cmd) {
    Node<T> *temp = head;

    int r = rand() % n;
    for (int i = 0; i < r; i++) {
        temp = temp -> next;
    }
    if (temp->command == cmd) {
        if (temp->next == nullptr) {
            return head->description;
        }else return temp->next->description;
    }
    return temp->description;
}
//finds and returns the node of a random command in the list, then removes the node
template<class T>
Node<T>* SLList<T>::getAndRemoveRandomCommand() {
    Node<T> *temp1 = head;
    Node<T> *temp2 = temp1;

    int r = rand() % n;
    for (int i = 0; i < r; i++) {
        temp1 = temp2;
        temp2 = temp2 -> next;
    }
    //removes node from list without deleting completely so that the node can be returned and used
    temp1->next = temp2->next;
    return temp2;
}
//accessor for the lists length variable n
template<class T>
int SLList<T>::getLength(){
    return n;
}


