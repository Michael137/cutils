#include <containers/linked_list>
#include <conatiners/linked_list_internal>

struct LinkedList {
    LinkedListNode_ *head
                    *tail;
    size_t size;

#ifdef LL_DEBUG
    char* dbgStr;
#endif // LL_DEBUG
};
