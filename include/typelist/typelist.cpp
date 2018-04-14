#include "typelist.h"

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
	return 0;
}
