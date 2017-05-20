#include "fenaddalcool.h"

void FenAddAlcool::genererCode()
{
    if(m_lineNomAlcool->text().isEmpty()) {
        QMessageBox::warning(this, windowTitle(), "Vous devez entrer un nom d'additif");
        return;
    }
    *m_nom = m_lineNomAlcool->text();
    *m_dosage = m_percent_alcool->value();
    *m_stock = m_cbStock->isChecked();
    *m_commande = m_cbCommande->isChecked();
}

FenAddAlcool::FenAddAlcool(QString &nom, float &dosage, bool &stock, bool &commande, QWidget *parent = 0) : m_nom{&nom}, m_dosage{&dosage}, m_stock{&stock}, m_commande{&commande}, QDialog{parent}
{
    this->setWindowTitle("Ajout d'un additif");
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *vboxFenAddAlcool = new QVBoxLayout;

    QFormLayout *formLayout = new QFormLayout();
    m_lineNomAlcool = new QLineEdit;
    formLayout->addRow("Nom : ", m_lineNomAlcool);
    m_percent_alcool = new QDoubleSpinBox;
        m_percent_alcool->setDecimals(1);
        m_percent_alcool->setSingleStep(0.1);
    formLayout->addRow("Pourcentage d'additif du eliquide : ", m_percent_alcool);
    vboxFenAddAlcool->addLayout(formLayout);
    QHBoxLayout *commandeLayout = new QHBoxLayout();
    m_cbStock = new QCheckBox("Épuisé");
    commandeLayout->addWidget(m_cbStock);
    m_cbCommande = new QCheckBox("Commander");
    commandeLayout->addWidget(m_cbCommande);
    vboxFenAddAlcool->addLayout(commandeLayout);

    m_envoyer = new QPushButton("Ajouter");
        m_envoyer->setAutoDefault(false);
    vboxFenAddAlcool->addWidget(m_envoyer);
    m_fermer = new QPushButton("Fermer");
        m_fermer->setAutoDefault(false);
    vboxFenAddAlcool->addWidget(m_fermer);

    setLayout(vboxFenAddAlcool);

    QObject::connect(m_fermer, SIGNAL(clicked(bool)), this, SLOT(accept()));
    QObject::connect(m_envoyer, SIGNAL(clicked(bool)), this, SLOT(genererCode()));
}
