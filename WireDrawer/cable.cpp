#include "cable.h"
Cable::Cable(CableStore &cablesStore_, bool isLeft):cablesStore__(cablesStore_), isLeft__(isLeft){
    auto &cables=cablesStore__.getCables(isLeft);
    level__=(cables.size());
    cables.insert(std::make_pair(cables.size(),this));

}
Cable::~Cable(){
    for(auto pin:pins__){        
        cablesStore__.getPinCablesMap().erase(pin.second);
        for(int isLeft=0;isLeft<2;++isLeft){            
            std::map<int/*absPinLeve*/,Pin*>absPinsToRemove;
            auto &absPins=cablesStore__.getLeveledPins(isLeft__);
            for(auto sidedPin:absPins)
                absPinsToRemove.insert(sidedPin);
            for(auto sidedPin:absPinsToRemove)
                absPins.erase(sidedPin.first);
        }
        delete pin.second;
    }
    pins__.clear();

    cablesStore__.getCables(isLeft__).erase(level__);
}
void Cable::addPin(){
    Pin* pin=new Pin(cablesStore__, level__, pins__.size(),isLeft__);
    pins__.insert(std::make_pair(pin->getNumInCable(),pin));
    cablesStore__.getPinCablesMap().insert(std::make_pair(pin,this));
    int absPinLevel=cablesStore__.getAbsPinLevel(pin);
    cablesStore__.getLeveledPins(isLeft__).insert(std::make_pair(absPinLevel,pin));

}






std::ostream& operator <<(std::ostream &o_, const Cable& cable_){
        o_<< ((cable_.isLeft__)?"left":"right")<<" cable "<<cable_.level__<< "{";
        for(auto pin:cable_.pins__){
            if(pin.first!=0)
                o_<<", ";
            o_<<*pin.second;
        }
        o_<<"}";
        return o_;
}

