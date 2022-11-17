#ifndef PINCONNECTION_H
#define PINCONNECTION_H
#include <QColor>
#include "cable.h"
#include "randomizer.h"

class PinConnection;
class PinConnectionsStore : public CableStore{
public:        
    virtual std::map<int /*absPinLevel*/,std::shared_ptr<PinConnection>> const & getOccpuiedLevels(bool isLeft_) const =0;
    virtual std::map<int /*connId*/,std::shared_ptr<PinConnection>> const & getConnections() const =0;
    virtual int getAbsPinLevel(std::shared_ptr<Pin>) const=0;
    virtual std::map<std::shared_ptr<Pin>, std::shared_ptr<PinConnection>>const & getPinsConnected() const=0;
};
class MutablePinConnectionsStore:public PinConnectionsStore, virtual public MutableCableStore{
public:
    virtual void createAssociation(std::shared_ptr<Pin>,std::shared_ptr<PinConnection>)=0;
};

class PinConnection{

    public :
    std::set<std::shared_ptr<Pin>>& getPins();
    static void genNextConnection(MutablePinConnectionsStore &pinConnectionsStore_,std::shared_ptr<PinConnection> conn_, int pinsCount_);
    int getConnId()const;
    //QColor getColor() const;
    std::shared_ptr<Pin> getLowest(const std::set<std::shared_ptr<Pin>>&pins_);
    std::shared_ptr<Pin> getHighest(const std::set<std::shared_ptr<Pin>> &pins_);

    std::shared_ptr<Pin> getLowest(bool isLeft_);
    std::shared_ptr<Pin> getLowest();
    std::shared_ptr<Pin> getHighest(bool isLeft_);
    std::shared_ptr<Pin> getHighest();
    std::set<std::shared_ptr<Pin>>& getPins(bool isLeft);
    friend std::ostream& operator<<(std::ostream & o_, const PinConnection& conn_);
    PinConnection(PinConnectionsStore &store_, int connId_);

private:

    const PinConnectionsStore& pinConnectionsStore__;
    std::set<std::shared_ptr<Pin>> pins__;
    std::set<std::shared_ptr<Pin>>leftPins__,rightPins__;
    std::shared_ptr<Pin> lowestLeft__,highestLeft__,lowestRight__, highestRight__;
    int connId__;
    QColor color__;
    static void addOnePin(MutablePinConnectionsStore &connsStore_, std::shared_ptr<PinConnection> conn_);


    bool operator<(const PinConnection&r_){return pins__<r_.pins__;  }
    bool operator==(const PinConnection&r_){return pins__==r_.pins__;}
};
#endif // PINCONNECTION_H
