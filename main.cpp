#include <iostream>
#include "ActorList.h"
#include <stdlib.h>

using namespace std;

string filename = "Movies_and_Actors.txt";
int main(){
    bool run = true;
    ActorList list;
    list.loadFile(filename);
    while(run){
        cout << "~~~~~~~~Main Menu~~~~~~~~" << endl;
        cout << "1: Find an actor's Bacon number" << endl;
        cout << "2: List all Bacon Movies" << endl;
        cout << "3: List all actors in a movie" << endl;
        cout << "4: List all movies including an actor" << endl;
        cout << "5: Distance between two actors" << endl;
        cout << "6: List all actors" << endl;
        cout << "7: List all movies" << endl;
        cout << "8: Quit" << endl;
        string input;
        string input2;
        int numInput;
        getline(cin,input);
        numInput = atoi(input.c_str());
        switch (numInput){
            case 1:
                cout << "What actor would you like to search?" << endl;
                getline(cin,input);
                list.findBaconNumber(input);
                break;
            case 2:
                list.findBaconMovies();
                break;
            case 3:
                cout << "What movie would you like to search?" << endl;
                getline(cin,input);
                list.movieActors(input);
                break;
            case 4:
                cout << "What actor would you like to search?" << endl;
                getline(cin,input);
                list.actorMovies(input);
                break;
            case 5:
                cout << "What is the first actor you would like to search?" << endl;
                getline(cin,input);
                cout << "What is the second actor you would like to search?" << endl;
                getline(cin,input2);
                list.findConnection(input,input2);
                break;
            case 6:
                list.listActors();
                break;
            case 7:
                list.listMovies();
                break;
            case 8:
                run = false;
                cout << "Goodbye!" << endl;
                break;
        }
    }
}
