// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/Matrix.h>
#include <unify/Cast.h>
using namespace unify;

Matrix::Matrix()
{
}

Matrix::Matrix( const Matrix & matrix )
{
	memcpy( &m, &matrix.m, sizeof( float ) * 4 * 4 );
}

Matrix::Matrix( Quaternion q, V3< float > translation )
{
	/*
	const float & x = q.x;
	const float & y = q.y;
	const float & z = q.z;
	const float & w = q.w;
	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;

	float xy = x * y;
	float wy = w * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wz = w * z;

	Matrix rotation;
	rotation.m[0][0] = 1.0f - 2.0f * y2 - 2.0f * z2;
	rotation.m[1][0] = 2.0f * xy - 2.0f * wz;
	rotation.m[2][0] = 2.0f * xz + 2.0f * wy;
	rotation.m[3][0] = 0.0f;

	rotation.m[0][1] = 2.0f * xy + 2.0f * wz;
	rotation.m[1][1] = 1.0f - 2.0f * x2 - 2.0f * z2;
	rotation.m[2][1] = 2.0f * yz - 2.0f * wx;
	rotation.m[3][1] = 0.0f;

	rotation.m[0][2] = 2.0f * xz - 2.0f * wy;
	rotation.m[1][2] = 2.0f * yz + 2.0f * wx;
	rotation.m[2][2] = 1.0f - 2.0f * x2 - 2.0f * y2;
	rotation.m[3][2] = 0.0f;

	rotation.m[0][3] = 0.0f;
	rotation.m[1][3] = 0.0f;
	rotation.m[2][3] = 0.0f;
	rotation.m[3][3] = 1.0f;
	*/

	/*
	Matrix scaleM( MatrixScale( scale ) );
	Matrix translationM( MatrixTranslate( translation ) );
	*this = scaleM * rotation * translationM;
	*/

	/*

	// invs (inverse square length) is only required if quaternion is not already normalised
	float invs = 1 / (sqx + sqy + sqz + sqw);
	m[0][0] = (sqx - sqy - sqz + sqw)*invs; // since sqw + sqx + sqy + sqz =1/invs*invs
	m[1][1] = (-sqx + sqy - sqz + sqw)*invs;
	m[2][2] = (-sqx - sqy + sqz + sqw)*invs;

	float tmp1 = q.x*q.y;
	float tmp2 = q.z*q.w;
	m[0][1] = 2.0f * (tmp1 + tmp2)*invs;
	m[1][0] = 2.0f * (tmp1 - tmp2)*invs;

	tmp1 = q.x*q.z;
	tmp2 = q.y*q.w;
	m[0][2] = 2.0f * (tmp1 - tmp2)*invs;
	m[2][0] = 2.0f * (tmp1 + tmp2)*invs;
	tmp1 = q.y*q.z;
	tmp2 = q.x*q.w;
	m[1][2] = 2.0f * (tmp1 + tmp2)*invs;
	m[2][1] = 2.0f * (tmp1 - tmp2)*invs;

	m[3][0] = translation.x;
	m[3][1] = translation.y;
	m[3][2] = translation.z;

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;

	m[3][3] = 1.0f;
	*/
	
	//q = q.Conjugate();

	const float & x = q.x;
	const float & y = q.y;
	const float & z = q.z;
	const float & w = q.w;

	float xs = x * x;
	float ys = y * y;
	float zs = z * z;

	SetRow( 0, { (1.0f - 2.0f * ys - 2.0f * zs),	(2.0f * x * y + 2.0f * w * z),	(2 * x * z - 2.0f * w * y),		0.0f } );
	SetRow( 1, { (2.0f * x * y - 2.0f * w * z),		(1.0f - 2.0f * xs - 2.0f * zs), (2.0f * y * z + 2.0f * w * x),	0.0f } );
	SetRow( 2, { (2.0f * x * z + 2.0f * w * y),		(2.0f * y * z - 2.0f * w * x),	(1.0f - 2.0f * xs - 2.0f * ys), 0.0f } );
	SetRow( 3, { translation, 1.0f } );
}

Matrix::Matrix( std::string text )
{
	FromString( text );
}

Matrix::~Matrix()
{
}

Matrix & Matrix::operator = ( const Matrix & matrix )
{
	memcpy( m, matrix.m, sizeof( float ) * 4 * 4 );
	return *this;
}

Matrix & Matrix::operator += ( const Matrix & matrix )
{
	m[0][0] += matrix.m[0][0];
	m[0][1] += matrix.m[0][1];
	m[0][2] += matrix.m[0][2];
	m[0][3] += matrix.m[0][3];

	m[1][0] += matrix.m[1][0];
	m[1][1] += matrix.m[1][1];
	m[1][2] += matrix.m[1][2];
	m[1][3] += matrix.m[1][3];

	m[2][0] += matrix.m[2][0];
	m[2][1] += matrix.m[2][1];
	m[2][2] += matrix.m[2][2];
	m[2][3] += matrix.m[2][3];

	m[3][0] += matrix.m[3][0];
	m[3][1] += matrix.m[3][1];
	m[3][2] += matrix.m[3][2];
	m[3][3] += matrix.m[3][3];
	return *this;
}

