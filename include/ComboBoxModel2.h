/*
 * ComboBoxModel2.h - declaration of class ComboBoxModel2
 *
 * Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
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

#ifndef COMBOBOX_MODEL2_H
#define COMBOBOX_MODEL2_H

#include <QtCore/QVector>
#include <QtCore/QPair>

#include "AutomatableModel.h"
#include "embed.h"

class PixmapLoader;


class EXPORT ComboBoxModel2 : public IntModel
{
	Q_OBJECT
public:
	ComboBoxModel2( Model* parent = NULL,
					const QString& displayName = QString(),
					bool isDefaultConstructed = false ) :
		IntModel( 0, 0, 0, parent, displayName, isDefaultConstructed )
	{
	}

	virtual ~ComboBoxModel2()
	{
		clear();
	}

	void addItem( const QString& text, 
			PixmapLoader* pixmapLoader = NULL, 
			const bool & isSeparator = false )
	{
		// m_separators.push_back( false );
		Item i( text, pixmapLoader, isSeparator );
		items.push_back( i );
		setRange( 0, items.size() - 1 );
	}

	void clear() {
		for ( Item& i : items )
			delete ( i.pixmapLoader );

		items.clear();
		setRange( 0, 0 );
		emit propertiesChanged();
	}

	const int findText( const QString& text ) const
	{
		for( QVector<Item>::ConstIterator it = items.begin(); it != items.end(); ++it )
		{
			if( ( *it ).text == text )
			{
				return it - items.begin();
			}
		}
		return -1; 
	}


	// current
	const QString currentText() const
	{
		return isValid() ?  ( items[ value() ].text         )  : nullptr;
	}
	const PixmapLoader* currentData() const
	{
		return isValid() ?   ( items[ value() ].pixmapLoader ) : NULL;
	}
	const bool currentSeparator() const
	{
		return isValid() ?   ( items[ value() ].isSeparator  ) : false;
	}

	// text
	const QString itemText( int i ) const
	{
		return  isValid() ? ( items[ i ].text ) : QString();
	}
	void setItemText( int i, QString text ) {
		if ( isValid( i ) )
			items[ i ].text = text;
	}

	// pixmapLoader
	const PixmapLoader* itemPixmap( int i ) const
	{
		return isValid( i ) ? ( items[ i ].pixmapLoader ) : NULL;
	}
	void setItemPixmap( int i, PixmapLoader* pixmapLoader )
	{
		if ( isValid( i ) )
			items[ i ].pixmapLoader = pixmapLoader;
	}

	// separator
	const bool itemSeparator( int i ) const
	{
		return isValid() ?     ( items[ i ].isSeparator ) : false;
	}
	void setItemSeparator( int i, bool isSeparator ) {
		if ( isValid( i ) )
			items[ i ].isSeparator = isSeparator;
	}
	void addSeparator() {
		setItemSeparator( items.size() -1 , true );
	}

	//size
	const int size() const
	{
		return items.size();
	}
private:
	const bool isValid() const
	{
		return ( 0 < size() && 0 <= value() && value() < size() );
	}
	const bool isValid( int newIndex ) const
	{
		return ( -1 <= newIndex && newIndex < size() );
	}
	class Item {
		public :
		QString text;
		PixmapLoader * pixmapLoader;
		bool isSeparator;
		
		Item( const QString & text=QString::null, PixmapLoader * pixmapLoader=NULL , const bool & isSeparator=false ) :
			text( text ), pixmapLoader( pixmapLoader ) , isSeparator( isSeparator )
		{
		}
	};
	QVector<Item> items;
};


#endif
