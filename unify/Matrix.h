/*
 * Unify Library
 * https://github.com/kit10us/unify
 * Copyright (c) 2002, Kit10 Studios LLC
 *
 * This file is part of Unify Library (a.k.a. Unify)
 *
 * Unify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Unify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unify.  If not, see <https://www.gnu.org/licenses/>.
 */


#pragma once

#include <unify/Unify.h>
#include <unify/V2.h>
#include <unify/V3.h>
#include <unify/V4.h>
#include <unify/Ray.h>
#include <unify/BBox.h>
#include <unify/RowColumn.h>
#include <unify/Quaternion.h>
#include <unify/Angle.h>

namespace unify
{
	class Matrix
	{
		// Named constructors...
		friend Matrix MatrixIdentity();
		friend Matrix MatrixZero();
		friend Matrix MatrixTranslate( const V3< float > & vector );
		friend Matrix MatrixOrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar );
		friend Matrix MatrixScale( const unify::V3< float > & scale );
		friend Matrix MatrixScale( float x, float y, float z );
		friend Matrix MatrixScale( float scale );
		friend Matrix MatrixRotationAboutAxis( const V3< float > & axis, Angle angle );
		friend Matrix MatrixPerspectiveFovLH( float fovy, float apsect, float zn, float zf );
		friend Matrix MatrixRotationX( Angle angle );
		friend Matrix MatrixRotationY( Angle angle );
		friend Matrix MatrixRotationZ( Angle angle );
		friend Matrix MatrixLookAtLH( const V3< float > & eyePosition, const V3< float > & at, const V3< float > & up );

	public:

		Matrix();
		Matrix( const Matrix & matrix );
		explicit Matrix( Quaternion orientation, V3< float > position = V3< float >( 0, 0, 0 ) );
		Matrix( std::string text );
		~Matrix();

		Matrix & operator = ( const Matrix & matrix );

		Matrix & operator += ( const Matrix & matrix );
		Matrix & operator -= ( const Matrix & matrix );
		Matrix & operator *= ( const Matrix & matrix );
		Matrix & operator *= ( const Quaternion & quaternion );
		Matrix & operator *= ( float multiplier );
		Matrix & operator /= ( float divisor );

		// binary operators
		Matrix operator + ( const Matrix & matrix ) const;
		Matrix operator - ( const Matrix & matrix ) const;
		Matrix operator * ( const Matrix & matrix ) const;
		Matrix operator * ( const Quaternion & quaternion ) const;
		Matrix operator * ( float multiplier ) const;
		Matrix operator / ( float divisor ) const;

		bool operator == ( const Matrix & matrix ) const;
		bool operator != ( const Matrix & matrix ) const;

		float &  operator()( const RowColumn< unsigned int > & rowColumn );
		float & operator()( unsigned int row, unsigned int column );

		const float & operator()( const RowColumn< unsigned int > & rowColumn ) const;
		const float & operator()( unsigned int row, unsigned int column ) const;

		unify::V4< float > & operator()( unsigned int row );
		const unify::V4< float > & operator()( unsigned int row ) const;

		Matrix & SetRotation( Quaternion quaternion );
		Matrix & Translate( V3< float > vector );
		Matrix & Scale( V3< float > vector );
		Matrix & Scale( float scale );

		void Set( unsigned int row, unsigned int column, float value );

		void SetLeft( const V3< float > & vec );
		void SetUp( const V3< float > & vec );
		void SetForward( const V3< float > & vec );
		void SetPosition( const V3< float > & vec );
		void SetLeft( float x, float y, float z );
		void SetUp( float x, float y, float z );
		void SetForward( float x, float y, float z );
		void SetPosition( float x, float y, float z );

		void SetRow( size_t row, unify::V4< float > v4 );
		void SetColumn( size_t column, unify::V4< float > v4 );

		unify::V4< float > GetRow( size_t row ) const;
		unify::V4< float > GetColumn( size_t column ) const;

		V3< float > GetLeft() const;
		V3< float > GetUp() const;
		V3< float > GetForward() const;
		V3< float > GetPosition() const;
		V3< float > GetScale() const;
		Quaternion GetRotation() const;

		float Determinant() const;
		bool IsIdentity() const;

		void BecomeIdentity();
		void Zero();

		/// <summary>
		/// Inverts this matrix.
		/// </summary>
		void Invert();

		/// <summary>
		/// Returns a copy of the inverse of this matrix, leaving the original matrix in tact.
		/// </summary>
		Matrix Inverse() const;

		void Transpose();
		void Transpose( const Matrix & matrix );

		V2< float > TransformCoord( const V2< float > v2 ) const;
		V3< float > TransformCoord( const V3< float > v3 ) const;

		void TransformCoords( V2< float > * coords, size_t size ) const;
		void TransformCoords( V3< float > * coords, size_t size ) const;

		V2< float > TransformNormal( const V2< float > v2 ) const;
		V3< float > TransformNormal( const V3< float > v3 ) const;
		
		V4< float > Transform( V4< float > v4 ) const;
	
		Ray TransformRay( Ray ray ) const;
		BBox< float > TransformBBox( BBox< float > bbox ) const;
		BSphere< float > TransformBSphere( BSphere< float > bsphere ) const;

		void RotateAboutAxis( const V3< float > & axis, Angle angle );

		void LookAtLH( const V3< float > & at, const V3< float > & up );

		void Orbit( const V3< float > & origin, const V2< float > & direction, Angle angle );

		std::string ToString() const;
		void FromString( std::string text );

		union {
			float m[4][4];
			float linear[16];
		};
	};

	Matrix MatrixIdentity();
	Matrix MatrixZero();
	Matrix MatrixTranslate( const V3< float > & vector );
	Matrix MatrixOrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar );
	Matrix MatrixScale( const unify::V3< float > & scale );
	Matrix MatrixScale( float x, float y, float z );
	Matrix MatrixScale( float scale );
	Matrix MatrixRotationAboutAxis( const V3< float > & axis, Angle angle );
	Matrix MatrixPerspectiveFovLH( float fovy, float apsect, float zn, float zf );
	Matrix MatrixRotationX( Angle angle );
	Matrix MatrixRotationY( Angle angle );
	Matrix MatrixRotationZ( Angle angle );
	Matrix MatrixLookAtLH( const V3< float > & eyePosition, const V3< float > & at, const V3< float > & up );
}