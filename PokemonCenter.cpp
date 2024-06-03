#include "PokemonCenter.h"


//Constructors

PokemonCenter::PokemonCenter():Building('C', 1, Point2D()){
   potion_capacity = 100;
   num_potions_remaining = potion_capacity;
   pokedollar_cost_per_potion = 5;
   state = POTIONS_AVAILABLE;
   cout << "PokemonCenter default constructed" << endl;
}
PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc):Building('C', in_id, in_loc){
    potion_capacity = potion_cap;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = potion_cost;
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter constructed" << endl;
}

//Destructor

PokemonCenter::~PokemonCenter(){
    cout << "Center Destroyed" << endl;
}

//functions

bool PokemonCenter::HasPotions(){
    if(num_potions_remaining >= 1){
        return true;
    }else{
        return false;
    }
}

unsigned int PokemonCenter::GetNumPotionRemaining(){
    return num_potions_remaining;
}

bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget){
    if((potion * pokedollar_cost_per_potion) <= budget){
        return true;
    }else{
        return false;
    }
}

double PokemonCenter::GetPokeDollarCost(unsigned int potion){
    return (potion * pokedollar_cost_per_potion);
}

unsigned int PokemonCenter::DistributePotion(unsigned int need){
    if(need <= num_potions_remaining){
        num_potions_remaining -= need;
        return need;
    }else{
        unsigned int retval = num_potions_remaining;
        num_potions_remaining = 0;
        return retval;
    }
}

bool PokemonCenter::Update(){
    if(num_potions_remaining == 0){
        bool retval = true;
        if(state == NO_POTIONS_AVAILABLE){
            retval = false;
        }
        state = NO_POTIONS_AVAILABLE;
        display_code = 'c';
        cout << "Pokemon Center " << id_num << "has run out of potions." << endl;
        return retval;
    }else{
        return false;
    }
}

void PokemonCenter::ShowStatus(){
    cout << "PokemonCenter Status: " << endl;
    Building::ShowStatus();
    cout << "PokeDollar cost per potion: " << pokedollar_cost_per_potion << endl;
    if(num_potions_remaining == 1){
        cout << "has " << num_potions_remaining << " potion remaining." << endl;
    }else{
        cout << "has " << num_potions_remaining << " potions remaining." << endl;
    }
    return;
}