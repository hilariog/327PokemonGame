#include "View.h"

//Constructor

View::View(){
    size = 11;
    scale = 2;
}

//Public members

void View::Clear(){
    for(int i = 0; i < view_maxsize; i++){
        for (int j = 0; j < view_maxsize; j++){
            grid[i][j][0] = '.';
            grid[i][j][1] = ' ';
        }
    }
    return;
}

void View::Plot(GameObject * ptr){
    int i, j;
    if(GetSubscripts(i,j,ptr -> GetLocation())){
        if(grid[i][j][0] != '.'){
            grid[i][j][0] = '*';
            grid[i][j][1] = ' ';
        }else{
            ptr->DrawSelf(grid[i][j]);
        }
    }
}

void View::Draw()
{
    for (int j = size-1; j >= -1; j--){
        for (int i = -1; i <= size-1; i++){  //grid axis
            if (i == -1 && j%2 == 0){
                cout << j*2;
                if (j/5 == 0){
                    cout << " ";
                }
            }else if (i == -1 && j%2 != 0){
                cout << "  ";
            }else if (j == -1 && i%2 == 0){
                cout << i*2;
                if (i/5 == 0){
                    cout << " ";
                }
                cout << "  ";
            }
            if (i >= 0 && j >=0){//draw objects
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
    return;
}

//Private Members

bool View::GetSubscripts(int &outX, int &outY, Point2D location){
    outX = (location.x - origin.x)/scale;
    outY = (location.y - origin.y)/scale;
    if((outX >= 0 && outX <= size)&&(outY >= 0 && outY <= size)){
        return true;
    }else{
        cout << "An object is outside the display.";
        return false;
    }
}