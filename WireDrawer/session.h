#ifndef SESSION_H
#define SESSION_H
#include "pin_connection.h"
#include <QPoint>
class Session : PinConnectionsStore
{
public:
    Session(int totalCables_, int oneCablePinsMax_, double connectedPercents_, int pinWidh_=PIN_WIDTH, int pinHeight_=PIN_HEIGHT, int cableGap_=CABLE_GAP);
    ~Session();

    QColor getColor(PinConnection* conn_) const{
        return colors__[(conn_->getConnId()+1)%(colors__.size()-1)];
    }
    int getTotalPinsCount()const{return pins__.size();}
    int getNewPinUniqId() const {return getTotalPinsCount();};
    void addPin(Pin *pin_){pins__.insert(std::make_pair(pin_->getId(),pin_));}
    Pin* getPin(int uniqId_){
        auto pin=pins__.find(uniqId_);
        return pin==pins__.end()?nullptr:pin->second;
    }
    void onPinRemoved(int uniqId_){pins__.erase(uniqId_);};

    int getPinLen(PinConnection* conn_);
    int getPinWidh()const{return pinWidh__;}
    int getPinHeight() const{return pinHeight__;}
    int getCableGap() const {return cableGap__;}
    QPoint getPinPoint(Pin* pin_);
    QPoint getPinMiddlePoint(Pin* pin_);
    int getPinsUsed();
    int getBusX(PinConnection* conn_, bool isLeft_);
    int getXRightBorder();
    int getYMax();
    int getXMax();
    int getXCenter();
    int getAbsPinLevel(Pin *pin_) const ;
    bool hasOccupiedWithLessId(int level, PinConnection* conn_ );
    int getPinY(Pin *pin_);
    int getPinX(Pin* pin_);
    int getAbsLevelY(int level){return level*pinHeight__+pinWidh__/2;}
    void deinit();
    bool init(int totalCables_, int oneCablePinsMax_, double connectedPinsPercent_);

    std::map<int /*pinLevel*/,PinConnection*>& getOccpuiedLevels(bool isLeft_);
    std::map<int /*connId*/,PinConnection*>& getConnections();
    std::map<Pin*, PinConnection*>& getPinsConnected();
    std::map<Pin*,Cable*>& getPinCablesMap();
    std::map<int/*level*/, Cable*>& getCables(bool isLeftSide_);
    std::map<int/*absPinLevel*/,Pin*>& getLeveledPins(bool isLeft_);


private:
    void setColors();
    static const int PIN_HEIGHT=20;
    static const int PIN_WIDTH=PIN_HEIGHT;
    static const int CABLE_GAP=PIN_HEIGHT;
    int pinWidh__,pinHeight__,cableGap__;
    std::vector<QColor> colors__;
    std::set<Cable*> cables__;
    std::map<int /*pinLevel*/,PinConnection*> occupiedLevelsLeftPins__,occupiedLevelsRightPins__;
    std::map<int /*connId*/,PinConnection*> connections__;
    std::map<Pin*, PinConnection*> pinsConnected__;
    std::map<Pin*,Cable*>pinCablesMap__;
    std::map<int/*level*/, Cable*> leftCables__,rightCables__;
    std::map<int/*absPinLevel*/,Pin*> absLeftPins__, absRightPins__;
    std::map<int,Pin*> pins__;
    friend std::ostream & operator <<(std::ostream &o, const Session&);
};

#endif // SESSION_H
