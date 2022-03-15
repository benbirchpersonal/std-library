
#include "include.h"
#include <cstdio>

/*
Sorting function example
*/
bool greaterThn ( int x1 , int x2 )
{
	return ( x1 > x2 );
}


int main ()
{

	// STRING TEST

	/*
	Testing empty string creation.
	Expected result:
	creates empty string and outputs nothing
	*/
	snd::str strE;
	printf ( strE.c_str () );


	/*
	Testing cosnt char string creation.
	Expected result:
	outputs test with newline character
	*/
	snd::str strCCT1 ( "test\n" );
	printf ( strCCT1.c_str () );


	/*
	Testing char string creation.
	Expected result:
	outputs char e
	*/
	snd::str strCT1 ( 'e' );
	printf ( strCT1.c_str () );

	/*
	Testing char string creation.
	Expected result:
	outputs char l
	*/
	snd::str strCT2 ( 'l' );
	printf ( strCT2.c_str () );

	/*
	Testing copy constructor
	Expected result:
	outputs test
	*/
	snd::str strCpy1 ( strCCT1 );
	printf ( strCpy1.c_str () );

	/*
	Testing string search function
	Expected result:
	
	*/

	if ( strCCT1.contains ("e" ) > -1)
		printf ( "%s contains e at index %i\n" , strCCT1.c_str (), strCCT1.contains("es"));

	if ( strCCT1.contains ( "l" ) > -1 )
		printf ( "%s contains l at %i\n" , strCCT1.c_str () , strCCT1.contains ( "l" ) );

	/*
	Testing string remove function
	Expected result:
	 "es"
	*/

	strCCT1 = strCCT1.remove ( 't' );
	printf ( strCCT1.c_str () );

	// REMOVE AT INDEX TEST



	/*
	Testing string search function
	Expected result:
	 "es"
	*/
	strCCT1 = strCCT1.removeAt ( 0 );
	printf ( strCCT1.c_str () );


	// CONST CHAR ASSIGNMENT TEST

	strCCT1 = "this is a test";
	printf ( strCCT1.c_str () );

	// SPLIT BY TEST AND ARRAY INSTANCIATION TEST

	/*
	Testing splitBy function
	Expected result: 
	4 seperate strings, "this" "is" "a" "test"
	*/
	snd::str strArr[4];
	int count = strCCT1.splitBy ( strArr , ' ' );
	printf ( "\n%i items in array:\n" , count );
	for ( int i = 0; i < count; i++ )
	{
		printf ( "%s\n",strArr[i].c_str());
	}


	/*
	length of string test
	Expected result:
	15
	*/
	printf ( "%i" , strCCT1.length () );



	// ARRAY TESTS
	printf("\nARRAY TESTS\n");
	/*
	Testing empty array creation.
	Expected result: array of size 10 with no elements.
	*/
	snd::arr<int , 10> testEmptyArr;

	/*
	Testing array creation through initializer list.
	Expected result: array of size 10 with given elements.
	*/
	snd::arr<int , 10> testInitList { 10,9,8,7,6,5,4,3,2,1 };

	/*
	Testing array assignment through initializer list.
	Expected result: array of size 10 with given elements.
	*/
	snd::arr<int , 10> testInitListAssignment = { 1,2,3,4,5,6,7,8,9,10 };


	/*
	Testing array sorting
	Expected result: sorted array of size 10
	*/
	testInitList.sort ( greaterThn );

	/*
	Testing array element count
	Expected result: 10
	*/
	printf ( "initList length (exp 10) :%i\n" , testInitList.count () );
	/*
	Testing array element count
	Expected result: 10
	*/
	printf ( "initList assigment length (exp 10) : %i\n" , testInitListAssignment.count () );

	/*
	Testing iterator and also testing the result of the sorting function.
	Expected result:
	numbers 1-10 in standard output
	*/
	for ( int x : testInitList )
	{
		printf ( "%i\n" , x );
	}
	/*
	Testing iterator and also testing the result of the sorting function.
	Expected result:
	numbers 1-10 in standard output
	*/
	for ( int x : testInitListAssignment )
	{
		printf ( "%i\n" , x );
	}
	/*
	Testing array item assignment
	Expected result:
	first item in array is 6
	*/
	testEmptyArr[0] = 6;
	printf("%i\n", testEmptyArr[0]);

	/*
	Testing erroneous data
	Expected result:
	failed assertion

	*/
	try
	{
		testInitList[12] = 5; // expected failed assertion here
	}
	catch ( int err )
	{
		printf ( "crashed!" );
	}

	printf("\n\n\nSTACK TESTS\n");

	/*
	Testing empty stack creation
	Expected result: 
	empty stack created
	*/
	snd::stack<int> emptyStackTest();

	/*
	Testing stack initializer list creation
	Expected result:
	Stack created with items 1,2,3,4,5,6,7,8,9,10
	*/

	snd::stack<int> StackTestInitList { 1,2,3,4,5,6,7,8,9,10 };
	for ( int x : StackTestInitList )
	{
		printf ( "%i\n" , x );
	}

	/*
	Testing stack initializer list creation
	Expected result:
	Stack created with items 1,2,3,4,5,6,7,8,9,10
	*/
	snd::stack<int> StackTestInitListAssignment = { 10,9,8,7,6,5,4,3,2,1 };
	for ( int x : StackTestInitListAssignment )
	{
		printf ( "%i\n" , x );
	}
	StackTestInitListAssignment.sort(greaterThn);
	for ( int x : StackTestInitListAssignment )
	{
		printf ( "%i\n" , x );
	}

	/*
	Testing stack push operation
	Expected result: 
	append 100 to the stack and print 100

	*/
	StackTestInitList.push(100);
	printf("%i\n", StackTestInitList.last ());


	/*
	Testing stack pop operation
	Expected result:
	pop 100 from the stack and print 100

	*/
	printf ( "%i\n" , StackTestInitList.pop() );



	printf("\n\n\nQUEUE TESTS\n");



	/*
	Testing empty queue creation
	Expected result:
	empty queue created
	*/
	snd::queue<int> emptyqueueTest ();

	/*
	Testing queue initializer list creation
	Expected result:
	queue created with items 1,2,3,4,5,6,7,8,9,10
	*/

	snd::queue<int> queueTestInitList { 1,2,3,4,5,6,7,8,9,10 };
	for ( int x : queueTestInitList )
	{
		printf ( "%i\n" , x );
	}

	/*
	Testing queue initializer list creation
	Expected result:
	queue created with items 1,2,3,4,5,6,7,8,9,10
	*/
	snd::queue<int> queueTestInitListAssignment = { 10,9,8,7,6,5,4,3,2,1 };
	for ( int x : queueTestInitListAssignment )
	{
		printf ( "%i\n" , x );
	}
	queueTestInitListAssignment.sort ( greaterThn );
	for ( int x : queueTestInitListAssignment )
	{
		printf ( "%i\n" , x );
	}

	/*
	Testing queue push operation
	Expected result:
	append 100 to the queue and print 100

	*/
	queueTestInitList.enqueue ( 100 );
	printf ( "%i\n" , queueTestInitList.last () );


	/*
	Testing queue dequeue operation
	Expected result:
	dequeue 100 from the queue and print 100

	*/
	printf ( "%i\n" , queueTestInitList.dequeue () );

	printf("\nCIRCULAR QUEUE TESTS\n");

	/*
	Testing empty circularQueue creation
	Expected result:
	empty circularQueue created
	*/

	snd::circularQueue<int, 10> emptycircularQueueTest ();

	/*
	Testing circularQueue initializer list creation
	Expected result:
	circularQueue created with items 1,2,3,4,5,6,7,8,9,10
	*/

	snd::circularQueue<int, 10> circularQueueTestInitList { 1,2,3,4,5,6,7,8,9,10 };
	for ( int x : circularQueueTestInitList )
	{
		printf ( "%i\n" , x );
	}

	/*
	Testing circularQueue initializer list creation
	Expected result:
	circularQueue created with items 1,2,3,4,5,6,7,8,9,10
	*/
	snd::circularQueue<int, 10> circularQueueTestInitListAssignment = { 10,9,8,7,6,5,4,3,2,1 };
	for ( int x : circularQueueTestInitListAssignment )
	{
		printf ( "%i\n" , x );
	}
	circularQueueTestInitListAssignment.sort ( greaterThn );
	for ( int x : circularQueueTestInitListAssignment )
	{
		printf ( "%i\n" , x );
	}

	/*
	Testing circularQueue push operation
	Expected result:
	do nothing as it is full
	should print 10

	*/
	circularQueueTestInitList.enqueue ( 100 );
	printf ( "%i\n" , circularQueueTestInitList.last () );


	/*
	Testing circularQueue deQueue operation
	Expected result:
	deQueue 1 from the circularQueue and print 1

	*/
	printf ( "%i\n" , circularQueueTestInitList.dequeue () );

	

	
	/*
	Testing pair creation
	*/
	snd::pair<int, const char*> pairTest;
	*pairTest.first = 1;
	*pairTest.second = "test";
	printf("\n{%i,%s}\n", *pairTest.first, *pairTest.second);




	snd::pair<int, int> pairSwapTest = { 1,2 };
	pairSwapTest.swap();

	printf("\n%i, %i \n", *pairSwapTest.first, *pairSwapTest.second);

	
	getchar ();


}

