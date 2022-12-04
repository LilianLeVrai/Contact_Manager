/**
 * @file ModificationsWindow.cpp
 * @brief Fichier cpp de la classe ModificationsWindow
 */

#include "ModificationsWindow.h"

ModificationsWindow::ModificationsWindow(QSqlDatabase * database, QWidget *parent)
    : QDialog(parent)
{
    this->database=database;
    this->initUI();
    this->fillModificationsTable();
}

ModificationsWindow::~ModificationsWindow(){}

void ModificationsWindow::initUI(){
    setModal(true);
    this->setWindowTitle("Liste des modifications");
    this->resize(1200, 600);

    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    this->modificationsTable = new QTableWidget(this);
    this->modificationsTable->setObjectName("modificationsTable");
    this->modificationsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->modificationsTable->setColumnCount(2);
    QStringList hlabels; hlabels <<"Modification"<<"Date";
    this->modificationsTable->setHorizontalHeaderLabels(hlabels);
    this->modificationsTable->verticalHeader()->setVisible(false);
    this->modificationsTable->horizontalHeader()->setSelectionMode(QAbstractItemView::NoSelection);
    this->modificationsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->modificationsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->modificationsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(this->modificationsTable);
}

void ModificationsWindow::fillModificationsTable(){
    int i=0;
    QSqlQuery query;
    if(!query.exec("select * from Modification;"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        while(query.next())
            {
            this->modificationsTable->insertRow(i);
            this->modificationsTable->setItem(i,0,new QTableWidgetItem(query.value(1).toString().toStdString().c_str()));
            this->modificationsTable->setItem(i,1,new QTableWidgetItem(query.value(2).toString().toStdString().c_str()));
            this->modificationsTable->item(i,1)->setTextAlignment(Qt::AlignCenter);
            i++;
            }
        }
}
