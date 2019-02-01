// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#include <unify/Quaternion.h>
#include <unify/Matrix.h>

using namespace unify;

Quaternion::Quaternion()
// No default effort.
{
}

Quaternion::Quaternion( float x, float y, float z, float w )
: x( x )
, y( y ) 
, z( z )
, w( w )
{
}

Quaternion::Quaternion( V3< float > axis, Angle angle )
{
	float s = sin( angle.ToRadians() / 2.0f );
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;
	w = cos( angle.ToRadians() / 2.0f );
}

Quaternion::Quaternion( const Quaternion & quaternion )
: x( quaternion.x )
, y( quaternion.y )
, z( quaternion.z )
, w( quaternion.w )
{
}

Quaternion::Quaternion( Matrix mat )
{
	float tr = mat.m[0][0] + mat.m[1][1] + mat.m[2][2];

	if ( tr > 0 ) {
		float S = sqrt( tr + 1.0f ) * 2.0f; // S=4*qw 
		w = 0.25f * S;
		x = (mat.m[1][2] - mat.m[2][1]) / S;
		y = (mat.m[2][0] - mat.m[0][2]) / S;
		z = (mat.m[0][1] - mat.m[1][0]) / S;
	}
	else if ( (mat.m[0][0] > mat.m[1][1])&(mat.m[0][0] > mat.m[2][2]) ) {
		float S = sqrt( 1.0f + mat.m[0][0] - mat.m[1][1] - mat.m[2][2] ) * 2.0f; // S=4*qx 
		w = (mat.m[1][2] - mat.m[2][1]) / S;
		x = 0.25f * S;
		y = (mat.m[1][0] + mat.m[0][1]) / S;

		z = (mat.m[2][0] + mat.m[0][2]) / S;
	}
	else if ( mat.m[1][1] > mat.m[2][2] ) {
		float S = sqrt( 1.0f + mat.m[1][1] - mat.m[0][0] - mat.m[2][2] ) * 2.0f; // S=4*qy
		w = (mat.m[2][0] - mat.m[0][2]) / S;
		x = (mat.m[1][0] + mat.m[0][1]) / S;
		y = 0.25f * S;
		z = (mat.m[2][1] + mat.m[1][2]) / S;
	}
	else {
		float S = sqrt( 1.0f + mat.m[2][2] - mat.m[0][0] - mat.m[1][1] ) * 2.0f; // S=4*qz
		w = (mat.m[0][1] - mat.m[1][0]) / S;
		x = (mat.m[2][0] + mat.m[0][2]) / S;
		y = (mat.m[2][1] + mat.m[1][2]) / S;
		z = 0.25f * S;
	}
}

bool Quaternion::IsIdentity() const
{
	return x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f;
}

Quaternion Quaternion::Conjugate() const
{
	return Quaternion( -x, -y, -z, w );
}

Quaternion Quaternion::Normalize() const
{	
	float n = sqrt( x * x + y * y + z * z + w * w );
	return Quaternion( x / n, y / n, z / n, w / n );
}	

V3< float > Quaternion::Up() const
{
	V3< float > up( 0, 1, 0 );
	return up * *this;
}

// assignment operators
Quaternion & Quaternion::operator += ( const Quaternion & quaternion )
{
	x += quaternion.x;
	y += quaternion.y;
	z += quaternion.z;
	w += quaternion.w;
	return *this;
}

Quaternion & Quaternion::operator -= ( const Quaternion & quaternion )
{
	x -= quaternion.x;
	y -= quaternion.y;
	z -= quaternion.z;
	w -= quaternion.w;
	return *this;
}

Quaternion & Quaternion::operator *= ( const Quaternion & quaternion )
{
	Quaternion o;
	const Quaternion & a = *this;
	const Quaternion & b = quaternion;
	o.x = b.w * a.x + b.x * a.w + b.y * a.z - b.z * a.y;
	o.y = b.w * a.y - b.x * a.z + b.y * a.w + b.z * a.x;
	o.z = b.w * a.z + b.x * a.y - b.y * a.x + b.z * a.w;
	o.w = b.w * a.w - b.x * a.x - b.y * a.y - b.z * a.z;
	*this = o;

	return *this;
}

Quaternion & Quaternion::operator *= ( float value )
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
	return *this;
}

Quaternion Quaternion::operator + ( const Quaternion & quaternion ) const
{
	Quaternion quaternionOut( *this );
	return quaternionOut += quaternion;
}

