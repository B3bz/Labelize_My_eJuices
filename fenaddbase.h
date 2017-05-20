#ifndef FENADDBASE_H
#define FENADDBASE_H
#include <QtWidgets>
#include "myqspinbox.h"

class FenAddBase : public QDialog // On hérite de <QWidget> (IMPORTANT)
{
    Q_OBJECT
public:
    FenAddBase(QString &p_nom, bool &p_zeroStock, bool &p_commande, int &p_pg, int &p_nico, QWidget *parent);

public slots:
    void genererCode();

private:
    QString *m_nom;
    bool *m_stock;
    bool *m_commande;
    int *m_pg;
    int *m_nico;
    QLineEdit *m_lineNom;
    MyQSpinBox *m_sbPg;
    MyQSpinBox *m_sbVg;
    QSpinBox *m_sbNico;
    QCheckBox *m_cbStock;
    QCheckBox *m_cbCommande;
    QPushButton *m_envoyer;
    QPushButton *m_fermer;
};

#endif // FENADDBASE_H
