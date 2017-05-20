#include "liquid.h"

Liquid::Liquid(int p_numero, std::string p_nom, bool p_zeroStock, bool p_commande)
    : m_nom{p_nom}, m_zeroStock{p_zeroStock}, m_commande{p_commande}
{
    setNumero(p_numero);
}

Liquid::~Liquid()
{}
//seters
void Liquid::setNumero(int p_numero)
{
    if(p_numero>0) m_numero = p_numero;
    else m_numero = 0;
}

void Liquid::setNom(std::string p_nom)
{
    m_nom = p_nom;
}

void  Liquid::setZeroStock(bool p_zeroStock)
{
    m_zeroStock = p_zeroStock;
}

void  Liquid::setCommande(bool p_commande)
{
    m_commande = p_commande;
}

//geters
int Liquid::getNumero() const
{
    return m_numero;
}

std::string Liquid::getNom() const
{
    return m_nom;
}

bool Liquid::getZeroStock() const
{
    return m_zeroStock;
}

bool Liquid::getCommande() const
{
    return m_commande;
}
