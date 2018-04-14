#include "typelist.h"
#include <type_traits>

using namespace tl;

int main()
{
	typedef internal::Typelist<
		char,
		internal::Typelist<
			signed char, internal::Typelist<unsigned char, internal::NullType>>>
		CharList;

	typedef internal::Typelist<
		signed char,
		internal::Typelist<
			short int,
			internal::Typelist<
				int, internal::Typelist<long int, internal::NullType>>>>
		SignedIntegrals;

	typedef TYPELIST_4( signed char, short int, int, long int )
		MacroSignedIntegrals;

	static_assert( std::is_same<SignedIntegrals, MacroSignedIntegrals>::value,
				   "Typelist macro expansion test" );

	static_assert( Length<CharList>::value == 3, "Length of typelist" );

	static_assert( std::is_same<TypeAt<CharList, 2>::Result, unsigned char>::value, "TypeAt test");

	return 0;
}
