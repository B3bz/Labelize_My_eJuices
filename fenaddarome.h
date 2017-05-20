#ifndef FENADDAROME_H
#define FENADDAROME_H
#include <QtWidgets>
#include "myqspinbox.h"
#include "myqdoublespinbox.h"

class FenAddArome : public QDialog // On hérite de <QWidget> (IMPORTANT)
{
    Q_OBJECT
public:
    FenAddArome(int &p_numero, QString &p_nom, bool &p_zeroStock, bool &p_commande, QString &p_fabricant, float &p_dosage, QString &p_pathImage, int &p_note, std::string &p_pathImages, const QStringList &listFabricants, const float p_gouteEnMl, QWidget *parent);

public slots:
    void genererCode();
    void ajouterImage();

private:
    int *m_numero;
    QString *m_nom;
    bool *m_stock;
    bool *m_commande;
    QString *m_fabricant;
    float *m_dosage;
    float m_volGoutte;
    QString *m_pathImage;
    int *m_note;

    QLabel *m_labelImage;
    QSpinBox *m_sbNumero;
    QLineEdit *m_lineNom;
    QCheckBox *m_cbStock;
    QCheckBox *m_cbCommande;
    QComboBox *m_cbFabricant;
    MyQDoubleSpinBox *m_sbDosage;
    MyQSpinBox *m_sbDosageGts;
    QPushButton *m_selectImage;
    QSpinBox *m_sbNote;
    std::string *m_pathImages;

    QPushButton *m_envoyer;
    QPushButton *m_fermer;
};

#endif // FENADDAROME_H
