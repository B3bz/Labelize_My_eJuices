#ifndef BASE_H
#define BASE_H
#include "liquid.h"

class Base : public Liquid
{
public:
    //constructeurs
    Base(int p_numero, std::string p_nom, bool p_zeroStock, bool p_commande, int p_pg, int p_nico);
    virtual ~Base();
    //seters
    void setPg(int p_pg);
    void setVg(int p_vg);
    void setNico(int p_nico);
    //geters
    int getPg() const;
    int getVg() const;
    int getNico() const;

private:
    int m_pg;
    int m_vg;
    int m_nico;
};

class baseSortByName
{
public:
    bool operator() (const Base* lhs, const Base* rhs)
    {
        return (lhs->getNom() < rhs->getNom());
    }
};

#endif // BASE_H
