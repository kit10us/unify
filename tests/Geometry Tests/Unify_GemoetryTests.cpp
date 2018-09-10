// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <unify/BBox.h>
#include <iostream>
#include <conio.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace std;

	cout << "Ray collision with BBox:" << endl;
	BBox<float > inFrontBBox( V3<float>( -10, -10, -10 ), V3<float>( 10, 10, 10 ) );
	inFrontBBox += V3<float>( 0, 0, 40 ); // Move BBox infront of us.

	Ray straightForwardRay( V3< float >( 0, 0, 0 ), V3< float >( 0, 0, 1 ) );
	Ray straightBackwardRay( V3< float >( 0, 0, 0 ), V3< float >( 0, 0, -1 ) );
	Ray straightForwardRayTooFarLeft( V3< float >( 0, 0, 0 ), V3< float >( 0, 0, 1 ) );
	straightForwardRayTooFarLeft.origin -= V3< float >( 11, 0, 0 );

	cout << "  1. straightRay should hit inFrontBBox: " << ( inFrontBBox.Intersects( straightForwardRay, 0, 1000 ) == true ? "success" : "fail" ) << endl;
	cout << "  2. inverse straightRay should miss inFrontBBox: " << (inFrontBBox.Intersects( straightBackwardRay, 0, 1000 ) == false ? "success" : "fail") << endl;
	cout << "  3. straightRay too far left should miss inFrontBBox: " << (inFrontBBox.Intersects( straightForwardRayTooFarLeft, 0, 1000 ) == false ? "success" : "fail") << endl;
	
	cin.ignore();

    return 0;
}