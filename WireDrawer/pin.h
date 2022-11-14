#ifndef PIN_H
#define PIN_H
#include <map>
#include <string>
#include <iostream>
class Pin;
class PinsStore{
public:
    virtual ~PinsStore(){};
    virtual int getTotalPinsCount()const =0;
    virtual int getNewPinUniqId() const =0;
    virtual void addPin(Pin *pin_)=0;
    virtual Pin* getPin(int uniqId_)=0;
    virtual void onPinRemoved(int uniqId_)=0;
};

class Pin{
public:
    Pin(PinsStore &pinsStore_, int cabId_,int numInCable_, bool isLeft_);
    int getNumInCable() const {return numInCable__;}
    int getId()const{return uniqId__;}
    bool isLeft() const {return isLeft__;}
    ~Pin();
    bool operator<(const Pin& r_) const{ return uniqId__<r_.uniqId__; }
    friend std::ostream& operator<< (std::ostream& o, const Pin& fred);
private:
    PinsStore &pinsStore__;
    int cabId__;
    int numInCable__;
    int uniqId__;
    bool isLeft__;
};

#endif // PIN_H
