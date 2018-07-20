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

// For non "char* dbgStr" members in DEBUG mode
#define DBG_CONTAINER_MEM( debug_type, container, member, default )            \
	_DBG_( debug_type )( container, member, default )

// For containers that have conditional "char* dbgStr" members
#define DBGSTR( debug_type, container )                                        \
	DBG_CONTAINER_MEM( debug_type, container, dbgStr, "" )

// If debug_type is off then assigns to stub var which is out of scope past the
// do loop
#define SET_DBGSTR( debug_type, container, msg )                               \
	do {                                                                       \
		DBG_CONTAINER_MEM( debug_type, container, dbgStr,                      \
						   __attribute( ( unused ) ) char* tmp_stub_var_ ) =   \
			msg;                                                               \
	} while( 0 )

#define SET_DBG_CONTAINER_MEM( debug_type, container, member, value )          \
	do {                                                                       \
		DBG_CONTAINER_MEM( debug_type, container, member,                      \
						   __attribute( ( unused ) ) void* tmp_stub_var_ ) =   \
			value;                                                             \
	} while( 0 )

#endif // DEBUG_H_IN
