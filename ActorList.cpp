#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include "ActorList.h"
/*This Class uses the Graph data structure to hold actors and movies, with actors connected in the Graph with movies instead of edge weight
Each Movie has connected actors that have acted in that movie and all actors have adjacent actors(connected by a common movie) and a list of movies they have acted in.
Author: Alex Fisher
*/
using namespace std;
ActorList::ActorList(){
}

ActorList::~ActorList(){
    for(unsigned int x = 0; x < movies.size(); x ++)
        delete movies[x];
    for(unsigned int x = 0; x < actors.size(); x ++)
        delete actors[x];
}
/*This method will take in the name of an actor and print out all of the movie the actor has acted in.If the name isn't in the list, the program will print "Actor not Found"
@param name The name of the actor
*/
void ActorList::actorMovies(string name){
    Actor *act = findActor(name,0,actors.size()-1);
    if(act == NULL){
        cout << "Actor not found" << endl;
        return;
    }
    for(unsigned int x = 0; x < act->movies.size(); x ++){
        cout << act->movies[x]->title << " : " << act->movies[x]->year << endl;
    }
    cout << "This actor acted in at least " << act->movies.size() << " movies." << endl;
}
/*This is a private method that will use the binary searching algorithm to find an actor
@param name The name of the actor we are searching for
@param front The index of the front of the search
@param back The index of the back of the search
@return The Actor pointer being searched for
*/
Actor *ActorList::findActor(string name,int front, int back){
    for(unsigned int x = 0; x < actors.size(); x ++){
        if(actors[x]->name == name)
            return actors[x];
    }
    return NULL;
}
/*This is a private method that will return the AdjActor in order to retrace the path used in findConnection() and findBaconNumber()
@param first The first actor to be connected from
@param second The actor to be connected to
@return The AdjActor with the second actor and Movie
ex: findAdj(Kevin Bacon,Rod Haase) returns AdjActor(Movie = Hero at Large,Actor = Rod Haase)
*/
AdjActor *ActorList::findAdj(Actor *first, Actor *second){
    for(unsigned int x = 0; x < first->adj.size(); x ++){
        if(first->adj[x]->actor->name == second->name)
            return first->adj[x];
    }
    return NULL;
}
/*This method prints out all of the movies Kevin Bacon has acted in (at least all the movies in the list he has acted in)
*/
void ActorList::findBaconMovies(){
    Actor *Bacon = findActor("Kevin Bacon",0,actors.size()-1);
    for(unsigned int x = 0; x < Bacon->movies.size(); x ++){
        cout << Bacon->movies[x]->title << " : " << Bacon->movies[x]->year << endl;
    }
}
/*This method will use a breadth first search to find the Bacon number of an actor and print the path
@param name The name of the actor
*/
void ActorList::findBaconNumber(string name){
    if(name == "Kevin Bacon"){
        cout << "Kevin Bacon is Kevin Bacon; Therefore, his Bacon number is 0" << endl;
        return;
    }
    Actor *Bacon = findActor("Kevin Bacon",0,actors.size()-1);
    Actor *act = findActor(name,0,actors.size()-1);
    if(act == NULL){
        cout << "Actor Not Found" << endl;
        return;
    }
    queue <Actor*> que;
    que.push(Bacon);
    for(unsigned int x = 0; x < actors.size(); x++){
        actors[x]->visited = false;
        actors[x]->Bacon = -1;
    }
    Bacon->previous = NULL;
    Bacon->visited = true;
    Bacon->Bacon = 0;
    while(!act->visited){
        if(que.empty()){
            cout << "Somehow, this actor has no connections to Kevin Bacon. For a more accurate Bacon number, visit www.Google.com" << endl;
            return;
        }
        Actor *temp = que.front();
        que.pop();
        for(unsigned int x = 0; x < temp->adj.size(); x ++){
            Actor *next = temp->adj[x]->actor;
            if(!next->visited){
                next->visited = true;
                next->Bacon = temp->Bacon + 1;
                next->previous = temp;
                que.push(next);
            }
        }
    }
    Actor *temp = act;
    int num = 0;
    while(temp->previous != NULL){
        AdjActor *adj = findAdj(temp,temp->previous);
        cout << temp->name << " acted in " << adj->movie->title << " with " << adj->actor->name << endl;
        temp = temp->previous;
        num ++;
    }
    cout << "This actor's bacon number is " << num << endl;
}
/*This method will use a breadth first search of the graph to find the movie distance between two actors and return the movie path
@param name1 The name of the first actor
@param name2 The name of the second actor
*/
void ActorList::findConnection(string name1,string name2){
    if(name1 == "Kevin Bacon"){
        findBaconNumber(name2);
        return;
    }
    if(name2 == "Kevin Bacon"){
        findBaconNumber(name1);
        return;
    }
    Actor *Bacon = findActor(name1,0,actors.size()-1);
    Actor *act = findActor(name2,0,actors.size()-1);
    if(act == NULL || Bacon == NULL){
        cout << "One or more actors were Not Found" << endl;
        return;
    }
    queue <Actor*> que;
    que.push(Bacon);
    for(unsigned int x = 0; x < actors.size(); x++){
        actors[x]->visited = false;
        actors[x]->Bacon = -1;
    }
    Bacon->previous = NULL;
    Bacon->visited = true;
    Bacon->Bacon = 0;
    while(!act->visited){
        if(que.empty()){
            cout << "These two actors have no connections in the parameters of this program somehow." << endl;
            return;
        }
        Actor *temp = que.front();
        que.pop();
        for(unsigned int x = 0; x < temp->adj.size(); x ++){
            Actor *next = temp->adj[x]->actor;
            if(!next->visited){
                next->visited = true;
                next->Bacon = temp->Bacon + 1;
                next->previous = temp;
                que.push(next);
            }
        }
    }
    Actor *temp = act;
    int num = 0;
    while(temp->previous != NULL){
        AdjActor *adj = findAdj(temp,temp->previous);
        cout << temp->name << " acted in " << adj->movie->title << " with " << adj->actor->name << endl;
        temp = temp->previous;
        num ++;
    }
    cout << "The distance between these two actors is " << num << endl;
}
/*This is a private method that will use the binary searching algorithm to find a movie
@param title The title of the movie we are searching for
@param front The index of the front of the search
@param back The index of the back of the search
@return The Movie pointer being searched for
*/
Movie *ActorList::findMovie(string title, int front, int back){
    if(movies[front]->title == title)
        return movies[front];
    if(movies[back]->title == title)
        return movies[back];
    int index = (front + back) / 2;
    if(index == front || index == back)
        return NULL;
    if(title.compare(movies[index]->title) < 0)
        return findMovie(title,front,index);
    else
        return findMovie(title,index,back);
}
/*This private method will use a kind of insertion sorting algorithm to insert the Actor pointer into the actors vector list in sorted order
@param actor The Actor to be added
*/
void ActorList::insertActor(Actor* actor){
    if(actors.size() == 0){
        actors.push_back(actor);
        return;
    }
    Actor *kicked;
    int index = -1;
    for(unsigned int x = 0; x < actors.size(); x ++){
        if(actor->name.compare(actors[x]->name) < 0){
            kicked = actors[x];
            actors[x] = actor;
            index = x + 1;
            break;
        }
    }
    if(index == -1){
        actors.push_back(actor);
        return;
    }
    Actor *temp;
    for(unsigned int x = index; x < actors.size(); x ++){
        temp = actors[x];
        actors[x] = kicked;
        kicked = temp;
    }
    actors.push_back(kicked);
}
/*This private method will use a kind of insertion sorting algorithm to insert the Movie pointer into the movies vector list in sorted order
@param movie The Movie to be added
*/
void ActorList::insertMovie(Movie* movie){
    if(movies.size() == 0){
        movies.push_back(movie);
        return;
    }
    Movie *kicked;
    int index = -1;
    for(unsigned int x = 0; x < movies.size(); x ++){
        if(movie->title.compare(movies[x]->title) < 0){
            kicked = movies[x];
            movies[x] = movie;
            index = x + 1;
            break;
        }
    }
    if(index == -1){
        movies.push_back(movie);
        return;
    }
    Movie *temp;
    for(unsigned int x = index; x < movies.size(); x ++){
        temp = movies[x];
        movies[x] = kicked;
        kicked = temp;
    }
    movies.push_back(kicked);
}
/*This method lists all the actors in alphabetical order because the actor list is sorted
*/
void ActorList::listActors(){
    for(unsigned int x = 0; x < actors.size(); x ++){
        cout << actors[x]->name << endl;
    }
    cout << "There are currently " << actors.size() << " actors available in this program." << endl;
}
/*This method lists all the movies in alphabetical order because the movie list is sorted
*/
void ActorList::listMovies(){
    for(unsigned int x = 0; x < movies.size(); x ++){
        cout << movies[x]->title << " : " << movies[x]->year << " : " << movies[x]->director << endl;
    }
    cout << "There are currently " << movies.size() << " movies available in this program." << endl;
}
/*This method loads the information from the file in the format "movie title,movie year,director name,actor name,actor name,..."
@param fileName The name of the file to be loaded
*/
void ActorList::loadFile(string fileName){
    ifstream file(fileName.c_str());
    string line;
    while(getline(file,line)){
        int index;
        int year;
        string title;
        string director;
        index = line.find(",");
        title = line.substr(0,index);
        line = line.substr(index + 1);
        index = line.find(",");
        year = atoi(line.substr(0,index).c_str());
        line = line.substr(index + 1);
        index = line.find(",");
        director = line.substr(0,index);
        line = line.substr(index + 1);
        Movie *newMovie = new Movie;
        newMovie->title = title;
        newMovie->year = year;
        newMovie->director = director;
        while(line.find(",") <= line.size()){
            index = line.find(",");
            string name = line.substr(0,index);
            Actor *act = findActor(name,0,actors.size()-1);
            if(act == NULL){
                act = new Actor;
                act->name = name;
                act->Bacon = -1;
                act->previous = NULL;
                insertActor(act);
            }
            newMovie->actors.push_back(act);
            act->movies.push_back(newMovie);
            line = line.substr(index + 1);
        }
        Actor *act = findActor(line,0,actors.size()-1);
        if(act == NULL){
            act = new Actor;
            act->name = line;
            act->Bacon = -1;
            act->previous = NULL;
            insertActor(act);
        }
        newMovie->actors.push_back(act);
        act->movies.push_back(newMovie);
        for(unsigned int x = 0; x < newMovie->actors.size(); x ++){
            for(unsigned int y = x + 1; y < newMovie->actors.size(); y ++){
                AdjActor *adjf = new AdjActor;
                AdjActor *adjb = new AdjActor;
                adjf->actor = newMovie->actors[y];
                adjf->movie = newMovie;
                adjb->actor = newMovie->actors[x];
                adjb->movie = newMovie;
                newMovie->actors[x]->adj.push_back(adjf);
                newMovie->actors[y]->adj.push_back(adjb);
            }
        }
        insertMovie(newMovie);
    }
}
/*This method is like the actorMovies method, however the user searches for a movie and the program prints all the actors that acted in that movie
@param title The title of the movie
*/
void ActorList::movieActors(string title){
    Movie *sabsab = findMovie(title,0,movies.size()-1);
    if(sabsab == NULL){
        cout << "Actor not found" << endl;
        return;
    }
    for(unsigned int x = 0; x < sabsab->actors.size(); x ++){
        cout << sabsab->actors[x]->name << endl;
    }
    cout << "There were about " << sabsab->actors.size() << " actors in this movie" << endl;
}
/*addition
 * This method will take in the name of a director and print out all of the movies directed by that director.
 *If the name isn't in the list, the program will print "Director not Found"
@param name The name of the director
* How To Run:
* list.directorMovies(input)
* Pre-Condition:
* waits for an input
* Post-Condition:
* traverses the movie array and reports if the director is found.
* 
 */