Matrix & Matrix::operator -= ( const Matrix & matrix )
{
	m[0][0] -= matrix.m[0][0];
	m[0][1] -= matrix.m[0][1];
	m[0][2] -= matrix.m[0][2];
	m[0][3] -= matrix.m[0][3];

	m[1][0] -= matrix.m[1][0];
	m[1][1] -= matrix.m[1][1];
	m[1][2] -= matrix.m[1][2];
	m[1][3] -= matrix.m[1][3];

	m[2][0] -= matrix.m[2][0];
	m[2][1] -= matrix.m[2][1];
	m[2][2] -= matrix.m[2][2];
	m[2][3] -= matrix.m[2][3];

	m[3][0] -= matrix.m[3][0];
	m[3][1] -= matrix.m[3][1];
	m[3][2] -= matrix.m[3][2];
	m[3][3] -= matrix.m[3][3];
	return *this;
}

Matrix & Matrix::operator *= ( const Matrix & matrix )
{
	Matrix result;
	result.m[0][0] = this->m[0][0] * matrix.m[0][0];
	result.m[0][0] += this->m[0][1] * matrix.m[1][0];
	result.m[0][0] += this->m[0][2] * matrix.m[2][0];
	result.m[0][0] += this->m[0][3] * matrix.m[3][0];
	result.m[0][1] = this->m[0][0] * matrix.m[0][1];
	result.m[0][1] += this->m[0][1] * matrix.m[1][1];
	result.m[0][1] += this->m[0][2] * matrix.m[2][1];
	result.m[0][1] += this->m[0][3] * matrix.m[3][1];
	result.m[0][2] = this->m[0][0] * matrix.m[0][2];
	result.m[0][2] += this->m[0][1] * matrix.m[1][2];
	result.m[0][2] += this->m[0][2] * matrix.m[2][2];
	result.m[0][2] += this->m[0][3] * matrix.m[3][2];
	result.m[0][3] = this->m[0][0] * matrix.m[0][3];
	result.m[0][3] += this->m[0][1] * matrix.m[1][3];
	result.m[0][3] += this->m[0][2] * matrix.m[2][3];
	result.m[0][3] += this->m[0][3] * matrix.m[3][3];

	result.m[1][0] = this->m[1][0] * matrix.m[0][0];
	result.m[1][0] += this->m[1][1] * matrix.m[1][0];
	result.m[1][0] += this->m[1][2] * matrix.m[2][0];
	result.m[1][0] += this->m[1][3] * matrix.m[3][0];
	result.m[1][1] = this->m[1][0] * matrix.m[0][1];
	result.m[1][1] += this->m[1][1] * matrix.m[1][1];
	result.m[1][1] += this->m[1][2] * matrix.m[2][1];
	result.m[1][1] += this->m[1][3] * matrix.m[3][1];
	result.m[1][2] = this->m[1][0] * matrix.m[0][2];
	result.m[1][2] += this->m[1][1] * matrix.m[1][2];
	result.m[1][2] += this->m[1][2] * matrix.m[2][2];
	result.m[1][2] += this->m[1][3] * matrix.m[3][2];
	result.m[1][3] = this->m[1][0] * matrix.m[0][3];
	result.m[1][3] += this->m[1][1] * matrix.m[1][3];
	result.m[1][3] += this->m[1][2] * matrix.m[2][3];
	result.m[1][3] += this->m[1][3] * matrix.m[3][3];
		
	result.m[2][0] = this->m[2][0] * matrix.m[0][0];
	result.m[2][0] += this->m[2][1] * matrix.m[1][0];
	result.m[2][0] += this->m[2][2] * matrix.m[2][0];
	result.m[2][0] += this->m[2][3] * matrix.m[3][0];
	result.m[2][1] = this->m[2][0] * matrix.m[0][1];
	result.m[2][1] += this->m[2][1] * matrix.m[1][1];
	result.m[2][1] += this->m[2][2] * matrix.m[2][1];
	result.m[2][1] += this->m[2][3] * matrix.m[3][1];
	result.m[2][2] = this->m[2][0] * matrix.m[0][2];
	result.m[2][2] += this->m[2][1] * matrix.m[1][2];
	result.m[2][2] += this->m[2][2] * matrix.m[2][2];
	result.m[2][2] += this->m[2][3] * matrix.m[3][2];
	result.m[2][3] = this->m[2][0] * matrix.m[0][3];
	result.m[2][3] += this->m[2][1] * matrix.m[1][3];
	result.m[2][3] += this->m[2][2] * matrix.m[2][3];
	result.m[2][3] += this->m[2][3] * matrix.m[3][3];

	result.m[3][0] = this->m[3][0] * matrix.m[0][0];
	result.m[3][0] += this->m[3][1] * matrix.m[1][0];
	result.m[3][0] += this->m[3][2] * matrix.m[2][0];
	result.m[3][0] += this->m[3][3] * matrix.m[3][0];
	result.m[3][1] = this->m[3][0] * matrix.m[0][1];
	result.m[3][1] += this->m[3][1] * matrix.m[1][1];
	result.m[3][1] += this->m[3][2] * matrix.m[2][1];
	result.m[3][1] += this->m[3][3] * matrix.m[3][1];
	result.m[3][2] = this->m[3][0] * matrix.m[0][2];
	result.m[3][2] += this->m[3][1] * matrix.m[1][2];
	result.m[3][2] += this->m[3][2] * matrix.m[2][2];
	result.m[3][2] += this->m[3][3] * matrix.m[3][2];
	result.m[3][3] = this->m[3][0] * matrix.m[0][3];
	result.m[3][3] += this->m[3][1] * matrix.m[1][3];
	result.m[3][3] += this->m[3][2] * matrix.m[2][3];
	result.m[3][3] += this->m[3][3] * matrix.m[3][3];

	*this = result;	
	return *this;
}

