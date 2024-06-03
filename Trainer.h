#ifndef TRAINER_H
#define TRAINER_H
#include "GameObject.h"
#include "PokemonGym.h"
#include "PokemonCenter.h"
#include "WildPokemon.h"
#include <math.h>
#include <cstdlib>

class Trainer:public GameObject{
    enum TrainerStates {
        STOPPED = 0,
        MOVING = 1,
        FAINTED = 2,
        AT_CENTER = 3,
        IN_GYM = 4,
        MOVING_TO_CENTER = 5,
        MOVING_TO_GYM = 6,
        BATTLING_IN_GYM = 7,
        RECOVERING_HEALTH = 8,
        SPONTANEOUS_COMBAT = 9
    };

    public:
    Trainer();
    Trainer(char);
    Trainer(string, int, char, unsigned int, Point2D);
    ~Trainer();
    void StartMoving(Point2D);
    void StartMovingToGym(PokemonGym*);
    void StartMovingToCenter(PokemonCenter*);
    void StartBattling(unsigned int);
    void StartRecoveringHealth(unsigned int);
    void Stop();
    bool HasFainted();
    bool ShouldBeVisible();
    void ShowStatus();
    bool Update();
    string getName();
    double getSpeed();//added for follow
    unsigned int getHealth();
    void wildEngaged(WildPokemon*);

    protected:
    bool UpdateLocation();
    void SetupDestination(Point2D);

    private:
    double speed;
    bool is_at_center;
    bool is_in_gym;
    unsigned int health;
    unsigned int experience;
    double PokeDollars;
    unsigned int battles_to_buy;
    unsigned int potions_to_buy;
    string name;
    PokemonCenter *current_center;
    PokemonGym *current_gym;
    WildPokemon* current_assailant;
    Point2D destination;
    Vector2D delta;
    char interruptedState;
};

static double GetRandomAmountOfPokeDollars();

#endif