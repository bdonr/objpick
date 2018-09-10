#include "myevent.h"

TraegerKlasse* MyEvent::getTraeger()
{
    return traeger;
}

void MyEvent::setTraeger( TraegerKlasse* &value)
{
    traeger = value;
}


void MyEvent::setType( Cg::EventType &value)
{
    type = value;
}

Cg::EventType MyEvent::getType()
{
    return type;
}

CgBaseEvent *MyEvent::clone()
{
    return new MyEvent(type, traeger);
}

MyEvent::MyEvent(enum Cg::EventType type, TraegerKlasse* traeger)
{
    setType(type);
    setTraeger(traeger);
}

