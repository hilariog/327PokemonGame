#ifndef MODEL_H
#define MODEL_H
#include "View.h"
#include "Trainer.h"
#include "WildPokemon.h"
#include <list>
using namespace std;


class Model{
    private:
    int time;
    list <GameObject*> object_ptrs;
    list <GameObject*> active_ptrs;
    list <Trainer*> trainer_ptrs;
    list <PokemonCenter*> center_ptrs;
    list <PokemonGym*> gym_ptrs;
    list <WildPokemon*> wild_ptrs;
    
    public:
    Model();
    virtual ~Model();
    Trainer *GetTrainerPtr(int);
    PokemonCenter *GetPokemonCenterPtr(int);
    PokemonGym *GetPokemonGymPtr(int);
    WildPokemon *GetWildPointer(int);
    bool Update();
    void Display(View &);
    void ShowStatus();
    void NewCommand(char, int, double, double);
};

#endif