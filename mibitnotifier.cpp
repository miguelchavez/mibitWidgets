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

#include "mibitnotifier.h"

#include <QPixmap>
#include <QIcon>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimeLine>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

MibitNotifier::MibitNotifier(QWidget *parent, const QString &file, const QPixmap &icon, const QPixmap &closeIcon, const bool &onTop)
        : QSvgWidget( parent )
{
    if (file != 0) setSVG(file);

    m_parent = parent;
    m_onTop = onTop;
    closedByUser = false;
    m_fileName = file;
    setMinimumHeight(100);
    setFixedSize(0,0); //until show we grow it
    setMaxHeight(max_H); //default sizes
    setMaxWidth(max_W);
    animRate = 500; //default animation speed (half second rate).

    img        = new QLabel();
    hLayout    = new QHBoxLayout();
    message    = new QLabel("");
    btnClose   = new QLabel(""); //only an image


    img->setPixmap(icon);
    img->setMaximumHeight(54); //the icon size is hardcoded now.
    img->setMaximumWidth(54);
    img->setAlignment(Qt::AlignLeft);
    img->setMargin(4);

    btnClose->setPixmap(closeIcon);
    btnClose->setMaximumHeight(34); //the icon size is hardcoded now.
    btnClose->setMaximumWidth(38);
    btnClose->setToolTip("Close Notification"); //what about translations?
    btnClose->setFixedSize(38,36);

    setLayout(hLayout);
    message->setWordWrap(true);
    message->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
    message->setMargin(10);

    hLayout->addWidget(img,0,Qt::AlignLeft);
    hLayout->addWidget(message,1,Qt::AlignLeft);
    hLayout->addWidget(btnClose,0,Qt::AlignRight);

    timeLine  = new QTimeLine(animRate, this);
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(animate(int)));
    connect(btnClose,SIGNAL(clicked()),this, SLOT(hideOnUserRequest()));
    connect(timeLine,SIGNAL(finished()), this, SLOT(onAnimationFinished()));
}

void MibitNotifier::showNotification( const QString &msg, const int &timeToLive) //timeToLive = 0 : not auto hide it.
{
    //set default msg if the sent is empty.
    if (msg.isEmpty()) setMessage(message->text()); else setMessage( msg );

    if (!m_onTop) setSVG("rotated_"+m_fileName); else setSVG(m_fileName);

    setGeometry(-1000,-1000,0,0);
    show();
    //update steps for animation, now that the window is showing.

    int maxStep; int minStep = 0;

    if ( m_onTop ) {
        maxStep = maxHeight;
        minStep = 0;
    } else {
        maxStep = m_parent->geometry().height()-maxHeight;
        minStep = m_parent->geometry().height();
    }

    timeLine->setFrameRange(minStep,maxStep);
    //make it grow
    timeLine->setDirection(QTimeLine::Forward);
    timeLine->start();
    btnClose->setFocus();

    if (timeToLive > 0 ) QTimer::singleShot(timeToLive,this,SLOT(hideDialog()));
}

void MibitNotifier::animate(const int &step)
{
    //get some sizes...
    QRect windowGeom = m_parent->geometry();
    int midPointX = (windowGeom.width()/2);
    int newX; int newW;
    QRect dRect;
    int pheight = m_parent->geometry().height();
    if (maxWidth < min_W ) newW = min_W; else newW = maxWidth;
    if ((midPointX-(newW/2)) < 0) newX = 0; else newX = midPointX - (newW/2);

    dRect.setX(newX);
    setFixedWidth(newW);

    if (m_onTop) { // Sliding from top
        dRect.setY(0);
        setGeometry(dRect);
        setFixedHeight(step);
    } else {       // Sliding from bottom
        int nh = pheight-step;
        if ( nh < min_H ) nh = min_H;
        dRect.setY(step);
        setGeometry(dRect);
        setFixedHeight(nh);

    }
}

void MibitNotifier::hideOnUserRequest()
{
    hideDialog();
    closedByUser = true;
}

void MibitNotifier::hideDialog()
{
    if ( !closedByUser ) {
        timeLine->toggleDirection();//reverse!
        timeLine->start();
    } else closedByUser = !closedByUser;
}

void MibitNotifier::onAnimationFinished()
{
    if (timeLine->direction() == QTimeLine::Backward) {
        close();
    }
}

void MibitNotifier::setOnBottom(const bool &sOnBottom)
{
    m_onTop = !sOnBottom;
}


void MibitNotifier::setSVG(const QString &file)
{
    load(file);
}

void MibitNotifier::setIcon(const QPixmap &icon)
{
     img->setPixmap(icon);
 }

void MibitNotifier::setMessage(const QString &msg)
{
    message->setText(msg);
}

void MibitNotifier::setTextColor(const QString &color)
{
    message->setStyleSheet(QString("color:%1").arg(color));
}

void MibitNotifier::mousePressEvent ( QMouseEvent * )
{
    hideOnUserRequest();
}


void MibitNotifier::keyPressEvent ( QKeyEvent * event )
{
    if ( event->key() == Qt::Key_Escape )
    {
        hideOnUserRequest();
    } //else ignore event.
}


MibitNotifier::~MibitNotifier() {}


