#include "arome.h"

//constructeurs
Arome::Arome(int p_numero, std::string p_nom, bool p_zeroStock, bool p_commande, std::string p_fabricant, float p_dosage, std::string p_path, int p_note)
    : Liquid(p_numero, p_nom, p_zeroStock, p_commande), m_fabricant{p_fabricant}, m_image{p_path}
{
    setDosage(p_dosage);
    setNote(p_note);
}

Arome::~Arome()
{}
//seters
void Arome::setFabricant(std::string p_fabricant)
{
    m_fabricant = p_fabricant;
}

void Arome::setDosage(float p_dosage)
{
    if(p_dosage > 0 && p_dosage < 100) m_dosage = p_dosage;
    else m_dosage = 0;
}

void  Arome::setImage(std::string p_path)
{
    m_image = p_path;
}

void  Arome::setNote(int p_note)
{
    if(p_note<0 || p_note > 5) m_note = 0;
    else m_note = p_note;
}

//geters
std::string Arome::getFabricant() const
{
    return m_fabricant;
}

float Arome::getDosage() const
{
    return m_dosage;
}

std::string Arome::getImage() const
{
    return m_image;
}

int Arome::getNote() const
{
    return m_note;
}
