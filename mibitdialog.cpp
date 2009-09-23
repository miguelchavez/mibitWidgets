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
#include <QGridLayout>

MibitDialog::MibitDialog( QWidget *parent, const QString &file, const QPixmap &icon )
{
    if (file != 0) setSVG(file);

    setMaximumHeight(MAX_SIZE);
    setMinimumHeight(150);
    //setFixedHeight(0);

    img    = new QLabel();
    layout = new QVBoxLayout();
    text   = new QLabel("");
    img->setPixmap(icon);
    img->setMaximumHeight(48); //the icon size is hardcoded now.
    img->setMaximumWidth(48);
    img->setAlignment(Qt::AlignCenter);

    setLayout(layout);
    text->setWordWrap(true);
    text->setMargin(5);

    timeLine = new QTimeLine(1000, this); //1 second animation, check later.
    timeLine->setFrameRange(0, 100); //100 steps check later
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(animate(int)));

}

MibitDialog::~MibitDialog()
{
}
