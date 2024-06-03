#include "GameCommand.h"

void DoMoveCommand(Model & model, int trainer_id, Point2D p1){
    model.GetTrainerPtr(trainer_id)->StartMoving(p1);
    cout << "Moving " << model.GetTrainerPtr(trainer_id)->getName() << " to " << p1 << endl;
    
    return;
}

void DoMoveToCenterCommand(Model & model, int trainer_id, int center_id){
    model.GetTrainerPtr(trainer_id)->StartMovingToCenter(model.GetPokemonCenterPtr(center_id));
    cout << "Moving " << model.GetTrainerPtr(trainer_id)->getName() << " to Pokemon Center " << model.GetPokemonCenterPtr(center_id)->GetId() << endl;
    
    return;
}

void DoMoveToGymCommand(Model & model, int trainer_id, int gym_id){
    model.GetTrainerPtr(trainer_id)->StartMovingToGym(model.GetPokemonGymPtr(gym_id));
    cout << "Moving " << model.GetTrainerPtr(trainer_id)->getName() << " to Pokemon Gym " << model.GetPokemonGymPtr(gym_id)->GetId() << endl;

    return;
}

void DoStopCommand(Model & model, int trainer_id){
    model.GetTrainerPtr(trainer_id)->Stop();
    cout << "Stopping " << model.GetTrainerPtr(trainer_id)->getName() << endl;
    
    return;
}

void DoBattleCommand(Model & model, int trainer_id, unsigned int battles){
    model.GetTrainerPtr(trainer_id)->StartBattling(battles);
    cout << model.GetTrainerPtr(trainer_id)->getName() << " is battling! " << endl;
    
    return;
}

void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed){
    model.GetTrainerPtr(trainer_id)->StartRecoveringHealth(potions_needed);
    cout << "Recovering " << model.GetTrainerPtr(trainer_id)->getName() << "'s Pokemon's health" << endl;
    
    return;
}

void DoAdvanceCommand(Model& model, View& view){
    cout << "Advancing one tick" << endl;
    model.Update();
    return;
}

void DoRunCommand(Model& model, View& view){
    cout << "Advancing to next event" << endl;
    while(model.Update() == false){
        
    }
    return;
}