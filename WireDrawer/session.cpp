#include "session.h"

Session::Session(int totalCables_, int oneCablePinsMax_,double connectedPercents_,  int pinWidh_, int pinHeight_, int cableGap_):
    pinWidh__(pinWidh_),pinHeight__(pinHeight_),cableGap__(cableGap_)
{
    setColors();
    init(totalCables_,oneCablePinsMax_, connectedPercents_ );
}
Session::~Session(){
    deinit();
}

void Session::setColors(){

    colors__.push_back(QColorConstants::Svg::black);
    colors__.push_back(QColorConstants::Svg::blue);
    colors__.push_back(QColorConstants::Svg::blueviolet);
    colors__.push_back(QColorConstants::Svg::brown);
    colors__.push_back(QColorConstants::Svg::burlywood);
    colors__.push_back(QColorConstants::Svg::cadetblue);
    colors__.push_back(QColorConstants::Svg::chocolate);
    colors__.push_back(QColorConstants::Svg::cornflowerblue);
    colors__.push_back(QColorConstants::Svg::crimson);
    colors__.push_back(QColorConstants::Svg::cyan);
    colors__.push_back(QColorConstants::Svg::darkblue);
    colors__.push_back(QColorConstants::Svg::darkcyan);
    colors__.push_back(QColorConstants::Svg::darkgoldenrod);
    colors__.push_back(QColorConstants::Svg::darkgray);
    colors__.push_back(QColorConstants::Svg::darkgreen);
    colors__.push_back(QColorConstants::Svg::darkgrey);
    colors__.push_back(QColorConstants::Svg::darkkhaki);
    colors__.push_back(QColorConstants::Svg::darkmagenta);
    colors__.push_back(QColorConstants::Svg::darkolivegreen);
    colors__.push_back(QColorConstants::Svg::darkorange);
    colors__.push_back(QColorConstants::Svg::darkorchid);
    colors__.push_back(QColorConstants::Svg::darkred);
    colors__.push_back(QColorConstants::Svg::darksalmon);
    colors__.push_back(QColorConstants::Svg::darkseagreen);
    colors__.push_back(QColorConstants::Svg::darkslateblue);
    colors__.push_back(QColorConstants::Svg::darkslategray);
    colors__.push_back(QColorConstants::Svg::darkslategrey);
    colors__.push_back(QColorConstants::Svg::darkturquoise);
    colors__.push_back(QColorConstants::Svg::darkviolet);
    colors__.push_back(QColorConstants::Svg::deeppink);
    colors__.push_back(QColorConstants::Svg::deepskyblue);
    colors__.push_back(QColorConstants::Svg::dimgray);
    colors__.push_back(QColorConstants::Svg::dimgrey);
    colors__.push_back(QColorConstants::Svg::dodgerblue);
    colors__.push_back(QColorConstants::Svg::firebrick);
    colors__.push_back(QColorConstants::Svg::floralwhite);
    colors__.push_back(QColorConstants::Svg::forestgreen);
    colors__.push_back(QColorConstants::Svg::fuchsia);
    colors__.push_back(QColorConstants::Svg::gainsboro);
    colors__.push_back(QColorConstants::Svg::ghostwhite);
    colors__.push_back(QColorConstants::Svg::gold);
    colors__.push_back(QColorConstants::Svg::goldenrod);
    colors__.push_back(QColorConstants::Svg::gray);
    colors__.push_back(QColorConstants::Svg::green);
    colors__.push_back(QColorConstants::Svg::greenyellow);
    colors__.push_back(QColorConstants::Svg::grey);
    colors__.push_back(QColorConstants::Svg::honeydew);
    colors__.push_back(QColorConstants::Svg::hotpink);
    colors__.push_back(QColorConstants::Svg::indianred);
    colors__.push_back(QColorConstants::Svg::indigo);
    colors__.push_back(QColorConstants::Svg::ivory);
    colors__.push_back(QColorConstants::Svg::khaki);
    colors__.push_back(QColorConstants::Svg::lavender);
    colors__.push_back(QColorConstants::Svg::lavenderblush);
    colors__.push_back(QColorConstants::Svg::lawngreen);
    colors__.push_back(QColorConstants::Svg::lemonchiffon);
    colors__.push_back(QColorConstants::Svg::lightblue);
    colors__.push_back(QColorConstants::Svg::lightcoral);
    colors__.push_back(QColorConstants::Svg::lightcyan);
    colors__.push_back(QColorConstants::Svg::lightgoldenrodyellow);
    colors__.push_back(QColorConstants::Svg::lightgray);
    colors__.push_back(QColorConstants::Svg::lightgreen);
    colors__.push_back(QColorConstants::Svg::lightgrey);
    colors__.push_back(QColorConstants::Svg::lightpink);
    colors__.push_back(QColorConstants::Svg::lightsalmon);
    colors__.push_back(QColorConstants::Svg::lightseagreen);
    colors__.push_back(QColorConstants::Svg::lightskyblue);
    colors__.push_back(QColorConstants::Svg::lightslategray);
    colors__.push_back(QColorConstants::Svg::lightslategrey);
    colors__.push_back(QColorConstants::Svg::lightsteelblue);
    colors__.push_back(QColorConstants::Svg::lightyellow);
    colors__.push_back(QColorConstants::Svg::lime);
    colors__.push_back(QColorConstants::Svg::limegreen);
    colors__.push_back(QColorConstants::Svg::linen);
    colors__.push_back(QColorConstants::Svg::magenta);
    colors__.push_back(QColorConstants::Svg::maroon);
    colors__.push_back(QColorConstants::Svg::mediumaquamarine);
    colors__.push_back(QColorConstants::Svg::mediumblue);
    colors__.push_back(QColorConstants::Svg::mediumorchid);
    colors__.push_back(QColorConstants::Svg::mediumpurple);
    colors__.push_back(QColorConstants::Svg::mediumseagreen);
    colors__.push_back(QColorConstants::Svg::mediumslateblue);
    colors__.push_back(QColorConstants::Svg::mediumspringgreen);
    colors__.push_back(QColorConstants::Svg::mediumturquoise);
    colors__.push_back(QColorConstants::Svg::mediumvioletred);
    colors__.push_back(QColorConstants::Svg::midnightblue);
    colors__.push_back(QColorConstants::Svg::mintcream);
    colors__.push_back(QColorConstants::Svg::mistyrose);
    colors__.push_back(QColorConstants::Svg::moccasin);
    colors__.push_back(QColorConstants::Svg::navajowhite);
    colors__.push_back(QColorConstants::Svg::navy);
    colors__.push_back(QColorConstants::Svg::oldlace);
    colors__.push_back(QColorConstants::Svg::olive);
    colors__.push_back(QColorConstants::Svg::olivedrab);
    colors__.push_back(QColorConstants::Svg::orange);
    colors__.push_back(QColorConstants::Svg::orangered);
    colors__.push_back(QColorConstants::Svg::orchid);
    colors__.push_back(QColorConstants::Svg::palegoldenrod);
    colors__.push_back(QColorConstants::Svg::palegreen);
    colors__.push_back(QColorConstants::Svg::paleturquoise);
    colors__.push_back(QColorConstants::Svg::palevioletred);
    colors__.push_back(QColorConstants::Svg::papayawhip);
    colors__.push_back(QColorConstants::Svg::peachpuff);
    colors__.push_back(QColorConstants::Svg::peru);
    colors__.push_back(QColorConstants::Svg::pink);
    colors__.push_back(QColorConstants::Svg::plum);
    colors__.push_back(QColorConstants::Svg::powderblue);
    colors__.push_back(QColorConstants::Svg::purple);
    colors__.push_back(QColorConstants::Svg::red);
    colors__.push_back(QColorConstants::Svg::rosybrown);
    colors__.push_back(QColorConstants::Svg::royalblue);
    colors__.push_back(QColorConstants::Svg::saddlebrown);
    colors__.push_back(QColorConstants::Svg::salmon);
    colors__.push_back(QColorConstants::Svg::sandybrown);
    colors__.push_back(QColorConstants::Svg::seagreen);
    colors__.push_back(QColorConstants::Svg::seashell);
    colors__.push_back(QColorConstants::Svg::sienna);
    colors__.push_back(QColorConstants::Svg::silver);
    colors__.push_back(QColorConstants::Svg::skyblue);
    colors__.push_back(QColorConstants::Svg::slateblue);
    colors__.push_back(QColorConstants::Svg::slategray);
    colors__.push_back(QColorConstants::Svg::slategrey);
    colors__.push_back(QColorConstants::Svg::snow);
    colors__.push_back(QColorConstants::Svg::springgreen);
    colors__.push_back(QColorConstants::Svg::steelblue);
    colors__.push_back(QColorConstants::Svg::tan);
    colors__.push_back(QColorConstants::Svg::teal);
    colors__.push_back(QColorConstants::Svg::thistle);
    colors__.push_back(QColorConstants::Svg::tomato);
    colors__.push_back(QColorConstants::Svg::turquoise);
    colors__.push_back(QColorConstants::Svg::violet);
    colors__.push_back(QColorConstants::Svg::wheat);
    colors__.push_back(QColorConstants::Svg::white);
    colors__.push_back(QColorConstants::Svg::whitesmoke);
    colors__.push_back(QColorConstants::Svg::yellow);
    colors__.push_back(QColorConstants::Svg::yellowgreen);
}

