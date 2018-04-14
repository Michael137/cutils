#ifndef TYPELIST_H_IN
#define TYPELIST_H_IN

// include <typelist/typelist_internal.h>
#include "typelist_internal.h"

#define TYPELIST_1( T1 ) tl::Typelist<T1, tl::internal::NullType>
#define TYPELIST_2( T1, T2 ) tl::Typelist<T1, TYPELIST_1( T2 )>
#define TYPELIST_3( T1, T2, T3 ) tl::Typelist<T1, TYPELIST_2( T2, T3 )>
#define TYPELIST_4( T1, T2, T3, T4 ) tl::Typelist<T1, TYPELIST_3( T2, T3, T4 )>
#define TYPELIST_5( T1, T2, T3, T4, T5 )                                       \
	tl::Typelist<T1, TYPELIST_4( T2, T3, T4, T5 )>

namespace tl
{

/*
** Typelist
*/
template<typename T, typename U> struct Typelist {
	typedef T Head;
	typedef U Tail;
};
/*
** Length
*/
template<typename TList> struct Length;
template<> struct Length<internal::NullType> {
	enum { value = 0 };
};

template<typename Head, typename Tail> struct Length<Typelist<Head, Tail>> {
	enum { value = 1 + Length<Tail>::value };
};

/*
** TypeAt
*/
template<typename TList, unsigned int idx> struct TypeAt;

template<typename Head, typename Tail> struct TypeAt<Typelist<Head, Tail>, 0> {
	typedef Head Result;
};

template<typename Head, typename Tail, unsigned int idx>
struct TypeAt<Typelist<Head, Tail>, idx> {
	typedef typename TypeAt<Tail, idx - 1>::Result Result;
};

/*
** IndexOf - Linear search through Typelist
*/
template<typename TList, typename T> struct IndexOf;

// List is null
template<typename T> struct IndexOf<internal::NullType, T> {
	enum { value = -1 };
};

// Found type in first element
template<typename T, typename Tail> struct IndexOf<Typelist<T, Tail>, T> {
	enum { value = 0 };
};

// Check rest of list
template<typename Head, typename Tail, typename T>
struct IndexOf<Typelist<Head, Tail>, T> {
  private:
	enum { temp = IndexOf<Tail, T>::value };

  public:
	enum { value = temp == -1 ? -1 : 1 + temp };
};

} // namespace tl

#endif // TYPELIST_H_IN
