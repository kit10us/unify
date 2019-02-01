// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/V2.h>

namespace unify
{
	template< typename T >
	class RowColumn
	{
	public:
		T row, column;

		RowColumn();
		RowColumn( T row, T column );
		RowColumn( const RowColumn< T > & rc );
		explicit RowColumn( std::string text );
				
		void Zero();

		// Conversion operators...
		RowColumn< T > & operator = ( const V2< T > & vec );

		// binary operators...
		RowColumn< T > & operator = ( const RowColumn< T > & rc );

		RowColumn< T > & operator += ( const RowColumn< T > & rc );
		RowColumn< T > & operator -= ( const RowColumn< T > & rc );
		RowColumn< T > & operator *= ( const RowColumn< T > & rc );
		RowColumn< T > & operator /= ( const RowColumn< T > & rc );
		RowColumn< T > & operator *= ( T val );
		RowColumn< T > & operator /= ( T val );

		RowColumn< T > operator + ( const RowColumn< T > & rc) const;
		RowColumn< T > operator - ( const RowColumn< T > & rc ) const;
		RowColumn< T > operator * ( const RowColumn< T > & rc ) const;
		RowColumn< T > operator / ( const RowColumn< T > & rc ) const;
		RowColumn< T > operator * ( T val ) const;
		RowColumn< T > operator / ( T val ) const;

		bool operator == ( const RowColumn< T > & rc ) const;
		bool operator != ( const RowColumn< T > & rc ) const;

		T CellCount() const;
	};
	#include <unify/RowColumn.inl>
}
