/***************************************************************************
 *   Copyright (C) 2009 by Miguel Chavez Gamboa                            *
 *   miguel@lemonpos.org                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "mainview.h"
#include "ui_mainview.h"

#include "../mibittip.h"
#include "../mibitdialog.h"
#include "../mibitnotifier.h"
#include "../mibitfloatpanel.h"

#include <QDebug>
#include <QTimer>
#include <QDesktopWidget>

mainView::mainView(QWidget *parent)
    : QWidget(parent), ui(new Ui::mainView)
{
    ui->setupUi(this);

    ui->lineEdit->setEmptyMessage("Type 'mibit' to see what happens");

    tip1 = new MibitTip(this, ui->lineEdit, "tip.svg",QPixmap("important.png") );
    tip3 = new MibitTip(this, ui->btnTest3, "tip.svg", QPixmap("important.png"), tpAbove );

    dialog1 = new MibitDialog(this,"Nothing","dialog-theme.opaque.svg",QPixmap("face-smile.png"), atSlideDown );
    dialog1->setSize(300,150);


    floatPanel = new MibitFloatPanel(this,"rotated_panel.svg", Bottom);
    floatPanel->setSize(350,200);
    floatPanel->addWidget(ui->toFloat);
    QTimer::singleShot(3000,floatPanel,SLOT(showPanel()));

    notifier = new MibitNotifier(this,"notifier.svg",QPixmap("information.png"));//onTop = true

    connect(ui->btnClosePanel, SIGNAL(clicked()), floatPanel, SLOT(hideOnUserRequest()));
    connect(ui->btnQuit, SIGNAL(clicked()),qApp, SLOT(quit()));
    ui->slider->setRange(0,100);
    connect(ui->slider, SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));

    connect(ui->btnTest1, SIGNAL(clicked()), SLOT(showTip1()));
    connect(ui->btnTest3, SIGNAL(clicked()), SLOT(showTip3()));

    connect(ui->btnDialog1, SIGNAL(clicked()), SLOT(showDialog1()));
    connect(ui->btnDialog2, SIGNAL(clicked()), SLOT(showDialog2()));
    connect(ui->btnDialog3, SIGNAL(clicked()), SLOT(showDialog3()));
    connect(ui->btnDialog4, SIGNAL(clicked()), SLOT(showDialog4()));

    connect(ui->btnNotify, SIGNAL(clicked()), this, SLOT(showNotify()) );
    connect(ui->btnNotify2, SIGNAL(clicked()), this, SLOT(showNotify2()) );
    connect(ui->lineEdit,SIGNAL(textEdited(QString)), this, SLOT(checkText(QString)));

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

void mainView::showTip3()
{
    tip3->showTip("This is a demo for the mibitTip class.. We also can draw it above the control, sliding up..");
}

void mainView::showDialog1()
{
    dialog1->setSVG("dialog-theme.opaque.svg");
    dialog1->setTextColor("White");//Ensure to pass a valid Qt-CSS color name.
    dialog1->showDialog("Welcome to mibitWidgets Demo!<br>This is a completely opaque window, you can change its opacity adding transparency on the SVG.", atSlideDown);
}

void mainView::showDialog2()
{
    dialog1->setSVG("dialog-theme.svg");
    dialog1->setTextColor("Yellow"); //Ensure to pass a valid Qt-CSS color name.
    dialog1->showDialog("<html>Semi transparent Dialog, enabled by <b>transparency</b> in the <i>SVG file</i>. Also you can <b><i>shake it</i></b> to take more attention.</html>", atSlideUp);
    dialog1->setShakeTTL(9000);
    QTimer::singleShot(1000,dialog1,SLOT(shake()));
}

void mainView::showDialog3()
{
    dialog1->setSVG("dialog-theme.opaque.svg");
    dialog1->setTextColor("Gray");//Ensure to pass a valid Qt-CSS color name.
    dialog1->showDialog("Dialog with a Grow Vertically Animation. You can Change the message color with the setTextColor() method.", atGrowCenterV);
    QTimer::singleShot(1000,dialog1,SLOT(wave()));
}

void mainView::showDialog4()
{
    dialog1->setSVG("dialog-theme.svg");
    dialog1->setTextColor("Orange");//Ensure to pass a valid Qt-CSS color name.
    dialog1->showDialog("Dialog with a Grow Horizontally Animation.", atGrowCenterH);
}

void mainView::showNotify()
{
    notifier->setSize(200,100);
    notifier->setOnBottom(false);
    notifier->showNotification("This is an animated notification, sliding down from top. It is semitransparent.",5000);
}

void mainView::showNotify2()
{
    notifier->setMaxHeight(100);
    notifier->setOnBottom(true);
    notifier->showNotification("This is an animated notification, sliding up from bottom. It is completely opaque.",5000);
}

void mainView::checkText(QString text)
{
    if (text.toLower() == "mibit") ui->lineEdit->shake();
}
