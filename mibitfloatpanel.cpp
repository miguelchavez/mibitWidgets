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

#include "mibitfloatpanel.h"

#include <QPixmap>
#include <QString>
#include <QHBoxLayout>
#include <QTimeLine>
#include <QTimer>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>

MibitFloatPanel::MibitFloatPanel(QWidget *parent, const QString &file, PanelPosition position)
        : QSvgWidget( parent )
{
    setMouseTracking(true);

    if (file != 0) setSVG(file);

    m_position = position;
    m_parent = parent;
    m_fileName = file;
    canBeHidden = false; //at the begining is hiden.
    setMinimumHeight(100);
    setMinimumWidth(100);
    setMaxHeight(100);
    setMaxWidth(100);
    setFixedHeight(0);
    animRate = 500; //default animation speed (half a second rate).

    hLayout    = new QHBoxLayout();
    setLayout(hLayout);



    QRect windowGeom = m_parent->geometry();
    int midPointX = (windowGeom.width()/2);
    int newX; int newW;
    QRect dRect;
    int pheight = m_parent->geometry().height();
    if (maxWidth < pMinW ) newW = pMinW; else newW = maxWidth;
    if ((midPointX-(newW/2)) < 0) newX = 0; else newX = midPointX - (newW/2);
    dRect.setX(newX);
    dRect.setY(height()/2);
    setFixedWidth(newW);
    setGeometry(dRect);



    timeLine  = new QTimeLine(animRate, this);
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(animate(int)));
    connect(timeLine,SIGNAL(finished()), this, SLOT(onAnimationFinished()));
}

void MibitFloatPanel::addWidget(QWidget * widget)
{
    hLayout->addWidget(widget, 0, Qt::AlignCenter);
}

void MibitFloatPanel::showPanel()
{
    if (timeLine->state() == QTimeLine::NotRunning && !canBeHidden) {
        setGeometry(-1000,-1000,0,0);
        show();
        //update steps for animation, now that the window is showing.
        int maxStep; int minStep = 0;

        //FIXME: add left and right positions!
        if ( m_position == Top ) {
            minStep = -maxHeight+10;
            maxStep =  -6;
        } else {
            maxStep = m_parent->geometry().height()-maxHeight;
            minStep = m_parent->geometry().height()-10;
        }
//        qDebug()<<" MaxStep:"<<maxStep<<" MinStep:"<<minStep<<" pos "<<m_position;

        timeLine->setFrameRange(minStep,maxStep);
        //make it grow
        timeLine->setDirection(QTimeLine::Forward);
        timeLine->start();

    } //else qDebug()<<"Panel is already showing... "<<geometry();
}

void MibitFloatPanel::animate(const int &step)
{
    //get some sizes...
    QRect windowGeom = m_parent->geometry();
    int midPointX = (windowGeom.width()/2);
    int newX; int newW;
    QRect dRect;
    int pheight = m_parent->geometry().height();
    if (maxWidth < pMinW ) newW = pMinW; else newW = maxWidth;
    if ((midPointX-(newW/2)) < 0) newX = 0; else newX = midPointX - (newW/2);

    dRect.setX(newX);
    setFixedWidth(newW);

    dRect.setY(step);
    setGeometry(dRect);
    setFixedHeight(maxHeight);

    if (m_position == Top) { // Sliding from top
        if (step == -maxHeight+10) {
            setFixedHeight(maxHeight);
        }
    } else {       // Sliding from bottom
        if (step == m_parent->geometry().height()-10) {
            setFixedHeight(maxHeight);
        }
    } 
    //qDebug()<<"Step:"<<step<< "Height:"<< rect().height()<<" maxHeight:"<<maxHeight<<" Position:"<<m_position;
}

void MibitFloatPanel::hideOnUserRequest()
{
    hideDialog();
}

void MibitFloatPanel::hideDialog()
{
    if ( canBeHidden ) {
        timeLine->setDirection(QTimeLine::Backward); //reverse!
        timeLine->start();
    }
}

void MibitFloatPanel::onAnimationFinished()
{
    if (timeLine->direction() == QTimeLine::Forward) {
        canBeHidden = true;
    } else canBeHidden = false;
}

void MibitFloatPanel::setPosition(const PanelPosition pos)
{
    // only changes the position when the notification is not showing..
    if (timeLine->state() == QTimeLine::NotRunning && size().height() <= 0)  m_position = pos;
}


void MibitFloatPanel::setSVG(const QString &file)
{
    load(file);
}


void MibitFloatPanel::enterEvent ( QEvent * event )
{
    QTimer::singleShot(100,this,SLOT(showPanel()));
}

void MibitFloatPanel::leaveEvent( QEvent *event )
{
    QTimer::singleShot(100,this,SLOT(hideOnUserRequest()));
}

MibitFloatPanel::~MibitFloatPanel() {}


