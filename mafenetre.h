#ifndef MAFENETRE_H
#define MAFENETRE_H
#include <QApplication>
#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include <QString>
#include <QStringList>
#include <QPair>

#include <QFile>
#include <QTextStream>

#include <QPixmap>
#include <QPainter>
#include <QComboBox>
#include <QPrinter>
#include <QPrintDialog>

#include "fenaddarome.h"
#include "fenaddbase.h"
#include "fenaddalcool.h"
#include "fentextegenere.h"
#include "fenoptions.h"
#include "listaromes.h"
#include "listbases.h"
#include "listalcools.h"
#include "myqspinbox.h"

#include <QDebug>

class MaFenetre : public QWidget // On hérite de QWidget. Nous récupérons donc automatiquement toutes les propriétés de QWidget.
{
    Q_OBJECT
    //Q_IMPORT_PLUGIN(qjpeg)
public:
    MaFenetre();
    //void genererProduit(Product fiche);
    void initSequence();
    int getQuantiteAProduire();
    void setQuantiteAProduire(int quantite);
    void construireFenetre();
    void setComboListAromes();
    void setComboListBases();
    void setComboListAlcools();
    void xCopy(QString sourceFolder, QString destFolder, QString filtre, QString subDirs);
    float mlArome();
    float mlAlcool();
    float mlPg();
    float mlVg();
    int pcPg();
    int pcVg();
    float tauxNico();
    int GenererNumeroArome();
    int modeAffichageArome;
public slots:
    bool creerEtiquette();
    void enregistrer();
    void imprimer();
    void getListeCommande();
    void afficherArome(int index);
    void afficherBase(int index);
    void afficherAlcool(int index);
    void ajouterArome();
    void ajouterBase();
    void ajouterAlcool();
    void retirerArome();
    void retirerBase();
    void retirerAlcool();
    void modifierArome();
    void modifierBase();
    void modifierAlcool();
    void sauverListeAromes();
    void sauverListeBases();
    void sauverListeAlcools();
    void setFenAlcool();
    void exporterBase();
    void importerBase();
    void modifierOptions();
    void about();
//signals:
private:
    QPixmap *m_px;
    QLabel *m_imageArome;

    MyQSpinBox *m_qttMl;
    QPushButton *m_boutonCommandes;
    QPushButton *m_boutonEnregistrerImage;
    QPushButton *m_boutonImprimerEtiquette;
    QLabel *m_imageEtiquette;
    QPushButton *m_boutonExporterBase;
    QPushButton *m_boutonImporterBase;
    QPushButton *m_boutonOptions;
    QPushButton *m_boutonAbout;

    QPushButton *m_boutonAjouterArome;
    QPushButton *m_boutonSupprimerArome;
    QPushButton *m_boutonAppliquerArome;
    QPushButton *m_boutonSauverListeAromes;
    QComboBox *m_comboListAromes;
    QLineEdit *m_lineNomArome;
    QLineEdit *m_lineMarqueArome;
    QSpinBox *m_lineNumeroArome;
    QDoubleSpinBox *m_percentArome;
    QSpinBox *m_sbNoteArome;
    QCheckBox *m_cbStockArome;
    QCheckBox *m_cbCommandeArome;

    QLabel *m_imageBase;
    QPushButton *m_boutonAjouterBase;
    QPushButton *m_boutonSupprimerBase;
    QPushButton *m_boutonAppliquerBase;
    QPushButton *m_boutonSauverListeBases;
    QComboBox *m_comboListBases;
    QLineEdit *m_lineNomBase;
    MyQSpinBox *m_percent_pg;
    MyQSpinBox *m_percent_vg;
    QSpinBox *m_mg_nico;
    QCheckBox *m_cbStockBase;
    QCheckBox *m_cbCommandeBase;

    QWidget *m_alcool_widget;
    QCheckBox *m_cbAlcool;
    QLabel *m_imageAlcool;
    QPushButton *m_boutonAjouterAlcool;
    QPushButton *m_boutonSupprimerAlcool;
    QPushButton *m_boutonAppliquerAlcool;
    QPushButton *m_boutonSauverListeAlcools;
    QComboBox *m_comboListAlcools;
    QLineEdit *m_lineNomAlcool;
    QDoubleSpinBox *m_percentAlcool;
    QCheckBox *m_cbStockAlcool;
    QCheckBox *m_cbCommandeAlcool;

    int m_quantite;
    float m_gouteEnMl;
    QFile *m_FileParams;

    std::string m_pathBases{QString(QCoreApplication::applicationDirPath() + "/ressources/bases/bases.txt").toStdString()};
    std::string m_pathAromes{QString(QCoreApplication::applicationDirPath() + "/ressources/bases/aromes.txt").toStdString()};
    std::string m_pathAlcools{QString(QCoreApplication::applicationDirPath() + "/ressources/bases/alcools.txt").toStdString()};
    std::string m_pathImg{QString(QCoreApplication::applicationDirPath() + "/ressources/img/").toStdString()};

    ListAromes m_listeAromes;
    ListBases m_listeBases;
    ListAlcools m_listeAlcools;
};



#endif // MAFENETRE_H
