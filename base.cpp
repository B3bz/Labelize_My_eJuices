#include "base.h"

//constructeurs
Base::Base(int p_numero, std::string p_nom, bool p_zeroStock, bool p_commande, int p_pg, int p_nico) : Liquid(p_numero, p_nom, p_zeroStock, p_commande)
{
    setPg(p_pg);
    setNico(p_nico);
}

Base::~Base()
{}
//seters
void Base::setPg(int p_pg)
{
    if (p_pg<0 || p_pg>100) { m_pg = 100; m_vg = 0; }
    else { m_pg = p_pg; m_vg = 100 - p_pg; }
}

void Base::setVg(int p_vg)
{
    setPg(100-p_vg);
}

void Base::setNico(int p_nico)
{
    if (p_nico<0) m_nico = 0;
    else m_nico = p_nico;
}

//geters
int Base::getPg() const
{
    return m_pg;
}

int Base::getVg() const
{
    return m_vg;
}

int Base::getNico() const
{
    return m_nico;
}
