#include "typelist.h"
#include <type_traits>

using namespace tl;

int main()
{
	typedef Typelist<
		char,
		Typelist<signed char, Typelist<unsigned char, internal::NullType>>>
		CharList;

	typedef Typelist<
		signed char,
		Typelist<short int,
				 Typelist<int, Typelist<long int, internal::NullType>>>>
		SignedIntegrals;

	typedef TYPELIST_4( signed char, short int, int, long int )
		MacroSignedIntegrals;

	static_assert( std::is_same<SignedIntegrals, MacroSignedIntegrals>::value,
				   "Typelist macro expansion test" );

	static_assert( Length<CharList>::value == 3, "Length of typelist" );

	static_assert(
		std::is_same<TypeAt<CharList, 2>::Result, unsigned char>::value,
		"TypeAt test" );

	static_assert( IndexOf<CharList, signed char>::value == 1, "IndexOf test" );

	return 0;
}
