#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

template<class T> struct Node
{
   private:
	bool marked_;
	T item_;

   public:
	int key; // Hash of item
	std::shared_ptr<Node<T>> next;
	std::mutex lock;

	// For logical deletion
	bool isMarked() { return marked_; }
	T getItem() { return item_; }

	explicit Node( T item )
	    : key( std::hash<T>{}( item ) )
	    , next( nullptr )
	    , marked_( false )
	    , item_( item )
	    , lock()
	{
	}

	Node( T item, int key )
	    : key( key )
	    , next( nullptr )
	    , marked_( false )
	    , item_( item )
	    , lock()
	{
	}
};

// List with optimistic synchronization
template<class T> class LazyList
{
   public:
	LazyList()
	    : head_( std::make_shared<Node<T>>( T(),
	                                        std::numeric_limits<int>::min() ) )
	    , tail_( std::make_shared<Node<T>>( T(),
	                                        std::numeric_limits<int>::max() ) )
	{
		head_->next = tail_;
	}

	bool add( T item )
	{
		int key = std::hash<T>{}( item );
		while( true )
		{
			auto pred = head_;
			auto curr = pred->next;
			while( curr->key < key )
			{
				pred = curr;
				curr = curr->next;
			}

			std::scoped_lock lock( pred->lock, curr->lock );
			if( validate( pred, curr ) )
			{
				if( curr->key == key )
					return false;
				else
				{
					auto node  = std::make_shared<Node<T>>( item );
					node->next = curr;
					pred->next = node;
					return true;
				}
			}
		}

		return false;
	}
	bool remove( T item ) { return true; }
	bool contains( T const& item ) { return true; }
	// bool validate( Node<T> const& a, Node<T> const& b ) { return true; }
	bool validate( std::shared_ptr<Node<T>> a, std::shared_ptr<Node<T>> b )
	{
		return true;
	}

   private:
	std::shared_ptr<Node<T>> head_;
	std::shared_ptr<Node<T>> tail_;
};

int main()
{
	LazyList<int> lst;
	lst.add( 5 );
	return 0;
}