Matrix & Matrix::operator *= ( const Quaternion & quaternion )
{
	*this *= Matrix( quaternion );
	return *this;
}

Matrix & Matrix::operator *= ( float multiplier )
{
	m[0][0] *= multiplier;
	m[0][1] *= multiplier;
	m[0][2] *= multiplier;
	m[0][3] *= multiplier;
	m[1][0] *= multiplier;
	m[1][1] *= multiplier;
	m[1][2] *= multiplier;
	m[1][3] *= multiplier;
	m[2][0] *= multiplier;
	m[2][1] *= multiplier;
	m[2][2] *= multiplier;
	m[2][3] *= multiplier;
	m[3][0] *= multiplier;
	m[3][1] *= multiplier;
	m[3][2] *= multiplier;
	m[3][3] *= multiplier;
	return *this;
}

Matrix & Matrix::operator /= ( float divisor )
{
	m[0][0] /= divisor;
	m[0][1] /= divisor;
	m[0][2] /= divisor;
	m[0][3] /= divisor;
	m[1][0] /= divisor;
	m[1][1] /= divisor;
	m[1][2] /= divisor;
	m[1][3] /= divisor;
	m[2][0] /= divisor;
	m[2][1] /= divisor;
	m[2][2] /= divisor;
	m[2][3] /= divisor;
	m[3][0] /= divisor;
	m[3][1] /= divisor;
	m[3][2] /= divisor;
	m[3][3] /= divisor;
	return *this;
}

// binary operators
Matrix Matrix::operator + ( const Matrix & matrix ) const
{
	Matrix result = *this;
	result += matrix;
	return result;
}

Matrix Matrix::operator - ( const Matrix & matrix ) const
{
	Matrix result = *this;
	result -= matrix;
	return result;
}

Matrix Matrix::operator * ( const Matrix & matrix ) const
{
	Matrix result = *this;
	result *= matrix;
	return result;
}

Matrix Matrix::operator * ( const Quaternion & quaternion ) const
{
	return *this * Matrix( quaternion );
}

Matrix Matrix::operator * ( float multiplier ) const
{
	Matrix result = *this;
	result *= multiplier;
	return result;
}

Matrix Matrix::operator / ( float divisor ) const
{
	Matrix result = *this;
	result /= divisor;
	return result;
}

bool Matrix::operator == ( const Matrix & matrix ) const
{
	for( int y = 0; y < 4; ++y )
	{
		for( int x = 0; x < 4; ++x )
		{
			if( m[x][y] != matrix.m[x][y] ) return false;
		}
	}
	return true;
}

bool Matrix::operator != ( const Matrix & matrix ) const
{
	return !(*this == matrix);
}

float & Matrix::operator()( const RowColumn< unsigned int > & rowColumn )
{
	return m[rowColumn.row][rowColumn.column];
}

float & Matrix::operator()( unsigned int row, unsigned int column )
{
	return m[row][column];
}
const float & Matrix::operator()( const RowColumn< unsigned int > & rowColumn ) const
{
	return m[rowColumn.row][rowColumn.column];
}

const float & Matrix::operator()( unsigned int row, unsigned int column ) const
{
	return m[row][column];
}

unify::V4< float > & Matrix::operator()( unsigned int row )
{
	return *(unify::V4< float >*)&m[ row ];
}

const unify::V4< float > & Matrix::operator()( unsigned int row ) const
{
	return *(unify::V4< float >*)&m[ row ];
}


Matrix & Matrix::SetRotation( const Quaternion & quaternion )
{
	// Store values to restore them after rotation.
	V3< float > scale = GetScale();
	V3< float > position = GetPosition();
	*this = Matrix( quaternion, position );
	*this *= unify::MatrixScale( scale );
	return *this;
}

Matrix & Matrix::Translate( const V3< float > & vector )
{
	Matrix translation( MatrixTranslate( vector ) );
	*this *= translation;
	return *this;
}

Matrix & Matrix::Scale( const V3< float > & vector )
{
	Matrix scale( unify::MatrixScale( vector ) );
	*this *= scale;
	return *this;
}

