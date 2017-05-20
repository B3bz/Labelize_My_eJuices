#include "mafenetre.h"

//à propos
void MaFenetre::about(){
    QMessageBox qmsgb;// QMessageBox::about(this, "À propos", "<strong>Labelize my eJuices</strong>").setIconPixmap(QPixmap(":etiquette.png"));
    qmsgb.setIconPixmap(QPixmap(":eliquid2.png"));
    qmsgb.setText("<p align='center'><strong>Labelize my eJuices</strong><br>""Version 1.2.160920<br>""labelize.my.ejuices@gmail.com<br>""Freeware basé sur Qt.</p>");
    qmsgb.setWindowTitle("À propos");
    qmsgb.exec();
}

//calculs
/*
float MaFenetre::mlPg(){// ((qtt à produire - qtt d'arome) * %pg / 100) + qtt d'arome
    if(m_cbAlcool->isChecked()) return ((this->m_qttMl->value()-(mlArome()+mlAlcool()))*m_percent_pg->value()/100)+mlArome();
    else return ((this->m_qttMl->value()-mlArome())*m_percent_pg->value()/100)+mlArome();
}

float MaFenetre::mlVg(){// (qtt à produire - qtt d'arome) * %vg / 100
    if(m_cbAlcool->isChecked()) return ((this->m_qttMl->value()-(mlArome()+mlAlcool()))*m_percent_vg->value()/100);
    else return ((this->m_qttMl->value()-mlArome())*m_percent_vg->value()/100);
}

int MaFenetre::pcPg(){
    if(m_cbAlcool->isChecked()) return 100*mlPg()/(mlPg()+mlVg()+mlAlcool());
    else return 100*mlPg()/(mlPg()+mlVg());
}
*/
float MaFenetre::mlArome(){// %arome * qtt à produire / 100
    return this->m_percentArome->value()*((float)(m_qttMl->value()))/100;
}

float MaFenetre::mlAlcool(){// %alcool * qtt à produire / 100
    return this->m_percentAlcool->value()*((float)(m_qttMl->value()))/100;
}

float MaFenetre::mlPg(){// ((qtt à produire - qtt d'arome) * %pg / 100) + qtt d'arome
    return ((this->m_qttMl->value()-mlArome())*m_percent_pg->value()/100)+mlArome();
}

float MaFenetre::mlVg(){// (qtt à produire - qtt d'arome) * %vg / 100
    return ((this->m_qttMl->value()-mlArome())*m_percent_vg->value()/100);
}

int MaFenetre::pcPg(){
    return 100*mlPg()/(mlPg()+mlVg());
}

int MaFenetre::pcVg(){
    return 100-pcPg();
}

float MaFenetre::tauxNico(){
    float result = m_mg_nico->value()*(1-m_percentArome->value()/100);
    return round(result * 10) / 10.0;
}

//affichage d'une fiche
bool MaFenetre::creerEtiquette(){
    /*
    static int comboListAromesValue;//, SIGNAL(currentIndexChanged(int)
    static int lineNumeroAromeValue;//, SIGNAL(valueChanged(int)), this, SLOT(creerEtiquette()));
    static double percentAromeValue;//, SIGNAL(valueChanged(double)
    //static QString lineNomAromeValue;//, SIGNAL(textEdited(QString))

    if(lineNumeroAromeValue==m_lineNumeroArome->value() && percentAromeValue==m_percentArome->value())
    {
        return;
    }
    if(comboListAromesValue!=m_comboListAromes->currentIndex())// && lineNumeroAromeValue!=m_lineNumeroArome->value())// && percentAromeValue!=m_percentArome->value()) && lineNomAromeValue!=m_lineNomArome->text())
    {
        lineNumeroAromeValue=m_lineNumeroArome->value();
        percentAromeValue=m_percentArome->value();
    }
    */
    bool correction{false};
    const int indexArome = m_comboListAromes->currentIndex();
    const QString pathFileTrame {":/etiquette.png"};
    int y1{30}, y2{48};
    if(m_cbAlcool->isChecked()) {y1 = 26; y2 = 39;}
    //création de l'étiquette
    m_px = new QPixmap(pathFileTrame); // import de la trame
    if(m_listeAromes.getTaille()>0) // Si la base arôme s'est pas vide on affiche la fiche
    {
        QPainter painter(m_px);
        QPixmap pxImageArome(QString::fromStdString(this->m_listeAromes.getImage(indexArome)));
        if(pxImageArome.isNull()) // si le fichier n'est pas lu par QPixmap :
        {
            //si le fichier existe on tente une conversion jpg
            if(QFile(QString::fromStdString(this->m_listeAromes.getImage(indexArome))).exists())
            {
                QString nomFichier(QString::fromStdString(this->m_listeAromes.getImage(indexArome)));
                nomFichier.remove(nomFichier.lastIndexOf("."), nomFichier.size());
                nomFichier.append(".png");
                QFile::copy(QString::fromStdString(this->m_listeAromes.getImage(indexArome)), nomFichier);
                m_imageArome->setPixmap(QPixmap(nomFichier).scaled(100,100,Qt::KeepAspectRatio));
                pxImageArome = nomFichier;
                if(!pxImageArome.isNull()) // si la conversion a réussi
                { // on affiche le fichier convertis
                    int choix = QMessageBox::warning(this, windowTitle(), "Erreur corrigée sur le fichier image de l'arome " + QString::fromStdString(this->m_listeAromes.getNom(indexArome)) + "\nVoulez vous sauvegarder la base ?", QMessageBox::Yes | QMessageBox::No);
                    if(choix == QMessageBox::Yes)
                    {
                        QFile::remove(QString::fromStdString(this->m_listeAromes.getImage(indexArome)));//on suprime l'image au mauvais format
                        m_listeAromes.setImage(indexArome, nomFichier.toStdString());// on corrige la base
                        sauverListeAromes();// et on la sauvegarde
                        correction = true;
                    }
                    else if(choix == QMessageBox::No)
                    {
                        QFile::remove(nomFichier); //sinon on suprime le fichier convertis
                    }
                }
                else QFile::remove(nomFichier);// si la conversion a échoué
            }
            if(!QFile(QString::fromStdString(this->m_listeAromes.getImage(indexArome))).exists() || pxImageArome.isNull())//si le fichier n'existe pas ou ne s'affiche pas
            {
                QMessageBox::critical(this, windowTitle(), "Le fichier image " + QString::fromStdString(this->m_listeAromes.getImage(indexArome)) + " de l'arôme " + QString::fromStdString(this->m_listeAromes.getNom(indexArome)) + " n'existe pas ou est illisible.");
                pxImageArome = QString::fromStdString(m_pathImg) + "eliquid.png"; // on affiche l'image générique jpg
                m_imageArome->setPixmap(QPixmap(":eliquid.png"));
            }
        }
        painter.drawPixmap(1,1,69,69, pxImageArome); // import de l'image arôme
        //nom arôme
        if(this->m_lineNomArome->text().size()<18) painter.setFont(QFont("Arial", 10));
        else painter.setFont(QFont("Arial", 9));
        painter.drawText(QPoint(75, 13), this->m_lineNomArome->text());
        //N° arôme et dosage
        painter.setFont(QFont("Arial", 8));
        if (modeAffichageArome==0) painter.drawText(QPoint(75, y1), "Numéro " + QString::number(this->m_lineNumeroArome->value()));
        else if (modeAffichageArome==1) painter.drawText(QPoint(75, y1), this->m_lineMarqueArome->text());
        if(int(mlArome()/m_gouteEnMl)<200)
            painter.drawText(QPoint(75, y2), QString::number(this->m_percentArome->value()) + "% = " + QString::number(mlArome(), 'f', 2) + "ml ≈ " + QString::number(mlArome()/m_gouteEnMl, 'f', 0 ) + "gts");
        else
            painter.drawText(QPoint(75, y2), QString::number(this->m_percentArome->value()) + "% = " + QString::number(mlArome(), 'f', 2) + "ml");
        //Alcool
        if(m_cbAlcool->isChecked()){
            painter.drawText(QPoint(75, 52), this->m_lineNomAlcool->text() + " " + QString::number(mlAlcool()/m_gouteEnMl, 'f', 0 ) + "gts");
        }
        //ratio pg/vg du mélange
        painter.setFont(QFont("Arial", 7));
        //if(m_cbAlcool->isChecked()) painter.drawText(QPoint(75, 65), "PG/VG " + QString::number((round(pcPg()-(m_percentAlcool->value()/2))*10)/10.0) + "/" + QString::number((round(pcVg()-(m_percentAlcool->value()/2))*10)/10.0));
        //else
        painter.drawText(QPoint(75, 65), "PG/VG " + QString::number(pcPg()) + "/" + QString::number(pcVg()));
        painter.drawText(QPoint(140, 65), "Nicotine " + QString::number(tauxNico()));
        //fin de création de l'étiquette
        painter.end();
    }
    m_imageEtiquette->setPixmap(*m_px);
    /*
    comboListAromesValue=m_comboListAromes->currentIndex();
    lineNumeroAromeValue=m_lineNumeroArome->value();
    percentAromeValue=m_percentArome->value();
    */
    return correction;
}

