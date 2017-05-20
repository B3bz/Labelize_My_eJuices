#ifndef MYQSPINBOX_H
#define MYQSPINBOX_H

#include <QSpinBox>

class MyQSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    MyQSpinBox();

public slots:
    void valeurChage(int nouvelleValeur);
    void valeurZero(double valeurRecue);
};

#endif // MYQSPINBOX_H
