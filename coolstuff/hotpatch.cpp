// g++ -pthread hotpatch.cpp && ./a.out
// clang++ -pthread hotpatch.cpp && ./a.out

#include <cassert>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include <sys/mman.h>

using namespace std::chrono_literals;

std::mutex g_mtx;

// clang-format off
#ifdef _WIN32
#error "Demo not supported on MSVC"
#else
#	define HOTPATCH_ALIGN(alignment)               \
             __attribute__((ms_hook_prologue))     \
             __attribute__((noinline))             \
             __attribute__((noclone))              \
             __attribute__((aligned(alignment)))
#endif

#define HOTPATCH HOTPATCH_ALIGN(8)
// clang-format on

static constexpr int PAGE_SIZE = 4096;

void hotpatch( void* target, void* replacement )
{
	// Is 8-byte aligned?
	assert( ( reinterpret_cast<uintptr_t>( target ) & 0x07 ) == 0 );

	void* page = reinterpret_cast<void*>( reinterpret_cast<uintptr_t>( target )
	                                      & ~0xfff );

	mprotect( page, PAGE_SIZE, PROT_WRITE | PROT_EXEC );

	uint32_t rel
	    = static_cast<char*>( replacement ) - static_cast<char*>( target ) - 5;

	// create x86 jump instruction to replacement address
	union {
		uint8_t data[8];
		uint64_t alignment;
	} instruction
	    = {{0xe9, static_cast<uint8_t>( rel >> 0 ),
	        static_cast<uint8_t>( rel >> 8 ), static_cast<uint8_t>( rel >> 16 ),
	        static_cast<uint8_t>( rel >> 24 )}};

	*reinterpret_cast<uint64_t*>( target )
	    = *reinterpret_cast<uint64_t*>( instruction.data );

	mprotect( page, PAGE_SIZE, PROT_EXEC );
}

HOTPATCH
int toHotpatch( int num )
{
	std::cout << "This function is being hotpatched " << num << std::endl;

	return num;
}

int replacement( int num )
{
	std::cout << "This is the replacement function " << num << std::endl;

	return num;
}

void workerCb( int arg )
{
	for( ;; )
	{
		std::lock_guard<std::mutex> lck( g_mtx );
		toHotpatch( arg );
		std::this_thread::sleep_for( 500ms );
	}
}

void hotpatcherCb( int arg )
{
	bool toggle = false;
	for( ;; )
	{
		std::lock_guard<std::mutex> lck( g_mtx );
		std::this_thread::sleep_for( 1s );
		if( toggle )
		{
			hotpatch( reinterpret_cast<void*>( toHotpatch ),
			          reinterpret_cast<void*>( replacement ) );
		}
		else
		{
			hotpatch( reinterpret_cast<void*>( replacement ),
			          reinterpret_cast<void*>( toHotpatch ) );
		}
		toggle ^= true;
	}
}

int main()
{
	std::thread worker{workerCb, 137};
	// std::thread hotpatcher{hotpatcherCb, 137};

	std::this_thread::sleep_for( 1s );
	hotpatch( reinterpret_cast<void*>( toHotpatch ),
	          reinterpret_cast<void*>( replacement ) );

	worker.join();
	// hotpatcher.join();
}
