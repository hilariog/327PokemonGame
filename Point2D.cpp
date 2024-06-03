#include "Point2D.h"

//constructors

Point2D::Point2D(){
    x = 0.0;
    y = 0.0;
}

Point2D::Point2D(double inx, double iny){
    x = inx;
    y = iny;
}

//nonmember functions and operators

double GetDistanceBetween(Point2D p1, Point2D p2){
    return (sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2)));
}

Vector2D Norm(Vector2D vec){//returns a vectors unit vec
    double mag = GetDistanceBetween(Point2D(),Point2D(vec.x,vec.y));//length of a vector
    return Vector2D(vec.x/mag,vec.y/mag);
}

ostream& operator<<(ostream& os, const Point2D& pt){
    os << '(' << pt.x << ',' << pt.y << ')';
    return os;
}

Point2D operator+(Point2D pt, Vector2D vc){
    return Point2D(pt.x + vc.x, pt.y + vc.y);
}

Vector2D operator-(Point2D p1, Point2D p2){
    return Vector2D(p1.x - p2.x, p1.y - p2.y);
}

