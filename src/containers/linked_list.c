#include <containers/linked_list.h>
#include <containers/linked_list_internal.h>
#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include <stdio.h> // printf

static void ll_inc_size_( LinkedList** llist )
{
    (*llist)->size++;
}

bool ll_create( LinkedList** llist )
{
    *llist = malloc( sizeof( LinkedList ) );
    (*llist)->head = NULL;
    (*llist)->tail = NULL;
    (*llist)->size = 0;

#ifdef LL_DEBUG
    (*llist)->dbgStr = "Map Created";
#endif
}

size_t ll_size( LinkedList const* llist )
{
    return llist->size;
}

void ll_debug( LinkedList const* llist, char const* extra )
{
#ifdef LL_DEBUG
    printf( "%s Linked List Debug: %s\n", extra, llist->dbgStr );
#endif // LL_DEBUG
}

// TODO: _Generic?
bool ll_push_front( LinkedList** llist, void const* data, const size_t data_size )
{
    if( llist && *llist )
    {
        void* copy = malloc( data_size );

        if( copy == NULL )
            return LL_FAILURE;

        memcpy( copy, data, data_size );

        LinkedListNode_* node = malloc( sizeof( LinkedListNode_ ) );

        if( node )
        {
            node->data = copy;

#ifdef LL_DEBUG
            node->dbgStr = "Node created";
#endif // LL_DEBUG

            LinkedListNode_* tmp = (*llist)->head;
            node->next = tmp;

            (*llist)->head = node;

            ll_inc_size_( llist );

            return LL_SUCCESS;
        }
        else
            return LL_FAILURE;
    }
    else
        return LL_INVALID_ARGS;
}

bool ll_free( LinkedList** llist )
{
    if( llist && *llist )
    {
        LinkedListNode_* tmp = (*llist)->head;
        while( tmp != NULL )
        {
            ll_debug_node_( tmp, "From free" );
            LinkedListNode_* next = tmp->next;
            free( tmp->data );
            free( tmp );
            tmp = next;
        }

        free( *llist );
        llist = NULL;
    }

    return LL_SUCCESS;
}

void* ll_at( LinkedList const* llist, const size_t idx )
{
    if( llist != NULL )
    {
        LinkedListNode_* tmp = llist->head;

        size_t ctr = 0;
        while( tmp != NULL )
        {
            if( ctr == idx )
            {
                ll_debug_node_( tmp, "From at" );

                return (void*)tmp->data; 
            }

            tmp = tmp->next;
            ctr++;
        }
    }
        return NULL; 
}

bool ll_remove( LinkedList** llist, const size_t idx )
{
    if( llist && *llist )
    {
        // TODO: llist_iter?
        LinkedListNode_ *curr,
                        *prev;

        prev = NULL;
        int ctr = 0;
        for( curr = (*llist)->head; curr != NULL; prev = curr,
                                                  curr = curr->next,
                                                  ++ctr )
        {
            if( idx == ctr )
            {
                if( prev == NULL )
                    (*llist)->head = curr->next;
                else
                    prev->next = curr->next;

                free( curr->data );
                free( curr );

                (*llist)->size--;

                return LL_SUCCESS;
            }
        }
    }
    else
        return LL_INVALID_ARGS;

    return LL_FAILURE;
}