void MaFenetre::xCopy(QString sourceFolder, QString destFolder, QString filtre, QString subDirs)
/*----------------------------------------------------------------------------------------------+
 | Copie d'une arborescence selon des filtres.                                                  |
 +----------------------------------------------------------------------------------------------+
 | QString filtre  : filtre de type  *   *.ini   ficher.*    fichier.xls     ...                |
 | QString subDirs : inclus ou non les sous répertoires                                         |
 |_____________________________________________________________________________________________*/
{
// variables et progress widgets
    QString stringTampon, fileTarget;
    // création du filtre de fichiers
    QStringList listFiltres;
    listFiltres << filtre;

    //on map le dossier à traiter
    QDir sourceDir(sourceFolder);
    //on applique le filtre de fichiers
    sourceDir.setNameFilters(listFiltres);

// création du dossier de destination
    QDir destDir(destFolder);
    if(!destDir.exists()) {destDir.mkdir(destFolder);}

// filtre de fichiers
    //on crée une liste des fichiers à copier pour le répertoire en cours
    QStringList fileList = sourceDir.entryList(QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot);// | QDir::NoSymLinks

// lecture de la liste de copie
    foreach(stringTampon, fileList) {//copie du fichier en cours dans le tampon
        // copie et indicateurs
        if (QFile::exists(destFolder + "/" + stringTampon)) QFile::remove(destFolder + "/" + stringTampon);
        QFile::copy(sourceFolder + "/" + stringTampon, destFolder + "/" + stringTampon);}//on copie le fichier
// méthode de copie avec sous repertoires
    if (subDirs=="Y") {
        //on crée une liste de strings contenant le nom des dossiers à copier pour le répertoire en cours
        QStringList dirsList = sourceDir.entryList(QDir::AllDirs | QDir::Hidden | QDir::NoDotAndDotDot); //  | QDir::NoSymLinks
        //on répète cette boucle pour chaque sous dossier
        foreach (stringTampon, dirsList) {
            // on relance xcopy sur ce dossier
            QString srcName = sourceFolder + "/" + stringTampon;
            QString destName = destFolder + "/" + stringTampon;
            //on relance xCopy pour les sous répertoires du répertoire en cours
            xCopy(srcName, destName, filtre, subDirs);
        }
    }
}

//enregistrer
void MaFenetre::enregistrer()
{
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    QString images = environment.value("USERPROFILE");
    //images.append("\\Pictures\\LabelizeMyeJuices\\exports\\");
    if(!QDir(images + "\\Pictures\\LabelizeMyeJuices\\exports").exists()){
        images.append("\\Pictures\\LabelizeMyeJuices");
        QDir(images).mkpath(".");
        images.append("\\exports");
        QDir(images).mkpath(".");
        images.append("\\");
    }
    else images.append("\\Pictures\\LabelizeMyeJuices\\exports\\");
    QFile file(QFileDialog::getSaveFileName(this, "Enregistrer l'étiquette", images + m_lineNomArome->text() + ".jpg", "Images (*.jpg)"));
    file.open(QIODevice::WriteOnly);
    m_px->save(&file, "JPG");
    file.close();
}

