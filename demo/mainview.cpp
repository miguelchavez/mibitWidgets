#include "mainview.h"
#include "ui_mainview.h"

#include "mibittip.h"
#include "mibitdialog.h"

#include <QDebug>
#include <QTimer>

mainView::mainView(QWidget *parent)
    : QWidget(parent), ui(new Ui::mainView)
{
    ui->setupUi(this);

    tip1 = new MibitTip(this, ui->dtedit, "tip.svg",QPixmap("important.png") );
    tip2 = new MibitTip(this, ui->edit1, "tip.svg", QPixmap("important.png") );
    tip3 = new MibitTip(this, ui->btnTest3, "tip.svg", QPixmap("important.png"), tpAbove );

    dialog1 = new MibitDialog(this,"Welcome to mibitWidgets Demo!","dialog-theme.svg",QPixmap("face-smile.png"), atSlideDown );
    dialog1->setSize(200,100);

    connect(ui->btnTest1, SIGNAL(clicked()), SLOT(showTip1()));
    connect(ui->btnTest2, SIGNAL(clicked()), SLOT(showTip2()));
    connect(ui->btnTest3, SIGNAL(clicked()), SLOT(showTip3()));


    connect(ui->btnDialog2, SIGNAL(clicked()), SLOT(showDialog2()));

    QTimer::singleShot(500,this,SLOT(showDialog1()));

}

mainView::~mainView()
{
    delete ui;
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
    dialog1->showDialog();
}

void mainView::showDialog2()
{
    dialog1->showDialog("Dialog with a slide down animation!", atSlideDown);
}
