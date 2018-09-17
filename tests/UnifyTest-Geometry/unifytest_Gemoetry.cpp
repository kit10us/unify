// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

//
// Purpose of test...
//    Test varois Unify geometry features.
//

#include <iostream>
#include <conio.h>
#include <unify/BBox.h>
#include <unify/TestSuite.h>

int main( int argc, char ** argv )
{
	using namespace unify;

	TestSuite testSuite( "Geometry", "   " );

	testSuite.BeginSuite();
	{

		Matrix identity( MatrixIdentity() );
		Matrix scale( MatrixScale( 10, 100, 1000 ) );
		Matrix translate( MatrixTranslate( V3< float >( 1, 2, 3 ) ) );
		testSuite.BeginCase( "Matrix Identity" );
		{
			testSuite.Assert( "IsIdentity", identity.IsIdentity() );
		}
		testSuite.EndCase();

		testSuite.BeginCase( "Matrix Scaling" );
		{
			testSuite.Assert( "not IsIdentity", scale.IsIdentity() == false );
			testSuite.Assert( "scale( 0, 0 )", scale( 0, 0 ) == 10.0f );
			testSuite.Assert( "scale( 1, 1 )", scale( 1, 1 ) == 100.0f );
			testSuite.Assert( "scale( 2, 2 )", scale( 2, 2 ) == 1000.0f );
			testSuite.EndCase();
		}

		testSuite.BeginCase( "Matrix Translation" );
		{
			testSuite.Assert( "translate( 3, 0 )", translate( 3, 0 ) == 1.0f );
			testSuite.Assert( "translate( 3, 1 )", translate( 3, 1 ) == 2.0f );
			testSuite.Assert( "translate( 3, 2 )", translate( 3, 2 ) == 3.0f );
			testSuite.EndCase();
		}

		testSuite.BeginCase( "Matrix Transforms" );
		{
			Matrix final( identity * scale * translate );
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
			testSuite.Assert( "transformedCoordV2.x", transformedCoordV2.x == 11.0f );
			testSuite.Assert( "transformedCoordV2.y", transformedCoordV2.y == 202.0f );
			testSuite.Assert( "transformedCoordV3.x", transformedCoordV3.x == 31.0f );
			testSuite.Assert( "transformedCoordV3.y", transformedCoordV3.y == 402.0f );
			testSuite.Assert( "transformedCoordV3.z", transformedCoordV3.z == 5003.0f );
			testSuite.Assert( "transformedNormalV2.x", transformedNormalV2.x == 10.0f );
			testSuite.Assert( "transformedNormalV2.y", transformedNormalV2.y == 200.0f );
			testSuite.Assert( "transformedNormalV2.x", transformedNormalV3.x == 30.0f );
			testSuite.Assert( "transformedNormalV2.y", transformedNormalV3.y == 400.0f );
			testSuite.Assert( "transformedNormalV2.z", transformedNormalV3.z == 5000.0f );
			testSuite.Assert( "transformedV4.x", transformedV4.x == 69.0f );
			testSuite.Assert( "transformedV4.y", transformedV4.y == 718.0f );
			testSuite.Assert( "transformedV4.z", transformedV4.z == 8027.0f );
			testSuite.Assert( "transformedV4.w", transformedV4.w == 9.0f );
			scale.Invert();
			translate.Invert();
			translate.TransformCoord( transformedCoordV3 );
			scale.TransformCoord( transformedCoordV3 );
		}
		testSuite.EndCase();

		testSuite.BeginCase( "Quaternion" );
		{
			Quaternion q{ QuaternionIdentity() };
			testSuite.Assert( "IsIdentity", q.IsIdentity() );
			q *= q;
			testSuite.Assert( "* operator", q.IsIdentity() );

			Matrix mx( MatrixRotationAboutAxis( V3< float >( 1, 0, 0 ), AngleInDegrees( 180 ) ) );
			V3< float > vm( 1, 1, 1 );
			mx.TransformCoord( vm );

			Quaternion qx( Quaternion( V3< float >( 1, 0, 0 ), AngleInDegrees( 180 ) ) );
			Matrix mfromq( qx );
			V3< float > vq( 1, 1, 1 );
			mfromq.TransformCoord( vq );
			testSuite.Assert( "Quaternion rotation equivalancy with a matrix rotation.", vm == vq );
			testSuite.EndCase();

			testSuite.BeginCase( "Ray collision with BBox" );
			BBox<float > inFrontBBox( V3<float>( -10, -10, -10 ), V3<float>( 10, 10, 10 ) );
			inFrontBBox += V3<float>( 0, 0, 40 ); // Move BBox infront of us.

			Ray straightForwardRay( V3< float >( 0, 0, 0 ), V3< float >( 0, 0, 1 ) );
			Ray straightBackwardRay( V3< float >( 0, 0, 0 ), V3< float >( 0, 0, -1 ) );
			Ray straightForwardRayTooFarLeft( V3< float >( 0, 0, 0 ), V3< float >( 0, 0, 1 ) );
			straightForwardRayTooFarLeft.origin -= V3< float >( 11, 0, 0 );

			testSuite.Assert( "straightRay should hit inFrontBBox", inFrontBBox.Intersects( straightForwardRay, 0, 1000 ) == true );
			testSuite.Assert( "inverse straightRay should miss inFrontBBox", inFrontBBox.Intersects( straightBackwardRay, 0, 1000 ) == false );
			testSuite.Assert( "straightRay too far left should miss inFrontBBox", inFrontBBox.Intersects( straightForwardRayTooFarLeft, 0, 1000 ) == false );
		}
		testSuite.EndCase();
	}
	testSuite.EndSuite();

	std::cout << "Press any Enter to finish...\n";
	std::cin.ignore();

    return 0;
}