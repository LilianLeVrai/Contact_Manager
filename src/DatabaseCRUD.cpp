/**
 * @file DatabaseCRUD.cpp
 * @brief Fichier cpp de la classe DatabaseCRUD
 */


#include "DatabaseCRUD.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "Contact.h"
#include "ListContact.h"


DatabaseCRUD::DatabaseCRUD(QSqlDatabase * database){
    this->database=database;
    this->date=nullptr;
}

DatabaseCRUD::~DatabaseCRUD(){
    delete(this->date);
}

void DatabaseCRUD::getAllContacts(ListContact * listContact){
    QSqlQuery query;
    if(!query.exec("select * from Contact;"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        listContact->removeAllContacts();
        while(query.next())
            {
            listContact->addContact(new Contact(query.value(0).toInt(),
                                                query.value(1).toString().toStdString(),
                                                query.value(2).toString().toStdString(),
                                                query.value(3).toString().toStdString(),
                                                query.value(4).toString().toStdString(),
                                                query.value(5).toString().toStdString(),
                                                query.value(6).toString().toStdString(),
                                                new Date(query.value(7).toString().toStdString())));
            }
        }
}

void DatabaseCRUD::searchByFilters(ListContact * listContact, QString searchBarContent,
                                  int indexFiltersCombobox, Date * filterFirstDate,Date * filterSecondDate){

//-------------------------
//préparation de la requête
//-------------------------
    QStringList stringList=searchBarContent.split(QRegExp(" "));//liste des mots
    stringList.removeAll(QString(""));

    QString s="select * from Contact";

    QString word;
    int nbCondition=0;
    for(int i=0; i<stringList.size(); i++)//on parcourt les mots
        {
        word=stringList.at(i);

        if(word=="@todo" && i+1<stringList.size() && stringList.at(i+1)!="@todo" && stringList.at(i+1)!="@date")//si le mot est égal à @todo et suivi d'autre chose qu'un tag
            {
            if(nbCondition==0)
                {s=s+" WHERE";}//si c'est la première condition on rajoute 'WHERE'
            if(nbCondition>0)//si nbCondition n'est pas à zéro c'est qu'il y a déjà une condition, il faut donc mettre un 'AND'
                {s=s+" AND";}
            nbCondition++;

            QStringList stringListTmp;
            while(i+1<stringList.size() && stringList.at(i+1)!="@todo" && stringList.at(i+1)!="@date")
                {//on récupère tout les mots suivant le @todo tant qu'on ne rencontre pas un autre tag
                i=i+1;
                stringListTmp.push_back(stringList.at(i));
                }
            s=s+" (idContact IN (SELECT idContact FROM Interaction INNER JOIN Todo ON Interaction.idInteraction=Todo.idInteraction WHERE";
            for(int j=0; j<stringListTmp.size(); j++)
                {//on défini la condition comme quoi les mots doivent être compris dans le contenu du @todo
                if(j>0)
                    s=s+" AND";
                s=s+" Todo.content LIKE '%"+stringListTmp.at(j)+"%'";
                }
            s=s+"))";
            }

        else if(word=="@date" && i+1<stringList.size() && stringList.at(i+1)!="@todo" && stringList.at(i+1)!="@date")//si le mot est égal à @date et suivi d'autre chose qu'un tag
            {
            if(nbCondition==0)
                {s=s+" WHERE";}//si c'est la première condition on rajoute 'WHERE'
            if(nbCondition>0)//si nbCondition n'est pas à zéro c'est qu'il y a déjà une condition, il faut donc mettre un 'AND'
                {s=s+" AND";}
            nbCondition++;
            i=i+1;
            QString date=stringList.at(i);
            s=s+" (idContact IN (SELECT idContact FROM Interaction INNER JOIN Todo ON Interaction.idInteraction=Todo.idInteraction WHERE dateTodo LIKE '%"+date+"%'))";
            }

        else if(word!="@todo" && word!="@date")
            {
            if(nbCondition==0)
                {s=s+" WHERE";}//si c'est la première condition on rajoute 'WHERE'
            if(nbCondition>0)//si nbCondition n'est pas à zéro c'est qu'il y a déjà une condition, il faut donc mettre un 'AND'
                {s=s+" AND";}
            nbCondition++;

            if(indexFiltersCombobox==0)
                {
                s=s+" (lastName LIKE '%"+word+"%'"
                    +" OR firstName LIKE '%"+word+"%'"
                    +" OR company LIKE '%"+word+"%'"
                    +" OR mail LIKE '%"+word+"%'"
                    +" OR phone LIKE '%"+word+"%'"
                    +" OR dateCreation LIKE '%"+word+"%')";
                }
            if(indexFiltersCombobox==1)
                s=s+" (lastName LIKE '%"+word+"%')";
            if(indexFiltersCombobox==2)
                s=s+" (firstName LIKE '%"+word+"%')";
            if(indexFiltersCombobox==3)
                s=s+" (company LIKE '%"+word+"%')";
            if(indexFiltersCombobox==4)
                s=s+" (mail LIKE '%"+word+"%')";
            if(indexFiltersCombobox==5)
                s=s+" (phone LIKE '%"+word+"%')";
            }

        }
        s=s+";";

//-------------------------
//execution de la requête
//-------------------------
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        listContact->removeAllContacts();
        ListContact listContactTemp;
        while(query.next())
            {
            listContactTemp.addContact(new Contact(query.value(0).toInt(),
                                                query.value(1).toString().toStdString(),
                                                query.value(2).toString().toStdString(),
                                                query.value(3).toString().toStdString(),
                                                query.value(4).toString().toStdString(),
                                                query.value(5).toString().toStdString(),
                                                query.value(6).toString().toStdString(),
                                                new Date(query.value(7).toString().toStdString())));
            }

        //filtrage par les dates faits avec les méthodes de la classe Date
        for(int i=0;i<listContactTemp.getSize();i++)
            {
            if(filterFirstDate==nullptr && filterSecondDate==nullptr)
                listContact->addContact(listContactTemp.getContactByIndex(i));
            if(filterFirstDate!=nullptr && filterSecondDate!=nullptr && listContactTemp.getContactByIndex(i)->getDateCreation()->isBetween(filterFirstDate,filterSecondDate))
               listContact->addContact(listContactTemp.getContactByIndex(i));
            if(filterFirstDate!=nullptr && filterSecondDate==nullptr && filterFirstDate->isLessThan(listContactTemp.getContactByIndex(i)->getDateCreation()))
               listContact->addContact(listContactTemp.getContactByIndex(i));
            if(filterFirstDate==nullptr && filterSecondDate!=nullptr && listContactTemp.getContactByIndex(i)->getDateCreation()->isLessThan(filterSecondDate))
               listContact->addContact(listContactTemp.getContactByIndex(i));
            }
        }
}



