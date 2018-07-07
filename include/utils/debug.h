#ifndef DEBUG_H_IN
#define DEBUG_H_IN

#define debug_more_( debug_type, fmt, ... )                                    \
	do {                                                                       \
		if( debug_type )                                                       \
			fprintf( stderr, "%s: %s:%d:%s(): " fmt, #debug_type, __FILE__,    \
					 __LINE__, __func__, __VA_ARGS__ );                        \
	} while( 0 )

#define debug_( debug_type, fmt, ... )                                         \
	do {                                                                       \
		if( debug_type ) fprintf( stderr, fmt, __VA_ARGS__ );                  \
	} while( 0 )

#define _DBGSTR_( debug_type ) DBGSTR_##debug_type
#define DBGSTR_0( container, member ) ""
#define DBGSTR_1( container, member ) ( container )->member

#define DBG_CONTAINER_MEM( debug_type, container, member )                     \
	_DBGSTR_( debug_type )( container, member )

// For containers that have conditional "dbgStr" members
#define DBGSTR( debug_type, container )                                        \
	DBG_CONTAINER_MEM( debug_type, container, dbgStr )

#endif // DEBUG_H_IN
