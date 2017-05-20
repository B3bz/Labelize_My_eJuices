#include "fenaddarome.h"

void FenAddArome::genererCode()
{
    if(m_lineNom->text().isEmpty()) {
        QMessageBox::warning(this, windowTitle(), "Vous devez entrer un nom d'arôme");
        return;
    }
    else if(m_sbDosage->value()==0 && m_sbDosageGts->value()==0) {
        QMessageBox::warning(this, windowTitle(), "Vous devez entrer un dosage");
        return;
    }
    *m_numero = m_sbNumero->value();
    *m_nom = m_lineNom->text();
    *m_stock = m_cbStock->isChecked();
    *m_commande = m_cbCommande->isChecked();
    *m_fabricant = m_cbFabricant->currentText();
    if (m_sbDosage->value()!=0) *m_dosage = m_sbDosage->value();
    else *m_dosage = (m_volGoutte*float(m_sbDosageGts->value()))*10;
    *m_note = m_sbNote->value();
}

void FenAddArome::ajouterImage()
{
    QString path = QFileDialog::getOpenFileName(this, "Sélectionner une image", QString(), "Images (*.png *.gif *.jpg *.jpeg)");//path du fichier
    QString fileName = path.right(path.size() - path.lastIndexOf("/") - 1);//nom du fichier + ext
    if(QFile((QString::fromStdString(*m_pathImages)) + fileName).exists())//si le fichier existe déjà dans le dossier ressources/img
    {
        if (QMessageBox::Yes==(QMessageBox::warning(this, windowTitle(), ("Le fichier existe déjà. Voulez vous le remplacer ?"), QMessageBox::Yes | QMessageBox::No))) {
            QFile::copy(path, (QString::fromStdString(*m_pathImages)) + fileName);//on le remplace
        }//ou pas
    }
    else QFile::copy(path, (QString::fromStdString(*m_pathImages)) + fileName);//sinon on copie le fichier dans le dossier ressources/img
    *m_pathImage = QString::fromStdString(*m_pathImages) + fileName;//path du fichier copié
    QPixmap pxImageArome(*m_pathImage);//on tente une lecture

    if(pxImageArome.isNull()) // si le fichier n'est pas lu par QPixmap :
    {
        QString pathFichierConvertit(*m_pathImage);//on crée une copie du fichier extension .PNG
        pathFichierConvertit.remove(pathFichierConvertit.lastIndexOf("."), pathFichierConvertit.size());
        pathFichierConvertit.append(".png");
        QFile::copy(*m_pathImage, pathFichierConvertit);
        pxImageArome = pathFichierConvertit;//on tente une nouvelle lecture
        // si la conversion a réussi on suprime l'image au mauvais format
        if(!pxImageArome.isNull()) {
            QFile::remove(*m_pathImage);
            *m_pathImage = pathFichierConvertit;}
        else {
            /*
    if(pxImageArome.isNull()) // si le fichier n'est pas lu par QPixmap :
    {
        QImage tmpImage(*m_pathImage , "PNG");//on charge le fichier dans un QImage au format PNG
        QImage whiteImage(tmpImage.size(), QImage::Format_ARGB32_Premultiplied);//on crée une QImage de la même taille blanche
        whiteImage.fill(QColor(Qt::white).rgb());
        QPainter painter(&whiteImage);
        painter.drawImage(0, 0, tmpImage);//on écrit l'image  dans la trame blanche
        painter.end();
        //QImage::Format format = tmpImage.format();
        //qDebug() << format;
        //QImage image{tmpImage.convertToFormat(QImage::Format_ARGB32_Premultiplied)};
        //image  = image.convertToFormat(QImage::Format_Indexed8, Qt::ThresholdDither|Qt::AutoColor);
        pxImageArome = QPixmap::fromImage(whiteImage);//on tente une nouvelle lecture
        if(!pxImageArome.isNull()) {
            QString pathFichierConvertit(*m_pathImage);
            pathFichierConvertit.remove(pathFichierConvertit.lastIndexOf("."), pathFichierConvertit.size());
            pathFichierConvertit.append(".png");
            pxImageArome.save(pathFichierConvertit, "PNG"); // just as a test
            //QFile::copy(*m_pathImage, pathFichierConvertit);
            pxImageArome = pathFichierConvertit;
            // si la conversion a réussi on suprime l'image au mauvais format
            QFile::remove(*m_pathImage);
            *m_pathImage = pathFichierConvertit;
        }
        else {
            QMessageBox::critical(this, windowTitle(), "Le fichier image " + path + " est illisible.");
            //QFile::remove(pathFichierConvertit);// si la conversion a échoué
            QFile::remove(*m_pathImage);
            *m_pathImage = QString::fromStdString(*m_pathImages) + "eliquid.png"; // on affiche l'image générique jpg
        }
    }*/
            QFile::remove(pathFichierConvertit);// si la conversion a échoué
            QFile::remove(*m_pathImage);
            QMessageBox::critical(this, windowTitle(), "Le fichier image " + path + " est illisible.");
            *m_pathImage = QString::fromStdString(*m_pathImages) + "eliquid.png"; // on affiche l'image générique jpg
        }
    }
    float x = QPixmap(*m_pathImage).height();
    float y = QPixmap(*m_pathImage).width();
    float z=0;
    if(x>y) z = x/100;
    else z = y/100;
    m_labelImage->setPixmap(QPixmap(*m_pathImage).scaled(x/z,y/z, Qt::KeepAspectRatio));
    //m_labelImage->setPixmap(QPixmap(*m_pathImage).scaled(100, 100, Qt::KeepAspectRatio));
}

