#include "Model.h"
#include "Input_Handling.h"

//Constructor

Model::Model(){
    time = 0;
    //Instantiate objects:
    Trainer* T1 = new Trainer("Ash", 1, 'T', 1, Point2D(5,1));
    Trainer* T2 = new Trainer("Misty", 2, 'T', 2, Point2D(10,1));
    PokemonCenter* C1 = new PokemonCenter(1, 1, 100, Point2D(1,20));
    PokemonCenter* C2 = new PokemonCenter(2, 2, 200, Point2D(10,20));
    PokemonGym* G1 = new PokemonGym(10, 1, 2, 3, 1, Point2D());
    PokemonGym* G2 = new PokemonGym(20, 5, 7.5, 4, 2, Point2D(5,5));
    WildPokemon* W1 = new WildPokemon("WildPokemon1", 5, 2, false, 1, Point2D(10,12));
    WildPokemon* W2 = new WildPokemon("WildPokemon2", 5, 2, false, 2, Point2D(15,5));

    object_ptrs.push_back(C1);
    object_ptrs.push_back(C2);
    object_ptrs.push_back(T1);
    object_ptrs.push_back(T2);
    object_ptrs.push_back(G1);
    object_ptrs.push_back(G2);
    object_ptrs.push_back(W1);
    object_ptrs.push_back(W2);
    active_ptrs.assign(object_ptrs.begin(),object_ptrs.end());

    center_ptrs.push_back(C1);
    center_ptrs.push_back(C2);
    trainer_ptrs.push_back(T1);
    trainer_ptrs.push_back(T2);
    gym_ptrs.push_back(G1);
    gym_ptrs.push_back(G2);
    wild_ptrs.push_back(W1);
    wild_ptrs.push_back(W2);

    // object_ptrs[0] = trainer_ptrs[0];
    // object_ptrs[1] = trainer_ptrs[1];
    // object_ptrs[2] = center_ptrs[0];
    // object_ptrs[3] = center_ptrs[1];
    // object_ptrs[4] = gym_ptrs[0];
    // object_ptrs[5] = gym_ptrs[1];
    // object_ptrs[6] = wild_ptrs[0];
    // object_ptrs[7] = wild_ptrs[1];
    // num_objects = 8;
    // num_trainers = 2;
    // num_gyms = 2;
    // num_centers = 2;
    // num_wilds = 2;
    cout << "Model Default Constructed" << endl;
}

//Destructor

Model::~Model(){
    for(list <GameObject*> :: iterator iter1 = object_ptrs.begin(); iter1 != object_ptrs.end(); iter1++)
    {
        delete *iter1;
    }
    // for(int i = 0; i < num_trainers; i++){
    //     delete trainer_ptrs[i];
    //     trainer_ptrs[i] = 0;
    // }
    // for(int i = 0; i < num_centers; i++){
    //     delete center_ptrs[i];
    //     center_ptrs[i] = 0;
    // }
    // for(int i = 0; i < num_gyms; i++){
    //     delete gym_ptrs[i];
    //     gym_ptrs[i] = 0;
    // }
    // for(int i = 0; i < num_wilds; i++){
    //     delete wild_ptrs[i];
    //     wild_ptrs[i] = 0;
    // }
    // for(int i = 0; i < 10; i++){
    //     object_ptrs[i] = 0;
    // }

    cout << "Model Destroyed" << endl;
}

// functions

Trainer* Model::GetTrainerPtr(int id){
    // for(int i = 0; i < num_trainers; i++){
    //     if(trainer_ptrs[i]->GetId() == id){
    //         cout << trainer_ptrs[i]->getName() << endl;
    //         return trainer_ptrs[i];
    //     }
    // }
    for (list <Trainer*> :: iterator iter1 = trainer_ptrs.begin(); iter1 != trainer_ptrs.end(); iter1++)
    {
        if ((*iter1)->GetId() == id){
            return *iter1;
        }    
    }
    return nullptr;
}

PokemonCenter* Model::GetPokemonCenterPtr(int id){
    // for(int i = 0; i < num_centers; i++){
    //     if(center_ptrs[i]->GetId() == id){
    //         return center_ptrs[i];
    //     }
    // }
    // return 0;
    for(list <PokemonCenter*> :: iterator iter1 =center_ptrs.begin(); iter1 != center_ptrs.end(); iter1++)
    {
        if((*iter1)->GetId() == id)
            return *iter1;
    }
    return nullptr;
}

PokemonGym* Model::GetPokemonGymPtr(int id){
    
    for(list <PokemonGym*> :: iterator iter1 = gym_ptrs.begin(); iter1 != gym_ptrs.end(); iter1++)
    {
        if((*iter1)->GetId() == id)
            return *iter1; 
    }
    return nullptr;
}

WildPokemon* Model::GetWildPointer(int id){
    
    for(list <WildPokemon*> :: iterator iter1 = wild_ptrs.begin(); iter1 != wild_ptrs.end(); iter1++)
    {
        if((*iter1)->GetId() == id)
            return *iter1; 
    }
    return nullptr;
}

