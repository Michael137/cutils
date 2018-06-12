#ifndef LL_LOOP_H_IN
#define LL_LOOP_H_IN

bool ll_has_loop_naive( LinkedList const* llist );
bool ll_has_loop_naive_hashed( LinkedList const* llist );
inline bool ll_has_loop( __attribute((unused)) LinkedList const* llist ) { return false; }

#endif // LL_LOOP_H_IN