void DatabaseCRUD::addContactBDD(Contact * contact){
    delete(this->date);
    this->date=new Date();
    this->date->setDateType(Date::WithHours);

    QString s="insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ";
    s=s+"('"+contact->getLastName().c_str()+"', '"+contact->getFirstName().c_str()+"', '"
            +contact->getCompany().c_str()+"', '"+contact->getMail().c_str()+"', '"
            +contact->getPhone().c_str()+"', '"+contact->getPathPicture().c_str()+"', '"
            +contact->getDateCreation()->toString().c_str()+"');";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}


    QString s2="insert into Modification(contentModified, dateModification, idTodo, idInteraction, idContact) values ";
    s2=s2+"('Ajout CONTACT : "+contact->getFirstName().c_str()+" "+contact->getLastName().c_str()+"', '"+this->date->toString().c_str()+"', null, null, last_insert_rowid());";
    QSqlQuery query2;
    if(!query2.exec(s2))
        {qDebug() << "AddContactModif : Impossible d'effectuer la requète :\n" << query2.lastError();}
}


void DatabaseCRUD::modifyContactBDD(Contact * contact){
    delete(this->date);
    this->date=new Date();
    this->date->setDateType(Date::WithHours);

    QString s="update Contact set ";
    s=s+"lastName='"+contact->getLastName().c_str()+"', firstName='"+contact->getFirstName().c_str()
            +"', company='"+contact->getCompany().c_str()+"', mail='"+contact->getMail().c_str()
            +"', phone='"+contact->getPhone().c_str()+"', picture='"+contact->getPathPicture().c_str()
            +"' where idContact="+QString::number(contact->getId())+";";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}

    QString s2="insert into Modification(contentModified, dateModification, idTodo, idInteraction, idContact) values ";
    s2=s2+"('Modification CONTACT : "+contact->getFirstName().c_str()+" "+contact->getLastName().c_str()+"', '"+this->date->toString().c_str()+"', null, null, "+QString::number(contact->getId())+");";
    QSqlQuery query2;
    if(!query2.exec(s2))
        {qDebug() << "ModifInteractionModif : Impossible d'effectuer la requète :\n" << query2.lastError();}
}

