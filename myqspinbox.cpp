#include "myqspinbox.h"

MyQSpinBox::MyQSpinBox() : QSpinBox()
{
}

void MyQSpinBox::valeurChage(int nouvelleValeur)
{
    this->setValue(100-nouvelleValeur);
}

void MyQSpinBox::valeurZero(double valeurRecue)
{
    if(valeurRecue!=0) this->setDisabled(true);
    else this->setDisabled(false);
}
