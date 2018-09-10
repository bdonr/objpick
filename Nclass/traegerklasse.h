#ifndef TRAEGERKLASSE_H
#define TRAEGERKLASSE_H


class TraegerKlasse
{
private:
    int projektion;
    int frustumTyp;
    int frustumValue;
public:
    TraegerKlasse();
    int getProjektion() const;
    void setProjektion(int value);
    int getFrustumTyp() const;
    void setFrustumTyp(int value);
    int getFrustumValue() const;
    void setFrustumValue(int value);
};

#endif // TRAEGERKLASSE_H
