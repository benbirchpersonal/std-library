#include "string-impl.h"
#include "array-impl.h"
#include "stack-impl.h"
int main() {
	arr<int> x = {0,1,4,2,6,3,5,7,8,3,1,4,5,2,3,5,2,3,5,2};
	stack<size_t> xy = x.find(2);
	for (size_t s : xy)
		printf("%i ", s);

	str teststr = "";
	teststr += "test";

}
