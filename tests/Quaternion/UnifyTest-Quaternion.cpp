#include <unify/Quaternion.h>
#include <unify/Matrix.h>
#include <iostream>
#include <conio.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using std::cout;
	using std::endl;

	Quaternion q( QuaternionIdentity() );
	assert( q.IsIdentity() );

	q *= q;
	assert( q.IsIdentity() );

	{
		Matrix mx( MatrixRotationAboutAxis( V3< float >( 1, 0, 0 ), AngleInDegrees( 180 ) ) );
		V3< float > vm( 1, 1, 1 );
		mx.TransformCoord( vm );

		Quaternion qx( Quaternion( V3< float >( 1, 0, 0 ), AngleInDegrees( 180 ) ) );
		Matrix mfromq( qx );
		V3< float > vq( 1, 1, 1 );
		mfromq.TransformCoord( vq );
		assert( vm == vq );
	}

	cout << "\nQuaternion tests passed!\n";
	cout << "Press any key to finish...\n";

	cout << std::endl << std::endl;
	while ( !_getch() );

	return 0;
}