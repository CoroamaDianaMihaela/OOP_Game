#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <QBrush>
#include <QFont>
#include <vector>
#include <string>

using namespace std;


class Final:public QWidget{

public:
    QVBoxLayout* finLay= new QVBoxLayout{};
    QTableWidget* finTab= new QTableWidget;
    QLabel* msg= new QLabel;
    QPalette p;

    Final(int n, int m, QVector<QPoint> PCShips){
        this->setWindowTitle("The Game ended");
        setLayout(finLay);


        finTab->setRowCount(n);
        finTab->setColumnCount(m);

        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++)
                finTab->setItem(i,j, new QTableWidgetItem(" "));


        p= finTab->palette();
        p.setColor(QPalette::Base,QColor(125,186,255));
        finTab->setPalette(p);

        for(auto const& pct:PCShips)
            finTab->item(pct.x(),pct.y())->setBackground(QColor(219,13,27));


        finTab->resizeRowsToContents();
        finTab->resizeColumnsToContents();


        msg->setText( "The PC won. This was the PC's table");
        finLay->addWidget(msg);
        finLay->addWidget(finTab);


    }

    ~Final(){
        delete finTab;
        delete finLay;
        delete msg;
    };

};



class Game: public QWidget{
public:
    Game(int n, int m, QVector<QPoint> userInputShips, QVector<QPoint> PCInputShips){
        PCscore=0;
        Userscore=0;
        nrRows=n;
        nrColumns=m;
        userShips=userInputShips;
        PCShips=PCInputShips;
        initJoc();
        initConnect();
    };

    ~Game(){
        delete tblUser;
        delete tblPC;
        delete label;
        delete label_2;
        delete mainLay;
        delete secLay;
    }
private:
    int PCscore;
    int Userscore;
    int nrRows;
    int nrColumns;
    QVector<QPoint> movePC;
    QPalette p;
    QTableWidget* tblUser= new QTableWidget;
    QTableWidget* tblPC= new QTableWidget;
    QLabel* label= new QLabel{" Waiting for the game to start.. " };
    QLabel* label_2= new QLabel{ };
    QVector<QPoint> userShips;
    QVector<QPoint> PCShips;
    QVBoxLayout* mainLay= new QVBoxLayout{};
    QHBoxLayout* secLay= new QHBoxLayout{};
    QHBoxLayout* thrLay=new QHBoxLayout{};
    void initJoc(){

        this->setLayout(mainLay);
        tblUser->setRowCount(nrRows);
        tblUser->setColumnCount(nrColumns);
        tblPC->setRowCount(nrRows);
        tblPC->setColumnCount(nrColumns);

        for(int i=0;i<=nrRows;i++)
            for(int j=0;j<=nrColumns;j++){
                tblUser->setItem(i,j, new QTableWidgetItem(" "));
                tblPC->setItem(i,j, new QTableWidgetItem("  "));
}

        p= tblUser->palette();
        p.setColor(QPalette::Base,QColor(125,186,255));
        tblUser->setPalette(p);
        p= tblPC->palette();
        p.setColor(QPalette::Base,QColor(125,186,255));
        tblPC->setPalette(p);
        tblUser->resizeRowsToContents();
        tblUser->resizeColumnsToContents();
        tblPC->resizeRowsToContents();
        tblPC->resizeColumnsToContents();


        secLay->addWidget(tblUser);
        secLay->addWidget(label_2);
        mainLay->addLayout(secLay);
        thrLay->addWidget(tblPC);
        thrLay->addWidget(label);
        mainLay->addLayout(secLay);
        mainLay->addLayout(thrLay);
        mainLay->addSpacing(30);

        this->setMaximumSize(1800,2000);
        this->setMinimumSize(800,300);


    };

    bool pcMove(){
        QPoint p;
        int x,y;
        if(movePC.isEmpty()){
            x= rand() % nrRows;
            y= rand() % nrColumns;
            p.setX(x);
            p.setY(y);
        }else{
             p = movePC.back();
             movePC.pop_back();
        }

        while(tblUser->item(p.x(),p.y())->background().color()==QColor(219,13,27) || tblUser->item(p.x(),p.y())->background().color()==Qt::white )
        {
            if(movePC.isEmpty()){
                x= rand() % nrRows;
                y= rand() % nrColumns;
                p.setX(x);
                p.setY(y);
            }else{
                p = movePC.back();
                movePC.pop_back();
            }
        }
        if(userShips.contains(p)==true){
            tblUser->item(p.x(),p.y())->setBackground(QColor(219,13,27));
            PCscore+=1;
            label_2->setText(" Calculator: ATINS ");
            if(p.x()+1<nrRows)
                movePC.push_back(QPoint(p.x()+1,p.y()));
            if(p.y()+1<nrColumns)
                movePC.push_back(QPoint(p.x(),p.y()+1));
            if(p.x()-1>=0)
                movePC.push_back(QPoint(p.x()-1,p.y()));
            if(p.y()-1>=0)
                movePC.push_back(QPoint(p.x(),p.y()-1));
        }else{
            tblUser->item(p.x(),p.y())->setBackground(Qt::white);
            label_2->setText(" Calculator: AER ");
        }

        if (Userscore== PCShips.size() && PCscore==userShips.size() ){
            QMessageBox::about(this,"The Game ended", "It's a tie");
            return true;
        }
        else if(PCscore==userShips.size())
        {
            Final* f = new Final(nrRows, nrColumns, PCShips);
            f->show();
            return true;
        }

        return false;
    };

