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
#include <vector>
#include <map>

namespace unify
{
	/// <summary>
	/// Frame provides a hierarchical relationship structure for the purpose of providing relative transformation in a rendering or physics pipeline.
	/// </summary>
	class Frame
	{
	public:
		/// <summary>
		/// Enabled or disables updating the entire tree if we are modified.
		/// </summary>
		static void UpdateOnChange( bool tf );

		/// <summary>
		/// Returns true if we update the entire tree upon modification.
		/// </summary>
		/// <returns></returns>
		static bool UpdateOnChange();

		/// <summary>
		/// Create a duplicate hierarchy.
		/// </summary>
		static Frame * CreateDuplicateHierarchy( const Frame * in );

		static void CreateIndexToFrameVector( std::vector< Frame * > & indexToFrameOut, Frame * frame );

		static void CreateNameToIndexMap( std::map< std::string, size_t > & nameToIndexOut, const std::vector< Frame * > & indexToFrameIn );

		Frame();
		Frame( std::string sName );
		Frame( const Frame & frame );
		virtual ~Frame();

		Frame & operator=( const Frame & frame );

		void SetMatrix( const Matrix & matrix );

		void AttachTo( Frame * newParent );
		
		// Update Frame and children frames
		virtual void Update();

		Frame & LookAt( const Frame & at, const V3< float > & up = V3< float >( 0, 1, 0 ) );
		Frame & LookAt( const V3< float > & at, const V3< float > & up = V3< float >( 0, 1, 0 ) );
		Frame & LookDirection( const V3< float > & direction, const V3< float > & left );
		Frame & MoveBy( const V3< float > & by );
		Frame & Slide( const V3< float > & axis, float amount );
		
		/// <summary>
		/// Orbit about an origin point, an amount of degrees. This orbit utilizes our current position, and orientation.
		/// </summary>
		Frame & Orbit( const V3< float > & origin, const V2< float > & direction, Angle angle );
		
		Frame & Orbit( const V3< float > & origin, const Quaternion & orbit, float distance );
		Frame & Rotate( const V3< float > & axis, Angle angle );
		Frame & Rotate( const Quaternion & q );
		Frame & RotateAbout( const V3< float > & axis, Angle angle );

		const Matrix & GetMatrix() const;

		/// <summary>
		/// Final matrix is the result of the parent matrix combined with our matrix.
		/// </summary>
		const Matrix & GetFinalMatrix() const;

		V3< float > GetLeft() const;
		V3< float > GetUp() const;
		V3< float > GetForward() const;
		Quaternion GetRotation() const;
		V3< float > GetPosition() const;

		Frame & SetLeft( const V3< float > & left );
		Frame & SetUp( const V3< float > & up );
		Frame & SetForward( const V3< float > & direction );
		Frame & SetRotation( const Quaternion & rotation );
		Frame & SetPosition( const V3< float > & position );
		Frame & Set( const Quaternion & orientation, const V3< float > & position, const V3< float > & scale = V3< float >( 1, 1, 1 ) );

		Frame * GetParent();
		Frame * GetChild();
		Frame * GetPrevious();
		Frame * GetNext();

		const Frame * GetParent() const;
		const Frame * GetChild() const;
		const Frame * GetPrevious() const;
		const Frame * GetNext() const;

		std::string GetName() const;
		bool IsDirty() const;

	protected:
		void MakeDirty( bool dirtySiblings = false );
		void AddChild( Frame * frame );
		void AddSibling( Frame * frame );

		Frame * m_child;
		Frame * m_previous;
		Frame * m_next;
		Frame * m_parent;

		std::string m_name;

		Matrix m_matrix;
		Matrix m_finalCached;

		bool	m_isDirty;

		static bool m_updateOnChange;
	};
}