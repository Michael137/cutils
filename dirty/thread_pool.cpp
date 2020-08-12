#include <atomic>
#include <iostream>
#include <queue>
#include <thread>
#include <type_traits>

class ThreadPool
{
	/*
	 *	ThreadPool tp{ 50 };
	 *	for(int i = 0; i < 60; ++i) {
	 *		tp.push([](int id, std::string const& message){ std::cout << message
	 *<< ' ' << id << std::endl; }, i, msg); if(i == 55) tp.clear();
	 *	}
	 *
	 *	clear: wait for running threads, clear queue
	 *	push: takes lambda and args..., adds work to queue, spawns thread if
	 *possible size: size of queue
	 *
	 *	Copy, move, &&=, &=: delete
	 *	Dtor: clear()
	 *	Ctor: optional size
	 */

   public:
	explicit ThreadPool( std::size_t cap = std::thread::hardware_concurrency() )
	    : mCapacity( cap )
	    , mIdle( cap )
	{
		for( int i = 0; i < cap; ++i )
		{
			mThreads.emplace_back( std::thread( [this]() {
				while( true )
				{
					std::unique_lock<std::mutex> lck{mQLock};
					mCV.wait( lck, [this]() {
						return !mQueue.empty() || !mPoolRunning;
					} );

					if( !mPoolRunning )
						return;

					--mIdle;

					auto work = mQueue.front();
					mQueue.pop();
					work();

					++mIdle;
				}
			} ) );
		}
	}

	template<typename T, typename... Args> void push( T&& fn, Args&&... args )
	{
		std::unique_lock<std::mutex> lck{mQLock};
		// mCV.wait( lck, [this]() { return mIdle > 0; } ); // TODO: block when
		// consumer bound?

		auto func
		    = std::bind( std::forward<T>( fn ), std::forward<Args>( args )... );
		mQueue.push( func );

		// lck.unlock(); // TODO: see how uncommenting this affects performance
		mCV.notify_one();
	}

	void stop()
	{
		// Clear queue
		mPoolRunning = false;

		{
			std::unique_lock<std::mutex> lck{mQLock};
			mCV.notify_all();
			std::queue<std::function<void()>>().swap( mQueue );
		}

		for( auto&& th: mThreads )
			if( th.joinable() )
				th.join();
	}

	~ThreadPool() { stop(); }

   private:
	ThreadPool( ThreadPool const& ) = delete;
	ThreadPool( ThreadPool&& )      = delete;

	ThreadPool& operator=( ThreadPool const& ) = delete;
	ThreadPool& operator=( ThreadPool&& ) = delete;

   private:
	std::queue<std::function<void()>> mQueue{};
	std::vector<std::thread> mThreads{};
	std::atomic<bool> mPoolRunning{true};
	std::mutex mQLock{};
	std::condition_variable mCV{};

	std::atomic<int> mIdle;
	std::size_t mCapacity;
};

int main()
{
	ThreadPool tp{10};
	for( int i = 0; i < 10; ++i )
		tp.push( []( int a ) { std::cout << "test" << std::endl; }, i );

	for( int i = 0; i < 10; ++i )
		tp.push( []( int a ) { std::cout << "test1" << std::endl; }, i );

	for( int i = 0; i < 10; ++i )
		tp.push( []( int a ) { std::cout << "test2" << std::endl; }, i );

	tp.stop();

	return 0;
}
