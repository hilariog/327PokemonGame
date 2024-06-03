#include "Building.h"

//constructors

Building::Building():GameObject('B'){
    trainer_count = 0;
    cout << "Building Default Constructed" << endl;
}

Building::Building(char code, int id, Point2D loc):GameObject(loc, id, code){
    trainer_count = 0;
    cout << "Building Constructed" << endl;
}

//destructor

Building::~Building(){
    cout << "Building Destroyed" << endl;
}

//members

void Building::AddOneTrainer(){
    trainer_count++;
    return;
}

void Building::RemoveOneTrainer(){
    if(trainer_count != 0){
        trainer_count--;
    }
    return;
}

void Building::ShowStatus(){
    cout << display_code << id_num << " at " << location << endl;
    if(trainer_count == 1){
        cout << trainer_count << " trainer is in this building." << endl;
    }else{
        cout << trainer_count << " trainers are in this building." << endl;
    }
    return;
}

bool Building::ShouldBeVisible(){
    return 1;
}