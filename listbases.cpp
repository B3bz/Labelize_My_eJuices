#include "listbases.h"

ListBases::ListBases()
{
}

ListBases::~ListBases()
{
}

void ListBases::ajouter(std::string p_nom, bool p_zeroStock, bool p_commande, int p_pg, int p_nico)
{
    m_listeBases.push_back(new Base(m_listeBases.size(), p_nom, p_zeroStock, p_commande, p_pg, p_nico));
}

void ListBases::retirer(int index)
{
    m_listeBases.erase(m_listeBases.begin()+index);

}
void ListBases::importList(std::string pathBases)
{
    QFile FileDatabase(QString::fromStdString(pathBases));
    QString stringTampon;
    if (!FileDatabase.open(QIODevice::ReadOnly | QIODevice::Text)) {return;}
    else
    {
        QTextStream in(&FileDatabase);// Création d'un objet QTextStream raccordé à objet QFile
        //const QPair<QString, int> patternNum         { "[NUMERO]", 9 }; // on recherche le motif, index du premier caractère de la valeur à récupérer
        const QPair<QString, int> patternNom         { "[NOM]", 6 };
        const QPair<QString, int> patternPg          { "[TAUXPG]", 9 };
        const QPair<QString, int> patternNico        { "[TAUXNICO]", 11 };
        const QPair<QString, int> patternStock       { "[0STOCK]", 9 };
        const QPair<QString, int> patternCommande    { "[COMMANDE]", 11 };
        QString nom{"temp"};
        int pg{0}, nico{0};//numero{0},
        bool stock {false}, commande {false};
        while (!in.atEnd())//on lis le fichier ligne par ligne jusqu'au bout
        {
            stringTampon = in.readLine();
            //if(stringTampon.contains(patternNum.first)) numero = stringTampon.right(stringTampon.size()-patternNum.second).toInt();
            if(stringTampon.contains(patternNom.first)) {nom = stringTampon.right(stringTampon.size()-patternNom.second);
                nom[0] = nom[0].toUpper();}
            else if(stringTampon.contains(patternPg.first)) pg = stringTampon.right(stringTampon.size()-patternPg.second).toInt();
            else if(stringTampon.contains(patternNico.first)) nico = stringTampon.right(stringTampon.size()-patternNico.second).toInt();
            else if(stringTampon.contains(patternStock.first)) stock = stringTampon.right(stringTampon.size()-patternStock.second).toInt();
            else if(stringTampon.contains(patternCommande.first)) commande = stringTampon.right(stringTampon.size()-patternCommande.second).toInt();
            else if(stringTampon.isEmpty()) ajouter(nom.toStdString(), stock, commande, pg, nico);
        }
        in.reset();
        FileDatabase.close();
    }
    std::sort(m_listeBases.begin(), m_listeBases.end(), baseSortByName());
}

void ListBases::setNom(int index, std::string nom)
{
    (m_listeBases[index])->setNom(nom);
}

void ListBases::setZeroStock(int index, bool stock)
{
    (m_listeBases[index])->setZeroStock(stock);
}

void ListBases::setCommande(int index, bool commande)
{
    (m_listeBases[index])->setCommande(commande);
}

void ListBases::setPg(int index, int pg)
{
    (m_listeBases[index])->setPg(pg);
}

void ListBases::setNico(int index, int nico)
{
    (m_listeBases[index])->setNico(nico);
}

//geters
int ListBases::getTaille() const
{
    return m_listeBases.size();
}

int ListBases::getNumero(int index) const
{
    return (m_listeBases[index])->getNumero();
}

std::string ListBases::getNom(int index) const
{
    return (m_listeBases[index])->getNom();
}

int ListBases::getPg(int index) const
{
    return (m_listeBases[index])->getPg();
}

int ListBases::getVg(int index) const
{
    return (m_listeBases[index])->getVg();
}

int ListBases::getNico(int index) const
{
    return (m_listeBases[index])->getNico();
}

bool ListBases::getZeroStock(int index) const
{
    return (m_listeBases[index])->getZeroStock();
}

bool ListBases::getCommande(int index) const
{
    return (m_listeBases[index])->getCommande();
}