bool Model::Update(){
    time++;
    int gymPassed = 0;
    int tFaint = 0;
    int retval = false;
    int i;
    for(list <PokemonGym*> :: iterator iter1 = gym_ptrs.begin(); iter1 != gym_ptrs.end(); iter1++)
    {
        if((*iter1)->Passed()){
            gymPassed++;
        }
    }

    if(gymPassed == i){
        cout << "GameOver: You win! All battles done! " << endl;
        exit(0);
    }

    for (list <Trainer*> :: iterator iter1 = trainer_ptrs.begin(); iter1 != trainer_ptrs.end(); iter1++)
    {
        if ((*iter1)->HasFainted()){
            tFaint++;
        }    
    }

    if(tFaint == i){
        cout << "GameOver: You Lose :( All trainers fainted. " << endl;
        exit(0);
    }

    for(list <WildPokemon*> :: iterator iter1 = wild_ptrs.begin(); iter1 != wild_ptrs.end(); iter1++){
        for(list <Trainer*> :: iterator iter2 = trainer_ptrs.begin(); iter2 != trainer_ptrs.end(); iter2++){
            if(GetDistanceBetween((*iter1)->GetLocation(),(*iter2)->GetLocation()) <= 5){//follows if trainer is close enough
                if(!(*iter1)->get_in_combat() && (*iter1)->IsAlive()){
                    (*iter1)->follow(*iter2);
                    cout << "in following range" << endl;
                }
            }
        }
    }

    for(list <GameObject*> :: iterator iter = active_ptrs.begin(); iter != active_ptrs.end(); iter++)
    {
        if(!(*iter)->ShouldBeVisible())
        {
            active_ptrs.erase(iter);
            break;
        }
    }

    for(list <GameObject*> :: iterator iter = active_ptrs.begin(); iter != active_ptrs.end(); iter++){
        if((*iter)->Update()){
            cout<< "updated model" << endl;
            retval = true;
        }
    }
    
    return retval;
}

void Model::Display(View &view){
    cout << "Time: " << time << endl;
    for ( list<GameObject*> :: iterator iter1 = active_ptrs.begin(); iter1 != active_ptrs.end(); iter1++){
        view.Plot(*iter1);
    }
    return;
}

void Model::ShowStatus(){
    for(list<GameObject*> :: iterator iter1 = object_ptrs.begin(); iter1 != object_ptrs.end(); iter1++ )
    {
        (*iter1)->ShowStatus();
    }
    return;
}

void Model :: NewCommand(char type, int in_id, double x, double y)
{
    switch(type)
    {
        case 'c': 
        {
            for(list <PokemonCenter*> :: iterator iter1 = center_ptrs.begin(); iter1 != center_ptrs.end(); iter1++)
            {
                if(in_id == (*iter1)->GetId())
                throw Invalid_Input("Sorry but please enter a Unique Center ID");
            }
            PokemonCenter* C = new PokemonCenter(in_id, 100, 2, Point2D(x,y));
            object_ptrs.push_back(C);
            active_ptrs.push_back(C);
            center_ptrs.push_back(C);
            cout << "New PokemonCenter created" << endl;
            break;
        }

        case 'g':
        {    
            for(list <PokemonGym*> :: iterator iter1 = gym_ptrs.begin(); iter1 != gym_ptrs.end(); iter1++)
            {
                if(in_id == (*iter1)->GetId())
                throw Invalid_Input("Sorry but please enter a Unique PokemonGym ID");
            }
            PokemonGym* G = new PokemonGym(25,2,10,5,in_id,Point2D(x,y));
            object_ptrs.push_back(G);
            active_ptrs.push_back(G);
            gym_ptrs.push_back(G);
            cout << "New PokemonGym created" << endl;
            break;
        }

        case 't':
        {
            for(list <Trainer*> :: iterator iter1 = trainer_ptrs.begin(); iter1 != trainer_ptrs.end(); iter1++)
            {
                if(in_id == (*iter1)->GetId())
                throw Invalid_Input("Sorry but please enter a Unique Trainer ID");
            }
            Trainer* T = new Trainer("NewTrainer",in_id,'S',1,Point2D(x,y));
            object_ptrs.push_back(T);
            active_ptrs.push_back(T);
            trainer_ptrs.push_back(T);
            cout << "New Trainer created" << endl;
            break;
        } 
        case 'w':
        {
            for(list <WildPokemon*> :: iterator iter1 = wild_ptrs.begin(); iter1 != wild_ptrs.end(); iter1++)
            {
                if(in_id == (*iter1)->GetId())
                throw Invalid_Input("Sorry but please enter a Unique Trainer ID");
            }
            WildPokemon* W = new WildPokemon("NewWildPokemon",5,2,false,in_id,Point2D(x,y));
            object_ptrs.push_back(W);
            active_ptrs.push_back(W);
            wild_ptrs.push_back(W);
            cout << "New Wild Pokemon created" << endl;
            break;
        }

        default:
        throw Invalid_Input("Sorry Please enter valid object type");
    }
}
