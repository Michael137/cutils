#ifndef HEAP_H_IN
#define HEAP_H_IN

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

template<typename T> struct HeapElement
{
  public:
	HeapElement( size_t idx, T value ) : idx_( idx ), value_( value ) {}
	HeapElement() : idx_(), value_( T() ) {}
	~HeapElement() {}

	HeapElement& operator=( HeapElement rhs )
	{
		swap( *this, rhs );
		return *this;
	}

	HeapElement( HeapElement const& rhs )
	{
		this->idx_ = rhs.Idx();
		this->value_ = rhs.Value();
	}

	friend void swap( HeapElement& lhs, HeapElement& rhs )
	{
		using std::swap;
		swap( lhs.idx_, rhs.idx_ );
		swap( lhs.value_, rhs.value_ );
	}

	size_t Left() { return 2 * idx_; }
	size_t Right() { return 2 * idx_ + 1; }
	size_t Parent() { return std::floor( idx_ / 2 ); }

	size_t Idx() const { return this->idx_; };
	T const& Value() const { return this->value_; };
	void Value( T value ) { this->value_ = value; };

  private:
	size_t idx_;
	T value_;
};

template<class T>
std::ostream& operator<<( std::ostream& os, HeapElement<T> const& he )
{
	return os << "[" << he.Idx() << ":" << he.Value() << "]";
}

template<typename T, template<class P> class HeapOrderPolicy>
class Heap : public HeapOrderPolicy<T>
{
  private:
	using HeapVec = std::vector<HeapElement<T>>;

  public:
	using iterator = typename HeapVec::iterator;
	using const_iterator = typename HeapVec::const_iterator;

	iterator begin() { return elements.begin(); }
	iterator end() { return elements.end(); }
	const_iterator begin() const { return elements.begin(); }
	const_iterator end() const { return elements.end(); }
	const_iterator cbegin() const { return elements.cbegin(); }
	const_iterator cend() const { return elements.cend(); }

	Heap( std::vector<T> const& vec )
		: elements(),
		  numOfElements( vec.size() ),
		  height( std::floor( log2( numOfElements ) ) )
	{
		BuildHeap( vec );
	}

	void BuildHeap( std::vector<T> const& vec )
	{
		numOfElements = vec.size();
		elements = this->vec2heap( vec );
		for( int i = std::floor( numOfElements ) / 2; i >= 0; --i ) {
			HeapOrderPolicy<T>::heapify( elements, i );
		}
	}

  private:
	// Vector of elements with strict weak ordering
	HeapVec elements;
	size_t numOfElements;
	size_t height;

	static HeapVec vec2heap( std::vector<T> const& vec )
	{
		HeapVec heap{};
		heap.resize( vec.size() );
		int i = 0;
		std::transform(
			vec.begin(), vec.end(), heap.begin(),
			[&i]( T const& val ) { return HeapElement( i++, val ); } );

		return heap;
	}
};

template<class T, template<class P> class HeapOrderPolicy>
void heapify_aux( std::vector<HeapElement<T>>& vec, size_t idx )
{
	auto cmp_fn = typename HeapOrderPolicy<T>::cmp_fn();
	size_t largest = 0;
	size_t left = vec[idx].Left();
	size_t right = vec[idx].Right();
	if( left < vec.size() && cmp_fn( vec[left].Value(), vec[idx].Value() ) )
		largest = left;
	else
		largest = idx;

	if( right < vec.size() &&
		cmp_fn( vec[right].Value(), vec[largest].Value() ) )
		largest = right;

	if( largest != idx ) {
		auto tmp = vec[idx].Value();
		vec[idx].Value( vec[largest].Value() );
		vec[largest].Value( tmp );
		heapify_aux<T, HeapOrderPolicy>( vec, largest );
	}
}

template<class T> class MaxHeapPolicy
{
  private:
	using HeapVec = std::vector<HeapElement<T>>;

  public:
	using cmp_fn = std::greater<T>;

	static void heapify( HeapVec& vec, size_t idx )
	{
		heapify_aux<T, MaxHeapPolicy>( vec, idx );
	}
};

template<class T> class MinHeapPolicy
{
  private:
	using HeapVec = std::vector<HeapElement<T>>;

  public:
	using cmp_fn = std::less<T>;

	static void heapify( HeapVec& vec, size_t idx )
	{
		heapify_aux<T, MinHeapPolicy>( vec, idx );
	}
};

template<typename T> using MaxHeap = Heap<T, MaxHeapPolicy>;
template<typename T> using MinHeap = Heap<T, MinHeapPolicy>;

#endif // HEAP_H_IN
