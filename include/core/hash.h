#ifndef HASH_H_IN
#define HASH_H_IN

#include <stddef.h>
#include <stdint.h>

size_t hash_str_djb( char const* );
uint64_t hash_int_64( uint64_t );
uint32_t hash_int_32( uint32_t );

#endif // HASH_H_IN
