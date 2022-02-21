#define DEBUG
#include "include.h"
int main()
{

	// STRING TEST

	// EMPTY INIT
	snd::str strE;
	printf(strE.c_str());


	// CONST CHAR INIT
	snd::str strCCT1 ("test"); 
	printf(strCCT1.c_str());


	// CHAR INIT
	snd::str strCT1('e');
	printf(strCT1.c_str());

	snd::str strCT2('l');
	printf(strCT2.c_str());

	// COPY CONSTRUCTOR

	snd::str strCpy1(strCCT1);
	printf(strCpy1.c_str());

	// CONTAINS TEST
	
	if (strCCT1.contains("e"))
		printf("%s contains e\n", strCCT1.c_str());

	if (strCCT1.contains("l"))
		printf("%s contains e\n", strCCT1.c_str());



	if (strCCT1.contains(strCT1))
		printf("%s contains e\n", strCCT1.c_str());

	if (strCCT1.contains(strCT2))
		printf("%s contains t\n", strCCT1.c_str());
	
	// REMOVE CHARACTER TEST
	
	strCCT1 = strCCT1.remove('t');
	printf(strCCT1.c_str());
	
	// REMOVE AT INDEX TEST
	
	strCCT1 = strCCT1.removeAt(0);
	printf(strCCT1.c_str());
	
	// CONST CHAR ASSIGNMENT TEST
	
	strCCT1 = "this is a test";
	
	
	// SPLIT BY TEST AND ARRAY INSTANCIATION TEST
	
	snd::str strArr[4];
	
	int count = splitBy(&strArr, ' ');
	printf("%i items in array:", count);
	for(int i = 0; i < count; i++){
		printf("%s", strArr[i]);	
	}
	// LENGTH TEST   
	printf("%i", strCCT1.length());
	
	// XOR TESTA
	printf("%i", strCCT1.Xor(0b01010101));


	// ARRAY TESTS

	snd::arr<int> testEmptyArr(10);

	snd::arr<int> testInitList {1,2,3,4,5,6,7,8,9,10};
	snd::arr<int> testInitListAssignment = {1,2,3,4,5,6,7,8,9,10};

	printf("initList length (exp 10) :%i", testInitList.count());
	printf("initList assigment length (exp 10) : %i", testInitListAssignment.Count());
	for(int x : testInitList){
		printf("%i", x);
	}

	for(int x : testInitListAssignment){
		printf("%i", x);
	}
	testEmptyArr[0] = 6;
	testInitList[12] = 5; // expected crash here
}
		   
		   
	