Matrix & Matrix::Scale( float scale )
{
	Matrix scaling( MatrixScale( scale ) );
	*this *= scaling;
	return *this;
}

void Matrix::Set( unsigned int row, unsigned int column, float value )
{
	m[row][column] = value;
}

void Matrix::SetLeft( const V3< float > & vec )
{
	*(V3< float > *)m[0] = vec;
}

void Matrix::SetUp( const V3< float > & vec )
{
	*(V3< float > *)m[1] = vec;
}

void Matrix::SetForward( const V3< float > & vec )
{
	*(V3< float > *)m[2] = vec;
}

void Matrix::SetPosition( const V3< float > & vec )
{
	*(V3< float > *)m[3] = vec;
}

void Matrix::SetLeft( float x, float y, float z )
{
	m[0][0] = x;
	m[0][1] = y;
	m[0][2] = z;
}

void Matrix::SetUp( float x, float y, float z )
{
	m[1][0] = x;
	m[1][1] = y;
	m[1][2] = z;
}

void Matrix::SetForward( float x, float y, float z )
{
	m[2][0] = x;
	m[2][1] = y;
	m[2][2] = z;
}

void Matrix::SetPosition( float x, float y, float z )
{
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
}

void Matrix::SetRow( size_t row, unify::V4< float > v4 )
{
	m[ row ][ 0 ] = v4.x;
	m[ row ][ 1 ] = v4.y;
	m[ row ][ 2 ] = v4.z;
	m[ row ][ 3 ] = v4.w;
}

void Matrix::SetColumn( size_t column, unify::V4< float > v4 )
{
	m[ 0 ][ column ] = v4.x;
	m[ 1 ][ column ] = v4.y;
	m[ 2 ][ column ] = v4.z;
	m[ 3 ][ column ] = v4.w;
}

unify::V4< float > Matrix::GetRow( size_t row ) const
{
	return{
		m[row][0],
		m[row][1],
		m[row][2],
		m[row][3]
	};
}

unify::V4< float > Matrix::GetColumn( size_t column ) const
{
	return
	{
		m[0][column],
		m[1][column],
		m[2][column],
		m[3][column]
	};
}


V3< float > Matrix::GetLeft() const
{
	return *(V3< float > *)m[0];
}

V3< float > Matrix::GetUp() const
{
	return *(V3< float > *)m[1];
}

V3< float > Matrix::GetForward() const
{
	return *(V3< float > *)m[2];
}

V3< float > Matrix::GetPosition() const
{
	return *(V3< float > *)m[3];
}

Quaternion Matrix::GetRotation() const
{
	Quaternion q;

	float trace = m[0][0] + m[1][1] + m[2][2]; // I removed + 1.0f; see discussion with Ethan
	if( trace > 0 ) {// I changed M_EPSILON to 0
		float s = 0.5f / sqrtf( trace + 1.0f );
		q.w = 0.25f / s;
		q.x = (m[2][1] - m[1][2]) * s;
		q.y = (m[0][2] - m[2][0]) * s;
		q.z = (m[1][0] - m[0][1]) * s;
	}
	else {
		if( m[0][0] > m[1][1] && m[0][0] > m[2][2] ) {
			float s = 2.0f * sqrtf( 1.0f + m[0][0] - m[1][1] - m[2][2] );
			q.w = (m[2][1] - m[1][2]) / s;
			q.x = 0.25f * s;
			q.y = (m[0][1] + m[1][0]) / s;
			q.z = (m[0][2] + m[2][0]) / s;
		}
		else if( m[1][1] > m[2][2] ) {
			float s = 2.0f * sqrtf( 1.0f + m[1][1] - m[0][0] - m[2][2] );
			q.w = (m[0][2] - m[2][0]) / s;
			q.x = (m[0][1] + m[1][0]) / s;
			q.y = 0.25f * s;
			q.z = (m[1][2] + m[2][1]) / s;
		}
		else {
			float s = 2.0f * sqrtf( 1.0f + m[2][2] - m[0][0] - m[1][1] );
			q.w = (m[1][0] - m[0][1]) / s;
			q.x = (m[0][2] + m[2][0]) / s;
			q.y = (m[1][2] + m[2][1]) / s;
			q.z = 0.25f * s;
		}
	}

	return q;
}

V3< float > Matrix::GetScale() const
{
	float l1 = V3< float >( (*this)(0, 0), (*this)(0, 1), (*this)(0, 2) ).Length();
	float l2 = V3< float >( (*this)(1, 0), (*this)(1, 1), (*this)(1, 2) ).Length();
	float l3 = V3< float >( (*this)(2, 0), (*this)(2, 1), (*this)(2, 2) ).Length();
	return V3< float >( l1, l2, l3 );
}

