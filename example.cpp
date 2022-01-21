#define DEBUG
#include "stack-impl.h"
int main ()
{
	snd::arr<int> x {1,2,3,4,5};
	for(int xx : x)
		printf("%i,",xx);
}