FenAddArome::FenAddArome(int &p_numero, QString &p_nom, bool &p_zeroStock, bool &p_commande, QString &p_fabricant, float &p_dosage, QString &p_pathImage, int &p_note, std::string &p_pathImages, const QStringList &listFabricants, const float p_gouteEnMl, QWidget *parent = 0) :
    m_numero{&p_numero}, m_nom{&p_nom}, m_stock{&p_zeroStock}, m_commande{&p_commande}, m_fabricant{&p_fabricant}, m_dosage{&p_dosage}, m_note{&p_note}, m_pathImage{&p_pathImage}, m_pathImages{&p_pathImages}, m_volGoutte{p_gouteEnMl}, QDialog{parent}
{
    *m_pathImage = QString::fromStdString(*m_pathImages) + "eliquid.png";
    this->setWindowTitle("Ajout d'un arôme");
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *vboxMainLayout = new QVBoxLayout;
    m_labelImage = new QLabel();
        m_labelImage->setAlignment(Qt::AlignCenter);
        m_labelImage->setPixmap(QPixmap(*m_pathImage).scaled(100,100,Qt::KeepAspectRatio));
    vboxMainLayout->addWidget(m_labelImage);
    m_selectImage = new QPushButton("Selectionner une image");
        m_selectImage->setAutoDefault(false);
    vboxMainLayout->addWidget(m_selectImage);

    QFormLayout *formLayout = new QFormLayout();

    m_lineNom = new QLineEdit;
    formLayout->addRow("Nom : ", m_lineNom);
    m_cbFabricant = new QComboBox;
        m_cbFabricant->addItems(listFabricants);
        m_cbFabricant->setEditable(true);
    formLayout->addRow("Marque : ", m_cbFabricant);
    m_sbNumero = new QSpinBox;
        m_sbNumero->setMaximum(999);
        m_sbNumero->setValue(p_numero);
    formLayout->addRow("Numéro : ", m_sbNumero);
    m_sbDosage = new MyQDoubleSpinBox;
        m_sbDosage->setDecimals(1);
        m_sbDosage->setSingleStep(0.5);
    formLayout->addRow("Pourcentage d'arôme dans le eLiquide: ", m_sbDosage);
    m_sbDosageGts = new MyQSpinBox;
        m_sbDosageGts->setMaximum(40);
    formLayout->addRow("Ou nombre de gouttes d'arôme pour 10ml: ", m_sbDosageGts);
    m_sbNote = new QSpinBox;
        m_sbNote->setMaximum(5);
    formLayout->addRow("Note / 5 : ", m_sbNote);
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
    QObject::connect(m_selectImage, SIGNAL(clicked(bool)), this, SLOT(ajouterImage()));
    QObject::connect(m_sbDosage, SIGNAL(valueChanged(double)), m_sbDosageGts, SLOT(valeurZero(double)));
    QObject::connect(m_sbDosageGts, SIGNAL(valueChanged(int)), m_sbDosage, SLOT(valeurZero(int)));
}
