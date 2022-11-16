#include "CalendarDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

CalendarDialog::CalendarDialog(QWidget *parent)
    : QDialog(parent)
{
    setModal(true);

    this->calendar=new QCalendarWidget(this);
    this->cancelButton=new QPushButton("Annuler");
    this->validateButton=new QPushButton("Valider");

    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QHBoxLayout * buttonLayout=new QHBoxLayout();

    buttonLayout->addWidget(this->cancelButton);
    buttonLayout->addWidget(this->validateButton);

    mainLayout->addWidget(this->calendar);
    mainLayout->addLayout(buttonLayout);

}
