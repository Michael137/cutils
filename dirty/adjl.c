#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_GRAPH_SIZE 32

typedef struct EdgeNode
{
	int value;
	struct EdgeNode* next;
} EdgeNode;

typedef struct
{
	EdgeNode** vertices;
	size_t num_vertices;
	size_t capacity;
} adjl;

void adjl_add_edges( adjl* a, int edges[][2], size_t num_edges )
{
	for( int i = 0; i < num_edges; ++i )
	{
		int from = edges[i][0];
		int to = edges[i][1];
		printf("Adding edge: %d %d\n", from, to);
		EdgeNode* n = malloc(sizeof(EdgeNode));
		n->value = to;
		if( a->vertices[from] == NULL)
		{
			a->num_vertices++;
			n->next = NULL;
			a->vertices[from] = n;
		} else {
			n->next = a->vertices[from];
			a->vertices[from] = n;
		}

		EdgeNode* n2 = malloc(sizeof(EdgeNode));
		n2->value = from;
		if( a->vertices[to] == NULL)
		{
			a->num_vertices++;
			n2->next = NULL;
			a->vertices[to] = n2;
		} else {
			n2->next = a->vertices[to];
			a->vertices[to] = n2;
		}
	}
}

adjl* adjl_create( size_t size )
{
	size_t init_size   = ( size == 0 ) ? INITIAL_GRAPH_SIZE : size;
	adjl* a            = malloc( sizeof( adjl ) );
	a->vertices     = calloc( init_size, sizeof( EdgeNode* ) );
	a->num_vertices = 0;
	a->capacity     = init_size;
}

int main()
{
	adjl* a = adjl_create( 0 );

	int edges[5][2] = {{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4}};
	adjl_add_edges( a, edges, 5 );
	printf("Vertices: %d\n", a->num_vertices);
	for(int i = 0; i < a->capacity; ++i)
	{
		if(a->vertices[i] != NULL)
		{
			EdgeNode* it = a->vertices[i];
			printf("%d: ", i);
			while(it != NULL)
			{
				printf("%d ", it->value);
				it = it->next;
			}
			puts("");
		}
	}

	return 0;
}
