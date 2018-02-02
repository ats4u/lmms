/*
 * ComboBox2.h - class ComboBox2, a combo box view for models
 *
 * Copyright (c) 2006-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 *
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#ifndef COMBOBOX2_H
#define COMBOBOX2_H

#include <QMenu>
#include <QWidget>

#include "ComboBoxModel2.h"
#include "AutomatableModelView.h"



class EXPORT ComboBox2 : public QWidget, public IntModelView
{
	Q_OBJECT
public:
	ComboBox2( QWidget* parent = NULL, const QString& name = QString() );
	virtual ~ComboBox2();

	ComboBoxModel2* model()
	{
		return castModel<ComboBoxModel2>();
	}

	const ComboBoxModel2* model() const
	{
		return castModel<ComboBoxModel2>();
	}

public slots:
	void selectNext();
	void selectPrevious();


protected:
	virtual void contextMenuEvent( QContextMenuEvent* event );
	virtual void mousePressEvent( QMouseEvent* event );
	virtual void paintEvent( QPaintEvent* event );
	virtual void wheelEvent( QWheelEvent* event );


private:
	static QPixmap* s_background;
	static QPixmap* s_arrow;
	static QPixmap* s_arrowSelected;

	QMenu m_menu;

	bool m_pressed;


private slots:
	void setItem( QAction* item );

} ;

#endif
