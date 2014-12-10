/* barry/barry.c */


#if HAVE_CONFIG_H
#  include "config.h"
#else
#  error "missing config.h"
#endif


#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define WHEREAMI()               \
do{                              \
    printf( "%s; %s:%d\n",       \
            __PRETTY_FUNCTION__, \
            __FILE__,            \
            __LINE__ );          \
}while(0)                        \
/**/


int
main( int argc, char**argv )
{
#if 0
    printf( "\n" );
    WHEREAMI();
    for( int i = 0; i != argc; ++i )
        printf( "argv[%d] == \"%s\"\n", i, argv[i] );
#endif

    while( true ){
        static struct option opts[] =
            {
                {"help",    no_argument,       0, 'h'},
                {"version", no_argument,       0, 'V'},
                {0, 0, 0, 0}
            };

        /* getopt_long stores the option index here. */
        int optidx = 0;

        int c = getopt_long( argc, argv, "Vh", opts, &optidx );

        /* Detect the end of the options. */
        if( -1 == c ) break ;

        switch( c ){
        case 0:
            /* If this option set a flag, do nothing else now. */
            if( 0 != opts[optidx].flag ){
                break ;
            }
            printf ("option %s", opts[optidx].name);
            if( optarg ){
                printf( " with arg %s", optarg );
            }
            printf( "\n" );
            break ;

        case 'h':
            WHEREAMI();
            printf( "option -h\n" );
            break ;

        case 'V':
            printf( "%s\n", BARRY_VERSION );
            break ;

        case '?':
            /* getopt_long already printed an error message. */
            break ;

        default:
            abort ();
        }
    }
    return EXIT_SUCCESS ;
}