Quaternion Quaternion::operator - ( const Quaternion & quaternion ) const
{
	Quaternion quaternionOut( *this );
	return quaternionOut -= quaternion;
}

Quaternion Quaternion::operator * ( const Quaternion & quaternion ) const
{
	Quaternion quaternionOut( *this );
	return quaternionOut *= quaternion;
}

Quaternion Quaternion::operator * ( float value ) const
{
	Quaternion quaternionOut( *this );
	return quaternionOut *= value;
}

bool Quaternion::operator == ( const Quaternion & quaternion ) const
{
	return (x == quaternion.x && y == quaternion.y && z == quaternion.z && w == quaternion.w) ? true : false;
}

bool Quaternion::operator != ( const Quaternion & quaternion ) const
{
	return !operator==( quaternion );
}

V3< float > Quaternion::operator *= ( V3< float > v ) const
{
	Quaternion vq( v.x, v.y, v.z, 0.0f );
	Quaternion p = Conjugate() * vq * *this;
	return V3< float >( p.x, p.y, p.z );
}

std::string Quaternion::ToString() const
{
	return Cast< std::string >( x ) + ", " + Cast< std::string >( y ) + ", " + Cast< std::string >( z ) + ", " + Cast< std::string >( w );
}

V3< float > unify::operator * ( V3 < float > v, Quaternion q )
{
	Quaternion vq( v.x, v.y, v.z, 0.0f );
	Quaternion p = q.Conjugate() * vq * q;
	return V3< float >( p.x, p.y, p.z );
}

V3< float > unify::operator * ( Quaternion q, V3< float > v )
{
	return ::operator*(v, q );
}

Quaternion unify::QuaternionIdentity()
{
	Quaternion q( 0, 0, 0, 1 );
	return q;
}

Quaternion unify::QuaternionFromEuler( const unify::V3< float > & euler )
{
	Quaternion q;

	float c1 = cos( euler.y );
	float c2 = cos( euler.x );
	float c3 = cos( euler.z );
	float s1 = sin( euler.y );
	float s2 = sin( euler.x );
	float s3 = sin( euler.z );

	q.w = sqrt( 1.0f + c1 * c2 + c1*c3 - s1 * s2 * s3 + c2*c3 ) / 2.0f;
	q.x = (c2 * s3 + c1 * s3 + s1 * s2 * c3) / (4.0f * q.w);
	q.y = (s1 * c2 + s1 * c3 + c1 * s2 * s3) / (4.0f * q.w);
	q.z = (-s1 * s3 + c1 * s2 * c3 + s2) / (4.0f * q.w);

	return q;
}

Quaternion unify::QuaternionSlerp( const Quaternion & qa, const Quaternion & qb, float t )
{
	Quaternion q;

	float cosHalfTheta = qa.w * qb.w + qa.x * qb.x + qa.y * qb.y + qa.z * qb.z;
	if ( abs( cosHalfTheta ) >= 1.0f )
	{
		q.w = qa.w; q.x = qa.x; q.y = qa.y; q.z = qa.z;
		return q;
	}

	float halfTheta = acos( cosHalfTheta );
	float sinHalfTheta = sqrt( 1.0f - cosHalfTheta*cosHalfTheta );

	if ( fabs( sinHalfTheta ) < 0.001f )
	{ // fabs is floating point absolute
		q.w = (qa.w * 0.5f + qb.w * 0.5f);
		q.x = (qa.x * 0.5f + qb.x * 0.5f);
		q.y = (qa.y * 0.5f + qb.y * 0.5f);
		q.z = (qa.z * 0.5f + qb.z * 0.5f);
		return q;
	}
	float ratioA = sin( (1.0f - t) * halfTheta ) / sinHalfTheta;
	float ratioB = sin( t * halfTheta ) / sinHalfTheta;

	q.w = (qa.w * ratioA + qb.w * ratioB);
	q.x = (qa.x * ratioA + qb.x * ratioB);
	q.y = (qa.y * ratioA + qb.y * ratioB);
	q.z = (qa.z * ratioA + qb.z * ratioB);

	return q;
}

Quaternion unify::QuaternionLookAt( unify::V3< float > eye, unify::V3< float > at, unify::V3< float > up )
{
	Matrix m = unify::MatrixLookAtLH( eye, at, up );
	m.Transpose();
	Quaternion q( m );
	return q;
}