float DeterminantFunc( const float * in, float * out )
{
	float inv[16], det;

	inv[0] = in[5] * in[10] * in[15] -
		in[5] * in[11] * in[14] -
		in[9] * in[6] * in[15] +
		in[9] * in[7] * in[14] +
		in[13] * in[6] * in[11] -
		in[13] * in[7] * in[10];

	inv[4] = -in[4] * in[10] * in[15] +
		in[4] * in[11] * in[14] +
		in[8] * in[6] * in[15] -
		in[8] * in[7] * in[14] -
		in[12] * in[6] * in[11] +
		in[12] * in[7] * in[10];

	inv[8] = in[4] * in[9] * in[15] -
		in[4] * in[11] * in[13] -
		in[8] * in[5] * in[15] +
		in[8] * in[7] * in[13] +
		in[12] * in[5] * in[11] -
		in[12] * in[7] * in[9];

	inv[12] = -in[4] * in[9] * in[14] +
		in[4] * in[10] * in[13] +
		in[8] * in[5] * in[14] -
		in[8] * in[6] * in[13] -
		in[12] * in[5] * in[10] +
		in[12] * in[6] * in[9];

	inv[1] = -in[1] * in[10] * in[15] +
		in[1] * in[11] * in[14] +
		in[9] * in[2] * in[15] -
		in[9] * in[3] * in[14] -
		in[13] * in[2] * in[11] +
		in[13] * in[3] * in[10];

	inv[5] = in[0] * in[10] * in[15] -
		in[0] * in[11] * in[14] -
		in[8] * in[2] * in[15] +
		in[8] * in[3] * in[14] +
		in[12] * in[2] * in[11] -
		in[12] * in[3] * in[10];

	inv[9] = -in[0] * in[9] * in[15] +
		in[0] * in[11] * in[13] +
		in[8] * in[1] * in[15] -
		in[8] * in[3] * in[13] -
		in[12] * in[1] * in[11] +
		in[12] * in[3] * in[9];

	inv[13] = in[0] * in[9] * in[14] -
		in[0] * in[10] * in[13] -
		in[8] * in[1] * in[14] +
		in[8] * in[2] * in[13] +
		in[12] * in[1] * in[10] -
		in[12] * in[2] * in[9];

	inv[2] = in[1] * in[6] * in[15] -
		in[1] * in[7] * in[14] -
		in[5] * in[2] * in[15] +
		in[5] * in[3] * in[14] +
		in[13] * in[2] * in[7] -
		in[13] * in[3] * in[6];

	inv[6] = -in[0] * in[6] * in[15] +
		in[0] * in[7] * in[14] +
		in[4] * in[2] * in[15] -
		in[4] * in[3] * in[14] -
		in[12] * in[2] * in[7] +
		in[12] * in[3] * in[6];

	inv[10] = in[0] * in[5] * in[15] -
		in[0] * in[7] * in[13] -
		in[4] * in[1] * in[15] +
		in[4] * in[3] * in[13] +
		in[12] * in[1] * in[7] -
		in[12] * in[3] * in[5];

	inv[14] = -in[0] * in[5] * in[14] +
		in[0] * in[6] * in[13] +
		in[4] * in[1] * in[14] -
		in[4] * in[2] * in[13] -
		in[12] * in[1] * in[6] +
		in[12] * in[2] * in[5];

	inv[3] = -in[1] * in[6] * in[11] +
		in[1] * in[7] * in[10] +
		in[5] * in[2] * in[11] -
		in[5] * in[3] * in[10] -
		in[9] * in[2] * in[7] +
		in[9] * in[3] * in[6];

	inv[7] = in[0] * in[6] * in[11] -
		in[0] * in[7] * in[10] -
		in[4] * in[2] * in[11] +
		in[4] * in[3] * in[10] +
		in[8] * in[2] * in[7] -
		in[8] * in[3] * in[6];

	inv[11] = -in[0] * in[5] * in[11] +
		in[0] * in[7] * in[9] +
		in[4] * in[1] * in[11] -
		in[4] * in[3] * in[9] -
		in[8] * in[1] * in[7] +
		in[8] * in[3] * in[5];

	inv[15] = in[0] * in[5] * in[10] -
		in[0] * in[6] * in[9] -
		in[4] * in[1] * in[10] +
		in[4] * in[2] * in[9] +
		in[8] * in[1] * in[6] -
		in[8] * in[2] * in[5];

	det = in[0] * inv[0] + in[1] * inv[4] + in[2] * inv[8] + in[3] * inv[12];

	if( det == 0 )
	{
		return 0;
	}

	det = 1.0f / det;

	if ( out != nullptr )
	{
		for( int  i = 0; i < 16; i++ )
		{
			out[i] = inv[i] * det;
		}
	}

	return det;
}

float Matrix::Determinant()const
{
	return DeterminantFunc( &m[0][0], 0 );
}

bool Matrix::IsIdentity() const
{
	for( int c = 0; c < 4; ++c )
	{
		for( int r = 0; r < 4; ++r )
		{
			if( r == c ) 
			{
				if ( m[c][r] != 1.0f ) return false;
			}
			else if( m[c][r] != 0.0f )
			{
				return false;
			}
		}
	}
	return true;
}

