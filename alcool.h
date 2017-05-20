#ifndef ALCOOL_H
#define ALCOOL_H
#include <string>

class Alcool
{
public:
    //constructeurs
    Alcool(std::string p_nom, float p_dosage, bool p_zeroStock, bool p_commande);
    ~Alcool();
    //seters
    void setNom(std::string p_nom);
    void setDosage(float p_dosage);
    void setZeroStock(bool p_zeroStock);
    void setCommande(bool p_commande);
    //geters
    float getDosage() const;
    std::string getNom() const;
    bool getZeroStock() const;
    bool getCommande() const;

protected:
    std::string m_nom;
    float m_dosage;
    bool m_zeroStock;
    bool m_commande;
};

class alcoolSortByName
{
public:
    bool operator() (const Alcool* lhs, const Alcool* rhs)
    {
        return (lhs->getNom() < rhs->getNom());
    }
};

#endif // ALCOOL_H
