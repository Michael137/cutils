#ifndef TYPELIST_H_IN
#define TYPELIST_H_IN

// include <typelist/typelist_internal.h>
#include "typelist_internal.h"

#define TYPELIST_1( T1 ) tl::internal::Typelist<T1, tl::internal::NullType>
#define TYPELIST_2( T1, T2 ) tl::internal::Typelist<T1, TYPELIST_1( T2 )>
#define TYPELIST_3( T1, T2, T3 )                                               \
	tl::internal::Typelist<T1, TYPELIST_2( T2, T3 )>
#define TYPELIST_4( T1, T2, T3, T4 )                                           \
	tl::internal::Typelist<T1, TYPELIST_3( T2, T3, T4 )>
#define TYPELIST_5( T1, T2, T3, T4, T5 )                                       \
	tl::internal::Typelist<T1, TYPELIST_4( T2, T3, T4, T5 )>

#endif // TYPELIST_H_IN
