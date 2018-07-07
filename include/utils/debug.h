#ifndef DEBUG_H_IN
#define DEBUG_H_IN

#define DEBUG_MORE_( debug_type, fmt, ... )                                    \
	do {                                                                       \
		if( debug_type )                                                       \
			fprintf( stderr, "%s: %s:%d:%s(): " fmt, #debug_type, __FILE__,    \
					 __LINE__, __func__, __VA_ARGS__ );                        \
	} while( 0 )

#define DEBUG_( debug_type, fmt, ... )                                         \
	do {                                                                       \
		if( debug_type ) fprintf( stderr, fmt, __VA_ARGS__ );                  \
	} while( 0 )

#define _DBG_( debug_type ) _DBG_##debug_type
#define _DBG_0( container, member, default ) default
#define _DBG_1( container, member, default ) ( container )->member

#define DBG_CONTAINER_MEM( debug_type, container, member, default )            \
	_DBG_( debug_type )( container, member, default )

// For containers that have conditional "dbgStr" members
#define DBGSTR( debug_type, container )                                        \
	DBG_CONTAINER_MEM( debug_type, container, dbgStr, "" )

#endif // DEBUG_H_IN