//exporter
void MaFenetre::exporterBase()
{
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    QString dossierSource = environment.value("USERPROFILE");
    QString dossierDestination = QFileDialog::getExistingDirectory(this, "Selection du dossier de destination", "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(QFile(QString::fromStdString(m_pathAromes)).exists()) {dossierSource = QCoreApplication::applicationDirPath() + "/ressources";}
    else if(QFile(dossierSource + "\\AppData\\Local\\VirtualStore\\Program Files (x86)\\Labelize My eJuices\\ressources\\bases\\aromes.txt").exists()) {dossierSource.append("\\AppData\\Local\\VirtualStore\\Program Files (x86)\\Labelize My eJuices\\ressources");}
    else QMessageBox::critical(this, "Fichiers non trouvé", "Pas de fichier base arôme détecté");
    if(dossierSource != environment.value("USERPROFILE")){
        xCopy(dossierSource, dossierDestination + "/LabelizeMyeJuices_save", "*", "Y");/*
        QFile fichierSavePath(dossierDestination + "/LabelizeMyeJuices_save/savepath.txt");
        if (fichierSavePath.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&fichierSavePath);// Création d'un objet QTextStream raccordé à objet QFile
            out << dossierSource;
            out << "\n";
            out.reset();
            fichierSavePath.close();
        }*/
    }
}

//importer
void MaFenetre::importerBase()
{
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    QString dossierSource = QFileDialog::getExistingDirectory(this, "Selection du dossier des données à restaurer", "/home", QFileDialog::ShowDirsOnly | QFileDialog::ReadOnly  | QFileDialog::DontResolveSymlinks);
    if (!QFile(dossierSource + "/bases/aromes.txt").exists()){
        QMessageBox::critical(this, "Fichiers introuvables", "Le dossier " + dossierSource + " ne contient pas de données à restaurer.\nVeuillez selectionner le dossier LabelizeMyeJuices_save");
    } else {
        xCopy(dossierSource, QCoreApplication::applicationDirPath() + "/ressources", "*", "Y");
        QMessageBox::information(this, "Restauration terminée", "Le dossier " + dossierSource + " a été restauré.\nRedémarrer Labelize My eJuices pour charger ces données");
    }
    /*QFile pathFileParams {dossierSource + "/savepath.txt"};
    QString stringTampon;
        QTextStream in(&pathFileParams);// Création d'un objet QTextStream raccordé à objet QFile
        stringTampon = in.readLine();
        in.reset();
        pathFileParams.close();
    }
    qDebug() << stringTampon;

    if(QFile(QString::fromStdString(m_pathAromes)).exists()) {dossierSource = QCoreApplication::applicationDirPath() + "/ressources";}
    else if(QFile(dossierSource + "\\AppData\\Local\\VirtualStore\\Program Files (x86)\\Labelize My eJuices\\ressources\\bases\\aromes.txt").exists()) {dossierSource.append("\\AppData\\Local\\VirtualStore\\Program Files (x86)\\Labelize My eJuices\\ressources");}
    else QMessageBox::critical(this, "Fichiers non trouvé", "Pas de fichier base arôme détecté");
    if(dossierSource != environment.value("USERPROFILE")) xCopy(dossierSource, dossierDestination + "/LabelizeMyeJuices_save", "*", "Y");*/
}

//imprimer
void MaFenetre::imprimer()
{
    QPrinter printer;
    QPrintDialog printDialog (&printer, this);
    if (printDialog.exec() == QDialog::Accepted)
    {
        QPainter painter;
        m_px->scaled(printer.pageRect().width(), printer.pageRect().height(), Qt::KeepAspectRatio);
        painter.begin(&printer);
        painter.drawPixmap(0, 0, *m_px);
        painter.end();
    }
}

//affichage des produits à commander
void MaFenetre::getListeCommande()
{
    bool trouve{false};
    QString liste{"Arômes :\n"};
    for(int i{0}; i < m_listeAromes.getTaille(); i++){
        if(m_listeAromes.getCommande(i)==true) {
            liste += QString::fromStdString(m_listeAromes.getNom(i)) + "   " + QString::fromStdString(m_listeAromes.getFabricant(i)) + "\n";
            trouve=true;
        }
    }
    liste += "\nBases :\n";
    for(int i{0}; i < m_listeBases.getTaille(); i++){
        if(m_listeBases.getCommande(i)==true) {
            liste += QString::fromStdString(m_listeBases.getNom(i)) + " " + QString::number(m_listeBases.getNico(i)) + "mg\n";
            trouve=true;
        }
    }
    liste += "\nAdditifs :\n";
    for(int i{0}; i < m_listeAlcools.getTaille(); i++){
        if(m_listeAlcools.getCommande(i)==true) {
            liste += QString::fromStdString(m_listeAlcools.getNom(i)) + "\n";
        trouve=true;
        }
    }

    if(trouve==false) QMessageBox::information(this, "Recherche terminée",  "Aucun produit à commander");
    else {
        FenTexteGenere *fenetreCommande = new FenTexteGenere(liste, this);
        fenetreCommande->exec();
    }
}

//import de la liste fichier INI
void MaFenetre::initSequence(){
    const QString pathFileParams {QCoreApplication::applicationDirPath() + "/PARAM.INI"};
    m_FileParams = new QFile(pathFileParams);
    QString stringTampon;
    if (!QFile(pathFileParams).exists()){
        QMessageBox::information(this, "Fichier introuvable", "Le fichier " + pathFileParams + " n'a pas été trouvé.\nCréation d'un fichier PARAM.INI par défaut.");
        QFile::copy(":PARAM.INI", QCoreApplication::applicationDirPath() + "/PARAM.INI");
    }
    if (!m_FileParams->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Fichier illisible", "Le fichier " + pathFileParams + " n'est pas accessible.\nSortie de l'application.");
        return;
    }
    else
    {
        QTextStream in(m_FileParams);// Création d'un objet QTextStream raccordé à objet QFile
        const QPair<QString, int> patternQtt        { "[QUANTITE]", 11 }; // on recherche le motif, index du premier caractère de la valeur à récupérer
        const QPair<QString, float> patternVolGoutte{ "[VOLGOUTTE]", 12 };
        const QPair<QString, int> patternAffAromes  { "[AFFICHAGE AROME]", 18 };
        int quantite{0}, affichageArome{0};
        while (!in.atEnd())//on lis le fichier ligne par ligne jusqu'au bout
        {
            stringTampon = in.readLine();
            if(stringTampon.contains(patternQtt.first)) quantite = stringTampon.right(stringTampon.size()-patternQtt.second).toInt();
            else if(stringTampon.contains(patternVolGoutte.first)) m_gouteEnMl = (stringTampon.right(stringTampon.size()-patternVolGoutte.second)).toFloat();
            else if(stringTampon.contains(patternAffAromes.first)) modeAffichageArome = (stringTampon.right(stringTampon.size()-patternAffAromes.second)).toInt();
        }
        in.reset();
        m_FileParams->close();
        setQuantiteAProduire(quantite);
        //copie de l'image arome par défaut si inexistante
        if(!QFile(QString::fromStdString(m_pathImg) + "eliquid.png").exists()) QFile::copy(":eliquid.png", QString::fromStdString(m_pathImg) + "eliquid.png");
    }
}

int MaFenetre::getQuantiteAProduire(){
    return m_quantite;
}

void MaFenetre::setQuantiteAProduire(int quantite){
    m_quantite = quantite;
}

//alcool
void MaFenetre::afficherAlcool(int index){
    if(m_listeAlcools.getTaille()==0)
    {
        const QString IMAGEALCOOL = (":/alcool.png");
        m_imageAlcool->setPixmap(QPixmap(IMAGEALCOOL).scaled(100,100,Qt::KeepAspectRatio));
        m_lineNomAlcool->setText("Liste vide");
        m_percentAlcool->setValue(0);
        m_cbStockAlcool->setChecked(1);
        m_cbCommandeAlcool->setChecked(1);
    }
    else
    {
        const QString IMAGEALCOOL = (":/alcool.png");
        m_imageAlcool->setPixmap(QPixmap(IMAGEALCOOL).scaled(100,100,Qt::KeepAspectRatio));
        m_lineNomAlcool->setText(QString::fromStdString(this->m_listeAlcools.getNom(index)));
        m_percentAlcool->setValue(this->m_listeAlcools.getDosage(index));
        m_cbStockAlcool->setChecked(this->m_listeAlcools.getZeroStock(index));
        m_cbCommandeAlcool->setChecked(this->m_listeAlcools.getCommande(index));
    }
}

void MaFenetre::ajouterAlcool(){
    QString nom{""};
    float dosage{0.0};
    bool stock{0}, commande{0};
    FenAddAlcool *fenetreAddAlcool = new FenAddAlcool(nom, dosage, stock, commande, this);
    fenetreAddAlcool->exec(); // fenetre modal permet de stoper le déroulement de la fonction tant que le pop up est ouvert
    if(!nom.isEmpty())
    {
        m_listeAlcools.ajouter(nom.toStdString(), dosage, stock, commande);
        m_comboListAlcools->addItem(nom);
        afficherAlcool(m_listeAlcools.getTaille()-1);
        m_comboListAlcools->setCurrentIndex(m_listeAlcools.getTaille()-1);
        creerEtiquette();
        QMessageBox::information(this, "Ajout effectué", "Enregistrez la liste pour conserver l'additif.");
    }
}

void MaFenetre::retirerAlcool(){
    if(m_listeAlcools.getTaille()>0)
    {
        m_listeAlcools.retirer(m_comboListAlcools->currentIndex());
        m_comboListAlcools->removeItem(m_comboListAlcools->currentIndex());
    }
    else QMessageBox::information(this, "Liste vide", "La liste des additifs est vide.");
}

void MaFenetre::modifierAlcool(){
    m_comboListAlcools->setItemText(this->m_comboListAlcools->currentIndex(), this->m_lineNomAlcool->text());
    m_listeAlcools.setNom(this->m_comboListAlcools->currentIndex(), this->m_lineNomAlcool->text().toStdString());
    m_listeAlcools.setDosage(this->m_comboListAlcools->currentIndex(), float(this->m_percentAlcool->value()));
    m_listeAlcools.setZeroStock(this->m_comboListAlcools->currentIndex(), this->m_cbStockAlcool->isChecked());
    m_listeAlcools.setCommande(this->m_comboListAlcools->currentIndex(), this->m_cbCommandeAlcool->isChecked());
    QMessageBox::information(this, "Modification effectuée", "Enregistrez la liste pour conserver les modifications.");
}

void MaFenetre::sauverListeAlcools(){
    QFile fichierAlcools(QString::fromStdString(m_pathAlcools));
    if (!fichierAlcools.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, windowTitle(), tr("Modification non prise en compte, vérifier l'accès au fichier ") + QString::fromStdString(m_pathAlcools));
    }
    else {
        QTextStream out(&fichierAlcools);// Création d'un objet QTextStream raccordé à objet QFile
        //parcours du vector aromes :
        for (int i{0}; i<m_listeAlcools.getTaille(); i++)
        {
            out << "[NOM]=" << QString::fromStdString(this->m_listeAlcools.getNom(i))
                << "\n[POURCENTAGE]=" << this->m_listeAlcools.getDosage(i)
                << "\n[0STOCK]=" << this->m_listeAlcools.getZeroStock(i)
                << "\n[COMMANDE]=" << this->m_listeAlcools.getCommande(i) << "\n\n";
        }
        out.reset();
        fichierAlcools.close();
        QMessageBox::information(this, "Modification effectuée",  "Liste d'additifs enregistrée.");
    }
}

