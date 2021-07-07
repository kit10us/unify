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


#include <unify/FrameLite.h>

using namespace unify;

FrameLite::FrameLite()
	: m_q( QuaternionIdentity() )
	, m_p( 0, 0, 0 )
	, m_mat{ MatrixIdentity() }
{
}

FrameLite::FrameLite( unify::Quaternion q, unify::V3< float > p )
	: m_q( q )
	, m_p( p )
	, m_mat{ m_q, m_p }
{
}

FrameLite::FrameLite( unify::Matrix matrix )
	: m_q( matrix.GetRotation() )
	, m_p( matrix.GetPosition() )
	, m_mat{ matrix }
{
}

FrameLite::~FrameLite()
{
}

// Set us up as a rotation matrix that looks at another frame's position, from our current position
void FrameLite::LookAt( const FrameLite & frame, const V3< float > & up )
{
	LookAt( frame.GetMatrix().GetPosition(), up );
}

void FrameLite::LookAt( const V3< float > & at, const V3< float > & up )
{	
	m_q = QuaternionLookAt( m_p, at, up );
	m_mat = Matrix{ m_q, m_p };
}

// Move ou position by an amount
void FrameLite::MoveBy( const V3< float > & by )
{
	SetPosition( GetPosition() + by );
}

void FrameLite::Orbit( const V3< float > & origin, const V2< float > & direction, Angle angle )
{
	m_mat.Orbit( origin, direction, angle );
	m_q = m_mat.GetRotation();
	m_p = m_mat.GetPosition();
}

void FrameLite::Orbit( const V3< float > & origin, const Quaternion & orbit )
{
	m_p -= origin;
	m_p = m_p * orbit;
	m_p += origin;

	m_mat = Matrix{ m_q, m_p };
}

void FrameLite::RotateAboutAxis( V3< float > axis, Angle angle )
{
	m_mat.RotateAboutAxis( axis, angle );
	m_q = m_mat.GetRotation();
	m_p = m_mat.GetPosition();
}

void FrameLite::PreMul( Quaternion q )
{
	m_q = q * m_q;
	m_mat = Matrix{ m_q, m_p };
}

void FrameLite::PostMul( Quaternion q )
{
	m_q = m_q * q;
	m_mat = Matrix{ m_q, m_p };
}

void FrameLite::PreMul( Matrix m )
{
	m_mat = m * m_mat;
	m_q = m_mat.GetRotation();
	m_p = m_mat.GetPosition();
}

void FrameLite::PostMul( Matrix m )
{
	m_mat = m_mat * m;
	m_q = m_mat.GetRotation();
	m_p = m_mat.GetPosition();
}

const Matrix FrameLite::GetMatrix() const
{
	return m_mat;
}

void FrameLite::ReadMatrix( Matrix * matrix ) const
{
	*matrix = m_mat;
}

void FrameLite::SetMatrix( unify::Matrix matrix )
{
	m_mat = matrix;
	m_q = m_mat.GetRotation();
	m_p = m_mat.GetPosition();
}

V3< float > FrameLite::GetLeft() const
{
	return m_mat.GetLeft();// m_q * V3< float >( 1, 0, 0 );
}

V3< float > FrameLite::GetUp() const
{
	return m_mat.GetUp(); // m_q * V3< float >( 0, 1, 0 );
}

V3< float > FrameLite::GetForward() const
{
	return m_mat.GetForward();// m_q * V3< float >( 0, 0, -1 );
}

Quaternion FrameLite::GetRotation() const
{
	return m_q;
}

V3< float > FrameLite::GetPosition() const
{
	return m_p;
}

void FrameLite::SetLeft( V3< float > left )
{
	m_mat.SetLeft( left );
	m_q = m_mat.GetRotation();
	m_p = m_mat.GetPosition();
}

void FrameLite::SetUp( V3< float > up )
{
	m_mat.SetUp( up );
	m_q = m_mat.GetRotation();
	m_p = m_mat.GetPosition();
}

void FrameLite::SetForward( V3< float > forward )
{
	m_mat.SetForward( forward );
	m_q = m_mat.GetRotation();
	m_p = m_mat.GetPosition();
}

void FrameLite::SetRotation( const Quaternion & rotation )
{
	m_q = rotation;
	m_mat = Matrix{ m_q, m_p };
}			

void FrameLite::SetPosition( const V3< float > & position )
{
	m_p = position;
	m_mat = Matrix{ m_q, m_p };
}
