#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QComboBox>


class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QPushButton * searchButton;
    QLineEdit * searchLineEdit;
    QTableView * contactsTable;
    QComboBox * filtersCombobox;
    QComboBox * sortCombobox;





public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
