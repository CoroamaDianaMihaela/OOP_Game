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
#include <QtWidgets/qstyle.h>
#include <vector>
#include <string>
#include "Controller.h"
using std::vector;
using std::string;
class Dialog : public QDialog
{
private:
    QHBoxLayout *main_layout=new QHBoxLayout{};
    QListWidget* ly= new QListWidget;
    QPushButton* btnStart= new QPushButton{"&Start"};

public:

    Dialog()
    {
        initStart();
        initConnect();
    }

    ~Dialog()
    {
        delete main_layout;
        delete ly;
        delete btnStart;
    }


    void initStart()
    {

            this->setLayout(main_layout);

            QPixmap image("C:\\Users\\GEMENELE\\Pictures\\barci_2.jpg");

            QLabel *imageLabel = new QLabel();
            imageLabel->setPixmap(image);

            QVBoxLayout *img_ly= new QVBoxLayout{};
            img_ly->addWidget(imageLabel);
            img_ly->addWidget(btnStart);
            btnStart->setStyleSheet( "background-color: rgb(135,206,250)");

            main_layout->addLayout(img_ly);

    }


    void initConnect()
    {
        QObject::connect(btnStart,&QPushButton::clicked,[&](){
           close();
           Controller* contr= new Controller{};
           contr->show();
        });

    }

//    void loadData()
//    {
//        vector<string> listProducts={"prod1","prod2","prod3","prod4","prod5","prod6"};
//        for(string word : listProducts)
//        {
//            ly->addItem(QString::fromStdString(word));
//        }
//    }


//    void initGUI(){

//    main_layout->addWidget(ly);

//    QHBoxLayout *secondary_layout= new QHBoxLayout{};
//    secondary_layout->addWidget(new QLabel{"Wassap"});
//    secondary_layout->addWidget(new QLineEdit);

//    main_layout->addLayout(secondary_layout);

////    VBoxLayout
//    QVBoxLayout *third_ly= new QVBoxLayout{};
//    third_ly->addWidget(new QLabel{"Wassap"});
//    third_ly->addWidget(new QLabel{"Sup"});
//    third_ly->addWidget(new QLabel{"was"});
//    third_ly->addWidget(new QLabel{"Yahoink"});
//    main_layout->addLayout(third_ly);

//    //form Layout
//    auto addLy= new QVBoxLayout{};

//    auto formLy= new QFormLayout{};
//    formLy->addRow("Nume",new QLineEdit);
//    formLy->addRow("Prenume",new QLineEdit);
//    formLy->addRow("Varsta",new QLineEdit);
//    formLy->addRow("Badassery",new QLineEdit);

//    addLy->addLayout(formLy);
//    auto lyBtn = new QHBoxLayout{};
//    lyBtn->addWidget(new QPushButton{"&Adauga"});
//    lyBtn->addWidget(new QPushButton{"&Sterge"});
//    lyBtn->addWidget(new QPushButton{"&Modifica"});
//    lyBtn->addWidget(btnExit);
//    addLy->addLayout(lyBtn);


//    main_layout->addLayout(addLy);

//};

};