void Matrix::BecomeIdentity()
{
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
	
	m[1][0] = m[2][0] = m[3][0] =
	m[0][1] = m[2][1] = m[3][1] =
	m[0][2] = m[1][2] = m[3][2] =
	m[0][3] = m[1][3] = m[2][3] = 0.0f;
}

void Matrix::Zero()
{
	memset( m, 0, sizeof( float ) * 4 * 4 );
}

void Matrix::Invert()
{
	DeterminantFunc( &m[0][0], &m[0][0] );
}

Matrix Matrix::Inverse() const
{
	Matrix result;
	result = *this;
	result.Invert();
	return result;
}

void Matrix::Transpose()
{
	std::swap( m[1][0], m[0][1] );
	std::swap( m[2][0], m[0][2] );
	std::swap( m[3][0], m[0][3] );
	std::swap( m[2][1], m[1][2] );
	std::swap( m[3][1], m[1][3] );
	std::swap( m[3][2], m[2][3] );
}

void Matrix::Transpose( const Matrix & matrix )
{
	*this = matrix;
	Transpose();
}

void Matrix::TransformCoord( V2< float > & coord ) const
{
	coord.x = m[0][0] * coord.x + m[1][0] * coord.y + m[2][0] * 1.0f + m[3][0] * 1.0f;
	coord.y = m[0][1] * coord.x + m[1][1] * coord.y + m[2][1] * 1.0f + m[3][1] * 1.0f;
}

void Matrix::TransformCoord( V3< float > & coord ) const
{
	coord.x = m[0][0] * coord.x + m[1][0] * coord.y + m[2][0] * coord.z + m[3][0] * 1.0f;
	coord.y = m[0][1] * coord.x + m[1][1] * coord.y + m[2][1] * coord.z + m[3][1] * 1.0f;
	coord.z = m[0][2] * coord.x + m[1][2] * coord.y + m[2][2] * coord.z + m[3][2] * 1.0f;
}

void Matrix::TransformCoords( V2< float > * coords, size_t size ) const
{
	for( size_t i = 0; i < size; i++ )
	{
		auto & coord = coords[i];
		coord.x = m[0][0] * coord.x + m[1][0] * coord.y + m[2][0] * 1.0f + m[3][0] * 1.0f;
		coord.y = m[0][1] * coord.x + m[1][1] * coord.y + m[2][1] * 1.0f + m[3][1] * 1.0f;
	}
}

void Matrix::TransformCoords( V3< float > * coords, size_t size ) const
{
	for( size_t i = 0; i < size; i++ )
	{
		auto & coord = coords[i];
		coord.x = m[0][0] * coord.x + m[1][0] * coord.y + m[2][0] * coord.z + m[3][0] * 1.0f;
		coord.y = m[0][1] * coord.x + m[1][1] * coord.y + m[2][1] * coord.z + m[3][1] * 1.0f;
		coord.z = m[0][2] * coord.x + m[1][2] * coord.y + m[2][2] * coord.z + m[3][2] * 1.0f;
	}
}


unify::V2< float > Matrix::TransformCoord_Copy( const unify::V2< float > & coord ) const
{
	unify::V2< float > copy( coord );
	TransformCoord( copy );
	return copy;
}

unify::V3< float > Matrix::TransformCoord_Copy( const unify::V3< float > & coord ) const
{
	unify::V3< float > copy( coord );
	TransformCoord( copy );
	return copy;
}

void Matrix::TransformNormal( V2< float > & coord ) const
{
	coord.x = m[0][0] * coord.x + m[1][0] * coord.y + m[2][0] * 0.0f + m[3][0] * 0.0f;
	coord.y = m[0][1] * coord.x + m[1][1] * coord.y + m[2][1] * 0.0f + m[3][1] * 0.0f;
}

void Matrix::TransformNormal( V3< float > & coord ) const
{
	coord.x = m[0][0] * coord.x + m[1][0] * coord.y + m[2][0] * coord.z + m[3][0] * 0.0f;
	coord.y = m[0][1] * coord.x + m[1][1] * coord.y + m[2][1] * coord.z + m[3][1] * 0.0f;
	coord.z = m[0][2] * coord.x + m[1][2] * coord.y + m[2][2] * coord.z + m[3][2] * 0.0f;
}

void Matrix::Transform( V4< float > & coord ) const
{
	coord.x = m[0][0] * coord.x + m[1][0] * coord.y + m[2][0] * coord.z + m[3][0] * coord.w;
	coord.y = m[0][1] * coord.x + m[1][1] * coord.y + m[2][1] * coord.z + m[3][1] * coord.w;
	coord.z = m[0][2] * coord.x + m[1][2] * coord.y + m[2][2] * coord.z + m[3][2] * coord.w;
	coord.w = m[0][3] * coord.x + m[1][3] * coord.y + m[2][3] * coord.z + m[3][3] * coord.w;
}

Ray Matrix::TransformRay( Ray ray ) const
{
	Ray out{ ray };
	TransformCoord( out.origin );
	TransformNormal( out.direction );
	return out;
}

