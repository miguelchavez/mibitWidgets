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


#include "mibittip.h"

#include <QtGui>
#include <QTimeLine>
#include <QSize>
#include <QRect>
#include <QLabel>


MibitTip::MibitTip( QWidget *parent, QWidget *partner, const QString &file )
    : QSvgWidget( parent )
{
    if (file != 0 )
        setSVG(file);

    setMaximumHeight(MAX_SIZE);
    setMinimumHeight(0);
    setFixedHeight(0);
    //save parent and partner pointers
    m_parent = parent;
    m_partner= partner;


    //create labels
    img    = new QLabel();
    layout = new QVBoxLayout();
    text   = new QLabel("");
    img->setPixmap(QPixmap("important.png")); //get emblem-important icon...
    img->setMaximumHeight(32);
    img->setAlignment(Qt::AlignCenter);
    layout->addWidget(img);
    layout->addWidget(text);
    layout->setMargin(4);
    setLayout(layout);
    text->setWordWrap(true);
    text->setMargin(5);
    ///TODO: insert the emblem-important icon.

    timeLine = new QTimeLine(1000, this);
    timeLine->setFrameRange(0, MAX_SIZE);
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(morph(int)));
}

MibitTip::~MibitTip ()
{
}

void MibitTip::showTip( const QString &msg )
{
    //get sizes
    QRect partnerGeom = m_partner->geometry();

    //calculate tip  position.
    int pw = partnerGeom.width();
    int ph = partnerGeom.height();
    int x  = partnerGeom.x() + 10;
    int y  = ph + partnerGeom.y() - 4; // the 4 is hardcoded, it must be the margin for the proper layout
    int tipWidth = pw - 20;

    //if ( tipWidth > MAX_W ) tipWidth = MAX_W; // really do this?

    setGeometry(x,y,tipWidth, height() );

    text->setText( msg );
    show();

    //make it grow
    timeLine->setDirection(QTimeLine::Forward);
    timeLine->start();
    //autoShrink
    QTimer::singleShot(5000, this, SLOT(autoHide()));
}

void MibitTip::morph(int newSize)
{
    //now it also resizes if partner is resized (window resized).
    setGeometry(QRect(m_partner->geometry().x()+10,
                      m_partner->geometry().y()+m_partner->height()-4,
                      m_partner->width()-20,
                      newSize));
    setFixedHeight(newSize);
}

void MibitTip::autoHide()
{
    timeLine->toggleDirection();//reverse!
    timeLine->start();
}

void MibitTip::setSVG(const QString &file)
{
    load(file); //we can load also from a Byte Array.
}



