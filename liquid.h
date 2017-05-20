#ifndef LIQUID_H
#define LIQUID_H
#include <string>
#include <QDebug>

class Liquid
{
public:
    Liquid(int p_numero, std::string p_nom, bool p_zeroStock, bool p_commande);
    virtual ~Liquid();
    //seters
    void setNumero(int p_numero);
    void setNom(std::string p_nom);
    void setZeroStock(bool p_zeroStock);
    void setCommande(bool p_commande);
    //geters
    int getNumero() const;
    std::string getNom() const;
    bool getZeroStock() const;
    bool getCommande() const;

protected:
    int m_numero;
    std::string m_nom;
    bool m_zeroStock;
    bool m_commande;
};

#endif // LIQUID_H