void MaFenetre::setComboListAlcools()
{
    for(int i{0}; i < this->m_listeAlcools.getTaille(); i++ ) m_comboListAlcools->addItem(QString::fromStdString(this->m_listeAlcools.getNom(i)));
}

void MaFenetre::setFenAlcool()
{
    if(m_cbAlcool->isChecked()) m_alcool_widget->show();
    else {
        m_alcool_widget->hide();
        this->hide();
        this->show();
    }
}

//arome
void MaFenetre::afficherArome(int index){
    if(m_listeAromes.getTaille()==0)
    {
        m_lineNomArome->setText("Liste vide");
        m_lineMarqueArome->setText("Liste vide");
        m_imageArome->setPixmap(QPixmap(":eliquid.png").scaled(100,100,Qt::KeepAspectRatio));
        m_lineNumeroArome->setValue(0);
        m_percentArome->setValue(0);
        m_sbNoteArome->setValue(0);
        m_cbStockArome->setChecked(1);
        m_cbCommandeArome->setChecked(1);
    }
    else
    {
        m_lineNomArome->setText(QString::fromStdString(this->m_listeAromes.getNom(index)));
        m_lineMarqueArome->setText(QString::fromStdString(this->m_listeAromes.getFabricant(index)));
        m_imageArome->setPixmap(QPixmap(QString::fromStdString(this->m_listeAromes.getImage(index))).scaled(100,100,Qt::KeepAspectRatio));
        m_lineNumeroArome->setValue(this->m_listeAromes.getNumero(index));
        m_percentArome->setValue(this->m_listeAromes.getDosage(index));
        m_sbNoteArome->setValue(this->m_listeAromes.getNote(index));
        m_cbStockArome->setChecked(this->m_listeAromes.getZeroStock(index));
        m_cbCommandeArome->setChecked(this->m_listeAromes.getCommande(index));
    }
}

int MaFenetre::GenererNumeroArome()
{
    int numero{0};
    bool trouve{false};
    while(!trouve)
    {
        trouve = true;
        numero++;
        for(int i{0}; i < m_listeAromes.getTaille(); i++)
        {
            if(numero == m_listeAromes.getNumero(i)) trouve=false;
        }
    }
    return numero;
}

void MaFenetre::ajouterArome(){
    QString nom{""}, fabricant{""}, nomImage{""};
    int numero{GenererNumeroArome()}, note{0};
    float dosage{0.0};
    bool stock{0}, commande{0};
    //liste des fabricants enregistrés
    QStringList fabricants;
    for(int i{0}; i < m_listeAromes.getTaille(); i++)
        fabricants << QString::fromStdString(m_listeAromes.getFabricant(i));
    for(int i{0}; i < fabricants.count(); i++){
        forever {// remove all occurrences at greater indexes
            int p = fabricants.lastIndexOf(fabricants.at(i));
            if (p == i) break;
            fabricants.removeAt(p);
        }
    }
    fabricants.sort();
    FenAddArome *fenetreAddArome = new FenAddArome(numero, nom, stock, commande, fabricant, dosage, nomImage, note, m_pathImg, fabricants, m_gouteEnMl, this);
    fenetreAddArome->exec(); // fenetre modal permet de stoper le déroulement de la fonction tant que le pop up est ouvert
    if(!nom.isEmpty())
    {
        m_listeAromes.ajouter(numero, nom.toStdString(), stock, commande, fabricant.toStdString(), dosage, nomImage.toStdString(), note);
        m_comboListAromes->addItem(nom);
        afficherArome(m_listeAromes.getTaille()-1);
        m_comboListAromes->setCurrentIndex(m_listeAromes.getTaille()-1);
        bool correction = creerEtiquette();
        if(!correction) QMessageBox::information(this, "Ajout effectué",  "Enregistrez la liste pour conserver la base d'arômes.");
    }
}

void MaFenetre::retirerArome(){
    if(m_listeAromes.getTaille()>0)
    {
        m_listeAromes.retirer(m_comboListAromes->currentIndex());
        m_comboListAromes->removeItem(m_comboListAromes->currentIndex());
    }
    else QMessageBox::information(this, "Liste vide",  "La liste des arômes est vide.");
}

