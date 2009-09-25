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
#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QtGui/QWidget>
class MibitTip;
class MibitDialog;

namespace Ui
{
    class mainView;
}

class mainView : public QWidget
{
    Q_OBJECT

public:
    mainView(QWidget *parent = 0);
    ~mainView();

private:
    Ui::mainView *ui;
    MibitTip *tip1;
    MibitTip *tip2;
    MibitTip *tip3;
    MibitDialog *dialog1;
private slots:
    void centerWindow();
    void showTip1();
    void showTip2();
    void showTip3();
    void showDialog1();
    void showDialog2();
    void showDialog3();
    void showDialog4();
};

#endif // MAINVIEW_H
