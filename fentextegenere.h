#ifndef FENTEXTEGENERE_H
#define FENTEXTEGENERE_H
#include <QtWidgets>

//FenCodeGenere.h : header de la fenêtre secondaire qui affiche le code généré ;

class FenTexteGenere : public QDialog // On hérite de <QWidget> (IMPORTANT)
{
    public:
    FenTexteGenere(QString &code, QWidget *parent);

    private:
    QTextEdit *codeGenere;
    QPushButton *fermer;
};

#endif // FENTEXTEGENERE_H
