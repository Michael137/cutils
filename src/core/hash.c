#include <core/hash.h>

// djb hash
size_t hash_str_djb( char const* str )
{
	size_t hash = 5381;
	int c;

	while( ( c = *str++ ) )
		hash = ( ( hash << 5 ) + hash ) + c; /* hash * 33 + c */

	return hash;
}

// Thomas Wang's 64-bit Mix Hash
// http://web.archive.org/web/20071223173210/http://www.concentric.net/%7ETtwang/tech/inthash.htm
uint64_t hash_int_64( uint64_t h )
{
	h = ( ~h ) + ( h << 21 ); // h = (h << 21) - h - 1;
	h = h ^ ( h >> 24 );
	h = ( h + ( h << 3 ) ) + ( h << 8 ); // h * 265
	h = h ^ ( h >> 14 );
	h = ( h + ( h << 2 ) ) + ( h << 4 ); // h * 21
	h = h ^ ( h >> 28 );
	h = h + ( h << 31 );
	return h;
}

// Robert Jenkins' 32-bit Hash
// http://web.archive.org/web/20071223173210/http://www.concentric.net/%7ETtwang/tech/inthash.htm
uint32_t hash_int_32( uint32_t h )
{
	h = ( h + 0x7ed55d16 ) + ( h << 12 );
	h = ( h ^ 0xc761c23c ) ^ ( h >> 19 );
	h = ( h + 0x165667b1 ) + ( h << 5 );
	h = ( h + 0xd3a2646c ) ^ ( h << 9 );
	h = ( h + 0xfd7046c5 ) + ( h << 3 );
	h = ( h ^ 0xb55a4f09 ) ^ ( h >> 16 );
	return h;
}