void ActorList::directorMovies(string name){
	int movieCount = 0;

	for(unsigned int x = 0; x < movies.size(); x ++){
		if (movies[x]->director == name) {
			movieCount++;
			cout << movies[x]->title << " : " << movies[x]->year << endl;
		}
	}
	if (movieCount > 0) {
		cout << "This director directed at least " << movieCount << " movies." << endl;
	} else {
		cout << "Director not Found" << endl;
	}
}
/*addition
 * This method will sort the movies in the list by year.
 * How To Run:
 * list.sortMoviesByYear();
 * Pre-Condition:
 * assumes there is a quick sort function
 * Post-Condition
 *
 * calls the quick sort function
  */
void ActorList::sortMoviesByYear(){
	quickSortYear(&movies, 0, movies.size()-1);
}

/* addition
 * This private method implements a quicksort algorithm on the movies vector
 * and sorts the movies by year.
 * How To Run:
 * quicksortYear(&movies,0,movies.size()-1);
 * Pre-Condition:
 * Assumes there is  movie array to sort
 * Post-Condition:
 * creates a rearranged array of Movies
 *
 * @param vector * movieArray pointer to movie vector
 * @param int left leftmost index in array
 * @param itn right rightmost index in array
 */
void ActorList::quickSortYear(std::vector<Movie *> *movieArray, int left, int right) {
     int i = left;
     int j = right;
     Movie *tmp;
     Movie *pivot = (*movieArray)[(left + right) / 2];
     while(i <= j){
          while((*movieArray)[i]->year < pivot->year)
               i++;
          while((*movieArray)[j]->year > pivot->year)
               j--;
          if(i <= j){
               tmp = (*movieArray)[i];
               (*movieArray)[i] = (*movieArray)[j];
               (*movieArray)[j] = tmp;
               i++;
               j--;
          }
     }
     if (left < j)
          quickSortYear(movieArray, left, j);
     if (i < right)
          quickSortYear(movieArray, i, right);
}
