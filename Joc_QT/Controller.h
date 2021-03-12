#pragma once
#include <QDialog>
#include <QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qmessagebox.h>
#include <vector>
#include <string>
#include "ServiceGUI.h"
class Controller:  public QWidget
{
    Q_OBJECT;
private:
    QFormLayout* form= new QFormLayout{};
    QPushButton* btnContinue= new QPushButton{"&Start the game"};
public:
        QLineEdit* txtRows=new QLineEdit();
        QLineEdit* txtColumns=new QLineEdit();
        QLineEdit* txtNrWarShips=new QLineEdit();
        QLineEdit* txtNrYachts=new QLineEdit();
        QLineEdit* txtNrSubmarines=new QLineEdit();
//    Un vas de război este format din 5 pătrățele, un yacht din 3 pătrățele, iar
//   un submarin din 2 pătrățele
    Controller()
    {
        run();
        initConnect();
    }

//    Controller(ServiceGUI service)
//    {
//        this->setLayout(form);
//        initConnect();
//    }

    ~Controller()
    {
        delete form;
        delete btnContinue;
    }

    void run()
    {
        this->setLayout(form);
        form->addRow(new QLabel("Number of rows: "),txtRows);
        form->addRow(new QLabel("Number of columns: "),txtColumns);
        form->addRow(new QLabel("Number of war ships: "),txtNrWarShips);
        form->addRow(new QLabel("Number of yachts: "),txtNrYachts);
        form->addRow(new QLabel("Number of submarines: "),txtNrSubmarines);
        form->addWidget(btnContinue);

        /*auto nrRows=txtRows->text().toInt();
        auto nrColumns=txtColumns->text().toInt();
        auto nrYachts=txtNrYachts->text().toInt();
        auto nrWarShips=txtNrWarShips->text().toInt();
        auto nrSubmarines=txtNrSubmarines->text().toInt()*/;

    }

    void initConnect()
    {
        QObject::connect(btnContinue,&QPushButton::clicked,[&](){
            ServiceGUI* service= new ServiceGUI(txtRows->text().toInt(),txtColumns->text().toInt(),txtNrWarShips->text().toInt(),txtNrSubmarines->text().toInt(),txtNrYachts->text().toInt());
            service->show();
            close();
        });

    }

    void menu()
    {
//        QWidget* firstMenu=new QWidget;
//        QVBoxLayout
    }
};
