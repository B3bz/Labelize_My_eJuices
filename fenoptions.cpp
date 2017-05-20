#include "fenoptions.h"

//Création du fichier INI
void FenOptions::enregistrer(){
    const QString pathFileParams {QCoreApplication::applicationDirPath() + "/PARAM.INI"};
    QFile fileParams(pathFileParams);
    QString stringTampon;
    if (!QFile(pathFileParams).exists()){
        QMessageBox::information(this, "Fichier introuvable", "Le fichier " + pathFileParams + " n'a pas été trouvé.\nCréation d'un fichier PARAM.INI par défaut.");
        QFile::copy(":PARAM.INI", QCoreApplication::applicationDirPath() + "/PARAM.INI");
    }
    if (!fileParams.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Fichier illisible", "Le fichier " + pathFileParams + " n'est pas accessible.\nSortie de l'application.");
        return;
    }
    else
    {
        QTextStream out(&fileParams);// Création d'un objet QTextStream raccordé à objet QFile
        out << "[QUANTITE]=" + QString::number(m_sbQtt->value()) + "\n\n[VOLGOUTTE]=" + QString::number(m_sbVolGoutte->value()) + "\n\n[AFFICHAGE AROME]=";
        if (m_numero->isChecked()) out << "0\n";
        else if(m_marque->isChecked()) out << "1\n";
        else out << "2\n";
        out.reset();
        fileParams.close();
        QMessageBox::information(this, "Modifications effectuées", "Vous devez relancer le programme afin de prendre en compte les modifications.");
    }
}

FenOptions::FenOptions(int p_qtt, float p_volGoutte, int p_modeAffichageArome, QWidget *parent = 0) : QDialog{parent}
{
    this->setWindowTitle("Options");
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *vboxMainLayout = new QVBoxLayout;

    QFormLayout *formLayout = new QFormLayout();
    m_sbQtt = new QSpinBox;
        m_sbQtt->setValue(p_qtt);
    formLayout->addRow("Quantité à produire par défaut : ", m_sbQtt);
    m_sbVolGoutte = new QDoubleSpinBox;
        m_sbVolGoutte->setSingleStep(0.001);
        m_sbVolGoutte->setDecimals(3);
        m_sbVolGoutte->setValue(p_volGoutte);
    formLayout->addRow("Volume d'une goutte (en ml) : ", m_sbVolGoutte);
    vboxMainLayout->addLayout(formLayout);

    QGroupBox *groupbox = new QGroupBox("Affichage dans l'étiquette");
    m_numero = new QRadioButton("Numéro de l'arôme");
    m_marque = new QRadioButton("Marque de l'arôme");
    m_rien = new QRadioButton("Ne pas afficher");
    if(p_modeAffichageArome==0) m_numero->setChecked(true);
    else if(p_modeAffichageArome==1) m_marque->setChecked(true);
    else m_rien->setChecked(true);
    QVBoxLayout *groupboxLayout = new QVBoxLayout;
    groupboxLayout->addWidget(m_numero);
    groupboxLayout->addWidget(m_marque);
    groupboxLayout->addWidget(m_rien);
    groupbox->setLayout(groupboxLayout);
    vboxMainLayout->addWidget(groupbox);

    m_enregistrer = new QPushButton("Enregistrer");
        m_enregistrer->setAutoDefault(false);
    vboxMainLayout->addWidget(m_enregistrer);
    m_fermer = new QPushButton("Fermer");
        m_fermer->setAutoDefault(false);
    vboxMainLayout->addWidget(m_fermer);

    setLayout(vboxMainLayout);

    QObject::connect(m_enregistrer, SIGNAL(clicked(bool)), this, SLOT(enregistrer()));
    QObject::connect(m_fermer, SIGNAL(clicked(bool)), this, SLOT(accept()));
}
