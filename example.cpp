#define STRING
#define ARRAY
#include "include.h"
int main() {
	arr<str> s = { "test","test","test" };
	printf("%s, %s, %s", s[0].c_str(), s[1].c_str(), s[2].c_str());

}
