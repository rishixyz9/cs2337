#ifndef DRIVER_H
#define DRIVER_H

#include <string>

class Driver
{
private:
    std::string name;
    double area; 
    static std::string compare;

public:
    Driver(){name="", area=0.0;}
    Driver(std::string myName){name=myName, area=0.0;}
    Driver(Driver&);

    std::string getName(){return name;}
    double getArea(){return area;}
    std::string getCompare(){return compare;}

    void setName(std::string newName){name=newName;}
    void setArea(double newArea){area=newArea;}
    void setCompare(std::string newCompare){compare=newCompare;}    

    bool operator< (const Driver&);
    bool operator> (const Driver&);

    friend std::ostream& operator<< (std::ostream&, const Driver&);

};

#endif