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
			const PixmapLoader& pixmapLoader = PixmapLoader(), 
			const bool& isSeparator = false )
	{
		items.push_back( Item( text, pixmapLoader, isSeparator ) );
		setRange( 0, items.size() - 1 );
	}

	void clear() {
		//for ( Item& i : items )
		//	delete ( i.pixmapLoader );

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
	const PixmapLoader currentData() const
	{
		return isValid() ?   ( items[ value() ].pixmapLoader ) : PixmapLoader();
	}
	const bool currentHasPixmap() const
	{
		// return false;
		return isValid() ?   ( items[ value() ].hasPixmapLoader ) : false;
	}
	const bool currentSeparator() const
	{
		return isValid() ?   ( items[ value() ].isSeparator  ) : false;
	}

	// text
	const QString itemText( int i ) const
	{
		return  isValid( i ) ? ( items[ i ].text ) : QString();
	}
	void setItemText( int i, QString text ) {
		if ( isValid( i ) ) {
			items[ i ].text = text;
			emit dataChanged();
		}
	}

	// pixmapLoader
	const PixmapLoader itemPixmap( int i ) const
	{
		return hasItemPixmap( i ) ? ( items[ i ].pixmapLoader ) : PixmapLoader();
	}
	void setItemPixmap( const int i, const PixmapLoader& pixmapLoader )
	{
		if ( isValid( i ) ) {
			items[ i ].pixmapLoader = pixmapLoader;
			emit dataChanged();
		}
	}
	bool hasItemPixmap( int i ) const
	{
		return isValid( i ) ? ( items[ i ].hasPixmapLoader ) : false;
	}

	// separator
	const bool itemSeparator( int i ) const
	{
		return isValid( i ) ?     ( items[ i ].isSeparator ) : false;
	}
	void setItemSeparator( int i, bool isSeparator ) {
		if ( isValid( i ) ) {
			items[ i ].isSeparator = isSeparator;
			emit dataChanged();
		}
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
		bool hasPixmapLoader;
		PixmapLoader pixmapLoader;
		bool isSeparator;
		
		Item(
			const QString& text = QString::null
		) : text( text ), 
			hasPixmapLoader( false ), 
			pixmapLoader( PixmapLoader() ),
			isSeparator( false ) {}

		Item(
			const QString& text, 
			const bool& isSeparator 
		) : text( text ), 
			hasPixmapLoader( false ),
			pixmapLoader( PixmapLoader() ),
			isSeparator( isSeparator ) {}

		Item(
			const QString& text, 
			const PixmapLoader& pixmapLoader
		) : text( text ),
			hasPixmapLoader( true ),
			pixmapLoader( pixmapLoader ),
			isSeparator( false ) {}

		Item(
			const QString& text, 
			const PixmapLoader& pixmapLoader,
			const bool& isSeparator 
		) : text( text ),
			hasPixmapLoader( true ),
			pixmapLoader( pixmapLoader ),
			isSeparator( isSeparator ) {}
	};
	QVector<Item> items;
};


#endif
