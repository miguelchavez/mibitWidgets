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

#ifndef MIBITFLOATPANEL_H
#define MIBITFLOATPANEL_H

#include <QSvgWidget>
class QTimeLine;
class QString;
class QHBoxLayout;
class QLabel;
class QPixmap;

/**
  * This class is used to display an animated floating panel
  * on Top, Bottom, Left or Right edges of the parent.
  * Are svg themed and borderless.
  *
  */

//namespace MibitFloatPanel {

    enum PanelPosition  {Top = 1, Bottom = 2, Left = 3, Right = 4 };
    enum PanelConstants {pMimH= 100, pMinW = 100 };


class MibitFloatPanel : public QSvgWidget
{
Q_OBJECT
public:
    MibitFloatPanel(QWidget *parent = 0, const QString &file = 0, PanelPosition position = Top);
    ~MibitFloatPanel();
    void addWidget(QWidget * widget);
    void hidePanel();
    void setPosition(const PanelPosition pos);
    void setSVG(const QString &file);
    void setMaxHeight(const int &m)   { setMaximumHeight(m); maxHeight = m; }
    void setMaxWidth(const int &m)   { setMaximumWidth(m); maxWidth = m; }
    void setSize( const int &w, const int &h ) { setMaxHeight(h); setMaxWidth(w); }
private:
    QTimeLine *timeLine;
    QHBoxLayout *hLayout;
    QWidget *m_parent;
    QString m_fileName;
    bool canBeHidden;
    int maxHeight;
    int maxWidth;
    int animRate;
    PanelPosition m_position;
private slots:
    void animate(const int &step);
    void hideDialog();
    void hideOnUserRequest();
    void onAnimationFinished();
    void showPanel();
protected:
    void enterEvent ( QEvent * event );
    void leaveEvent ( QEvent * event );
};

//} //end namespace
#endif // MIBITFLOATPANEL_H