BBox< float > Matrix::TransformBBox( BBox< float > bbox ) const
{
	BBox< float > out{ bbox };
	TransformCoord( out.inf );
	TransformCoord( out.sup );
	return out;
}

BSphere< float > Matrix::TransformBSphere( BSphere< float > bsphere ) const
{
	BSphere< float > out{ bsphere };
	TransformCoord( out.center );
	return out;
}

void Matrix::RotateAboutAxis( const V3< float > & axis, Angle angle )
{
	Matrix rotation = MatrixRotationAboutAxis( axis, angle );
	*this *= rotation;
}

void Matrix::LookAtLH( const V3< float > & at, const V3< float > & up )
{
	V3< float > eyePosition( GetPosition() );
	*this = unify::MatrixLookAtLH( eyePosition, at, up );
}

void Matrix::Orbit( const V3< float > & origin, const V2< float > & direction, Angle angle )
{
	// Re-origin our position...
	V3< float > newPosition( GetPosition() - origin );

	Quaternion q = Quaternion( V3< float >( direction.y, direction.x, 0 ), angle );

	newPosition = newPosition * q;

	unify::V3< float > p = newPosition + origin;
	SetPosition( p );
	//Quaternion q = GetRotation();
	//m_mat = Matrix{ m_q, m_p };
}

std::string Matrix::ToString() const
{
	using std::string;
	string out;
	out += "{";
	for( int r = 0; r < 4; ++r )
	{
		out += "{";
		for( int c = 0; c < 4; ++c )
		{
			out += unify::Cast<string>( (*this)(r, c) );
			if( c < 3 )
			{
				out += ",";
			}
		}
		if( r < 3 )
		{
			out += "}\n";
		}
		else
		{
			out += "}}";
		}
	}
	return out;
}

void Matrix::FromString( std::string text )
{	
	size_t index = 0;
	size_t left = 0;
	size_t right = 0;
	
	char sep = 0;

	if( sep == 0 && text.find( ',' ) != std::string::npos )
	{
		sep = ',';
	}
	if( sep == 0 && text.find( ' ' ) != std::string::npos )
	{
		sep = ' ';
	}

	assert( sep );

	do
	{
		right = text.find( sep, left );
		std::string value = text.substr( left, right - left );
		linear[index] = Cast< float >( value );
		left = right + 1;
		index++;
	} while ( right != std::string::npos );
}



Matrix unify::MatrixIdentity()
{
	Matrix matrix;
	matrix.BecomeIdentity();
	return matrix;
}

Matrix unify::MatrixZero()
{
	Matrix matrix;
	matrix.Zero();
	return matrix;
}

