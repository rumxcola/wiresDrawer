#include "graphpanel.h"

GraphPanel::GraphPanel(QWidget *parent_):QWidget(parent_)
{

}


void GraphPanel::reinit(int cables_, int oneCablePinsMax_, double connectedPercents_){
    if(session__)
        delete session__;
    session__=new Session(cables_,oneCablePinsMax_, connectedPercents_);
    repaint();
}

void GraphPanel::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    if(!session__)
        return;
    for(int side=0;side<2;++side)
        for(auto it:session__->getCables(side))
            drawCable(it.second);
    std::set<int>occupied;
    for(auto conn:session__->getConnections())
        drawConnection(conn.second,occupied);
}


void GraphPanel::drawCable(std::shared_ptr<Cable> cable_){
    for(auto it:cable_->getPins())
        drawPin(it.second);
}


void GraphPanel::drawPin(std::shared_ptr<Pin> pin_){
    QPainter painter(this);
    auto pinPoint=session__->getPinPoint(pin_);
    QRect rect(pinPoint.x(),pinPoint.y(),session__->getPinWidh(),session__->getPinHeight());
    QBrush brush(QColorConstants::Svg::white);
    painter.fillRect(rect,brush);
    painter.drawRect(rect);
}
void GraphPanel::setPainter(QPainter& painter_, std::shared_ptr<PinConnection> conn_){
    QBrush brush(session__->getColor(conn_));
    QPen pen(session__->getColor(conn_),3);
    painter_.setPen(pen);
    painter_.setBrush(brush);
    return;
}

void GraphPanel::drawOutgrowth(QPainter &painter_, std::shared_ptr<PinConnection>conn_, bool isLeft_){
    for(auto pin:conn_->getPins(isLeft_)){
        QPoint pinPoint=session__->getPinMiddlePoint(pin);
        QPoint busPoint(session__->getBusX(conn_,isLeft_),pinPoint.y());
        QLine line(busPoint,pinPoint);
        painter_.drawLine(line);
    }
}
void GraphPanel::drawOneSidePinsBus(QPainter &painter_, std::shared_ptr<PinConnection> conn_, bool isLeft_){
    int busX=session__->getBusX(conn_, isLeft_);
    std::shared_ptr<Pin>lowest=conn_->getLowest(isLeft_);
    std::shared_ptr<Pin>highest=conn_->getHighest(isLeft_);
    if(!lowest || !highest)
        return;
    QLine leftBus(busX,session__->getPinMiddlePoint(lowest).y(),busX,session__->getPinMiddlePoint(highest).y());
    painter_.drawLine(leftBus);
}



int GraphPanel::findVacantLevel(std::shared_ptr<PinConnection> conn_, std::set<int>& occupied_){
    int lvl;
    bool IS_LEFT=true;
    auto highest=conn_->getHighest(IS_LEFT);
    Fluctuator approximator(session__->getAbsPinLevel(highest));
    for(lvl=approximator.getNext();;lvl=approximator.getNext()){
        if(occupied_.find(lvl)!=occupied_.end())
            continue;
        if(session__->hasOccupiedWithLessId(lvl,conn_))
            continue;
        occupied_.insert(lvl);
        break;
    }
    return lvl;
}
void GraphPanel::drawDetour(QPainter &painter_, std::shared_ptr<PinConnection> conn_, std::set<int> &occupied_){
    bool IS_LEFT=true;
    if(conn_->getPins(IS_LEFT).empty() || conn_->getPins(!IS_LEFT).empty())
            return;

    auto leftPinPoint=session__->getPinMiddlePoint(conn_->getHighest(IS_LEFT));
    auto rightPinPoint=session__->getPinMiddlePoint(conn_->getHighest(!IS_LEFT));
    int leftBusX=session__->getBusX(conn_,IS_LEFT);
    int rightBusX=session__->getBusX(conn_,!IS_LEFT);
    int y=session__->getAbsLevelY(findVacantLevel(conn_,occupied_));
    QLine leftVLine(leftBusX,leftPinPoint.y(),leftBusX,y);
    QLine rightVLine(rightBusX,rightPinPoint.y(),rightBusX,y);
    QLine line(leftBusX,y,rightBusX,y);
    painter_.drawLine(leftVLine);
    painter_.drawLine(rightVLine);
    painter_.drawLine(line);
}
void GraphPanel::drawConnection(std::shared_ptr<PinConnection> conn_, std::set<int>& ocupied_){
    QPainter painter(this);
    setPainter(painter,conn_);
    for(int side=0;side<2;++side){
        drawOneSidePinsBus(painter,conn_,side);
        drawOutgrowth(painter,conn_,side);
    }
    if(!drawConn__)
        return;
    drawDetour(painter,conn_,ocupied_);
}


void GraphPanel::onDbgOut()
{
    std::cout<<*session__<<std::endl;
    repaint();
}



void GraphPanel::genNewSession(int cables_, int oneCablePinsMax_, double connectedPercents_)
{
    reinit(cables_,oneCablePinsMax_, connectedPercents_);
    repaint();
}


