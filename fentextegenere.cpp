#include "fentextegenere.h"

FenTexteGenere::FenTexteGenere(QString &code, QWidget *parent = 0) : QDialog(parent)
{
    this->setWindowIcon(QIcon(":order.png"));
    this->setWindowTitle("Liste de commandes");
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    codeGenere = new QTextEdit();
    codeGenere->setPlainText(code);//gets and sets the text editor's contents as plain text
    codeGenere->setReadOnly(true);//the text edit is read-only.
    codeGenere->setFont(QFont("Courier"));
    codeGenere->setLineWrapMode(QTextEdit::NoWrap);

    fermer = new QPushButton("Fermer");

    QVBoxLayout *vboxFenCodeGenere = new QVBoxLayout;
    vboxFenCodeGenere->addWidget(codeGenere);
    vboxFenCodeGenere->addWidget(fermer);

    resize(350, 450);

    setLayout(vboxFenCodeGenere);

    QObject::connect(fermer, SIGNAL(clicked()), this, SLOT(accept()));
}
