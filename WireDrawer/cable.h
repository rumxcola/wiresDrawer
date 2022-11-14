#ifndef CABLE_H
#define CABLE_H
#include <set>
#include "pin.h"
class Cable;
class CableStore:public PinsStore{
public:
    virtual ~CableStore(){}
    virtual std::map<Pin*,Cable*>& getPinCablesMap()=0;
    virtual std::map<int/*level*/, Cable*>& getCables(bool isLeftSide_)=0;
    virtual std::map<int/*absPinLevel*/,Pin*>& getLeveledPins(bool isLeft)=0;
    virtual int getAbsPinLevel(Pin *pin_) const =0;
};

class Cable{
private:    
    CableStore &cablesStore__;
    std::map<int/*numInCable__*/,Pin *> pins__;
    bool isLeft__;
    int level__;


public:
    static int getAbsPinLevel(CableStore &cablesStore_, Pin *pin_);

    Cable(CableStore &cablesStore_, bool isLeft);
    ~Cable();
    bool isLeft() const {return isLeft__;}
    void addPin();
    int getCableLvl(){return level__;}
    std::map<int/*numInCable__*/,Pin *> getPins()const{return pins__;}
    friend std::ostream & operator <<(std::ostream &o, const Cable&);
};

#endif // CABLE_H
