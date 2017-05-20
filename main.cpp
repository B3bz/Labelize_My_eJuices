#include "mafenetre.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MaFenetre *fenetre = new MaFenetre();
    fenetre->show();

    return app.exec();
}
