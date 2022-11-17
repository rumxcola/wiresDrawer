#ifndef SESSION_H
#define SESSION_H
#include "pin_connection.h"
#include <QPoint>
class Session : public MutablePinConnectionsStore
{
public:
    Session(int totalCables_, int oneCablePinsMax_, double connectedPercents_, int pinWidh_=PIN_WIDTH, int pinHeight_=PIN_HEIGHT, int cableGap_=CABLE_GAP);
    ~Session();

    virtual void createAssociation(std::shared_ptr<Pin> pin_,std::shared_ptr<Cable> cable_){
        auto &sidedCables=cable_->isLeft()? leftCables__: rightCables__;
        pinCablesMap__[pin_]=cable_;
        pins__[pin_->getId()]=pin_;
        sidedCables[cable_->getCableLvl()]=cable_;
    }

    void recalcLevels(){
        auto pins=decltype(pins__)();
        std::transform(pins__.begin(),pins__.end(),std::inserter(pins,pins.begin()),[this](decltype(pins__)::value_type &x){
            return std::make_pair(getAbsPinLevel(x.second),x.second);
        });
        for(auto pin:pins__){
            auto &sidedPins= pin.second->isLeft()? absLeftPins__: absRightPins__;
            sidedPins[pin.second->getId()]= pin.second;
        }
        for(auto conn:pinsConnected__)
            for(auto pin:conn.second->getPins()){
                auto &occupiedLevels=pin->isLeft()?occupiedLevelsLeftPins__:occupiedLevelsRightPins__;
                occupiedLevels[getAbsPinLevel(pin)]=conn.second;
        }

    }

    void createAssociation(std::shared_ptr<Pin> pin_,std::shared_ptr<PinConnection> conn_){
        pinsConnected__[pin_]=conn_;
    }



    QColor getColor(std::shared_ptr<PinConnection>  conn_) const{
        return colors__[(conn_->getConnId()+1)%(colors__.size()-1)];
    }


    int getPinLen(std::shared_ptr<PinConnection> conn_);
    int getPinWidh()const{return pinWidh__;}
    int getPinHeight() const{return pinHeight__;}
    int getCableGap() const {return cableGap__;}
    QPoint getPinPoint(std::shared_ptr<Pin>  pin_);
    QPoint getPinMiddlePoint(std::shared_ptr<Pin> pin_);
    int getPinsUsed();
    int getBusX(std::shared_ptr<PinConnection> conn_, bool isLeft_);
    int getXRightBorder();
    int getYMax();
    int getXMax();
    int getXCenter();
    int getAbsPinLevel(std::shared_ptr<Pin> pin_){
        auto pinCable=pinCablesMap__.find(pin_)->second;
        auto const &cables=pinCable->isLeft()? leftCables__:rightCables__;
        int pinLevel=pin_->getNumInCable();
        for(auto cableIt:cables)
            if(cableIt.first<pinCable->getCableLvl())
                pinLevel+=cableIt.second->getPins().size()+1;
        return pinLevel;
    }
    int getAbsPinLevel(std::shared_ptr<Pin> pin_) const ;
    bool hasOccupiedWithLessId(int level, std::shared_ptr<PinConnection> conn_ );
    int getPinY(std::shared_ptr<Pin> pin_);
    int getPinX(std::shared_ptr<Pin> pin_);
    int getAbsLevelY(int level){return level*pinHeight__+pinWidh__/2;}
    void deinit();
    bool init(int totalCables_, int oneCablePinsMax_, double connectedPinsPercent_);


    std::map<int /*absPinLevel*/,std::shared_ptr<PinConnection>> const & getOccpuiedLevels(bool isLeft_) const {
        return isLeft_?occupiedLevelsLeftPins__:occupiedLevelsRightPins__;
    }
    std::map<int /*connId*/,std::shared_ptr<PinConnection>> const & getConnections() const {return connections__;}
    std::map<std::shared_ptr<Pin>, std::shared_ptr<PinConnection>>const & getPinsConnected(){return pinsConnected__;}
    std::map<std::shared_ptr<Pin>,std::shared_ptr<Cable>>& getPinCablesMap(){return pinCablesMap__;}
    std::map<int/*level*/, std::shared_ptr<Cable>>& getCables(bool isLeftSide_){return isLeftSide_?leftCables__:rightCables__;}
    std::map<int/*absPinLevel*/,Pin*>& getLeveledPins(bool isLeft_);

    std::map<int /*absPinLevel*/,std::shared_ptr<Pin>> const & getPins(){return pins__;}
    std::map<std::shared_ptr<Pin>, std::shared_ptr<PinConnection>>const & getPinsConnected() const{return pinsConnected__;}
private:
    void setColors();
    static const int PIN_HEIGHT=20;
    static const int PIN_WIDTH=PIN_HEIGHT;
    static const int CABLE_GAP=PIN_HEIGHT;
    int pinWidh__,pinHeight__,cableGap__;
    std::vector<QColor> colors__;
    std::set<std::shared_ptr<Cable>> cables__;
    std::map<int /*pinLevel*/,std::shared_ptr<PinConnection>> occupiedLevelsLeftPins__,occupiedLevelsRightPins__;
    std::map<int /*connId*/,std::shared_ptr<PinConnection>> connections__;
    std::map<std::shared_ptr<Pin>, std::shared_ptr<PinConnection>> pinsConnected__;
    std::map<std::shared_ptr<Pin>,std::shared_ptr<Cable>>pinCablesMap__;
    std::map<int/*level*/, std::shared_ptr<Cable>> leftCables__,rightCables__;
    std::map<int/*pinId*/,std::shared_ptr<Pin>> absLeftPins__, absRightPins__;
    std::map<int /*pinId*/,std::shared_ptr<Pin>> pins__;
    friend std::ostream & operator <<(std::ostream &o, const Session&);
};

#endif // SESSION_H
