#ifndef PIN_H
#define PIN_H
#include <map>
#include <string>
#include <iostream>
#include <memory>

class Pin{
public:
    Pin(int uniqId_, int cabId_,int numInCable_, bool isLeft_);
    int getNumInCable() const {return numInCable__;}
    int getId()const{return uniqId__;}
    bool isLeft() const {return isLeft__;}

    bool operator<(const Pin& r_) const{ return uniqId__<r_.uniqId__; }
    friend std::ostream& operator<< (std::ostream& o, const Pin& pin_);
    friend std::ostream& operator<< (std::ostream& o, const std::shared_ptr<Pin>&pin_);
private:
    int cabId__;
    int numInCable__;
    int uniqId__;
    bool isLeft__;
};



#endif // PIN_H