void DatabaseCRUD::deleteContactBDD(Contact * contact){
    delete(this->date);
    this->date=new Date();
    this->date->setDateType(Date::WithHours);

    QString s="update Modification set ";
    s=s+"idContact=null, idInteraction=null, idTodo=null where idContact="+QString::number(contact->getId())+";";
    QSqlQuery query2;
    if(!query2.exec(s))
        {qDebug() << "DeleteContactNull : Impossible d'effectuer la requète :\n" << query2.lastError();}

    QString s2="insert into Modification(contentModified, dateModification, idTodo, idInteraction, idContact) values ";
    s2=s2+"('Suppression CONTACT : "+contact->getFirstName().c_str()+" "+contact->getLastName().c_str()+"', '"+this->date->toString().c_str()+"', null, null, null);";
    QSqlQuery query3;
    if(!query3.exec(s2))
        {qDebug() << "DeleteContactModif : Impossible d'effectuer la requète :\n" << query3.lastError();}

    QSqlQuery query;
    if(!query.exec("delete from Contact where idContact="+QString::number(contact->getId())+";"))
        {qDebug() << "DeleteContact : Impossible d'effectuer la requète :\n" << query.lastError();}
}

void DatabaseCRUD::addInteractionBDD(Interaction * interaction, Contact * contact){
    delete(this->date);
    this->date=new Date();
    this->date->setDateType(Date::WithHours);

    QString s="insert into Interaction(content, dateCreation, idContact) values ";
    s=s+"('"+interaction->getContent().c_str()+"', '"
            +interaction->getDate()->toString().c_str()+"', "
            +QString::number(contact->getId())+");";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}

    QString s2="insert into Modification(contentModified, dateModification, idTodo, idInteraction, idContact) values ";
    s2=s2+"('Ajout INTERACTION a <"+contact->getFirstName().c_str()+" "+contact->getLastName().c_str()+"> : "+interaction->getContent().c_str()+"', '"+this->date->toString().c_str()+"', null, last_insert_rowid(), "+QString::number(contact->getId())+");";
    QSqlQuery query2;
    if(!query2.exec(s2))
        {qDebug() << "AddInteractionModif : Impossible d'effectuer la requète :\n" << query2.lastError();}
}


void DatabaseCRUD::modifyInteractionBDD(Interaction * interaction, Contact * contact){
    delete(this->date);
    this->date=new Date();
    this->date->setDateType(Date::WithHours);

    QString s="update Interaction set ";
    s=s+"content='"+interaction->getContent().c_str()
            +"' where idInteraction="+QString::number(interaction->getId())+";";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}

    QString s2="insert into Modification(contentModified, dateModification, idTodo, idInteraction, idContact) values ";
    s2=s2+"('Modification INTERACTION de <"+contact->getFirstName().c_str()+" "+contact->getLastName().c_str()+"> : "+interaction->getContent().c_str()+"', '"+this->date->toString().c_str()+"', null, "+QString::number(interaction->getId())+", "+QString::number(contact->getId())+");";
    QSqlQuery query2;
    if(!query2.exec(s2))
        {qDebug() << "ModifContactModif : Impossible d'effectuer la requète :\n" << query2.lastError();}
}

