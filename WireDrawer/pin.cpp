#include "pin.h"
Pin::Pin(int uniqId_, /*PinsStore &pinsStore_,*/ int cabId_, int numInCable_, bool isLeft_):
            uniqId__(uniqId_), cabId__(cabId_),
            numInCable__(numInCable_),isLeft__(isLeft_){
}


std::ostream& operator<< (std::ostream& o_, const Pin& pin_)
{
    return o_<<"["<<(pin_.isLeft__?"l":"r")
            <<pin_.cabId__<<"]"<<pin_.numInCable__<<":"<<pin_.uniqId__;
}

std::ostream& operator<<   (std::ostream &o_, const std::shared_ptr<Pin>& wraper_){
        if(wraper_)
            o_<<*wraper_;
        else
            o_<<"nullptr";
        return o_;
    }
