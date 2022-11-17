#ifndef CABLE_H
#define CABLE_H
#include <set>
#include "pin.h"
class Cable;
class CableStore{//:{public PinsStore{
public:
    virtual ~CableStore(){}
    virtual std::map<int /*absPinLevel*/,std::shared_ptr<Pin>> const & getPins()=0;    
};
class MutableCableStore:public CableStore{
public:
    virtual void createAssociation(std::shared_ptr<Pin>,std::shared_ptr<Cable>)=0;
};

class Cable{
private:    
    //CableStore &cablesStore__;
    std::map<int/*numInCable__*/,std::shared_ptr<Pin>> pins__;
    int uniqId__;
    int level__;
    bool isLeft__;


public:
    static void addNewPin(MutableCableStore& cablesStore_, std::shared_ptr<Cable> cable_);

    Cable(int uniqId_, int level_, bool isLeft);
    bool isLeft() const {return isLeft__;}
    int getCableLvl(){return level__;}
    std::map<int/*numInCable__*/,std::shared_ptr<Pin>> const &getPins(){return pins__;}
    friend std::ostream & operator <<(std::ostream &o, const Cable&);
};

#endif // CABLE_H
