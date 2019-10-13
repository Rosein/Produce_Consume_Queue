#include "errno.h"  //perror
#include "stdint.h" //uint32_t
#include "stdlib.h" //malloc
#include "stdio.h"  //printf
#include "stdbool.h"
#include "assert.h"

typedef struct 
{
    uint32_t * producer;
    uint32_t * consumer;
    uint32_t * arr;
    uint32_t max_size;
    uint32_t cur_size;
} PCQueue_t;



uint32_t * begin( PCQueue_t * queue )
{
    return queue -> arr;    
}

uint32_t * end( PCQueue_t * queue )
{
    return begin( queue ) + queue -> max_size;    
}

uint32_t * NOTHING_TO_CONSUME( PCQueue_t * queue )
{
    return begin( queue ) + queue -> max_size + 2;    
}

bool is_empty( PCQueue_t * queue )
{
    return 0 == queue -> cur_size;
}

void init( PCQueue_t * queue, int max_size )
{
    queue -> max_size = max_size;
    queue -> cur_size = 0;
    queue -> arr = ( uint32_t * ) malloc( max_size * sizeof( uint32_t ) );
    if( !queue -> arr )
        perror( "Bad alloc in init PCQueue_t." );
    queue -> producer = begin( queue );
    queue -> consumer = NOTHING_TO_CONSUME( queue );
}

void produce( PCQueue_t * queue, uint32_t new_elem )
{
    //Check if Full
    if( queue -> cur_size == queue -> max_size ||
        queue -> producer == queue -> consumer )
        return;
    //Add Elem
    *( queue -> producer ) = new_elem;
    queue -> cur_size++;
    //Introduce consumer
    if( queue -> cur_size == 1 )
        queue -> consumer = queue -> producer;
    //Update P
    if( queue -> producer < end( queue ) )
        queue -> producer++;
    else
        queue -> producer = begin( queue ); 
}

uint32_t consume( PCQueue_t * queue )
{
    uint32_t eaten;
    if( 0 < queue -> cur_size )
    {
        eaten = *( queue -> consumer );
        if( queue -> cur_size == queue -> max_size )
            queue -> producer = queue -> consumer;
        queue -> cur_size--;

    }
    if( 0 < queue -> cur_size )
    {
        if( queue -> consumer + 1 < end( queue ) )
            queue -> consumer++;
        else
            queue -> consumer = begin( queue );
    }
    else
        queue -> consumer = NOTHING_TO_CONSUME( queue );
    return eaten;
}