void DatabaseCRUD::deleteInteractionBDD(Interaction * interaction, Contact * contact){
    delete(this->date);
    this->date=new Date();
    this->date->setDateType(Date::WithHours);

    QString s="update Modification set ";
    s=s+"idInteraction=null, idTodo=null where idInteraction="+QString::number(interaction->getId())+";";
    QSqlQuery query2;
    if(!query2.exec(s))
        {qDebug() << "DeleteInteractionNull : Impossible d'effectuer la requète :\n" << query2.lastError();}

    QString s2="insert into Modification(contentModified, dateModification, idTodo, idInteraction, idContact) values ";
    s2=s2+"('Suppression INTERACTION de <"+contact->getFirstName().c_str()+" "+contact->getLastName().c_str()+"> : "+interaction->getContent().c_str()+"', '"+this->date->toString().c_str()+"', null, null, "+QString::number(contact->getId())+");";
    QSqlQuery query3;
    if(!query3.exec(s2))
        {qDebug() << "DeleteInteractionModif : Impossible d'effectuer la requète :\n" << query3.lastError();}

    QSqlQuery query;
    if(!query.exec("delete from Interaction where idInteraction="+QString::number(interaction->getId())+";"))
        {qDebug() << "Delete : Impossible d'effectuer la requète :\n" << query.lastError();}
}

void DatabaseCRUD::addTagBDD(Todo * todo, Interaction * interaction, Contact * contact){
    delete(this->date);
    this->date=new Date();
    this->date->setDateType(Date::WithHours);

    QString s;
    if(todo->getDate()!=nullptr)
        {
        s="insert into Todo(content, dateTodo, idInteraction) values ";
        s=s+"('"+todo->getContent().c_str()+"', '"
                +todo->getDate()->toString().c_str()+"', "
                +QString::number(interaction->getId())+");";
        }
    else
        {
        s="insert into Todo(content, idInteraction) values ";
        s=s+"('"+todo->getContent().c_str()+"', "
                +QString::number(interaction->getId())+");";
        }
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "AddTag : Impossible d'effectuer la requète :\n" << query.lastError();}

    QString s2="insert into Modification(contentModified, dateModification, idTodo, idInteraction, idContact) values ";
    s2=s2+"('Ajout TODO a <"+interaction->getContent().c_str()+"> du contact <"+contact->getFirstName().c_str()+" "+contact->getLastName().c_str()+"> : "+todo->getContent().c_str()+"', '"+this->date->toString().c_str()+"', last_insert_rowid(), "+QString::number(interaction->getId())+", "+QString::number(contact->getId())+");";
    QSqlQuery query2;
    if(!query2.exec(s2))
        {qDebug() << "AddTagModif : Impossible d'effectuer la requète :\n" << query2.lastError();}
}


void DatabaseCRUD::modifyTagBDD(Todo * todo, Interaction * interaction, Contact * contact){
    delete(this->date);
    this->date=new Date();
    this->date->setDateType(Date::WithHours);

    QString s="update Todo set ";
    s=s+"content='"+todo->getContent().c_str();
    if(todo->getDate()==nullptr)
        s=s+"', dateTodo=NULL";
    else
        s=s+"', dateTodo='"+todo->getDate()->toString().c_str()+"'";
    s=s+" where idTodo="+QString::number(todo->getId())+";";
    QSqlQuery query;
    if(!query.exec(s))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}

    QString s2="insert into Modification(contentModified, dateModification, idTodo, idInteraction, idContact) values ";
    s2=s2+"('Modification TODO de <"+interaction->getContent().c_str()+"> du contact <"+contact->getFirstName().c_str()+" "+contact->getLastName().c_str()+"> : "+todo->getContent().c_str()+"', '"+this->date->toString().c_str()+"', "+QString::number(todo->getId())+", "+QString::number(interaction->getId())+", "+QString::number(contact->getId())+");";
    QSqlQuery query2;
    if(!query2.exec(s2))
        {qDebug() << "ModifTagModif : Impossible d'effectuer la requète :\n" << query2.lastError();}
}

