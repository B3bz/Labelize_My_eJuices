#include "fenaddbase.h"

void FenAddBase::genererCode()
{
    if(m_lineNom->text().isEmpty()) {
        QMessageBox::warning(this, windowTitle(), "Vous devez entrer un nom pour la base");
        return;
    }
    *m_nom = m_lineNom->text();
    *m_pg = m_sbPg->value();
    *m_nico = m_sbNico->value();
    *m_stock = m_cbStock->isChecked();
    *m_commande = m_cbCommande->isChecked();
}

FenAddBase::FenAddBase(QString &p_nom, bool &p_zeroStock, bool &p_commande, int &p_pg, int &p_nico, QWidget *parent = 0) : m_nom{&p_nom}, m_stock{&p_zeroStock}, m_commande{&p_commande}, m_pg{&p_pg}, m_nico{&p_nico}, QDialog{parent}
{
    this->setWindowTitle("Ajout d'une base");
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *vboxMainLayout = new QVBoxLayout;

    QFormLayout *formLayout = new QFormLayout();
    m_lineNom = new QLineEdit;
        m_lineNom->setText("Base");
    formLayout->addRow("Nom : ", m_lineNom);
    m_sbPg = new MyQSpinBox;
        m_sbPg->setMaximum(100);
        m_sbPg->setValue(50);
    formLayout->addRow("Pourcentage de pg dans la base : ", m_sbPg);
    m_sbVg = new MyQSpinBox;
        m_sbVg->setMaximum(100);
        m_sbVg->setValue(50);
    formLayout->addRow("Pourcentage de vg dans la base : ", m_sbVg);
    m_sbNico = new QSpinBox;
        m_sbNico->setMaximum(100);
    formLayout->addRow("mg/ml de nicotine dans la base : ", m_sbNico);
    vboxMainLayout->addLayout(formLayout);
    QHBoxLayout *commandeLayout = new QHBoxLayout();
    m_cbStock = new QCheckBox("Épuisé");
    commandeLayout->addWidget(m_cbStock);
    m_cbCommande = new QCheckBox("Commander");
    commandeLayout->addWidget(m_cbCommande);
    vboxMainLayout->addLayout(commandeLayout);

    m_envoyer = new QPushButton("Ajouter");
        m_envoyer->setAutoDefault(false);
    vboxMainLayout->addWidget(m_envoyer);
    m_fermer = new QPushButton("Fermer");
        m_fermer->setAutoDefault(false);
    vboxMainLayout->addWidget(m_fermer);

    setLayout(vboxMainLayout);

    QObject::connect(m_fermer, SIGNAL(clicked(bool)), this, SLOT(accept()));
    QObject::connect(m_envoyer, SIGNAL(clicked(bool)), this, SLOT(genererCode()));
    QObject::connect(m_sbPg, SIGNAL(valueChanged(int)), m_sbVg, SLOT(valeurChage(int)));
    QObject::connect(m_sbVg, SIGNAL(valueChanged(int)), m_sbPg, SLOT(valeurChage(int)));
}
