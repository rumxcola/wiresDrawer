#include "cable.h"
Cable::Cable(int uniqId_, int level_, bool isLeft):uniqId__(uniqId_), level__(level_), isLeft__(isLeft){

}

void Cable::addNewPin(MutableCableStore &cablesStore_, std::shared_ptr<Cable> cable_){
    auto pin=std::make_shared<Pin>(cablesStore_.getPins().size(), cable_->level__, cable_->pins__.size(),cable_->isLeft__);
    cable_->pins__.insert(std::make_pair(pin->getNumInCable(),pin));
    cablesStore_.createAssociation(pin,cable_);
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

