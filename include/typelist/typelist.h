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

namespace tl {

// Length
template<typename TList> struct Length;
template<> struct Length<internal::NullType>
{
	enum { value = 0 };
};

template<typename Head, typename Tail>
struct Length<internal::Typelist<Head, Tail>>
{
	enum { value = 1 + Length<Tail>::value };
};

// TypeAt
template<class TList, unsigned int idx> struct TypeAt;

template<class Head, class Tail> struct TypeAt<internal::Typelist<Head, Tail>, 0>
{
	typedef Head Result;
};

template<class Head, class Tail, unsigned int idx>
struct TypeAt<internal::Typelist<Head, Tail>, idx>
{
	typedef typename TypeAt<Tail, idx - 1>::Result Result;
};

} // namespace tl

#endif // TYPELIST_H_IN
