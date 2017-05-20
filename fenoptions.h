#ifndef FENOPTIONS_H
#define FENOPTIONS_H

#include <QtWidgets>

class FenOptions : public QDialog // On hérite de <QWidget> (IMPORTANT)
{
    Q_OBJECT
public:
    FenOptions(int p_qtt, float p_volGoutte, int p_modeAffichageArome, QWidget *parent);

public slots:
    void enregistrer();

private:

    QSpinBox *m_sbQtt;
    QDoubleSpinBox *m_sbVolGoutte;
    QRadioButton *m_numero;
    QRadioButton *m_marque;
    QRadioButton *m_rien;

    QPushButton *m_enregistrer;
    QPushButton *m_fermer;
};

#endif // FENOPTIONS_H
