#ifndef LISTAROMES_H
#define LISTAROMES_H
#include <QApplication>
#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QPair>
#include "arome.h"

class ListAromes
{
public:
    //constructeurs
    ListAromes();
    ~ListAromes();
    //void ajouterArome(Arome *arome);
    //seters
    void importList(std::string pathAromes);
    void ajouter(int p_numero, std::string p_nom, bool p_zeroStock, bool p_commande, std::string p_fabricant, float p_dosage, std::string p_path, int p_note);
    void retirer(int index);
    void setImage(int index, std::string path);
    void setNumero(int index, int numero);
    void setNom(int index, std::string nom);
    void setZeroStock(int index, bool stock);
    void setCommande(int index, bool commande);
    void setFabricant(int index, std::string fabricant);
    void setDosage(int index, float dosage);
    void setNote(int index, int note);
    //geters
    int getTaille() const;
    int getNumero(int index) const;
    std::string getNom(int index) const;
    std::string getFabricant(int index) const;
    float getDosage(int index) const;
    std::string getImage(int index) const;
    bool getZeroStock(int index) const;
    bool getCommande(int index) const;
    int getNote(int index) const;

private:
    std::vector<Arome*> m_listeAromes;
};

#endif // LISTAROMES_H
