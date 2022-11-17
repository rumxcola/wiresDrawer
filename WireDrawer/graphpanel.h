#ifndef GRAPHPANEL_H
#define GRAPHPANEL_H

#include <QWidget>
#include <QPainter>
#include "session.h"

class GraphPanel : public QWidget
{
    Q_OBJECT
public:
    GraphPanel(QWidget* parent_ );
    bool hasDrawConnFlag(){return drawConn__;}
    void setDrawConnFlag(bool drawConn_){drawConn__=drawConn_;}
    virtual QSize sizeHint() const { return minimumSizeHint();    };
    virtual QSize minimumSizeHint() const{return QSize(session__->getXMax(),session__->getYMax());};


public slots:
    void onDbgOut();
    void genNewSession(int cables_, int oneCablePinsMax_, double connectedPercents_);

private:
    Session* session__=nullptr;
    bool drawConn__=false;
    void paintEvent(QPaintEvent *event);
    void reinit(int cables_, int oneCablePinsMax_, double connectedPercents_);
    int findVacantLevel(std::shared_ptr<PinConnection>conn_, std::set<int> &occupied_);
    void drawCable(std::shared_ptr<Cable> cable_);
    void drawPin(std::shared_ptr<Pin> pin_);
    void drawConnection(std::shared_ptr<PinConnection> conn_, std::set<int> &ocupied_);
    void drawDetour(QPainter &painter_, std::shared_ptr<PinConnection>conn_, std::set<int> &occupied_);
    void drawOutgrowth(QPainter &painter_, std::shared_ptr<PinConnection>conn_, bool isLeft_);
    void drawOneSidePinsBus(QPainter &painter_, std::shared_ptr<PinConnection>conn_, bool isLeft_);
    void setPainter(QPainter &painter_, std::shared_ptr<PinConnection> conn_);
    bool drawSidesLink(QPainter &painter_, std::shared_ptr<PinConnection>conn_);

};

class Fluctuator{
public:
    Fluctuator(int initVal_):initVal__(initVal_){}
    int getNext(){
        if((sign__=sign__*-1)==-1)
            ++counter__;
        int sum=initVal__+sign__*counter__;
        return sum>0?sum:getNext();
    }
private:
    int initVal__;
    int counter__=0;
    int sign__=-1;
};



#endif // GRAPHPANEL_H
