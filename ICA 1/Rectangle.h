#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>

class Rectangle
{
private:
    double length;
    double width;

public:
    Rectangle(){length=0.0;width=0.0;}
    Rectangle(double x, double y){length=x;width=y;}
    Rectangle(Rectangle&);

    double getLength(){return length;}
    double getWidth(){return width;}

    void setLength(double x){length = x;}
    void setWidth(double y){width = y;}

    Rectangle operator+ (const Rectangle&);
    Rectangle operator- (const Rectangle&);

    //pre ++i
    Rectangle& operator++ ();

    //post i++
    Rectangle operator++ (int);

    bool operator< (const Rectangle&);
    bool operator> (const Rectangle&);

    friend std::ostream& operator<< (std::ostream&, const Rectangle&);

};

#endif