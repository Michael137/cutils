// g++ -pthread hotpatch.cpp && ./a.out
// clang++ -pthread hotpatch.cpp && ./a.out

#include <atomic>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include <sys/mman.h>

using namespace std::chrono_literals;

std::mutex g_mtx;
std::condition_variable g_cv;
std::atomic<bool> g_shouldPatch{false};

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

	// Doesn't work on W^X (write XOR execute) systems
	mprotect( page, PAGE_SIZE, PROT_WRITE | PROT_EXEC );

	// To account for E9 instruction sub 5 bytes
	uint32_t rel
	    = static_cast<char*>( replacement ) - static_cast<char*>( target ) - 5;

	// Create x86 jump instruction to replacement address
	// Assumes addrs lay within 2gb
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

void unpatch( void* target )
{
	// Is 8-byte aligned?
	assert( ( reinterpret_cast<uintptr_t>( target ) & 0x07 ) == 0 );

	void* page = reinterpret_cast<void*>( reinterpret_cast<uintptr_t>( target )
	                                      & ~0xfff );

	// Doesn't work on W^X (write XOR execute) systems
	mprotect( page, PAGE_SIZE, PROT_WRITE | PROT_EXEC );

	// Replace hook stub with NOPs
	union {
		uint8_t data[8];
		uint64_t alignment;
	} instruction = {{0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48}};

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

__attribute__( ( optimize( "O0" ) ) ) void workerCb( int arg )
{
	for( int i = 0;; ++i )
	{
		{
			std::lock_guard<std::mutex> lck( g_mtx );
			toHotpatch( arg );
		}

		if( i >= 10 )
		{
			g_cv.notify_one();
			i = 0;
		}

		std::this_thread::sleep_for( 100ms );
	}
}

__attribute__( ( optimize( "O0" ) ) ) void hotpatcherCb( int arg )
{
	for( ;; )
	{
		std::unique_lock<std::mutex> lck( g_mtx );
		g_cv.wait( lck );

		// Listen for signal
		if( g_shouldPatch )
		{
			hotpatch( reinterpret_cast<void*>( toHotpatch ),
			          reinterpret_cast<void*>( replacement ) );
			g_shouldPatch = false;
		}
		else
		{
			unpatch( reinterpret_cast<void*>( toHotpatch ) );
			g_shouldPatch = true;
		}
	}
}

int main()
{
	std::thread worker{workerCb, 137};
	std::thread hotpatcher{hotpatcherCb, 137};

	hotpatcher.join();
	worker.join();
}
