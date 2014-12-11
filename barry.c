/* barry/barry.c */


#if HAVE_CONFIG_H
#  include "config.h"
#else
#  error "missing config.h"
#endif


#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>


#define WHEREAMI( STREAM )        \
do{                               \
    fprintf( STREAM,              \
             "%s; %s:%d\n",       \
             __PRETTY_FUNCTION__, \
             __FILE__,            \
             __LINE__ );          \
}while(0)                         \
/**/


#define FAIL_UNLESS( EXPR )   \
do{                           \
    if( ! ( EXPR ) ){         \
        perror( #EXPR );      \
        WHEREAMI( stderr );   \
        exit( EXIT_FAILURE ); \
    }                         \
}while(0)                     \
/**/


void print_help( void )
{
    printf("\nUsage:");
    printf("\n  barry [options] [files...]");
    printf("\n");
    printf("\nOptions:");
    printf("\n");
    printf("\n  -V, --version     output version information and exit");
    printf("\n  -h, --help        display this help and exit");
    printf("\n  -o, --out <file>  write to specified file");
    printf("\n");
    printf("\n");
}


int
main( int const argc, char**argv )
{
#if 0
    printf( "\n" );
    WHEREAMI();
    for( int i = 0; i != argc; ++i )
        printf( "argv[%d] == \"%s\"\n", i, argv[i] );
#endif

    FILE*foutput = stdout ;

    while( true ){
        static struct option opts[] =
            {
                { "help",    no_argument,       0, 'h' },
                { "version", no_argument,       0, 'V' },
                { "output",  required_argument, 0, 'o' },
                { 0, 0, 0, 0 }
            };

        /* getopt_long stores the option index here. */
        int optidx = 0;

        int c = getopt_long( argc, argv, "Vho:", opts, &optidx );

        /* printf( "optidx == %d\n", optidx ); */

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

        case 'V':
            printf( "barry %s\n", BARRY_VERSION );
            return EXIT_SUCCESS ;

        case 'h':
            print_help();
            return EXIT_SUCCESS ;

        case 'o':
            FAIL_UNLESS( foutput = fopen( optarg, "w" ) );
            break ;

        default:
            fprintf( stderr, "getopt_long() returned '%c'", c );
        case '?':
            /* getopt_long already printed an error message. */
            print_help();
            return EXIT_FAILURE ;
        }
    }

    for( int i = optind, n = argc; i < n; ++i ){
        FILE*finput ;
        FAIL_UNLESS( finput = fopen( argv[i], "r" ) );

        FAIL_UNLESS
            ( 0 <= fprintf
              ( foutput, "\nunsigned char thingo [] =\n    " ) );

        char const*del = "{" ;
        for( int c = fgetc( finput ), m = 0; EOF != c; c = fgetc( finput ) ){
            FAIL_UNLESS
                ( 0 <= fprintf
                  ( foutput, "%s 0x%02x", del, c ) );
            del = ( ++m % 8 ) ? "," : ",\n     " ;
        }
        fprintf( foutput, " };\n\n" );
        FAIL_UNLESS( 0 == fclose( finput ) );
    }

    FAIL_UNLESS( 0 == fclose( foutput ) );

    return EXIT_SUCCESS ;
}