Matrix unify::MatrixTranslate( const V3< float > & vector )
{
	Matrix matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[0][1] = 0.0f;
	matrix.m[0][2] = 0.0f;
	matrix.m[0][3] = 0.0f;

	matrix.m[1][0] = 0.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[1][2] = 0.0f;
	matrix.m[1][3] = 0.0f;

	matrix.m[2][0] = 0.0f;
	matrix.m[2][1] = 0.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[2][3] = 0.0f;

	matrix.m[3][0] = vector.x;
	matrix.m[3][1] = vector.y;
	matrix.m[3][2] = vector.z;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix unify::MatrixOrthoOffCenterLH( float left, float right, float bottom, float top, float znear, float zfar )
{
	Matrix matrix;
	matrix.m[0][0] = 2.0f / (right - left);
	matrix.m[0][1] = 0.0f;
	matrix.m[0][2] = 0.0f;
	matrix.m[0][3] = 0.0f;

	matrix.m[1][0] = 0.0f;
	matrix.m[1][1] = 2.0f / (top - bottom);
	matrix.m[1][2] = 0.0f;
	matrix.m[1][3] = 0.0f;

	matrix.m[2][0] = 0.0f;
	matrix.m[2][1] = 0.0f;
	matrix.m[2][2] = 1.0f / (zfar - znear);
	matrix.m[2][3] = 0.0f;

	matrix.m[3][0] = (left + right) / (left - right);
	matrix.m[3][1] = (top + bottom) / (bottom - top);
	matrix.m[3][2] = znear / (znear - zfar);
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Matrix unify::MatrixScale( const unify::V3< float > & scale )
{
	Matrix matrix;
	matrix.m[0][0] = scale.x;
	matrix.m[1][1] = scale.y;
	matrix.m[2][2] = scale.z;
	matrix.m[3][3] = 1.0f;
	matrix.m[1][0] = matrix.m[2][0] = matrix.m[3][0] =
		matrix.m[0][1] = matrix.m[2][1] = matrix.m[3][1] =
		matrix.m[0][2] = matrix.m[1][2] = matrix.m[3][2] =
		matrix.m[0][3] = matrix.m[1][3] = matrix.m[2][3] = 0.0f;
	return matrix;
}

Matrix unify::MatrixScale( float x, float y, float z )
{
	return MatrixScale( unify::V3< float >( x, y, z ) );
}

Matrix unify::MatrixScale( float scale )
{
	return MatrixScale( unify::V3< float >( scale, scale, scale ) );
}

Matrix unify::MatrixRotationAboutAxis( const V3< float > & axis, Angle angle )
{
	Matrix matrix = MatrixIdentity();
	// Create rotation matrices using axis as scalar against angle.
	matrix *= MatrixRotationX( angle * axis.x );
	matrix *= MatrixRotationY( angle * axis.y );
	matrix *= MatrixRotationZ( angle * axis.z );
	return matrix;
}

Matrix unify::MatrixPerspectiveFovLH( float fovy, float aspect, float zn, float zf )
{
	Matrix matrix;
	float yScale = 1.0f / tan( fovy / 2 );
	float xScale = yScale / aspect;

	matrix.m[0][0] = xScale;
	matrix.m[0][1] = 0;
	matrix.m[0][2] = 0;
	matrix.m[0][3] = 0;

	matrix.m[1][0] = 0;
	matrix.m[1][1] = yScale;
	matrix.m[1][2] = 0;
	matrix.m[1][3] = 0;

	matrix.m[2][0] = 0;
	matrix.m[2][1] = 0;
	matrix.m[2][2] = zf / (zf - zn);
	matrix.m[2][3] = 1;

	matrix.m[3][0] = 0;
	matrix.m[3][1] = 0;
	matrix.m[3][2] = -zn*zf / (zf - zn);
	matrix.m[3][3] = 0;

	return matrix;
}

Matrix unify::MatrixRotationX( Angle angle )
{
	Matrix matrix;
	float radians = angle.ToRadians();
	matrix.m[0][0] = matrix.m[3][3] = 1.0f;
	matrix.m[0][3] = matrix.m[1][3] = matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = matrix.m[3][1] = matrix.m[3][2] = 0.0f;

	matrix.m[0][1] = matrix.m[1][0] = 0.0f;
	matrix.m[2][0] = matrix.m[0][2] = 0.0f;

	matrix.m[1][1] = cos( radians );
	matrix.m[2][1] = -sin( radians );
	matrix.m[1][2] = sin( radians );
	matrix.m[2][2] = cos( radians );
	return matrix;
}

Matrix unify::MatrixRotationY( Angle angle )
{
	Matrix matrix;
	float radians = angle.ToRadians();
	matrix.m[1][1] = matrix.m[3][3] = 1.0f;
	matrix.m[0][3] = matrix.m[1][3] = matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = matrix.m[3][1] = matrix.m[3][2] = 0.0f;

	matrix.m[1][0] = matrix.m[1][2] = 0.0f;
	matrix.m[0][1] = matrix.m[2][1] = 0.0f;

	matrix.m[0][0] = cos( radians );
	matrix.m[2][0] = sin( radians );
	matrix.m[0][2] = -sin( radians );
	matrix.m[2][2] = cos( radians );
	return matrix;
}

Matrix unify::MatrixRotationZ( Angle angle )
{
	Matrix matrix;
	float radians = angle.ToRadians();
	matrix.m[2][2] = matrix.m[3][3] = 1.0f;
	matrix.m[0][3] = matrix.m[1][3] = matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = matrix.m[3][1] = matrix.m[3][2] = 0.0f;

	matrix.m[2][0] = matrix.m[2][1] = 0.0f;
	matrix.m[0][2] = matrix.m[1][2] = 0.0f;

	matrix.m[0][0] = cos( radians );
	matrix.m[1][0] = -sin( radians );
	matrix.m[0][1] = sin( radians );
	matrix.m[1][1] = cos( radians );
	return matrix;
}

/*
zaxis = normal( At - Eye )
xaxis = normal( cross( Up, zaxis ) )
yaxis = cross( zaxis, xaxis )

 xaxis.x				yaxis.x				zaxis.x				0
 xaxis.y				yaxis.y				zaxis.y				0
 xaxis.z				yaxis.z				zaxis.z				0
 -dot( xaxis, eye )		-dot(yaxis,eye)		-dot(zaxis, eye)	1
*/

Matrix unify::MatrixLookAtLH( const V3< float > & eye, const V3< float > & at, const V3< float > & up )
{
	Matrix matrix = unify::MatrixIdentity();

	typedef unify::V3< float > V;

	V zaxis = V::V3Normalized( at - eye );
	V xaxis = V::V3Normalized( V::V3Cross( up, zaxis ) );
	V yaxis = V::V3Cross( zaxis, xaxis );


	matrix.SetRow( 0, { xaxis.x,				yaxis.x,			zaxis.x,			0 } );
	matrix.SetRow( 1, { xaxis.y,				yaxis.y,			zaxis.y,			0 } );
	matrix.SetRow( 2, { xaxis.z,				yaxis.z,			zaxis.z,			0 } );
	matrix.SetRow( 3, { -xaxis.Dot( eye ),		-yaxis.Dot( eye ),	-zaxis.Dot( eye ),	1 } );

	return matrix;
}
