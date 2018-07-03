#ifndef DEBUG_H_IN
#define DEBUG_H_IN

#define debug_more_( debug_type, fmt, ... )                                    \
	do {                                                                       \
		if( #debug_type )                                                      \
			fprintf( stderr, "%s: %s:%d:%s(): " fmt, #debug_type, __FILE__,    \
					 __LINE__, __func__, __VA_ARGS__ );                        \
	} while( 0 )

#define debug_( debug_type, fmt, ... )                                         \
	do {                                                                       \
		if( #debug_type ) fprintf( stderr, fmt, __VA_ARGS__ );                 \
	} while( 0 )

#endif // DEBUG_H_IN
