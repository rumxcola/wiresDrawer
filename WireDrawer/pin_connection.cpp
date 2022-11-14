#include "pin_connection.h"



PinConnection::PinConnection(PinConnectionsStore &pinConnectionsStore_):
    pinConnectionsStore__(pinConnectionsStore_),
    connId__(pinConnectionsStore_.getConnections().size()){
    //color__=QColor(r,g,b);
    /*std::vector<QColor> colors;
    colors.push_back(QColorConstants::Black);
    colors.push_back(QColorConstants::Svg::deeppink);
    colors.push_back(QColorConstants::Svg::lightpink);
    colors.push_back(QColorConstants::Svg::olive);
    colors.push_back(QColorConstants::Magenta);
    colors.push_back(QColorConstants::Gray);
    colors.push_back(QColorConstants::Green);
    colors.push_back(QColorConstants::Svg::maroon);
    colors.push_back(QColorConstants::Svg::paleturquoise);
    colors.push_back(QColorConstants::Svg::lightblue);
    colors.push_back(QColorConstants::Svg::purple);
    colors.push_back(QColorConstants::Svg::mediumaquamarine);
    color__=colors[connId__];*/
}




void PinConnection::addOnePin(){
    Pin* pin=nullptr;
    do
        pin=pinConnectionsStore__.getPin(Randomizer::getRandom(0,pinConnectionsStore__.getTotalPinsCount()-1));
    while(pinConnectionsStore__.getPinsConnected().find(pin)!=pinConnectionsStore__.getPinsConnected().end());

    pinConnectionsStore__.getPinsConnected()[pin]=this;
    pins__.insert(pin);
    (pin->isLeft()?leftPins__:rightPins__).insert(pin);

    int absPinLevel=pinConnectionsStore__.getAbsPinLevel(pin);
    auto &occupiedLevels=pinConnectionsStore__.getOccpuiedLevels(pin->isLeft());
    occupiedLevels[absPinLevel]=this;
}
PinConnection::~PinConnection(){
    for(int side=0;side<2;++side){
        std::set<int /*pinLevel*/> levelsToRemove;
        for(auto occPin:pinConnectionsStore__.getOccpuiedLevels(side))
            if(this==occPin.second)
                levelsToRemove.insert(occPin.first);
        for(auto occPin:levelsToRemove)
            pinConnectionsStore__.getOccpuiedLevels(side).erase(occPin);
    }
    pins__.clear();
    leftPins__.clear();
    rightPins__.clear();
    pinConnectionsStore__.getConnections().erase(connId__);
}


std::set<Pin *>& PinConnection::getPins(){return pins__;}
PinConnection* PinConnection::genNextConnection(PinConnectionsStore& pinConnectionsStore_, int pinsCount_)
{
    pinsCount_=Randomizer::getRandom(2,pinsCount_);
    PinConnection* conn=new PinConnection(pinConnectionsStore_);
    pinConnectionsStore_.getConnections().insert(std::make_pair(conn->connId__,conn));
    for(int i=0;i<pinsCount_;++i)
        conn->addOnePin();
    return conn;
}

std::ostream& operator<<(std::ostream & o_, const PinConnection& conn_){
    o_<<"conn "<<conn_.connId__<<"{";
    for(auto it=conn_.pins__.begin();it!=conn_.pins__.end();++it)
        o_<<(it==conn_.pins__.begin()?"":", ")<<(**it);
    o_<<"}\n";
    for(int side=0;side<2;++side){
        o_<<"\t"<<(side?"l":"r")<<"{";
        for(auto lvl:conn_.pinConnectionsStore__.getOccpuiedLevels(side))
            if(lvl.second==&conn_)
                o_<<lvl.first<<" ";
        o_<<"}";
    }
    return o_;
}
int PinConnection::getConnId()const { return connId__;}
//QColor PinConnection::getColor() const{return color__;}
Pin* PinConnection::getLowest(const std::set<Pin *> &pins_){
    Pin *lowestPin=pins_.empty()?nullptr:*pins_.begin();
    for(auto crntPin:pins_)
        if(pinConnectionsStore__.getAbsPinLevel(crntPin)> pinConnectionsStore__.getAbsPinLevel(lowestPin))
                lowestPin=crntPin;
    return lowestPin;
}
Pin* PinConnection::getHighest(const std::set<Pin*> &pins_){
    auto highestPin=pins_.empty()?nullptr:*pins_.begin();
    for(auto crntPin:pins_)        
        if(pinConnectionsStore__.getAbsPinLevel(crntPin)< pinConnectionsStore__.getAbsPinLevel(highestPin))
            highestPin=crntPin;
    return highestPin;
}

Pin* PinConnection::getLowest(bool isLeft_){return getLowest(isLeft_? leftPins__:rightPins__);}
Pin* PinConnection::getLowest(){return getLowest(pins__);}
Pin* PinConnection::getHighest(bool isLeft_){return getHighest(isLeft_? leftPins__:rightPins__);}
Pin* PinConnection::getHighest(){return getHighest(pins__);}
std::set<Pin *>& PinConnection::getPins(bool isLeft){return isLeft?leftPins__:rightPins__;}

