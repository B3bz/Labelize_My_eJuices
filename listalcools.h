#ifndef LISTALCOOLS_H
#define LISTALCOOLS_H
#include <QApplication>
#include <vector>
#include <QString>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QPair>
#include "alcool.h"

class ListAlcools
{
public:
    ListAlcools();
    ~ListAlcools();
    //seters
    void ajouter(std::string p_nom, float p_dosage, bool p_zeroStock, bool p_commande);
    void retirer(int index);
    void importList(std::string pathAlcools);
    void setNom(int index, std::string nom);
    void setDosage(int index, float dosage);
    void setZeroStock(int index, bool stock);
    void setCommande(int index, bool commande);
    //geters
    int getTaille() const;
    std::string getNom(int index) const;
    float getDosage(int index) const;
    bool getZeroStock(int index) const;
    bool getCommande(int index) const;

private:
    std::vector<Alcool*> m_listeAlcools;
};

#endif // LISTALCOOLS_H
