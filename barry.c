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


bool
goodc( char const c )
{
    return
        ( ( '0' <= c ) && ( c <= '9' ) ) ||
        ( ( 'A' <= c ) && ( c <= 'Z' ) ) ||
        ( ( 'a' <= c ) && ( c <= 'z' ) ) ||
        ( '_' == c ) ;
}


char*
symbolize( char const*o )
{
    static char buf[ PATH_MAX ] ;
    memset( buf, 0, PATH_MAX );
    for( size_t i = 0, n = strlen( o ); i < n ; ++i ){
        buf[i] = goodc( o[i] ) ? o[i] : '_' ;
    }
    return buf ;
}


void
print_help( FILE*f )
{
    fprintf( f, "\nUsage:");
    fprintf( f, "\n  barry [option]... [<file>...]");
    fprintf( f, "\n");
    fprintf( f, "\nOptions:");
    fprintf( f, "\n");
    fprintf( f, "\n  -V, --version     output version information and exit");
    fprintf( f, "\n  -h, --help        display this help and exit");
    fprintf( f, "\n  -o, --out <file>  write to specified file (default stdout)" );
    fprintf( f, "\n");
    fprintf( f, "\n");
}


void
readwrite( FILE*fin, FILE*fout )
{
    char const*del = "\n{" ;
    for( int c = fgetc( fin ), m = 0; EOF != c; c = fgetc( fin ) ){
        FAIL_UNLESS
            ( 0 <= fprintf
              ( fout, "%s 0x%02x", del, c ) );
        del = ( ++m % 8 ) ? "," : ",\n " ;
    }
    fprintf( fout, " };\n" );

}


int
main( int const argc, char**argv )
{
    FILE*fout = stdout ;

    while( true ){
        static struct option opts[] =
            {
                { "help",    no_argument,       0, 'h' },
                { "version", no_argument,       0, 'V' },
                { "out",     required_argument, 0, 'o' },
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
            print_help( stdout );
            return EXIT_SUCCESS ;

        case 'o':
            FAIL_UNLESS( fout = fopen( optarg, "w" ) );
            break ;

        default:
            fprintf( stderr, "getopt_long() returned '%c'", c );
        case '?':
            /* getopt_long already printed an error message. */
            print_help( stderr );
            return EXIT_FAILURE ;
        }
    }


    size_t non_opt_args = 0 ;

    for( int i = optind, n = argc ; i < n ; ++i ){
        ++non_opt_args ;

        FILE*fin ;
        if( 0 == strcmp( "-", argv[i] ) ){
            /* do explicit stdin */
            fin = stdin ;
        }else{
            /* do named file */
            FAIL_UNLESS( fin = fopen( argv[i], "r" ) );
            FAIL_UNLESS
                ( 0 <= fprintf
                  ( fout,
                    "\nunsigned char %s [] =",
                    symbolize( argv[i] ) ) );
        }
        readwrite( fin, fout );
        FAIL_UNLESS( 0 == fclose( fin ) );
    }

    if( 0 == non_opt_args ){
        readwrite( stdin, fout );
    }

    FAIL_UNLESS( 0 == fclose( fout ) );

    return EXIT_SUCCESS ;
}
