# better-string-implementation
This is a Header-only c++ string implentation which specializes in dealing with small strings.🧵


## Usage ⌨

### Instantiation 
A string can be instanciated through a `char`, `const char*`, `str&`, or `shared_ptr<str>`.
  
```c++
#include "string-impl.h"

int main(){
  str x = "hello world";
  str y = x;
}
```
### Transformations / Operations 🪓➕🔍
Strings can be concatenated, characters removed, characters removed by index, split into a str array, and a multitude of other things. The syntax is kept as basic and minimal as possible.
For example, the output of this code: 
```c++
#include "string-impl.h"

int main(){
  str x = "hello world";
  str y = x;
  x += (y + (x).remove('l'));
  printf(x.c_str());
}
```
Would be `hello worldhello worldheo word`

### C-Like Functions 💾

I've implemented a number of c like functions, such as:
  - `strcmp`
  - `strncmp`
  - `strstr`
  - `strlen`
  - `strcat`

These work the same as their C equivalents and can be used not just with str-str comparisons, but also can be used in parralell with const char* and char[].
for example:
```c++
#include "string-impl.h"

int main()
{
	str x = "hello world";
	str z = "world";
	str y = x;
	if (strcmp(x, y) == 0)
		printf("its equal! \n");

	if (strcmp(x, "test") != 0)
		printf("not equal! \n");

	printf("world occurs at the index %i!", strstr(x, z));
}
```


All of the functions have detialed descriptions of their functions and parameters.

![image](https://user-images.githubusercontent.com/93481691/139591696-ab8584c4-4288-410d-beb3-e20f586ae139.png)


## Contributions
Please report any bugs, Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)
