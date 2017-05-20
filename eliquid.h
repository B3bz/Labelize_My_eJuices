#ifndef ELIQUID_H
#define ELIQUID_H
#include <string>
#include <utility>
#include "base.h"
#include "arome.h"
using Alcool = std::pair<double, std::string>;

class Eliquid
{
public:
    //constructeurs
    Eliquid();
    Eliquid(Base p_base, Arome p_arome, Alcool p_alcool, std::string p_nom, int p_quantite);
    ~Eliquid();
    //seters
    void setBase(Base p_base);
    void setArome(Arome p_arome);
    void setAlcool(double p_ml, std::string p_nom);
    void setNom(std::string p_nom);
    void setQuantite(int p_quantite);
    //geters
    Base getBase() const;
    Arome getArome() const;
    std::pair<double, std::string> getAlcool() const;
    std::string getNom() const;
    int getQuantite() const;

private:
    Base *m_base;
    Arome *m_arome;
    std::pair<double, std::string> *m_alcool;
    std::string m_nom;
    int m_quantite;
};

#endif // ELIQUID_H
