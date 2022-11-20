#ifndef DETAILSCONTACTDIALOG_H
#define DETAILSCONTACTDIALOG_H


#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QLabel>

#include "Contact.h"


class DetailsContactDialog : public QDialog
{
    Q_OBJECT

    private:
        Contact * contact;

        QLabel * picture;
        QPushButton * modifyButton;




    public:
        DetailsContactDialog(Contact *,QWidget *parent = 0);
        ~DetailsContactDialog();

        void initUI();
        void initConnect();
        void fillInfo();
};

#endif // DETAILSCONTACTDIALOG_H
