#include "pin.h"
Pin::Pin(PinsStore &pinsStore_, int cabId_, int numInCable_, bool isLeft_):
            pinsStore__(pinsStore_), cabId__(cabId_),
            numInCable__(numInCable_),isLeft__(isLeft_){
    uniqId__=pinsStore__.getNewPinUniqId();
    pinsStore__.addPin(this);
}
Pin::~Pin(){
    pinsStore__.onPinRemoved(uniqId__);
}



std::ostream& operator<< (std::ostream& o_, const Pin& pin_)
{
    return o_<<"["<<(pin_.isLeft__?"l":"r")
            <<pin_.cabId__<<"]"<<pin_.numInCable__<<":"<<pin_.uniqId__;
}
