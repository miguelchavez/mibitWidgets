#include "mainview.h"
#include "ui_mainview.h"

#include "../mibittip.h"
#include "../mibitdialog.h"

#include <QDebug>
#include <QTimer>
#include <QDesktopWidget>

mainView::mainView(QWidget *parent)
    : QWidget(parent), ui(new Ui::mainView)
{
    ui->setupUi(this);

    tip1 = new MibitTip(this, ui->dtedit, "tip.svg",QPixmap("important.png") );
    tip2 = new MibitTip(this, ui->edit1, "tip.svg", QPixmap("important.png") );
    tip3 = new MibitTip(this, ui->btnTest3, "tip.svg", QPixmap("important.png"), tpAbove );

    dialog1 = new MibitDialog(this,"Welcome to mibitWidgets Demo!","dialog-theme.svg",QPixmap("face-smile.png"), atSlideDown );
    dialog1->setSize(300,150);

    connect(ui->btnTest1, SIGNAL(clicked()), SLOT(showTip1()));
    connect(ui->btnTest2, SIGNAL(clicked()), SLOT(showTip2()));
    connect(ui->btnTest3, SIGNAL(clicked()), SLOT(showTip3()));


    connect(ui->btnDialog1, SIGNAL(clicked()), SLOT(showDialog1()));
    connect(ui->btnDialog2, SIGNAL(clicked()), SLOT(showDialog2()));
    connect(ui->btnDialog3, SIGNAL(clicked()), SLOT(showDialog3()));
    connect(ui->btnDialog4, SIGNAL(clicked()), SLOT(showDialog4()));

    QTimer::singleShot(700,this,SLOT(showDialog1()));
    QTimer::singleShot(0,this,SLOT(centerWindow()));

}

mainView::~mainView()
{
    delete ui;
}

void mainView::centerWindow()
{
    QRect screenRect = QApplication::desktop()->screenGeometry(QApplication::desktop()->screenNumber(this));
    setGeometry( (screenRect.width()/2) - geometry().width()/2,
                 (screenRect.height()/2) - geometry().height()/2,
                 geometry().width(),geometry().height());
 }

void mainView::showTip1()
{
    tip1->showTip("This is a demo for the mibitTip class.. The tip slides down below its partner control.");
}

void mainView::showTip2()
{
    tip2->showTip("This is a demo for the mibitTip class.. Just more text to display.");
}

void mainView::showTip3()
{
    tip3->showTip("This is a demo for the mibitTip class.. We also can draw it above the control, sliding up..");
}

void mainView::showDialog1()
{
    dialog1->setTextColor("White");//Ensure to pass a valid Qt-CSS color name.
    dialog1->showDialog("Dialog with a slide Down Animation", atSlideDown);
}

void mainView::showDialog2()
{
    dialog1->setTextColor("Yellow"); //Ensure to pass a valid Qt-CSS color name.
    dialog1->showDialog("<html>Dialog with a <b>slide Up</b> animation. Also you can <b><i>shake it</i></b> to take more attention.</html>", atSlideUp);
    QTimer::singleShot(3000,dialog1,SLOT(shake()));
}

void mainView::showDialog3()
{
      dialog1->setTextColor("Gray");//Ensure to pass a valid Qt-CSS color name.
    dialog1->showDialog("Dialog with a Grow Vertically Animation. You can Change the message color with the setTextColor() method.", atGrowCenterV);
}

void mainView::showDialog4()
{
      dialog1->setTextColor("Orange");//Ensure to pass a valid Qt-CSS color name.
    dialog1->showDialog("Dialog with a Grow Horizontally Animation.", atGrowCenterH);
}
