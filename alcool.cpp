#include "alcool.h"

//constructeurs
Alcool::Alcool(std::string p_nom, float p_dosage, bool p_zeroStock, bool p_commande)
    : m_nom{p_nom}, m_zeroStock{p_zeroStock}, m_commande{p_commande}
{
    setDosage(p_dosage);
}

Alcool::~Alcool()
{

}

//seters
void Alcool::setNom(std::string p_nom)
{
    m_nom = p_nom;
}

void Alcool::setDosage(float p_dosage)
{
    if(p_dosage > 0 && p_dosage < 100) m_dosage = p_dosage;
    else m_dosage = 0;
}

void  Alcool::setZeroStock(bool p_zeroStock)
{
    m_zeroStock = p_zeroStock;
}

void  Alcool::setCommande(bool p_commande)
{
    m_commande = p_commande;
}

//geters
std::string Alcool::getNom() const
{
    return m_nom;
}

float Alcool::getDosage() const
{
    return m_dosage;
}

bool Alcool::getZeroStock() const
{
    return m_zeroStock;
}

bool Alcool::getCommande() const
{
    return m_commande;
}
