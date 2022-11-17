#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QCalendarWidget>
#include <QObject>
#include <QDate>

class CalendarDialog : public QDialog
{
    Q_OBJECT

    private:
        QCalendarWidget * calendar;
        QPushButton * cancelButton;
        QPushButton * validateButton;

        /**
         * @brief Permet d'initialiser les éléments d'interfaces (Layout, taille, items des selecteurs, nom, et autres propriétés).
         */
        void initUI();
        /**
         * @brief Permet d'initialiser les connect.
         */
        void initConnect();

    public:
        CalendarDialog(QWidget *parent = 0);

    public slots:
        void validateCloseDialog();
        void cancelCloseDialog();

    signals:
        void emitClose(QDate *);
};

#endif // CALENDARDIALOG_H