void DatabaseCRUD::deleteTagBDD(Todo * todo, Interaction * interaction, Contact * contact){
    delete(this->date);
    this->date=new Date();
    this->date->setDateType(Date::WithHours);

    QString s="update Modification set ";
    s=s+"idTodo=null where idTodo="+QString::number(todo->getId())+";";
    QSqlQuery query2;
    if(!query2.exec(s))
        {qDebug() << "DeleteTodoNull : Impossible d'effectuer la requète :\n" << query2.lastError();}

    QString s2="insert into Modification(contentModified, dateModification, idTodo, idInteraction, idContact) values ";
    s2=s2+"('Suppression TODO de <"+interaction->getContent().c_str()+"> du contact <"+contact->getFirstName().c_str()+" "+contact->getLastName().c_str()+"> : "+todo->getContent().c_str()+"', '"+this->date->toString().c_str()+"', null, "+QString::number(interaction->getId())+", "+QString::number(contact->getId())+");";
    QSqlQuery query3;
    if(!query3.exec(s2))
        {qDebug() << "DeleteTodoModif : Impossible d'effectuer la requète :\n" << query3.lastError();}

    QSqlQuery query;
    if(!query.exec("delete from Todo where idTodo="+QString::number(todo->getId())+";"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
}

void DatabaseCRUD::getInteractionByContact(ListInteraction * listInteraction, Contact * contact){    
    QSqlQuery query;
    if(!query.exec("select * from Interaction where idContact="+QString::number(contact->getId())+";"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        listInteraction->removeAllInteractions();
        while(query.next())
            {
            Interaction * interaction=new Interaction(query.value(0).toInt(),
                                                      query.value(1).toString().toStdString(),
                                                      new Date(query.value(7).toString().toStdString()),
                                                      new ListTodo());
            this->getTodoByInteraction(interaction->getListTodo(), interaction);
            listInteraction->addInteraction(interaction);
            }
        }
}

void DatabaseCRUD::getTodoByInteraction(ListTodo * listTodo, Interaction * interaction){
    QSqlQuery query;
    if(!query.exec("select * from Todo where idInteraction="+QString::number(interaction->getId())+";"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        listTodo->removeAllTodos();
        while(query.next())
            {
            if(query.value(2).isNull())
                listTodo->addTodo(new Todo(query.value(0).toInt(),
                                    query.value(1).toString().toStdString(),
                                    nullptr));
            else
                listTodo->addTodo(new Todo(query.value(0).toInt(),
                                    query.value(1).toString().toStdString(),
                                    new Date(query.value(2).toString().toStdString())));

            }
        listTodo->sortTags();
        }
}

void DatabaseCRUD::fillModificationsTable(QTableWidget * modificationsTable){
    modificationsTable->setRowCount(0);
    int i=0;
    QSqlQuery query;
    if(!query.exec("select * from Modification;"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        while(query.next())
            {
            modificationsTable->insertRow(i);
            modificationsTable->setItem(i,0,new QTableWidgetItem(query.value(1).toString().toStdString().c_str()));
            modificationsTable->setItem(i,1,new QTableWidgetItem(query.value(2).toString().toStdString().c_str()));
            modificationsTable->item(i,1)->setTextAlignment(Qt::AlignCenter);
            i++;
            }
        }
}

void DatabaseCRUD::fillModificationsTableByContact(QTableWidget * modificationsTable, Contact * contact){
    modificationsTable->setRowCount(0);
    int i=0;
    QSqlQuery query;
    if(!query.exec("select * from Modification where idContact="+QString::number(contact->getId())+";"))
        {qDebug() << "Impossible d'effectuer la requète :\n" << query.lastError();}
    else
        {
        while(query.next())
            {
            modificationsTable->insertRow(i);
            modificationsTable->setItem(i,0,new QTableWidgetItem(query.value(1).toString().toStdString().c_str()));
            modificationsTable->setItem(i,1,new QTableWidgetItem(query.value(2).toString().toStdString().c_str()));
            modificationsTable->item(i,1)->setTextAlignment(Qt::AlignCenter);
            i++;
            }
        }
}