void MaFenetre::modifierArome(){
    m_comboListAromes->setItemText(this->m_comboListAromes->currentIndex(), this->m_lineNomArome->text());
    m_listeAromes.setNumero(this->m_comboListAromes->currentIndex(), this->m_lineNumeroArome->value());
    m_listeAromes.setNom(this->m_comboListAromes->currentIndex(), this->m_lineNomArome->text().toStdString());
    m_listeAromes.setZeroStock(this->m_comboListAromes->currentIndex(), this->m_cbStockArome->isChecked());
    m_listeAromes.setCommande(this->m_comboListAromes->currentIndex(), this->m_cbCommandeArome->isChecked());
    m_listeAromes.setFabricant(this->m_comboListAromes->currentIndex(), this->m_lineMarqueArome->text().toStdString());
    m_listeAromes.setDosage(this->m_comboListAromes->currentIndex(), float(this->m_percentArome->value()));
    m_listeAromes.setNote(this->m_comboListAromes->currentIndex(), this->m_sbNoteArome->value());
    QMessageBox::information(this, "Modification effectuée",  "Enregistrez la liste pour conserver les modifications.");
}

void MaFenetre::sauverListeAromes(){
    QFile fichierAromes(QString::fromStdString(m_pathAromes));
    if (!fichierAromes.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, windowTitle(), tr("Modification non prise en compte, vérifier l'accès au fichier ") + QString::fromStdString(m_pathAromes));
    }
    else {
        QTextStream out(&fichierAromes);// Création d'un objet QTextStream raccordé à objet QFile
        //parcours du vector aromes :
        for (int i{0}; i<m_listeAromes.getTaille(); i++)
        {
            out << "[NUMERO]=" << this->m_listeAromes.getNumero(i)
                << "\n[NOM]=" << QString::fromStdString(this->m_listeAromes.getNom(i))
                << "\n[FABRICANT]=" << QString::fromStdString(this->m_listeAromes.getFabricant(i))
                << "\n[POURCENTAGE]=" << this->m_listeAromes.getDosage(i);
            QString fileName = QString::fromStdString(this->m_listeAromes.getImage(i));
            fileName = fileName.right(fileName.size() - fileName.lastIndexOf("/") - 1);
            out << "\n[IMAGE]=" << fileName
                << "\n[0STOCK]=" << this->m_listeAromes.getZeroStock(i)
                << "\n[COMMANDE]=" << this->m_listeAromes.getCommande(i)
                << "\n[NOTE]=" << this->m_listeAromes.getNote(i) << "\n\n";
        }
        out.reset();
        fichierAromes.close();
        QMessageBox::information(this, "Modification effectuée",  "Liste d'arômes enregistrée.");
    }
}

void MaFenetre::setComboListAromes()
{
    for(int i{0}; i<this->m_listeAromes.getTaille(); i++ ) m_comboListAromes->addItem(QString::fromStdString(this->m_listeAromes.getNom(i)));
}

//base
void MaFenetre::afficherBase(int index){
    if(m_listeBases.getTaille()==0)
    {
        const QString IMAGEBASE = (":/base.png");
        m_imageBase->setPixmap(QPixmap(IMAGEBASE).scaled(100,100,Qt::KeepAspectRatio));
        m_lineNomBase->setText("Liste vide");
        m_percent_pg->setValue(0);
        m_percent_vg->setValue(0);
        m_mg_nico->setValue(0);
        m_cbStockBase->setChecked(1);
        m_cbCommandeBase->setChecked(1);
    }
    else
    {
        const QString IMAGEBASE = (":/base.png");
        m_imageBase->setPixmap(QPixmap(IMAGEBASE).scaled(100,100,Qt::KeepAspectRatio));
        m_lineNomBase->setText(QString::fromStdString(this->m_listeBases.getNom(index)));
        m_percent_pg->setValue(this->m_listeBases.getPg(index));
        m_percent_vg->setValue(this->m_listeBases.getVg(index));
        m_mg_nico->setValue(this->m_listeBases.getNico(index));
        m_cbStockBase->setChecked(this->m_listeBases.getZeroStock(index));
        m_cbCommandeBase->setChecked(this->m_listeBases.getCommande(index));
    }
}

void MaFenetre::ajouterBase(){
    QString nom{""};
    int pg{0}, nico{0};
    bool stock{0}, commande{0};
    FenAddBase *fenetreAddBase = new FenAddBase(nom, stock, commande, pg, nico, this);
    fenetreAddBase->exec(); // fenetre modal permet de stoper le déroulement de la fonction tant que le pop up est ouvert
    if(!nom.isEmpty())
    {
        m_listeBases.ajouter(nom.toStdString(), stock, commande, pg, nico);
        m_comboListBases->addItem(nom);
        afficherBase(m_listeBases.getTaille()-1);
        m_comboListBases->setCurrentIndex(m_listeBases.getTaille()-1);
        creerEtiquette();
        QMessageBox::information(this, "Ajout effectué",  "Enregistrez la liste pour conserver la base.");
    }
}

void MaFenetre::retirerBase(){
    if(m_listeBases.getTaille()>0)
    {
        m_listeBases.retirer(m_comboListBases->currentIndex());
        m_comboListBases->removeItem(m_comboListBases->currentIndex());
    }
    else QMessageBox::information(this, "Liste vide",  "La liste de bases est vide.");
}

void MaFenetre::modifierBase(){
    m_comboListBases->setItemText(this->m_comboListBases->currentIndex(), this->m_lineNomBase->text());
    m_listeBases.setNom(this->m_comboListBases->currentIndex(), this->m_lineNomBase->text().toStdString());
    m_listeBases.setZeroStock(this->m_comboListBases->currentIndex(), this->m_cbStockBase->isChecked());
    m_listeBases.setCommande(this->m_comboListBases->currentIndex(), this->m_cbCommandeBase->isChecked());
    m_listeBases.setPg(this->m_comboListBases->currentIndex(), this->m_percent_pg->value());
    m_listeBases.setNico(this->m_comboListBases->currentIndex(), this->m_mg_nico->value());
    QMessageBox::information(this, "Modification effectuée",  "Enregistrez la liste pour conserver les modifications.");
}

void MaFenetre::sauverListeBases(){
    QFile fichierBases(QString::fromStdString(m_pathBases));
    if (!fichierBases.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, windowTitle(), tr("Modification non prise en compte, vérifier l'accès au fichier ") + QString::fromStdString(m_pathBases));
    }
    else {
        QTextStream out(&fichierBases);// Création d'un objet QTextStream raccordé à objet QFile
        //parcours du vector aromes :
        for (int i{0}; i<m_listeBases.getTaille(); i++)
        {
            out << "[NUMERO]=" << this->m_listeBases.getNumero(i)
                << "\n[NOM]=" << QString::fromStdString(this->m_listeBases.getNom(i))
                << "\n[TAUXPG]=" << this->m_listeBases.getPg(i)
                << "\n[TAUXNICO]=" << this->m_listeBases.getNico(i)
                << "\n[0STOCK]=" << this->m_listeBases.getZeroStock(i)
                << "\n[COMMANDE]=" << this->m_listeBases.getCommande(i) << "\n\n";
        }
        out.reset();
        fichierBases.close();
        QMessageBox::information(this, "Modification effectuée",  "Liste de bases enregistrée.");
    }
}

