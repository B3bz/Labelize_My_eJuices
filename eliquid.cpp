#include "eliquid.h"

//constructeurs
Eliquid::Eliquid() : m_nom{0}, m_quantite{0}
{
    //m_base = new Base();
    //m_arome = new Arome();
    m_alcool = new Alcool(0.0, "DEFINIR");
}

Eliquid::Eliquid(Base p_base, Arome p_arome, Alcool p_alcool, std::string p_nom, int p_quantite) :
    m_nom{p_nom}, m_quantite{p_quantite}
{
    //m_base = new Base(p_base.getPg(), p_base.getNico());
    //m_arome = new Arome(p_arome.getNumero(), p_arome.getNom(), p_arome.getFabricant(), p_arome.getDosage());
    m_alcool = new Alcool(p_alcool.first, p_alcool.second);
}

Eliquid::~Eliquid()
{
    delete m_base;
    delete m_arome;
    delete m_alcool;
}

/*
Eliquid::Eliquid(Arome p_arome, std::pair<double, std::string> p_alcool, std::string p_nom, int p_quantite,
                 int p_pg, int p_vg, int p_nico,) :
    m_arome{p_arome}, m_alcool{p_alcool}, m_nom{p_nom}, m_quantite{p_quantite},
    m_base{p_pg, p_vg, p_nico}
{
}
*/

//seters
void Eliquid::setBase(Base p_base)
{
    this->m_base = &p_base;
}

void Eliquid::setArome(Arome p_arome)
{
    this->m_arome = &p_arome;
}

void Eliquid::setAlcool(double p_ml, std::string p_nom)
{
    this->m_alcool->first = p_ml;
    this->m_alcool->second = p_nom;
}

void Eliquid::setNom(std::string p_nom)
{
    m_nom = p_nom;
}

void Eliquid::setQuantite(int p_quantite)
{
    m_quantite = p_quantite;
}
//geters
Base Eliquid::getBase() const
{
    return *m_base;
}

Arome Eliquid::getArome() const
{
    return *m_arome;
}

std::pair<double, std::string> Eliquid::getAlcool() const
{
    return *m_alcool;
}

std::string Eliquid::getNom() const
{
    return m_nom;
}

int Eliquid::getQuantite() const
{
    return m_quantite;
}

