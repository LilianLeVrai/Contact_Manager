#ifndef DETAILSCONTACTDIALOG_H
#define DETAILSCONTACTDIALOG_H


#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

#include "MessageLabel.h"
#include "EditContactDialog.h"
#include "Contact.h"


class DetailsContactDialog : public QDialog
{
    Q_OBJECT

    private:
        Contact * contact;

        MessageLabel * errorMessage;
        QLabel * picture;
        QPushButton * modifyContactButton;

        QLabel * infoContactLabel;
        QComboBox * interactionCombobox;
        QPushButton * addInteractionButton;
        QPushButton * removeInteractionButton;

        EditContactDialog * modifyContactDialog;



    public:
        DetailsContactDialog(Contact *,QWidget *parent = 0);
        ~DetailsContactDialog();

        void initUI();
        void initConnect();
        void fillInfo();



    public slots:
        void openModifyContactDialog();
        void editContact(Contact*, bool);

    signals:
        void emitModifyContact(Contact*, bool);
};

#endif // DETAILSCONTACTDIALOG_H
