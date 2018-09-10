// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <unify/Matrix.h>
#include <iostream>
#include <conio.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace std;

	Matrix m( MatrixIdentity() );
	assert( m.IsIdentity() );
	
	Matrix scale( MatrixScale( 10, 100, 1000 ) );
	assert( scale.IsIdentity() == false );
	assert( scale( 0, 0 ) == 10.0f );
	assert( scale( 1, 1 ) == 100.0f );
	assert( scale( 2, 2 ) == 1000.0f );

	Matrix translate( MatrixTranslate( V3< float >( 1, 2, 3 ) ) );
	assert( translate( 3, 0 ) == 1.0f );
	assert( translate( 3, 1 ) == 2.0f );
	assert( translate( 3, 2 ) == 3.0f );

	Matrix final( m * scale * translate );
	V2< float > transformedCoordV2( 1, 2 );
	V3< float > transformedCoordV3( 3, 4, 5 );
	V4< float > transformedV4( 6, 7, 8, 9 );
	V2< float > transformedNormalV2( 1, 2 );
	V3< float > transformedNormalV3( 3, 4, 5 );
	final.TransformCoord( transformedCoordV2 );
	final.TransformCoord( transformedCoordV3 );
	final.TransformNormal( transformedNormalV2 );
	final.TransformNormal( transformedNormalV3 );
	final.Transform( transformedV4 );
	assert( transformedCoordV2.x == 11.0f );
	assert( transformedCoordV2.y == 202.0f );
	assert( transformedCoordV3.x == 31.0f );
	assert( transformedCoordV3.y == 402.0f );
	assert( transformedCoordV3.z == 5003.0f );
	assert( transformedNormalV2.x == 10.0f );
	assert( transformedNormalV2.y == 200.0f );
	assert( transformedNormalV3.x == 30.0f );
	assert( transformedNormalV3.y == 400.0f );
	assert( transformedNormalV3.z == 5000.0f );
	assert( transformedV4.x == 69.0f );
	assert( transformedV4.y == 718.0f );
	assert( transformedV4.z == 8027.0f );
	assert( transformedV4.w == 9.0f );
	scale.Invert();
	translate.Invert();
	translate.TransformCoord( transformedCoordV3 );
	scale.TransformCoord( transformedCoordV3 );

	cout << "\nMatrix tests passed!\n";
	cout << "Press any key to finish...\n";

	cin.ignore();

    return 0;
}