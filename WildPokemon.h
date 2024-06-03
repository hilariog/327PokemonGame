#ifndef WILDPOKEMON_H
#define WILDPOKEMON_H
#include "GameObject.h"
#include "Point2D.h"
#include "Vector2D.h"
class Trainer;

class WildPokemon: public GameObject{
    enum WildPokemonStates {
        IN_ENVIRONMENT = 0,
        DEAD = 1,
        IN_TRAINER = 2,
        FOLLOWING = 3
    };

    protected:
    double attack;
    double health;
    bool variant;
    bool in_combat;
    string name;
    Trainer* current_trainer;
    public:
    WildPokemon(string name, double attack, double health, bool variant, int id, Point2D in_loc);
    void follow(Trainer* t);
    bool get_variant();
    double get_attack();
    double get_health();
    bool get_in_combat();
    bool Update();
    void ShowStatus();
    bool ShouldBeVisible();
    bool IsAlive();
};

#endif