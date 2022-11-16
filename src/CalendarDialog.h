#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QCalendarWidget>


class CalendarDialog : public QDialog
{
    Q_OBJECT

    private:
        QCalendarWidget * calendar;
        QPushButton * cancelButton;
        QPushButton * validateButton;


public:
    CalendarDialog(QWidget *parent = 0);
};

#endif // CALENDARDIALOG_H
