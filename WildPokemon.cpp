#include "WildPokemon.h"
#include "Trainer.h"

//Constructor

WildPokemon::WildPokemon(string name, double attack, double health, bool variant, int id, Point2D in_loc):GameObject(in_loc, id, 'W'){
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    state = IN_ENVIRONMENT;
    in_combat = false;
    cout << "Wild Pokemon Constructed" << endl;
}

void WildPokemon::follow(Trainer* T){
    current_trainer = T;
    state = FOLLOWING;
    Point2D trainerLoc = T->GetLocation();
    Vector2D DistanceToTrainer = ((trainerLoc) - location);//gives vector with dist to trainer
    double mag = GetDistanceBetween(Point2D(),Point2D(DistanceToTrainer.x,DistanceToTrainer.y));//length of a vector
    location = location + ((DistanceToTrainer/mag) * (1.15 * T->getSpeed()));//the wild pokemon moves at 1.25 times the speed of the trainer in the directioon of the trainer every update step

    if(GetDistanceBetween(location,(trainerLoc)) <= 1){//when pokemon catches trainer
        cout << name << " caught trainer!" << endl;
        location = trainerLoc;
        in_combat = true;
        state = IN_TRAINER;
        T->wildEngaged(this);
    }
    return;
}

bool WildPokemon::get_variant(){
    return variant;
}

double WildPokemon::get_attack(){
    return attack;
}

double WildPokemon::get_health(){
    return health;
}

bool WildPokemon::get_in_combat(){
    return in_combat;
}

bool WildPokemon::Update(){
    bool retval = false;
    srand(time(NULL));

    switch(state){
        case IN_ENVIRONMENT:
            break;
        case FOLLOWING:
            cout<<"following"<<endl;
            if(in_combat){
                retval = true;
            }
            break;
        case IN_TRAINER:
            cout << "intrainer state" << endl;
            if(!(current_trainer->HasFainted())){
                health -= rand() % 1 + 2;//decreases pokemon's health by random number between 1 and 2.
            }else{
                state = IN_ENVIRONMENT;
                in_combat = false;
            }
            if(!IsAlive()){
                cout << "wild pokemon died" << endl;
                health = 0;
                attack = 0;
                state = DEAD;
                display_code = 'w';
                in_combat = false;
            }
            retval = true;
            break;
        case DEAD:
            retval = false;
            break;
        default:
        break;
    }

    return retval;
}

void WildPokemon::ShowStatus(){
    cout << name << " Status: " << endl;
    GameObject::ShowStatus();
    cout << "State: " << state << endl;
    cout << "Health: " << health << endl;
    cout << "Attack: " << attack << endl;
}

bool WildPokemon::ShouldBeVisible(){
    if(health > 0){
        return true;
    }else{
        return false;
    }
}

bool WildPokemon::IsAlive(){
    if(health <= 0){
        return 0;
    }else{
        return 1;
    }
}