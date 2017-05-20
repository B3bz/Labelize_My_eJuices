#ifndef MYQDOUBLESPINBOX_H
#define MYQDOUBLESPINBOX_H

#include <QDoubleSpinBox>

class MyQDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    MyQDoubleSpinBox();

public slots:
    void valeurZero(int valeurRecue);
};

#endif // MYQDOUBLESPINBOX_H