int Session::getPinLen(PinConnection* conn_){
    return (conn_->getConnId()+2)*pinWidh__;
}
QPoint Session::getPinPoint(Pin* pin_){
    return QPoint(getPinX(pin_),getPinY(pin_));
}
QPoint Session::getPinMiddlePoint(Pin* pin_){
    return QPoint(getPinX(pin_)+pinWidh__/2,getPinY(pin_)+pinHeight__/2);
}
int Session::getPinsUsed(){return getPinsConnected().size();}
int Session::getBusX(PinConnection* conn_, bool isLeft_){return isLeft_?getPinLen(conn_):(getXRightBorder()-getPinLen(conn_));}
int Session::getXRightBorder(){return 2*getXCenter()+pinWidh__;  }
int Session::getYMax(){
    bool isLeft=absLeftPins__.size()>absRightPins__.size();
    return (getCables(isLeft).size()+1)*cableGap__+((isLeft?absLeftPins__:absRightPins__).size()+2)*pinHeight__;
}
int Session::getXMax(){    return getXRightBorder()+pinWidh__;}
int Session::getXCenter(){return (connections__.size()+1)*pinWidh__;}
int Session::getAbsPinLevel(Pin *pin_) const {
    auto pinCable=pinCablesMap__.find(pin_)->second;
    auto cables=pinCable->isLeft()? leftCables__:rightCables__;
    int pinLevel=pin_->getNumInCable();
    for(auto cableIt:cables)
        if(cableIt.first<pinCable->getCableLvl())
            pinLevel+=cableIt.second->getPins().size()+1;
    return pinLevel;
}