void MaFenetre::setComboListBases()
{
    for(int i{0}; i<this->m_listeBases.getTaille(); i++ ) m_comboListBases->addItem(QString::fromStdString(this->m_listeBases.getNom(i)));
}

//options
void MaFenetre::modifierOptions(){
    FenOptions *fenetreOptions = new FenOptions(getQuantiteAProduire(), m_gouteEnMl, modeAffichageArome, this);
    fenetreOptions->exec(); // fenetre modal permet de stoper le déroulement de la fonction tant que le pop up est ouvert
}

//création de la fenêtre
void MaFenetre::construireFenetre(){
    //1 HBox
    QHBoxLayout *main_layout = new QHBoxLayout();

    //1.1   VBox
    QVBoxLayout *composants_layout = new QVBoxLayout();
    //partie arômes
    QLabel *labelArome = new QLabel("Arôme");
        labelArome->setFont(QFont(labelArome->font().toString(), 14, QFont::Bold));
        labelArome->setAlignment(Qt::AlignHCenter);
    composants_layout->addWidget(labelArome);
    //1.1..1 HBox
    QWidget *arome_widget = new QWidget();
    QHBoxLayout *arome_hlayout = new QHBoxLayout();
    //1.1..1...1 VBox
    QVBoxLayout *composants_labelAromeLayout = new QVBoxLayout();
    m_imageArome = new QLabel;
    composants_labelAromeLayout->addWidget(m_imageArome);
    //1.1..1...1....1 HBox
    QHBoxLayout *boutons_arome_layout = new QHBoxLayout();
    m_boutonAjouterArome = new QPushButton();
        m_boutonAjouterArome->setIcon(QIcon(QPixmap(":add.png")));
        m_boutonAjouterArome->setToolTip("Ajouter l'arôme");
    boutons_arome_layout->addWidget(m_boutonAjouterArome);
    m_boutonSupprimerArome = new QPushButton();
        m_boutonSupprimerArome->setIcon(QIcon(QPixmap(":delete.png")));
        m_boutonSupprimerArome->setToolTip("Retirer l'arôme");
    boutons_arome_layout->addWidget(m_boutonSupprimerArome);
    m_boutonSauverListeAromes = new QPushButton();
        m_boutonSauverListeAromes->setIcon(QIcon(QPixmap(":save.png")));
        m_boutonSauverListeAromes->setToolTip("Enregister la liste");
    boutons_arome_layout->addWidget(m_boutonSauverListeAromes);
    composants_labelAromeLayout->addLayout(boutons_arome_layout);
    arome_hlayout->addLayout(composants_labelAromeLayout);
    //1.1..1...2 VBox
    QVBoxLayout *composants_formFicheAromeLayout = new QVBoxLayout();
    m_comboListAromes = new QComboBox();
    composants_formFicheAromeLayout->addWidget(m_comboListAromes);
    //1.1..1...2....1 Form
    QFormLayout *formFicheAromeLayout = new QFormLayout();
    m_lineNomArome = new QLineEdit;
    formFicheAromeLayout->addRow("Nom : ", m_lineNomArome);
    m_lineMarqueArome = new QLineEdit;
    formFicheAromeLayout->addRow("Marque : ", m_lineMarqueArome);
    m_lineNumeroArome = new QSpinBox;
        m_lineNumeroArome->setMaximum(999);
    formFicheAromeLayout->addRow("Numéro : ", m_lineNumeroArome);
    m_percentArome = new QDoubleSpinBox;
        m_percentArome->setDecimals(1);
        m_percentArome->setSingleStep(0.5);
    formFicheAromeLayout->addRow("Pourcentage arôme : ", m_percentArome);
    m_sbNoteArome = new QSpinBox;
        m_sbNoteArome->setMaximum(5);
    formFicheAromeLayout->addRow("Note/5 : ", m_sbNoteArome);
    composants_formFicheAromeLayout->addLayout(formFicheAromeLayout);
    //1.1..1...2....2 HBox
    QHBoxLayout *commandeAromeLayout = new QHBoxLayout();
    m_cbStockArome = new QCheckBox("Épuisé");
    commandeAromeLayout->addWidget(m_cbStockArome);
    m_cbCommandeArome = new QCheckBox("Commander");
    commandeAromeLayout->addWidget(m_cbCommandeArome);
    m_boutonAppliquerArome = new QPushButton();
        m_boutonAppliquerArome->setIcon(QIcon(QPixmap(":apply.png")));
        m_boutonAppliquerArome->setToolTip("Appliquer les modifications à l'arôme");
    commandeAromeLayout->addWidget(m_boutonAppliquerArome);
    composants_formFicheAromeLayout->addLayout(commandeAromeLayout);

    arome_hlayout->addLayout(composants_formFicheAromeLayout);
    arome_widget->setLayout(arome_hlayout);
    composants_layout->addWidget(arome_widget);

    //partie base
    QLabel *labelBase = new QLabel("Base");
        labelBase->setFont(QFont(labelBase->font().toString(), 14, QFont::Bold));
        labelBase->setAlignment(Qt::AlignHCenter);
    composants_layout->addWidget(labelBase);
    //1.1..2 HBox
    QWidget *base_widget = new QWidget();
    QHBoxLayout *base_hlayout = new QHBoxLayout();
    //1.1..2...1 VBox
    QVBoxLayout *composants_labelBaseLayout = new QVBoxLayout();
    m_imageBase = new QLabel;
    composants_labelBaseLayout->addWidget(m_imageBase);
    //1.1..2...1....1 HBox
    QHBoxLayout *boutons_base_layout = new QHBoxLayout();
    m_boutonAjouterBase = new QPushButton();
        m_boutonAjouterBase->setIcon(QIcon(QPixmap(":add.png")));
        m_boutonAjouterBase->setToolTip("Ajouter la base");
    boutons_base_layout->addWidget(m_boutonAjouterBase);
    m_boutonSupprimerBase = new QPushButton();
        m_boutonSupprimerBase->setIcon(QIcon(QPixmap(":delete.png")));
        m_boutonSupprimerBase->setToolTip("Retirer la base");
    boutons_base_layout->addWidget(m_boutonSupprimerBase);
    m_boutonSauverListeBases = new QPushButton();
        m_boutonSauverListeBases->setIcon(QIcon(QPixmap(":save.png")));
        m_boutonSauverListeBases->setToolTip("Enregister la liste");
    boutons_base_layout->addWidget(m_boutonSauverListeBases);
    composants_labelBaseLayout->addLayout(boutons_base_layout);
    base_hlayout->addLayout(composants_labelBaseLayout);
    //1.1..2...2 VBox
    QVBoxLayout *composants_formFicheBaseLayout = new QVBoxLayout();
    m_comboListBases = new QComboBox();
    composants_formFicheBaseLayout->addWidget(m_comboListBases);
    //1.1..2...2....1   Form
    QFormLayout *formFicheBaseLayout = new QFormLayout();
    m_lineNomBase = new QLineEdit;
    formFicheBaseLayout->addRow("Nom : ", m_lineNomBase);
    m_percent_pg = new MyQSpinBox;
        m_percent_pg->setMaximum(100);
    formFicheBaseLayout->addRow("Pourcentage PG : ", m_percent_pg);
    m_percent_vg = new MyQSpinBox;
        m_percent_vg->setMaximum(100);
    formFicheBaseLayout->addRow("Pourcentage VG : ", m_percent_vg);
    m_mg_nico = new QSpinBox;
    formFicheBaseLayout->addRow("Nicotine (mg/ml) : ", m_mg_nico);
    composants_formFicheBaseLayout->addLayout(formFicheBaseLayout);
    //1.1..2...2....2 HBox
    QHBoxLayout *commandeBaseLayout = new QHBoxLayout();
    m_cbStockBase = new QCheckBox("Épuisé");
    commandeBaseLayout->addWidget(m_cbStockBase);
    m_cbCommandeBase = new QCheckBox("Commander");
    commandeBaseLayout->addWidget(m_cbCommandeBase);
    m_boutonAppliquerBase = new QPushButton();
        m_boutonAppliquerBase->setIcon(QIcon(QPixmap(":apply.png")));
        m_boutonAppliquerBase->setToolTip("Appliquer les modifications à la base");
    commandeBaseLayout->addWidget(m_boutonAppliquerBase);
    composants_formFicheBaseLayout->addLayout(commandeBaseLayout);

    base_hlayout->addLayout(composants_formFicheBaseLayout);
    base_widget->setLayout(base_hlayout);
    composants_layout->addWidget(base_widget);

    //partie alcool
    QHBoxLayout *cbAlcoolLayout = new QHBoxLayout();
    m_cbAlcool = new QCheckBox("Additif", this);
        m_cbAlcool->setFont(QFont(m_cbAlcool->font().toString(), 14, QFont::Bold));
    cbAlcoolLayout->addWidget(m_cbAlcool);
    cbAlcoolLayout->setAlignment(Qt::AlignHCenter);
    composants_layout->addLayout(cbAlcoolLayout);
    //1.1..3 HBox
    m_alcool_widget = new QWidget();
    m_alcool_widget->hide();
    QHBoxLayout *alcool_hlayout = new QHBoxLayout();
    //1.1..3...1 VBox
    QVBoxLayout *composants_labelAlcoolLayout = new QVBoxLayout();
    m_imageAlcool = new QLabel;
    composants_labelAlcoolLayout->addWidget(m_imageAlcool);
    //1.1..3...1....1 HBox
    QHBoxLayout *boutons_alcool_layout = new QHBoxLayout();
    m_boutonAjouterAlcool = new QPushButton();
        m_boutonAjouterAlcool->setIcon(QIcon(QPixmap(":add.png")));
        m_boutonAjouterAlcool->setToolTip("Ajouter l'additif");
    boutons_alcool_layout->addWidget(m_boutonAjouterAlcool);
    m_boutonSupprimerAlcool = new QPushButton();
        m_boutonSupprimerAlcool->setIcon(QIcon(QPixmap(":delete.png")));
        m_boutonSupprimerAlcool->setToolTip("Retirer l'additif");
    boutons_alcool_layout->addWidget(m_boutonSupprimerAlcool);
    m_boutonSauverListeAlcools = new QPushButton();
        m_boutonSauverListeAlcools->setIcon(QIcon(QPixmap(":save.png")));
        m_boutonSauverListeAlcools->setToolTip("Enregister la liste");
    boutons_alcool_layout->addWidget(m_boutonSauverListeAlcools);
    composants_labelAlcoolLayout->addLayout(boutons_alcool_layout);
    alcool_hlayout->addLayout(composants_labelAlcoolLayout);
    //1.1..3...2 VBox
    QVBoxLayout *composants_formFicheAlcoolLayout = new QVBoxLayout();
    m_comboListAlcools = new QComboBox();
    composants_formFicheAlcoolLayout->addWidget(m_comboListAlcools);
    //1.1..3...2....1   Form
    QFormLayout *formFicheAlcoolLayout = new QFormLayout();
    m_lineNomAlcool = new QLineEdit;
    formFicheAlcoolLayout->addRow("Nom : ", m_lineNomAlcool);
    m_percentAlcool = new QDoubleSpinBox;
        m_percentAlcool->setDecimals(1);
        m_percentAlcool->setSingleStep(0.1);
    formFicheAlcoolLayout->addRow("Pourcentage additif : ", m_percentAlcool);
    composants_formFicheAlcoolLayout->addLayout(formFicheAlcoolLayout);
    //1.1..3...2....2 HBox
    QHBoxLayout *commandeAlcoolLayout = new QHBoxLayout();
    m_cbStockAlcool = new QCheckBox("Épuisé");
    commandeAlcoolLayout->addWidget(m_cbStockAlcool);
    m_cbCommandeAlcool = new QCheckBox("Commander");
    commandeAlcoolLayout->addWidget(m_cbCommandeAlcool);
    m_boutonAppliquerAlcool = new QPushButton();
        m_boutonAppliquerAlcool->setIcon(QIcon(QPixmap(":apply.png")));
        m_boutonAppliquerAlcool->setToolTip("Appliquer les modifications à l'a base'additif");
    commandeAlcoolLayout->addWidget(m_boutonAppliquerAlcool);
    composants_formFicheAlcoolLayout->addLayout(commandeAlcoolLayout);

    alcool_hlayout->addLayout(composants_formFicheAlcoolLayout);
    m_alcool_widget->setLayout(alcool_hlayout);
    composants_layout->addWidget(m_alcool_widget);

    m_boutonCommandes = new QPushButton("Afficher la liste de commande");
        m_boutonCommandes->setIcon(QIcon(QPixmap(":order.png")));

    composants_layout->addWidget(m_boutonCommandes);

    //partie image
    //1.2   VBox
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::lightGray);
    QWidget *image_widget = new QWidget();
        image_widget->setAutoFillBackground(true);
        image_widget->setPalette(pal);
    QVBoxLayout *image_layout = new QVBoxLayout();

    //partie prod
    QLabel *labelImage = new QLabel("Étiquette");
        labelImage->setFont(QFont(labelImage->font().toString(), 14, QFont::Bold));
        labelImage->setAlignment(Qt::AlignHCenter);
    image_layout->addWidget(labelImage);
    //1.2..1 Form
    QFormLayout *formProdLayout = new QFormLayout();
    m_qttMl = new MyQSpinBox();
        m_qttMl->setValue(getQuantiteAProduire());
        m_qttMl->setMaximum(1000);
    formProdLayout->addRow("Millilitres à produire : ", m_qttMl);
    image_layout->addLayout(formProdLayout);
    m_imageEtiquette = new QLabel;
    image_layout->addWidget(m_imageEtiquette);

    m_boutonEnregistrerImage = new QPushButton("Enregistrer l'étiquette");
        //m_boutonEnregistrerImage->setIcon(QIcon(QPixmap(":savelabel.png")));
    image_layout->addWidget(m_boutonEnregistrerImage);

    m_boutonImprimerEtiquette = new QPushButton("Imprimer l'étiquette");
        //m_boutonImprimerEtiquette->setIcon(QIcon(QPixmap(":printlabel.png")));
    image_layout->addWidget(m_boutonImprimerEtiquette);

    m_boutonExporterBase = new QPushButton("Exporter la base");
        //m_boutonExporterBase->setIcon(QIcon(QPixmap(":databasesave.png")));
    image_layout->addWidget(m_boutonExporterBase);

    m_boutonImporterBase = new QPushButton("Restaurer la base");
        //m_boutonImporterBase->setIcon(QIcon(QPixmap(":databaserestor.png")));
    image_layout->addWidget(m_boutonImporterBase);
    image_layout->addStretch();

    m_boutonOptions = new QPushButton("Options");
    image_layout->addWidget(m_boutonOptions);

    m_boutonAbout = new QPushButton("À propos");
    image_layout->addWidget(m_boutonAbout);
    image_widget->setLayout(image_layout);

    main_layout->addLayout(composants_layout);
    main_layout->addWidget(image_widget);
    this->setLayout(main_layout);
}

