// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

/// <summary>
/// Test DataLock.
/// </summary>

#include <unify/DataLock.h>
#include <unify/String.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;
	using namespace string;

	Suite suite;
	suite.BeginSuite( "DataLock" );
	{
		suite.BeginCase( "FromString" );
		suite.Assert( "from \"None\"", DataLockAccess::None == DataLockAccess::FromString( "None" ) );
		suite.Assert( "from \"Readonly\"", DataLockAccess::Readonly == DataLockAccess::FromString( "Readonly" ) );
		suite.Assert( "from \"Writeonly\"", DataLockAccess::Writeonly == DataLockAccess::FromString( "Writeonly" ) );
		suite.Assert( "from \"Readonly\"", DataLockAccess::ReadWrite == DataLockAccess::FromString( "ReadWrite" ) );
		suite.EndCase();

		suite.BeginCase( "ToString" );
		suite.Assert( "from \"None\"", "None" == DataLockAccess::ToString( DataLockAccess::None ) );
		suite.Assert( "from \"Readonly\"", "Readonly" == DataLockAccess::ToString( DataLockAccess::Readonly ) );
		suite.Assert( "from \"Writeonly\"", "Writeonly" == DataLockAccess::ToString( DataLockAccess::Writeonly ) );
		suite.Assert( "from \"Readonly\"", "ReadWrite" == DataLockAccess::ToString( DataLockAccess::ReadWrite ) );
		suite.EndCase();

		suite.BeginCase( "ReadAccess" );
		suite.Assert( "None", DataLockAccess::ReadAccess( DataLockAccess::None ) == false );
		suite.Assert( "Readonly", DataLockAccess::ReadAccess( DataLockAccess::Readonly ) == true );
		suite.Assert( "Writeonly", DataLockAccess::ReadAccess( DataLockAccess::Writeonly ) == false );
		suite.Assert( "Readonly", DataLockAccess::ReadAccess( DataLockAccess::ReadWrite ) == true );
		suite.EndCase();

		suite.BeginCase( "WriteAccess" );
		suite.Assert( "None", DataLockAccess::WriteAccess( DataLockAccess::None ) == false );
		suite.Assert( "Readonly", DataLockAccess::WriteAccess( DataLockAccess::Readonly ) == false );
		suite.Assert( "Writeonly", DataLockAccess::WriteAccess( DataLockAccess::Writeonly ) == true );
		suite.Assert( "Readonly", DataLockAccess::WriteAccess( DataLockAccess::ReadWrite ) == true );
		suite.EndCase();

		suite.BeginCase( "GetItemReadonly" );
		{
			struct Data
			{
				int value1;
				int value2;
				int value3;

				bool operator==( const Data & data ) const
				{
					return value1 == data.value1 && value2 == data.value2 && value3 == data.value3;
				}
			};

			Data data[] =
			{
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 }
			};

			DataLock lock( &data, sizeof( Data ) * 3, 3, DataLockAccess::Readonly, 0 );

			suite.Assert( "first element", (*lock.GetItemReadonly< Data >( 0 )) == Data{ 1, 2, 3 } );
			suite.Assert( "second element", (*lock.GetItemReadonly< Data >( 1 )) == Data{ 4, 5, 6 } );
			suite.Assert( "third element", (*lock.GetItemReadonly< Data >( 2 )) == Data{ 7, 8, 9 } );
		}

		suite.BeginCase( "GetData" );
		{
			struct Data
			{
				int value1;
				int value2;
				int value3;

				bool operator==( const Data & data ) const
				{
					return value1 == data.value1 && value2 == data.value2 && value3 == data.value3;
				}
			};

			Data data[] =
			{
				{ 1, 2, 3 },
				{ 4, 5, 6 },
				{ 7, 8, 9 }
			};

			DataLock lock( &data, sizeof( Data ) * 3, 3, DataLockAccess::ReadWrite, 0 );

			Data writeData[] =
			{
				{ 10, 11, 12 },
				{ 13, 14, 15 },
				{ 16, 17, 18 }
			};

			*lock.GetItem< Data >( 0 ) = writeData[0];
			*lock.GetItem< Data >( 1 ) = writeData[1];
			*lock.GetItem< Data >( 2 ) = writeData[2];

			suite.Assert( "first element", (*lock.GetItemReadonly< Data >( 0 )) == Data{ 10, 11, 12 } );
			suite.Assert( "second element", (*lock.GetItemReadonly< Data >( 1 )) == Data{ 13, 14, 15 } );
			suite.Assert( "third element", (*lock.GetItemReadonly< Data >( 2 )) == Data{ 16, 17, 18 } );
		}
		suite.EndCase();
	}
	suite.EndSuite();
	return 0;
}