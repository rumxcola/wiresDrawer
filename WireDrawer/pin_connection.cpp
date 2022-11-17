#include "pin_connection.h"



PinConnection::PinConnection(PinConnectionsStore &store_, int connId_):pinConnectionsStore__(store_),connId__(connId_){

}


void PinConnection::addOnePin(MutablePinConnectionsStore & connsStore_, std::shared_ptr<PinConnection> conn_){
    std::shared_ptr<Pin> pin=nullptr;
    auto &map=((PinConnectionsStore&)connsStore_).getPins();
    std::vector<std::shared_ptr<Pin>> mapCopy;
    mapCopy.reserve(map.size());

    std::transform(map.begin(),map.end(),
                   std::back_inserter(mapCopy),[]( const std::pair<int,std::shared_ptr<Pin>>&x){return x.second;});
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(mapCopy.begin(),mapCopy.end(),generator);
    for(auto crntpin:mapCopy)
        if(connsStore_.getPinsConnected().find(crntpin)==connsStore_.getPinsConnected().end()){
            pin=crntpin;
            break;
        }
    if(pin==nullptr)
        return;
    conn_->pins__.insert(pin);
    (pin->isLeft()?conn_->leftPins__:conn_->rightPins__).insert(pin);
    connsStore_.createAssociation(pin,conn_);
}

std::set<std::shared_ptr<Pin>>& PinConnection::getPins(){return pins__;}
void PinConnection::genNextConnection(MutablePinConnectionsStore& pinConnectionsStore_, std::shared_ptr<PinConnection> conn_, int pinsCount_)
{
    pinsCount_=Randomizer::getRandom(2,pinsCount_);        
    for(int i=0;i<pinsCount_;++i)
        PinConnection::addOnePin(pinConnectionsStore_,conn_);
}

std::ostream& operator<<(std::ostream & o_, const PinConnection& conn_){
    o_<<"conn "<<conn_.connId__<<"{";
    for(auto it=conn_.pins__.begin();it!=conn_.pins__.end();++it)
        o_<<(it==conn_.pins__.begin()?"":", ")<<(**it);
    o_<<"}\n";
    for(int side=0;side<2;++side){
        o_<<"\t"<<(side?"l":"r")<<"{";
        for(auto lvl:conn_.pinConnectionsStore__.getOccpuiedLevels(side))
            if(&(*lvl.second)==&conn_)
                o_<<lvl.first<<" ";
        o_<<"}";
    }
    return o_;
}
int PinConnection::getConnId()const { return connId__;}
std::shared_ptr<Pin> PinConnection::getLowest(const std::set<std::shared_ptr<Pin> > &pins_){
    std::shared_ptr<Pin>lowestPin=pins_.empty()?nullptr:*pins_.begin();
    for(auto crntPin:pins_)
        if(pinConnectionsStore__.getAbsPinLevel(crntPin)> pinConnectionsStore__.getAbsPinLevel(lowestPin))
                lowestPin=crntPin;
    return lowestPin;
}
std::shared_ptr<Pin> PinConnection::getHighest(const std::set<std::shared_ptr<Pin>> &pins_){
    auto highestPin=pins_.empty()?nullptr:*pins_.begin();
    for(auto crntPin:pins_)        
        if(pinConnectionsStore__.getAbsPinLevel(crntPin)< pinConnectionsStore__.getAbsPinLevel(highestPin))
            highestPin=crntPin;
    return highestPin;
}

std::shared_ptr<Pin> PinConnection::getLowest(bool isLeft_){return getLowest(isLeft_? leftPins__:rightPins__);}
std::shared_ptr<Pin> PinConnection::getLowest(){return getLowest(pins__);}
std::shared_ptr<Pin> PinConnection::getHighest(bool isLeft_){return getHighest(isLeft_? leftPins__:rightPins__);}
std::shared_ptr<Pin> PinConnection::getHighest(){return getHighest(pins__);}
std::set<std::shared_ptr<Pin> > &PinConnection::getPins(bool isLeft){return isLeft?leftPins__:rightPins__;}

