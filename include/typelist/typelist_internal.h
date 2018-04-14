#ifndef TYPELIST_INTERNAL_H_IN
#define TYPELIST_INTERNAL_H_IN

namespace tl
{
namespace internal
{

class NullType
{
};
struct EmptyType {
};

template<typename T, typename U> struct Typelist {
	typedef T Head;
	typedef U Tail;
};

} // namespace internal
} // namespace tl

#endif // TYPELIST_INTERNAL_H_IN
