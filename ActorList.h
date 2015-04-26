#ifndef ACTORLIST_H_INCLUDED
#define ACTORLIST_H_INCLUDED

#include <string>
#include <vector>
using namespace std;

struct Actor;
struct Movie;
struct AdjActor;

struct AdjActor{
    Actor *actor;
    Movie *movie;
};

struct Movie{
    int year;
    string title;
    string director;
    vector <Actor*> actors;
};

struct Actor{
    vector <Movie*> movies;
    vector <AdjActor*> adj;
    Actor *previous;
    int Bacon;
    string name;
    bool visited;
};

class ActorList{
    private:
        vector <Actor*> actors;
        vector <Movie*> movies;
        Actor *findActor(string name,int front, int back);
        AdjActor *findAdj(Actor *first, Actor *second);
        Movie *findMovie(string title,int front, int back);
        void insertActor(Actor *actor);
        void insertMovie(Movie *movie);
    public:
        ActorList();
        ~ActorList();
        void actorMovies(string name);
        void findBaconMovies();
        void findBaconNumber(string name);
        void findConnection(string name1,string name2);
        void listActors();
        void listMovies();
        void loadFile(string filename);
        void movieActors(string title);
};




#endif // ACTORLIST_H_INCLUDED
