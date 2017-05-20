#ifndef LISTBASES_H
#define LISTBASES_H
#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QPair>
#include "base.h"

class ListBases
{
public:
    //constructeurs
    ListBases();
    ~ListBases();
    //seters
    void importList(std::string pathBases);
    void ajouter(std::string p_nom, bool p_zeroStock, bool p_commande, int p_pg, int p_nico);
    void retirer(int index);
    void setNom(int index, std::string nom);
    void setZeroStock(int index, bool stock);
    void setCommande(int index, bool commande);
    void setPg(int index, int p_pg);
    void setNico(int index, int nico);
    //geters
    int getTaille() const;
    int getNumero(int index) const;
    std::string getNom(int index) const;
    int getPg(int index) const;
    int getVg(int index) const;
    int getNico(int index) const;
    bool getZeroStock(int index) const;
    bool getCommande(int index) const;

private:
    std::vector<Base*> m_listeBases;
};

#endif // LISTBASES_H
