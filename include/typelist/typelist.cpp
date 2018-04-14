#include "typelist.h"

using namespace tl;

int main()
{
	typedef internal::Typelist<char,
				   internal::Typelist<signed char,
				   internal::Typelist<unsigned char, internal::NullType>>> CharList;
	return 0;
}
