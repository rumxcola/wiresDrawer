#ifndef PINCONNECTION_H
#define PINCONNECTION_H
#include <QColor>
#include "cable.h"
#include "randomizer.h"

class PinConnection;
class PinConnectionsStore : public CableStore{
public:
    virtual ~PinConnectionsStore(){}
    virtual std::map<int /*pinLevel*/,PinConnection*>& getOccpuiedLevels(bool isLeft_)=0;
    virtual std::map<int /*connId*/,PinConnection*>& getConnections()=0;
    virtual std::map<Pin*, PinConnection*>& getPinsConnected()=0;
};

class PinConnection{

    public :
    std::set<Pin *>& getPins();
    static PinConnection* genNextConnection(PinConnectionsStore &pinConnectionsStore_, int pinsCount_);
    int getConnId()const;
    //QColor getColor() const;
    Pin* getLowest(const std::set<Pin*>&pins_);
    Pin* getHighest(const std::set<Pin *> &pins_);

    Pin* getLowest(bool isLeft_);
    Pin* getLowest();
    Pin* getHighest(bool isLeft_);
    Pin* getHighest();
    std::set<Pin *>& getPins(bool isLeft);
    friend std::ostream& operator<<(std::ostream & o_, const PinConnection& conn_);
    ~PinConnection();
private:

    PinConnectionsStore& pinConnectionsStore__;
    std::set<Pin *> pins__;
    std::set<Pin *>leftPins__,rightPins__;
    int connId__;
    QColor color__;
    void addOnePin();

    PinConnection(PinConnectionsStore& pinConnectionsStore_);

    bool operator<(const PinConnection&r_){return pins__<r_.pins__;  }
    bool operator==(const PinConnection&r_){return pins__==r_.pins__;}
};
#endif // PINCONNECTION_H
