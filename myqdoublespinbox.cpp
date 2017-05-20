#include "myqdoublespinbox.h"

MyQDoubleSpinBox::MyQDoubleSpinBox()
{

}

void MyQDoubleSpinBox::valeurZero(int valeurRecue)
{
    if(valeurRecue!=0) this->setDisabled(true);
    else this->setDisabled(false);
}
