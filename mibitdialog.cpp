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

#include "mibitdialog.h"

#include <QPixmap>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimeLine>
#include <QPushButton>
#include <QDebug>

MibitDialog::MibitDialog( QWidget *parent, const QString &msg, const QString &file, const QPixmap &icon, AnimationType animation )
        : QSvgWidget( parent )
{
    if (file != 0) setSVG(file);

    m_parent = parent;
    animType = animation;
    setMinimumHeight(150);
    setFixedSize(0,0); //until show we grow it
    setMaxHeight(maxH); //default sizes
    setMaxWidth(maxW);


    img      = new QLabel();
    hLayout   = new QHBoxLayout();
    vLayout  = new QVBoxLayout();
    text     = new QLabel(msg);
    btnClose = new QPushButton("Close"); ///TODO: what about translations???


    img->setPixmap(icon);
    img->setMaximumHeight(48); //the icon size is hardcoded now.
    img->setMaximumWidth(48);
    img->setAlignment(Qt::AlignLeft);

    btnClose->setMaximumWidth(120);
    btnClose->setShortcut(Qt::Key_Escape);

    setLayout(vLayout);
    text->setWordWrap(true);
    text->setMargin(5);

    hLayout->addWidget(img,0,Qt::AlignLeft);
    hLayout->addWidget(text,0,Qt::AlignLeft);
    vLayout->addLayout(hLayout,0);
    vLayout->addWidget(btnClose,0,Qt::AlignCenter);

    timeLine = new QTimeLine(800, this); //1 second animation, check later.
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(animate(int)));
    connect(btnClose,SIGNAL(clicked()),this, SLOT(hideDialog()));
    connect(timeLine,SIGNAL(finished()), this, SLOT(onAnimationFinished()));
}

MibitDialog::~MibitDialog()
{
}


void MibitDialog::showDialog(const QString &msg, AnimationType animation )
{
    //set default msg if the sent is empty. Also set the animation -the same way-.
    if (msg.isEmpty()) setMessage(text->text()); else setMessage( msg );
    if (animation == 0) setAnimationType( atSlideDown ); else setAnimationType( animation );

    show();
    //update steps for animation, now that the window is showing.
    int maxStep; int minStep = 0;
    if ( animType == atSlideDown || animType == atSlideUp ) {
        maxStep = (m_parent->geometry().height()/2)-(maxHeight/2);
        minStep = -maxHeight;
        //timeLine->setCurveShape(QTimeLine::EaseOutCurve); //QTimeLine::SineCurve: Hacerlo criticamente amortiguado
    } else if ( animType == atGrowCenterH ) maxStep = maxWidth;
    else maxStep=maxHeight;

    timeLine->setFrameRange(minStep,maxStep);
    //make it grow
    timeLine->setDirection(QTimeLine::Forward);
    timeLine->start();

    btnClose->setFocus();
}

void MibitDialog::animate(int step)
{
    //get some sizes...
    int textW = text->width();
    int textH = text->height();
    int btnH = btnClose->height();
    QRect windowGeom = m_parent->geometry();
    int midPointX = (windowGeom.width()/2);
    int midPointY = (windowGeom.height()/2);
    int newY;
    int newX;
    if ((midPointX-(maxWidth/2)) < 0) newX = 0; else newX = midPointX - maxWidth/2;
    if ((midPointY-(maxHeight/2)) < 0) newY = 0; else newY = midPointY - maxHeight/2;

    QRect dRect;
    switch (animType) {
        case atGrowCenterV:   // Grow from Center Vertically.. to up and down
            //
        break;
        case atGrowCenterH:   // Grow from Center Horizontally... from left to right
        break;
        case atSlideDown:    // Slide down
            dRect.setX(newX);
            dRect.setY(step);
            dRect.setWidth(maxWidth);
            dRect.setHeight(maxHeight);
            setGeometry(dRect);

            setFixedHeight(maxHeight);
            setFixedWidth(maxWidth);
        break;
        case atSlideUp:     // Slide up
        break;
        default:
        break;
    }
}

void MibitDialog::hideDialog()
{
    timeLine->toggleDirection();//reverse!
    timeLine->start();
}

void MibitDialog::onAnimationFinished()
{
    if (timeLine->direction() == QTimeLine::Backward) {
        close();
        //qDebug()<<"Animation finished and it was in backward direction";
    } else
}


void MibitDialog::setSVG(const QString &file)
{
    load(file);
}

void MibitDialog::setIcon(const QPixmap &icon)
{
     img->setPixmap(icon);
 }

void MibitDialog::setMessage(const QString &msg)
{
    text->setText(msg);
}
