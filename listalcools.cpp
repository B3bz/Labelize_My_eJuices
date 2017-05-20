#include "listalcools.h"

//constructeurs
ListAlcools::ListAlcools()
{

}

ListAlcools::~ListAlcools()
{
}

//seters
void ListAlcools::ajouter(std::string p_nom, float p_dosage, bool p_zeroStock, bool p_commande)
{
    m_listeAlcools.push_back(new Alcool(p_nom, p_dosage, p_zeroStock, p_commande));

}

void ListAlcools::retirer(int index)
{
    m_listeAlcools.erase(m_listeAlcools.begin()+index);

}

void ListAlcools::importList(std::string pathAlcools)
{
    QFile FileDatabase(QString::fromStdString(pathAlcools));
    QString stringTampon;
    if (!FileDatabase.open(QIODevice::ReadOnly | QIODevice::Text)) {return;}
    else
    {
        QTextStream in(&FileDatabase);// Création d'un objet QTextStream raccordé à objet QFile
        const QPair<QString, int> patternNom         { "[NOM]", 6 }; // on recherche le motif, index du premier caractère de la valeur à récupérer
        const QPair<QString, int> patternPc          { "[POURCENTAGE]", 14 };
        const QPair<QString, int> patternStock       { "[0STOCK]", 9 };
        const QPair<QString, int> patternCommande    { "[COMMANDE]", 11 };
        QString nom{"temp"};
        float dosage {0.0};
        bool stock {false}, commande {false};
        while (!in.atEnd())//on lis le fichier ligne par ligne jusqu'au bout
        {
            stringTampon = in.readLine();
            if(stringTampon.contains(patternNom.first)) {nom = stringTampon.right(stringTampon.size()-patternNom.second);
                nom[0] = nom[0].toUpper();}
            else if(stringTampon.contains(patternPc.first)) dosage = stringTampon.right(stringTampon.size()-patternPc.second).toFloat();
            else if(stringTampon.contains(patternStock.first)) stock = stringTampon.right(stringTampon.size()-patternStock.second).toInt();
            else if(stringTampon.contains(patternCommande.first)) commande = stringTampon.right(stringTampon.size()-patternCommande.second).toInt();
            else if(stringTampon.isEmpty()) ajouter(nom.toStdString(), dosage, stock, commande);
        }
        in.reset();
        FileDatabase.close();
    }
    std::sort(m_listeAlcools.begin(), m_listeAlcools.end(), alcoolSortByName());
}

void ListAlcools::setNom(int index, std::string nom)
{
    (m_listeAlcools[index])->setNom(nom);
}

void ListAlcools::setDosage(int index, float dosage)
{
    (m_listeAlcools[index])->setDosage(dosage);
}

void ListAlcools::setZeroStock(int index, bool stock)
{
    (m_listeAlcools[index])->setZeroStock(stock);
}

void ListAlcools::setCommande(int index, bool commande)
{
    return (m_listeAlcools[index])->setCommande(commande);
}

//geters
int ListAlcools::getTaille() const
{
    return m_listeAlcools.size();
}

std::string ListAlcools::getNom(int index) const
{
    return (m_listeAlcools[index])->getNom();
}

float ListAlcools::getDosage(int index) const
{
    return (m_listeAlcools[index])->getDosage();
}

bool ListAlcools::getZeroStock(int index) const
{
    return (m_listeAlcools[index])->getZeroStock();
}

bool ListAlcools::getCommande(int index) const
{
    return (m_listeAlcools[index])->getCommande();
}