bool Session::hasOccupiedWithLessId(int level, PinConnection* conn_ ){
    for(int side=0;side<2;++side){
        bool isLeft=side;
        auto &occupied=isLeft?occupiedLevelsLeftPins__:occupiedLevelsRightPins__;
        auto finded=occupied.find(level);
        if(finded!=occupied.end() && finded->second->getConnId() > conn_->getConnId())
            return true;
    }
    return false;
}
int Session::getPinY(Pin *pin_){
    Cable *pinCable=getPinCablesMap()[pin_];
    int height=0;
    auto &oneSideCables=getCables(pinCable->isLeft());
    for(auto& cableIt:oneSideCables)
        if(pinCable->getCableLvl()>cableIt.first)
            height+=(cableIt.second->getPins().size())*pinHeight__+cableGap__;
    height+=(pin_->getNumInCable()*pinHeight__);
    return height;
}
int Session::getPinX(Pin* pin_){
    return getPinCablesMap()[pin_]->isLeft()?0:2*(connections__.size()+1)*pinWidh__;
}

void Session::deinit(){
    for(auto connIt=connections__.begin();connIt!=connections__.end(); )
        delete connIt++->second;
    connections__.clear();
    for(auto cable:cables__)
        delete cable;
    cables__.clear();

}
bool Session::init(int totalCables_, int oneCablePinsMax_, double connectedPinsPercent_){
    for(int cableNum=0;cableNum<totalCables_;++cableNum){
        bool isLeft=cableNum%2;
        Cable* cable=new Cable(*this,isLeft);
        cables__.insert(cable);
        int pinsCount=Randomizer::getRandom(1,oneCablePinsMax_);
        for(int pinNum=0;pinNum<pinsCount;++pinNum)
            cable->addPin();

    }

    int maxPinsConnected=static_cast<int>(pins__.size()*connectedPinsPercent_);
    int pinsRest;
    while((pinsRest=maxPinsConnected-getPinsUsed())>=2){
        if(pinsRest<2)
            return true;
        int pinsCountMax=Randomizer::getRandom(2,pinsRest);
        auto conn=PinConnection::genNextConnection(*this, pinsCountMax);
        connections__.insert(std::make_pair(conn->getConnId(),conn));
    }

    return true;
}

std::map<int /*pinLevel*/,PinConnection*>& Session::getOccpuiedLevels(bool isLeft_){
    return isLeft_?occupiedLevelsLeftPins__:occupiedLevelsRightPins__;
}
std::map<int /*connId*/,PinConnection*>& Session::getConnections(){
    return connections__;
}
std::map<Pin*, PinConnection*>& Session::getPinsConnected(){
    return pinsConnected__;
}
std::map<Pin*,Cable*>& Session::getPinCablesMap(){
    return pinCablesMap__;
}
std::map<int/*level*/, Cable*>& Session::getCables(bool isLeftSide_){
    return isLeftSide_?leftCables__:rightCables__;
}
std::map<int/*absPinLevel*/,Pin*>& Session::getLeveledPins(bool isLeft_){
    return isLeft_?absLeftPins__:absRightPins__;
}

std::ostream& operator <<(std::ostream &o_, const Session& session_){

    for(auto conn:session_.connections__)
        std::cout<<*conn.second<<"\n highest="<<*conn.second->getHighest()<<"\n lowest="<<*conn.second->getLowest()<<"\n\n";

    std::cout<<"Cables:\n";
    for(int side=0;side<2;++side)
        for(auto it: (side?session_.leftCables__:session_.rightCables__))
            std::cout<<*it.second<<"\n";

    for(auto pin:session_.pins__){
        if(!pin.second->isLeft())
            continue;
        auto cable=session_.pinCablesMap__.find(pin.second)->second;
        std::cout<<"Pin: "
               <<(pin.second->isLeft()?"left":"right")
               <<" cable"<<cable->getCableLvl()
               <<"["<<pin.second->getNumInCable()<<"] abslvl="
               <<session_.getAbsPinLevel(pin.second)<<"\n";
    }

    return o_;
}
