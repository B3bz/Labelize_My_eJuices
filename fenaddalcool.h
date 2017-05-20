#ifndef FENADDALCOOL_H
#define FENADDALCOOL_H
#include <QtWidgets>

class FenAddAlcool : public QDialog // On hérite de <QWidget> (IMPORTANT)
{
    Q_OBJECT
public:
    FenAddAlcool(QString &nom, float &dosage, bool &stock, bool &commande, QWidget *parent);

public slots:
    void genererCode();

private:
    QString *m_nom;
    float *m_dosage;
    bool *m_stock;
    bool *m_commande;
    QLineEdit *m_lineNomAlcool;
    QDoubleSpinBox *m_percent_alcool;
    QCheckBox *m_cbStock;
    QCheckBox *m_cbCommande;
    QPushButton *m_envoyer;
    QPushButton *m_fermer;
};
#endif // FENADDALCOOL_H
