#include "Trainer.h"

// Constructors

Trainer::Trainer():GameObject('T'){
    speed = 5;
    state = STOPPED;
    is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    name = "GoofyDefaultBozo";
    current_center = NULL;
    current_gym = NULL;
    destination = Point2D(0.0, 0.0);
    cout << "Trainer default constructed " << endl;
}

Trainer::Trainer(char code):GameObject(code){
    speed = 5;
    state = STOPPED;
     is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    name = "GoofyDefaultBozo";
    current_center = NULL;
    current_gym = NULL;
    destination = Point2D(0.0, 0.0);
    cout << "Trainer constructed " << endl;
    
}

Trainer::Trainer(string inName, int id, char code, unsigned int inSpeed, Point2D loc):GameObject(loc, id, code){
    speed = inSpeed;
    name = inName;
    state = STOPPED;
    is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = NULL;
    current_gym = NULL;
    destination = Point2D(0.0, 0.0);
    cout << "Trainer constructed " << endl;
}

//Destructor

Trainer::~Trainer(){
    cout << "Trainer destroyed" << endl;
}

// Member Functions

void Trainer::StartMoving(Point2D dest){
    SetupDestination(dest);
    if(state == FAINTED){
        cout << display_code << id_num << "My pokemon have fainted. I may move but you cannot see me." << endl;
    }
    if(dest.x == location.x && dest.y == location.y){
        cout << display_code << id_num << "I'm already there. See?" << endl;
        if(state != FAINTED){//i guess if they're fainted and no longer moving theyll stay being fainted.
            state = STOPPED;
        }
    }else{
        cout << display_code << id_num << "On my way." << endl;
        state = MOVING;
    }
}

void Trainer::StartMovingToGym(PokemonGym* destGym){
    SetupDestination(destGym -> GetLocation());
    current_gym = destGym;
    if(HasFainted()){
        cout << display_code << id_num << ": My Pokemon fainted so I can't move to gym." << endl;
    }else if(destGym -> GetLocation().x == location.x && destGym -> GetLocation().y == location.y){
        cout << display_code << id_num << ": I'm already at the Pokemon Gym!" << endl;
        state = IN_GYM;
    }else{
        cout << display_code << id_num << ": On my way to gym " << destGym -> GetId() << endl;
        state = MOVING_TO_GYM;
    }
}

void Trainer::StartMovingToCenter(PokemonCenter *destCent){
    SetupDestination(destCent -> GetLocation());
    current_center = destCent;
    if(HasFainted()){
        cout << display_code << id_num << ": My Pokemon have fainted, I should have gone to the Center." << endl;
    }
    if(destCent -> GetLocation().x == location.x && destCent -> GetLocation().y == location.y){
        cout << display_code << id_num << ": I'm already at the Pokemon Center!" << endl;
        state = AT_CENTER;
    }else{
        cout << display_code << id_num << ": On my way to Center " << destCent -> GetId() << endl;
        state = MOVING_TO_CENTER;
    }
}

void Trainer::StartBattling(unsigned int num_battles){
    if(state == IN_GYM){
        if(PokeDollars < (current_gym -> GetPokeDollarCost(num_battles))){
            cout << display_code << id_num << ": Not Enough Money for Battles." << endl;
        }else if(current_gym -> GetNumBattlesRemaining() == 0){
            cout << display_code << id_num << ": Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
        }else{
            state = BATTLING_IN_GYM;
            battles_to_buy = (current_gym -> TrainPokemon(num_battles))/(current_gym ->GetExperiencePerBattle());
            cout << display_code << id_num << ": Started to battle at the PokemonGym " << current_gym -> GetId() << " with " << num_battles << " battles." << endl;
        }
    }else if(state == FAINTED){
        cout << display_code << id_num << ":  My Pokemon have fainted so no more battles for me..." << endl;
    }else{
        cout << display_code << id_num << ": I can only battle in a PokemonGym!" << endl;
    }
}

void Trainer::StartRecoveringHealth(unsigned int numPot){
    if(state == AT_CENTER){
        if(PokeDollars < (current_center -> GetPokeDollarCost(numPot))){
            cout << display_code << id_num << ": Not Enough Money to recover health." << endl;
        }else if(current_center -> GetNumPotionRemaining() == 0){
            cout << display_code << id_num << ":  Cannot recover! No potion remaining in this Pokemon Center" << endl;
        }else{
            state = RECOVERING_HEALTH;
            potions_to_buy = current_center -> DistributePotion(numPot);
            cout << display_code << id_num << ": Started recovering " << numPot << " potions at Pokemon Center " << current_center -> GetId() << endl;
        }
    }else{
        cout << display_code << id_num << ": I can only battle in a PokemonGym!" << endl;
    }
}

void Trainer::Stop(){
    state = STOPPED;
    cout << display_code << id_num << ": Stopping..." << endl;
}

bool Trainer::HasFainted(){
    if(health == 0){
        return true;
    }else{
        return false;
    }
}

bool Trainer::ShouldBeVisible(){
    if(HasFainted()){
        return false;
    }else{
        return true;
    }
}

