#include <functional>
#include <iostream>
#include <memory>
#include <vector>

template<class T> struct Node
{
   private:
	bool marked_;
	T item_;

   public:
	int key; // Hash of item
	std::shared_ptr<Node<T>> next;

	void lock(){};
	void unlock(){};

	// For logical deletion
	bool isMarked() { return marked_; }
	T getItem() { return item_; }

	Node( T item )
	    : key( std::hash<T>{}( item ) )
	    , next( nullptr )
	    , marked_( false )
	    , item_( item )
	{
	}
};

// List with optimistic synchronization
template<class T> class LazyList
{
   public:
	bool add( T item )
	{
		int key = std::hash<T>{}( item );
		while( true )
		{
			auto pred = head_;
			auto curr = head_->next;
			while( curr->key < key )
			{
				pred = curr;
				curr = curr->next;
			}

			pred->lock();
			try
			{
				FinallyWrapper<void()> predUnlock(
				    [&pred]() { pred->unlock(); } );
				curr->lock();
				try
				{
					FinallyWrapper<void()> currUnlock(
					    [&curr]() { curr->unlock(); } );
					if( validate( *curr, *pred ) )
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
				catch( ... )
				{
					std::terminate();
				}
			}
			catch( ... )
			{
				std::terminate();
			}
		}

		return false;
	}
	bool remove( T item ) { return true; }
	bool contains( T const& item ) { return true; }
	bool validate( Node<T> const& a, Node<T> const& b ) { return true; }

   private:
	std::shared_ptr<Node<T>> head_;

	template<class F> class FinallyWrapper
	{
	   public:
		FinallyWrapper( std::function<F> finally_fn )
		    : fn_( finally_fn )
		{
		}
		~FinallyWrapper() { fn_(); }

	   private:
		std::function<F> fn_;
	};
};

int main()
{
	LazyList<int> lst;
	lst.add( 5 );
	return 0;
}
