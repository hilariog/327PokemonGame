#include "PokemonGym.h"

//constructors

PokemonGym::PokemonGym():Building('G', 1, Point2D()){
    state = NOT_DEFEATED;
    max_number_of_battles = 10;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = 1;
    PokeDollar_cost_per_battle = 1; 
    experience_per_battle = 2;
    cout << "PokemonGym default constructed" << endl;
}

PokemonGym::PokemonGym(unsigned int maxBat, unsigned int healthLoss, double price, unsigned int expGain, int in_id, Point2D in_loc):Building('G', in_id, in_loc){
    state = NOT_DEFEATED;
    max_number_of_battles = maxBat;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = healthLoss;
    PokeDollar_cost_per_battle = price;
    experience_per_battle = expGain;
    cout << "PokemonGym constructed" << endl;
}

//Destructor

PokemonGym::~PokemonGym(){
    cout << "Gym Destroyed" << endl;
}

//functions

double PokemonGym::GetPokeDollarCost(unsigned int numBat){
    return (numBat * PokeDollar_cost_per_battle);
}

unsigned int PokemonGym::GetHealthCost(unsigned int numBat){
    return (numBat * health_cost_per_battle);
}

unsigned int PokemonGym::GetNumBattlesRemaining(){
    return num_battle_remaining;
}

bool PokemonGym::IsAbleToBattle(unsigned int numBat, double budget, unsigned int health){
    if(budget >= (numBat * PokeDollar_cost_per_battle) && health >= (numBat * health_cost_per_battle)){
        return true;
    }else{
        return false;
    }
}

unsigned int PokemonGym::TrainPokemon(unsigned int batUnit){
    if(batUnit <= num_battle_remaining){
        num_battle_remaining -= batUnit;
        return (batUnit * experience_per_battle);
    }else{
        unsigned int retval = num_battle_remaining;
        num_battle_remaining = 0;
        return (retval * experience_per_battle);
    }
}

unsigned int PokemonGym::GetExperiencePerBattle(){
    return experience_per_battle;
}

bool PokemonGym::Update(){
    if(num_battle_remaining == 0){
        bool retval = false;
        if(state == NOT_DEFEATED){
            retval = true;
        }
        state = DEFEATED;
        display_code = 'g';
        cout << display_code << id_num << "has been beaten." << endl;
        return retval;
    }else{
        return false;
    }
}

bool PokemonGym::Passed(){
    if(num_battle_remaining == 0){
        return true;
    }else{
        return false;
    }
}

void PokemonGym::ShowStatus(){
    cout << "PokemonGym Status: " << endl;
    Building::ShowStatus();
    cout << "Max number of battles: " <<  max_number_of_battles << endl;
    cout << "Health cost per battle: " << health_cost_per_battle << endl;
    cout << "PokeDollar per battle: " << PokeDollar_cost_per_battle << endl;
    cout << "Experience per battle: " << experience_per_battle << endl;
    cout << num_battle_remaining << " battle(s) are remaining for this PokemonGym" << endl;
    return;
}