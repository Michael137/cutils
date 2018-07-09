#ifndef HASH_H_IN
#define HASH_H_IN

#include <stddef.h>
#include <stdint.h>

size_t hash_str_djb( char const* );
int64_t hash_int_64( int64_t );

#endif // HASH_H_IN
