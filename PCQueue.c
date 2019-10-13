#include "PCQueue.h"
void ConsumeFirstAfterTwiceProduce ()
{
    PCQueue_t sut;
    init( &sut, 16 );
    produce( &sut, 1 );
    produce( &sut, 2 );
    assert( !is_empty( &sut ) );
    assert( consume( &sut ) == 1 );
    printf("\033[0;32m[ OK ]\033[0m Passed: %s \n", __func__ ); 
}

void JumpAfterProduceFilledToEnd ()
{
    PCQueue_t sut;
    init( &sut, 5 );
    produce( &sut, 1 );
    produce( &sut, 2 );
    produce( &sut, 3 );
    produce( &sut, 4 );
    produce( &sut, 5 );
    assert( !is_empty( &sut ) );
    consume( &sut );
    assert( sut.producer == begin( &sut ) );

    printf("\033[0;32m[ OK ]\033[0m Passed: %s \n", __func__ ); 
}

void ConsumeAllAfterProducerJump ()
{
    PCQueue_t sut;
    init( &sut, 5 );
    for( int i = 0; i < 5; i++ )
        produce( &sut, i + 1 );
    assert( !is_empty( &sut ) );
    for( int i = 0; i < 5; i++ )
        consume( &sut );
    assert( sut.producer == begin( &sut ) );
    assert( sut.consumer == NOTHING_TO_CONSUME( &sut ) );
    printf("\033[0;32m[ OK ]\033[0m Passed: %s \n", __func__ ); 
}


int main()
{
    ConsumeFirstAfterTwiceProduce();
    ConsumeAllAfterProducerJump();
    JumpAfterProduceFilledToEnd();
    return 0;
}