MaFenetre::MaFenetre() : QWidget()
{
    QCoreApplication::setApplicationName("Labelize my eJuices");
    //chargement du param.ini
    initSequence();
    //création de la fenêtre
    construireFenetre();
    //importation des produits
    this->m_listeAromes.importList(m_pathAromes);
    this->m_listeBases.importList(m_pathBases);
    this->m_listeAlcools.importList(m_pathAlcools);
    setComboListAromes();
    setComboListBases();
    setComboListAlcools();
    afficherBase(0);
    afficherArome(0);
    afficherAlcool(0);
    creerEtiquette();

    //SIGNAUX
    QObject::connect(m_comboListAromes, SIGNAL(currentIndexChanged(int)), this, SLOT(afficherArome(int)));
    QObject::connect(m_comboListAromes, SIGNAL(currentIndexChanged(int)), this, SLOT(creerEtiquette()));
    QObject::connect(m_lineNomArome, SIGNAL(textEdited(QString)), this, SLOT(creerEtiquette()));
    QObject::connect(m_lineNumeroArome, SIGNAL(editingFinished()), this, SLOT(creerEtiquette()));
    QObject::connect(m_percentArome, SIGNAL(editingFinished()), this, SLOT(creerEtiquette()));
    QObject::connect(m_boutonAjouterArome, SIGNAL(clicked(bool)), this, SLOT(ajouterArome()));
    QObject::connect(m_boutonSupprimerArome, SIGNAL(clicked(bool)), this, SLOT(retirerArome()));
    QObject::connect(m_boutonAppliquerArome, SIGNAL(clicked(bool)), this, SLOT(modifierArome()));
    QObject::connect(m_boutonSauverListeAromes, SIGNAL(clicked(bool)), this, SLOT(sauverListeAromes()));

    QObject::connect(m_percent_pg, SIGNAL(valueChanged(int)), m_percent_vg, SLOT(valeurChage(int)));
    QObject::connect(m_percent_vg, SIGNAL(valueChanged(int)), m_percent_pg, SLOT(valeurChage(int)));
    QObject::connect(m_percent_pg, SIGNAL(editingFinished()), this, SLOT(creerEtiquette()));
    QObject::connect(m_percent_vg, SIGNAL(editingFinished()), this, SLOT(creerEtiquette()));
    QObject::connect(m_mg_nico, SIGNAL(editingFinished()), this, SLOT(creerEtiquette()));
    QObject::connect(m_comboListBases, SIGNAL(currentIndexChanged(int)), this, SLOT(afficherBase(int)));
    QObject::connect(m_comboListBases, SIGNAL(currentIndexChanged(int)), this, SLOT(creerEtiquette()));
    QObject::connect(m_boutonAjouterBase, SIGNAL(clicked(bool)), this, SLOT(ajouterBase()));
    QObject::connect(m_boutonSupprimerBase, SIGNAL(clicked(bool)), this, SLOT(retirerBase()));
    QObject::connect(m_boutonAppliquerBase, SIGNAL(clicked(bool)), this, SLOT(modifierBase()));
    QObject::connect(m_boutonSauverListeBases, SIGNAL(clicked(bool)), this, SLOT(sauverListeBases()));

    QObject::connect(m_cbAlcool, SIGNAL(clicked(bool)), this, SLOT(setFenAlcool()));
    QObject::connect(m_cbAlcool, SIGNAL(clicked(bool)), this, SLOT(creerEtiquette()));
    QObject::connect(m_comboListAlcools, SIGNAL(currentIndexChanged(int)), this, SLOT(afficherAlcool(int)));
    QObject::connect(m_comboListAlcools, SIGNAL(currentIndexChanged(int)), this, SLOT(creerEtiquette()));
    QObject::connect(m_lineNomAlcool, SIGNAL(textEdited(QString)), this, SLOT(creerEtiquette()));
    QObject::connect(m_percentAlcool, SIGNAL(editingFinished()), this, SLOT(creerEtiquette()));
    QObject::connect(m_boutonAjouterAlcool, SIGNAL(clicked(bool)), this, SLOT(ajouterAlcool()));
    QObject::connect(m_boutonSupprimerAlcool, SIGNAL(clicked(bool)), this, SLOT(retirerAlcool()));
    QObject::connect(m_boutonAppliquerAlcool, SIGNAL(clicked(bool)), this, SLOT(modifierAlcool()));
    QObject::connect(m_boutonSauverListeAlcools, SIGNAL(clicked(bool)), this, SLOT(sauverListeAlcools()));

    QObject::connect(m_qttMl, SIGNAL(valueChanged(int)), this, SLOT(creerEtiquette()));
    QObject::connect(m_boutonCommandes, SIGNAL(clicked(bool)), this, SLOT(getListeCommande()));
    QObject::connect(m_boutonEnregistrerImage, SIGNAL(clicked(bool)), this, SLOT(enregistrer()));
    QObject::connect(m_boutonImprimerEtiquette, SIGNAL(clicked(bool)), this, SLOT(imprimer()));
    QObject::connect(m_boutonExporterBase, SIGNAL(clicked(bool)), this, SLOT(exporterBase()));
    QObject::connect(m_boutonImporterBase, SIGNAL(clicked(bool)), this, SLOT(importerBase()));
    QObject::connect(m_boutonOptions, SIGNAL(clicked(bool)), this, SLOT(modifierOptions()));
    QObject::connect(m_boutonAbout, SIGNAL(clicked(bool)), this, SLOT(about()));
}