    void initConnect(){
        QObject::connect(tblPC,&QTableWidget::cellClicked,[&](){

            int crtRow= tblPC->currentRow();
            int crtColumn= tblPC->currentColumn();

            QPoint p;
            p.setX(crtRow);

            p.setY(crtColumn);
            if(tblPC->item(p.x(),p.y())->background().color()==QColor(219,13,27) || tblPC->item(p.x(),p.y())->background().color()==Qt::white)
                QMessageBox::warning(this,"Imposibil","You already pressed this button");
            else{
                if(PCShips.contains(p)==true)
                {
                tblPC->item(crtRow,crtColumn)->setBackground(QColor(219,13,27));
                Userscore+=1;

                label->setText(" Utilizator: ATINS ");

            }else{
                label->setText(" Utillizator: AER ");
                tblPC->item(crtRow,crtColumn)->setBackground(Qt::white);
            }


            bool gata=pcMove();

            if(gata==true)
                close();
            else
                if(Userscore==PCShips.size())
                {
                    QMessageBox::about(this,"The Game ended", "The User Won");
                    close();
                }

            }

        });

    }

};

//#pragma once
//#include <QDialog>
//#include <QApplication>
//#include <QtWidgets/qlabel.h>
//#include <QtWidgets/qpushbutton.h>
//#include <QtWidgets/qboxlayout.h>
//#include <QtWidgets/qformlayout.h>
//#include <QtWidgets/qlistwidget.h>
//#include <QtWidgets/qlineedit.h>
//#include <QtWidgets/qtablewidget.h>
//#include <QtWidgets/qmessagebox.h>
//#include <QtWidgets/qstyle.h>
//#include <QVector>
//#include <vector>
//#include <string>
//#include "Controller.h"
//#include "BoardGame.h"
//using std::vector;
//using std::string;

//class Game:public QWidget{
//private:


//public:
//    QTableWidget* tblUser=new QTableWidget;
//    QTableWidget* tblPC=new QTableWidget;
//    QHBoxLayout* ly=new QHBoxLayout{};
//    QLabel* actiunePc=new QLabel{"Action Pc"};
//    QLabel* actiuneUser=new QLabel{"Action User"};
//    QVBoxLayout* buttons=new QVBoxLayout{};
//    QVector<QPoint> user;
//    QVector<QPoint> PC;

//    Game(int nrRow, int nrColumns, QVector<QPoint> userPoints, QVector<QPoint> PCPoints)
//    {
//        this->init(nrRow,nrColumns);
//        QVector<QPoint> user=userPoints;
//        QVector<QPoint> PC=PCPoints;
//    }
//    void init(int nrRows, int nrColumns)
//    {
//        this->setLayout(ly);

//        tblUser->setRowCount(nrRows);
//        tblUser->setColumnCount(nrColumns);
//        tblPC->setRowCount(nrRows);
//        tblPC->setColumnCount(nrColumns);
//        for(int i=0;i<nrRows;i++)
//         { for(int j=0;j<nrColumns;j++)
//          {
//              tblPC->setItem(i,j,new QTableWidgetItem(" "));
//              tblUser->setItem(i,j,new QTableWidgetItem(" "));
//          }
//        }
//        tblPC->resizeRowsToContents();
//        tblPC->resizeColumnsToContents();
//        tblUser->resizeRowsToContents();
//        tblUser->resizeColumnsToContents();

//        buttons->addWidget(actiunePc);
//        buttons->addWidget(actiuneUser);

//        ly->addWidget(tblPC);
//        ly->addLayout(buttons);
//        ly->addWidget(tblUser);


//    }

//    void initConnect()
//    {
//        QObject::connect(tblUser,&QTableWidget::doubleClicked,[&](){

//            QPoint p;
//            p.setX(tblUser->currentRow());
//            p.setY(tblUser->currentColumn());
//            if(PC.contains(p))
//            {
//                tblUser->item(tblUser->currentRow(),tblUser->currentColumn())->setBackground(QColor(219,13,27));

//            }
//            else
//            {


//            }


//        });


//    }
//    void startGame()
//    {




//    }

//};