void Trainer::ShowStatus(){
    cout << name << " Status: " << endl;
    GameObject::ShowStatus();
    switch(state){
        case STOPPED:
            cout << " stopped" << endl;
            break;
        case MOVING:
            cout << " moving at the speed of " << speed << " to destination " << destination << " at each step of " << delta << ". " << endl;
            break;
        case FAINTED:
            cout << " fainted" << endl;
            break;
        case AT_CENTER:
            cout << " in Pokemon Center " << current_center -> GetId() << endl;
            break;
        case IN_GYM:
            cout << " in Pokemon Gym " << current_gym -> GetId() << endl;
            break;
        case MOVING_TO_CENTER:
            cout << " heading to Pokemon Center " << current_center -> GetId() << " at a speed of " << speed << " at each step of " << delta << ". " << endl;
            break;
        case MOVING_TO_GYM:
            cout << " heading to Pokemon Gym " << current_gym -> GetId() << " at a speed of " << speed << " at each step of " << delta << ". " << endl;
            break;
        case BATTLING_IN_GYM:
            cout << " battling in Pokemon Gym " << current_gym -> GetId() << endl;
            break;
        case RECOVERING_HEALTH:
            cout << " Recovering health in Pokemon Center " << current_center -> GetId() << endl;
            break;
        case SPONTANEOUS_COMBAT:
            cout << " Engaged with Wild Pokemon " << endl;
            break;
        default:
        break;
    }
    cout << "Health: " << health << endl;
    cout << "PokeDollars: " << PokeDollars << endl;
    cout << "Experience: " << experience << endl;
    return;
}

bool Trainer::Update(){
    bool retval;
    if(HasFainted()){
        cout << name << " has run out of health and can't move." << endl;
        state  = FAINTED;
        retval = 1;
    }
    
    switch(state){
        case STOPPED:
            retval = false;
            break;
        case MOVING:
            retval = UpdateLocation();
            cout << "retval" << retval <<endl;
            if(retval){
                state = STOPPED;
            }
            break;
        case FAINTED:
            retval = false;
            break;
        case AT_CENTER:
            retval = false;
            break;
        case IN_GYM:
            retval = false;
            break;
        case MOVING_TO_CENTER:
            retval = UpdateLocation();
            if(retval){
                state = AT_CENTER;
                is_at_center = true;
                current_center -> AddOneTrainer();
            }
            break;
        case MOVING_TO_GYM:
            retval = UpdateLocation();
            if(retval){
                state = IN_GYM;
                is_in_gym = true;
                current_gym -> AddOneTrainer();
            }
            break;
        case BATTLING_IN_GYM:
            experience += (current_gym -> GetExperiencePerBattle() * battles_to_buy);
            health -= current_gym -> GetHealthCost(battles_to_buy);
            PokeDollars -= current_gym -> GetPokeDollarCost(battles_to_buy);
            cout << "** " << name << " completed " << battles_to_buy << "battle(s)!" << endl;
            cout << "** " << name << " gained " << (battles_to_buy * current_gym -> GetExperiencePerBattle()) << " experience!" << endl;
            state = IN_GYM;
            retval = true;
            break;
        case RECOVERING_HEALTH:
            health += (potions_to_buy * 5);
            PokeDollars -= (current_center -> GetPokeDollarCost(potions_to_buy));
            break;
        case SPONTANEOUS_COMBAT:
            cout << "** " << name << " was caught by a wild pokemon with " << current_assailant->get_health() << " health and " << current_assailant->get_attack() << " attack." << endl;
            health -= (current_assailant->get_attack());
            if(!(current_assailant->IsAlive())){//resumes what they were doing if pokemon was killed
                cout << "I killed wild pokemon" << endl;
                experience += 5;
                PokeDollars += GetRandomAmountOfPokeDollars();
                state = STOPPED;
            }
            if(HasFainted()){
                cout << "A wild Pokemon has killed " << name << endl;
                state  = FAINTED;
            }

        default:
        break;
    }
    return retval;
}

string Trainer::getName(){
    return name;
}

double Trainer::getSpeed(){//added for follow
    return speed;
}

unsigned int Trainer::getHealth(){//added for follow
    return health;
}

void Trainer::wildEngaged(WildPokemon* wild){//changes trainer state and stores what it was doing before so it can resume
    interruptedState = state;
    state = SPONTANEOUS_COMBAT;
    current_assailant = wild;
    return;
}

//Protected members

bool Trainer::UpdateLocation(){
    if((fabs(destination.x - location.x) <= fabs(delta.x)) && (fabs(destination.y - location.y) <= fabs(delta.y))){
        location = destination;
        cout << "arrived" << endl;
        return true;
    }else{
        location = location + delta;
        health -= 1;
        PokeDollars += GetRandomAmountOfPokeDollars();
        cout << "moved" << endl;
        return false;
    }
}

void Trainer::SetupDestination(Point2D dest){
    if (current_center != NULL){
        if((GetDistanceBetween(location, current_center->GetLocation()) == 0) && (GetDistanceBetween(dest, current_center->GetLocation()) != 0)){
            current_center->RemoveOneTrainer();
        }
    }
    if(current_gym != NULL){
        if(GetDistanceBetween(location, current_gym -> GetLocation()) == 0 && GetDistanceBetween(dest, current_gym -> GetLocation()) != 0){
            current_gym->RemoveOneTrainer();
        }
    }
    destination = dest;
    delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
    return;
}

// Non members

double GetRandomAmountOfPokeDollars(){
    srand(time(0));
    return ((double)(rand()%201)/100.0);
}

