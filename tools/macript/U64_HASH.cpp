// implementation of djb2

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main (int argc, char * argv[])
{
	unsigned long long U64HashCode = 5831;
	int character;	
	size_t i = 1; 
	/**
	** we set "i" to 1 to start, because the perl script "macript.pl" is feeding
	** "./U64_HASH" as the first command line argument and to have consistent
	** hashes between preprocessing and runtime we do not want that
	** to be considered by the hash function
	**/

	while ( (i < argc) && (character = *argv[i++]) )
	{
		U64HashCode = ((U64HashCode << 5) + U64HashCode) + character;
		/* U64HashCode * 32 + character*/
	}

	cout << U64HashCode;
	
	return 0;
}