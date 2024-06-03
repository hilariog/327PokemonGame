#include "GameCommand.h"
#include "Input_Handling.h"

int main(){
    Model CeruleanCity;
    View gooey;
    char command;
    int trainer;

    while(command != 'q'){
        
        //CeruleanCity.Update();
        gooey.Clear();
        CeruleanCity.Display(gooey);
        CeruleanCity.ShowStatus();
        gooey.Draw();
        cout << "Enter Command: ";
        if(!(cin >> command)){
            throw Invalid_Input("Was Expecting a character");
        }else{
            try{
                switch (command){
                    case 'n':
                        int ID;
                        double x,y;
                        char type;

                        cout << "New object type: ";
                        if(!(cin >> type)){
                            throw Invalid_Input("Was expecting a char");
                            break;
                        }
                        cout << "ID: ";
                        if(!(cin >> ID)){
                            throw Invalid_Input("Was expecting an Integer");
                            break;
                        }
                        if(ID > 9 || ID < 0){
                            throw Invalid_Input("Sorry but the game only supports ID between 0 and 9");
                            break;
                        }
                        cout << "X: ";
                        if(!(cin >> x)){
                            throw Invalid_Input("Was expecting a double");
                            break;
                        }
                        cout << "Y: " << endl;
                        if(!(cin >> y)){
                            throw Invalid_Input("Was expecting a double");
                            break;
                        }
                        if(x > 20 || x < 0 || y > 20 || y < 0){
                            throw Invalid_Input("Please enter coordinates within the grid");
                            break;
                        }
                        CeruleanCity.NewCommand(type,ID,x,y);
                        break;
                    case 'm':
                        double X, Y;
                    
                        cout << "You've chosen to move. Please enter: \n Trainer Id: ";
                        if(!(cin >> trainer)){
                            throw Invalid_Input("Was expecting an integer");
                            break;
                        }
                        if(CeruleanCity.GetTrainerPtr(trainer) == nullptr){
                            throw Invalid_Input("That wasn't a valid trainer ID");
                            break;
                        }

                        cout << " X: ";
                        if(!(cin >> X)){
                            throw Invalid_Input("Was expecting a double");
                            break;
                        }
                        cout << " Y: ";
                        if(!(cin >> Y)){
                            throw Invalid_Input("Was expecting a double");
                            break;
                        }  
                        DoMoveCommand(CeruleanCity, trainer, Point2D(x,y));
                        break;
                    case 'c':
                        int center;

                        cout << "You've chosen to move to a Center. Please enter: \n Trainer Id: ";
                        if(!(cin >> trainer)){
                            throw Invalid_Input("Was expecting an integer");
                            break;
                        }
                        if(CeruleanCity.GetTrainerPtr(trainer) == nullptr){
                            throw Invalid_Input("That wasn't a valid trainer ID");
                            break;
                        }
                        cout << " Center ID: ";
                        if(!(cin >> center)){
                            throw Invalid_Input("Was expecting an integer");
                            break;
                        }
                        if(CeruleanCity.GetPokemonCenterPtr(center) == nullptr){
                            throw Invalid_Input("That wasn't a valid Center ID");
                            break;
                        }
                        DoMoveToCenterCommand(CeruleanCity, trainer, center);
                        break;
                    case 'g':
                        int gym;

                        cout << "You've chosen to move to a Gym. Please enter: \n Trainer Id: ";
                        if(!(cin >> trainer)){
                            throw Invalid_Input("Was expecting an integer");
                            break;
                        }
                        if(CeruleanCity.GetTrainerPtr(trainer) == nullptr){
                            throw Invalid_Input("That wasn't a valid trainer ID");
                            break;
                        }
                        cout << " Gym ID: ";
                        if(!(cin >> gym)){
                            throw Invalid_Input("Was expecting an integer");
                            break;
                        }
                        if(CeruleanCity.GetPokemonGymPtr(gym) == nullptr){
                            throw Invalid_Input("That wasn't a valid Gym ID");
                            break;
                        }
                        DoMoveToGymCommand(CeruleanCity, trainer, gym);
                        break;
                    case 's':
                        cout << "You've chosen to stop. Please enter: \n Trainer Id: ";
                        if(!(cin >> trainer)){
                            throw Invalid_Input("Was expecting an integer");
                            break;
                        }
                        if(CeruleanCity.GetTrainerPtr(trainer) == nullptr){
                            throw Invalid_Input("That wasn't a valid trainer ID");
                            break;
                        }
                        DoStopCommand(CeruleanCity, trainer);
                        break;
                    case 'p':
                        unsigned int potion;

                        cout << "You've chosen to Recover Healh. Please enter: \n Trainer Id: ";
                        if(!(cin >> trainer)){
                            throw Invalid_Input("Was expecting an integer");
                            break;
                        }
                        if(CeruleanCity.GetTrainerPtr(trainer) == nullptr){
                            throw Invalid_Input("That wasn't a valid trainer ID");
                            break;
                        }
                        cout << " Potion amount: ";
                        if(!(cin >> potion)){
                            throw Invalid_Input("Was expecting an unsigned integer");
                            break;
                        }
                        DoRecoverInCenterCommand(CeruleanCity, trainer, potion);
                        break;
                    case 'b':
                        unsigned int battle;

                        cout << "You've chosen to Battle. Please enter: \n Trainer Id: ";
                        if(!(cin >> trainer)){
                            throw Invalid_Input("Was expecting an integer");
                            break;
                        }
                        if(CeruleanCity.GetTrainerPtr(trainer) == nullptr){
                            throw Invalid_Input("That wasn't a valid trainer ID");
                            break;
                        }
                        cout << " Battle amount: ";
                        if(!(cin >> battle)){
                            throw Invalid_Input("Was expecting an unsigned integer");
                            break;
                        }
                        DoBattleCommand(CeruleanCity, trainer, battle);
                        break;
                    case 'a':
                        cout << "Advancing one tick" << endl;
                        DoAdvanceCommand(CeruleanCity, gooey);
                        break;
                    case 'r':
                        cout << "Running . . ." << endl;
                        DoRunCommand(CeruleanCity,gooey);
                        break;
                    case 'q':
                        cout << "Quitting" << endl;
                        break;
                    default:
                        throw Invalid_Input("Was expecting a valid command");
                    break;
                }
            }
            catch (Invalid_Input& except){
            cout << "Invalid input - " << except.msg_ptr << endl;
            }
        }
    }
    CeruleanCity.~Model();
    return 0;
}