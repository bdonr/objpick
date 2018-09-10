#ifndef MYEVENT_H
#define MYEVENT_H
#include "traegerklasse.h"
#include "CgBase/CgBaseEvent.h"
#include "CgBase/CgEnums.h"

class MyEvent : public CgBaseEvent
{
private:
    TraegerKlasse* traeger;
    enum Cg::EventType type;
public:
    MyEvent();
    MyEvent(enum Cg::EventType type, TraegerKlasse* traeger);
    ~MyEvent(){};

    TraegerKlasse* getTraeger();
    void setTraeger(TraegerKlasse* &value);
    void setType(Cg::EventType &value);

    enum Cg::EventType getType();
    CgBaseEvent* clone();
};

#endif // MYEVENT_H
