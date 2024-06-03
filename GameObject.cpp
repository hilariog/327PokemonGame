#include "GameObject.h"

//Constructor

GameObject::GameObject(char code){
    display_code = code;
    id_num = 1;
    state = '0';
    cout << "GameObject Constructed" << endl;
}

GameObject::GameObject(Point2D loc, int id, char code){
    display_code = code;
    id_num = id;
    state = '0';
    location = loc;
    cout << "GameObject Constructed" << endl;
}

//Destructor

GameObject::~GameObject(){
    cout << "GameObject Destroyed" << endl;
}

//Members

Point2D GameObject::GetLocation(){
    return location;
}

int GameObject::GetId(){
    return id_num;
}

char GameObject::GetState(){
    return state;
}

void GameObject::ShowStatus(){
    cout << display_code << id_num << " at " << location << endl;
}

void GameObject::DrawSelf(char * ptr){
    ptr[0] = display_code;
    ptr[1] = '0' + id_num;
    return;
}