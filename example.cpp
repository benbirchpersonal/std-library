#define DEBUG
#include "include.h"
#include <array>
bool greaterThn (  int x1 ,  int x2 )
{
	return ( x1 > x2 );
}

int main ()
{
	std::array<int,10> x;
	// STRING TEST

	// EMPTY INIT
	snd::str strE;
	printf ( strE.c_str () );


	// CONST CHAR INIT
	snd::str strCCT1 ( "test" );
	printf ( strCCT1.c_str () );


	// CHAR INIT
	snd::str strCT1 ( 'e' );
	printf ( strCT1.c_str () );

	snd::str strCT2 ( 'l' );
	printf ( strCT2.c_str () );

	// COPY CONSTRUCTOR

	snd::str strCpy1 ( strCCT1 );
	printf ( strCpy1.c_str () );

	// CONTAINS TEST

	if ( strCCT1.contains ( "e" ) )
		printf ( "%s contains e\n" , strCCT1.c_str () );

	if ( strCCT1.contains ( "l" ) )
		printf ( "%s contains e\n" , strCCT1.c_str () );



	if ( strCCT1.contains ( strCT1 ) )
		printf ( "%s contains e\n" , strCCT1.c_str () );

	if ( strCCT1.contains ( strCT2 ) )
		printf ( "%s contains t\n" , strCCT1.c_str () );

	// REMOVE CHARACTER TEST

	strCCT1 = strCCT1.remove ( 't' );
	printf ( strCCT1.c_str () );

	// REMOVE AT INDEX TEST

	strCCT1 = strCCT1.removeAt ( 0 );
	printf ( strCCT1.c_str () );

	// CONST CHAR ASSIGNMENT TEST

	strCCT1 = "this is a test";


	// SPLIT BY TEST AND ARRAY INSTANCIATION TEST

	snd::str strArr[4];

	int count = strCCT1.splitBy ( strArr , ' ' );
	printf ( "%i items in array:" , count );
	for ( int i = 0; i < count; i++ )
	{
		printf ( "%s" , strArr[i] );
	}
	// LENGTH TEST   
	printf ( "%i" , strCCT1.length () );

	// XOR TEST
	printf ( "%i" , strCCT1.Xor ( 0b01010101 ).c_str() );


	// ARRAY TESTS

	snd::arr<int, 10> testEmptyArr;

	snd::arr<int, 10> testInitList { 10,9,8,7,6,5,4,3,2,1 };
	snd::arr<int, 10> testInitListAssignment = { 1,2,3,4,5,6,7,8,9,10 };

	testInitList.sort ( greaterThn );


	printf ( "initList length (exp 10) :%i\n" , testInitList.count () );
	printf ( "initList assigment length (exp 10) : %i\n" , testInitListAssignment.count() );
	for ( int x : testInitList )
	{
		printf ( "%i\n" , x );
	}

	for ( int x : testInitListAssignment )
	{
		printf ( "%i\n" , x );
	}
	testEmptyArr[0] = 6;
	try
	{
		testInitList[12] = 5; // expected crash here	
	}
	catch ( int err )
	{
		printf ( "crashed!" );
	}

	

	snd::stack<int> emptyStackTest;

	snd::stack<int> StackTestInitList {1,2,3,4,5,6,7,8,9,10};
	for ( int x : StackTestInitList )
	{
		printf ( "%i\n" , x );
	}

	snd::stack<int> StackTestInitListAssignment = { 1,2,3,4,5,6,7,8,9,10 };
	for ( int x : StackTestInitListAssignment )
	{
		printf ( "%i\n" , x );
	}
	getchar();


}


