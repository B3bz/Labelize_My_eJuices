#include "listaromes.h"

//constructeurs
ListAromes::ListAromes()
{
}

ListAromes::~ListAromes()
{
}

/*
void ListAromes::ajouterArome(Arome *arome)
{
    m_listeAromes.push_back(new Arome(arome->getNumero(),
                                      arome->getNom(),
                                      arome->getFabricant(),
                                      arome->getDosage(),
                                      arome->getImage(),
                                      arome->getZeroStock(),
                                      arome->getCommande(),
                                      arome->getNote()));
}

*/

//seters
void ListAromes::importList(std::string pathAromes)
{
    QFile FileDatabase(QString::fromStdString(pathAromes));
    QString stringTampon;
    if (!FileDatabase.open(QIODevice::ReadOnly | QIODevice::Text)) {return;}
    else
    {
        QTextStream in(&FileDatabase);// Création d'un objet QTextStream raccordé à objet QFile
        const QPair<QString, int> patternNum         { "[NUMERO]", 9 }; // on recherche le motif, index du premier caractère de la valeur à récupérer
        const QPair<QString, int> patternNom         { "[NOM]", 6 };
        const QPair<QString, int> patternFab         { "[FABRICANT]", 12 };
        const QPair<QString, int> patternPc          { "[POURCENTAGE]", 14 };
        const QPair<QString, int> patternImg         { "[IMAGE]", 8 };
        const QPair<QString, int> patternStock       { "[0STOCK]", 9 };
        const QPair<QString, int> patternCommande    { "[COMMANDE]", 11 };
        const QPair<QString, int> patternNote        { "[NOTE]", 7 };
        QString nom{"temp"}, image{"temp"}, fabricant{"temp"};
        int numero {0}, note {0};
        float dosage {0.0};
        bool stock {false}, commande {false};
        while (!in.atEnd())//on lis le fichier ligne par ligne jusqu'au bout
        {
            stringTampon = in.readLine();
            if(stringTampon.contains(patternNum.first)) numero = stringTampon.right(stringTampon.size()-patternNum.second).toInt();
            else if(stringTampon.contains(patternNom.first)) {nom = stringTampon.right(stringTampon.size()-patternNom.second);
                nom[0] = nom[0].toUpper();}
            else if(stringTampon.contains(patternFab.first)) fabricant = stringTampon.right(stringTampon.size()-patternFab.second);
            else if(stringTampon.contains(patternPc.first)) dosage = stringTampon.right(stringTampon.size()-patternPc.second).toFloat();
            else if(stringTampon.contains(patternImg.first)) image = (QCoreApplication::applicationDirPath() + "/ressources/img/" + stringTampon.right(stringTampon.size()-patternImg.second));
            else if(stringTampon.contains(patternStock.first)) stock = stringTampon.right(stringTampon.size()-patternStock.second).toInt();
            else if(stringTampon.contains(patternCommande.first)) commande = stringTampon.right(stringTampon.size()-patternCommande.second).toInt();
            else if(stringTampon.contains(patternNote.first)) note = stringTampon.right(stringTampon.size()-patternNote.second).toInt();
            else if(stringTampon.isEmpty()) ajouter(numero, nom.toStdString(), stock, commande, fabricant.toStdString(), dosage, image.toStdString(), note);
        }
        in.reset();
        FileDatabase.close();
    }
    std::sort(m_listeAromes.begin(), m_listeAromes.end(), sortByName());
}

void ListAromes::ajouter(int p_numero, std::string p_nom, bool p_zeroStock, bool p_commande, std::string p_fabricant, float p_dosage, std::string p_path, int p_note)
{
    m_listeAromes.push_back(new Arome(p_numero, p_nom, p_zeroStock, p_commande, p_fabricant, p_dosage, p_path, p_note));
}

void ListAromes::retirer(int index)
{
    m_listeAromes.erase(m_listeAromes.begin()+index);
}

void ListAromes::setImage(int index, std::string path)
{
    return (m_listeAromes[index])->setImage(path);
}

void ListAromes::setNumero(int index, int numero)
{
    (m_listeAromes[index])->setNumero(numero);
}

void ListAromes::setNom(int index, std::string nom)
{
    (m_listeAromes[index])->setNom(nom);
}

void ListAromes::setZeroStock(int index, bool stock)
{
    (m_listeAromes[index])->setZeroStock(stock);
}

void ListAromes::setCommande(int index, bool commande)
{
    (m_listeAromes[index])->setCommande(commande);
}

void ListAromes::setFabricant(int index, std::string fabricant)
{
    (m_listeAromes[index])->setFabricant(fabricant);
}

void ListAromes::setDosage(int index, float dosage)
{
    (m_listeAromes[index])->setDosage(dosage);
}

void ListAromes::setNote(int index, int note)
{
    (m_listeAromes[index])->setNote(note);
}

//geters
int ListAromes::getTaille() const
{
    return m_listeAromes.size();
}

int ListAromes::getNumero(int index) const
{
    return (m_listeAromes[index])->getNumero();
}

std::string ListAromes::getNom(int index) const
{
    return (m_listeAromes[index])->getNom();
}

std::string ListAromes::getFabricant(int index) const
{
    return (m_listeAromes[index])->getFabricant();
}

float ListAromes::getDosage(int index) const
{
    return (m_listeAromes[index])->getDosage();
}

std::string ListAromes::getImage(int index) const
{
    return (m_listeAromes[index])->getImage();
}

bool ListAromes::getZeroStock(int index) const
{
    return (m_listeAromes[index])->getZeroStock();
}

bool ListAromes::getCommande(int index) const
{
    return (m_listeAromes[index])->getCommande();
}

int ListAromes::getNote(int index) const
{
    return (m_listeAromes[index])->getNote();
}
