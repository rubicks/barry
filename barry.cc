/* barry/barry.cc */


#include <cstdlib>
#include <iostream>

#include <boost/program_options.hpp>

#include "barry_detail.hh"
#include "barry.hh"


namespace po = boost::program_options ;


po::options_description&&
barry::detail::optdes( void )
{
    po::options_description ret( "allowed options" );
    ret.add_options()
        ( "help,h"    , "display help message"        )
        ( "version,v" , "display version information" )
        ;
    return std::move( ret );
}


po::variables_map&&
barry::detail::varmap( int ac, char const*av[] )
{
    po::variables_map ret ;
    po::options_description desc ;
    po::store( po::parse_command_line( ac, av, optdes() ), ret );
    /* po::notify( ret ); */
    return std::move( ret );
}


std::ostream&
operator<<( std::ostream&os, barry::pops const&o )
{
    return os
        << "{"
        << "version_:" << o.version_
        << ","
        << "help_:" << o.help_
        << "}"
        ;
}


barry::pops
barry::parse_opts( int argc, char const*argv[] )
{
    po::variables_map const varmap = barry::detail::varmap( argc, argv );
    return barry::pops();
}


int
barry::main( int argc, char const*argv[] )
{
    barry::pops pops = barry::parse_opts( argc, argv );
    std::cout << pops << std::endl ;
    return EXIT_SUCCESS ;
}



#if 0
barry_opts
barry_parse_opts( int argc, char**argv )
{
    barry_opts ret ;
    ret.version_ = false ;
    ret.help_    = false ;

    while( true ){
        int idx = 0 ;
        int c = getopt_long( argc, argv, "vh", opts, &idx );

        if( -1 == c ) break ;

    reswitch:
        switch( c ){
        case 0:
            c = opts[ idx ].val ;
            goto reswitch ;
        case 'v': 
            printf( "option -v/--version\n" );
            ret.version_ = true ;
            break ;
        case 'h':
            printf( "option -h/--help\n" );
            ret.help_ = true ;
            break ;
        case '?':
            break ;
        default:
            abort();
        }
    }
    return ret ;
}


int
barry_run( int argc, char**argv )
{
    barry_popts_t popts = barry_parse_opts( argc, argv );
    printf("popts.version_ == %s\n", _boolstr( popts.version_ ) );
    printf("popts.help_    == %s\n", _boolstr( popts.help_    ) );

    return EXIT_SUCCESS ;
}

#endif


