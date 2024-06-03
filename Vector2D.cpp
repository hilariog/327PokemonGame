#include "Vector2D.h"

Vector2D::Vector2D(){
    x = 0.0;
    y = 0.0;
}

Vector2D::Vector2D(double inx, double iny){
    x = inx;
    y = iny;
}

ostream& operator<<(ostream& os, const Vector2D& v){
    os << '<' << v.x << ',' << v.y << '>';
    return os;
}

Vector2D operator*(Vector2D v, double d){
    return Vector2D(v.x * d, v.y * d);
}

Vector2D operator/(Vector2D v, double d){
    if(d == 0){
        return v;
    }else{
        return Vector2D(v.x / d, v.y / d);
    }
}