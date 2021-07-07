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
#include <unify/Matrix.h>

namespace unify
{
	/// <summary>
	/// Order of color components.
	/// </summary>
	class FrameLite
	{
	public:
		FrameLite();
		FrameLite( unify::Quaternion q, unify::V3< float > p );
		FrameLite( unify::Matrix matrix );
		virtual ~FrameLite();

		/// <summary>
		/// Have our frame face a specific point.
		/// </summmary>
		void LookAt( const FrameLite & at, const V3< float > & up = V3< float >( 0, 1, 0 ) );

		/// <summary>
		/// Have our frame face a specific point.
		/// </summmary>
		void LookAt( const V3< float > & at, const V3< float > & up = V3< float >( 0, 1, 0 ) );

		void MoveBy( const V3< float > & by );

		void Orbit( const V3< float > & origin, const V2< float > & direction, Angle angle );

		void Orbit( const V3< float > & origin, const Quaternion & orbit );

		void RotateAboutAxis( V3< float > axis, Angle angle );
		
		void PreMul( Quaternion q );
		void PostMul( Quaternion q );

		// TODO: Remove matrix interfaces...
		void PreMul( Matrix m );
		void PostMul( Matrix m );

		const Matrix GetMatrix() const;
		void ReadMatrix( Matrix * matrix ) const;

		void SetMatrix( unify::Matrix matrix );

		V3< float > GetLeft() const;
		V3< float > GetUp() const;
		V3< float > GetForward() const;
		Quaternion GetRotation() const;
		V3< float > GetPosition() const;		

		void SetLeft( V3< float > left);
		void SetUp( V3< float > up );
		void SetForward( V3< float > forward );
		void SetRotation( const Quaternion & rotation );
		void SetPosition( const V3< float > & position );

	protected:
		unify::Quaternion m_q;
		unify::V3< float > m_p;
		unify::Matrix m_mat;
	};
}