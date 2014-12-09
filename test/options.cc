/* barry/test/options.cc */

#include <stdlib.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/program_options.hpp>

#include "barry.hh"


namespace
{


    struct args
    {
        typedef std::vector< std::string >result_type ;
        result_type
        operator()( int argc, char const*argv[] )
        {
            result_type ret( argc );
            for( int i = 0; i != argc; ++i )
                ret[i] = argv[i] ;
            return ret ;
        }
    } _args ;


    template< typename T >
    std::ostream&
    operator<<( std::ostream&os,
                std::vector< T >const&o )
    {
        std::string pre = "[" ;
        for( auto e : o ){
            os << pre << e ;
            pre = "," ;
        }
        return os << "]" ;
    }

    barry::pops
    _pops_init( void )
    {
        barry::pops ret ;
        ret.version_ = false ;
        ret.help_    = false ;
        return ret ;
    }


    template< typename K, typename V >
    std::ostream&
    operator<<( std::ostream&os,
                std::map< K, V >const&o )
    {
        std::string pre = "{" ;
        for( auto e : o ){
            os << pre << e.first << ":" << e.second ;
            pre = "," ;
        }
        return os << "}" ;
    }
}


int
main( int argc, char const*argv[] )
{
    std::cout
        << "args == "
        << _args( argc, argv )
        << std::endl ;

    namespace po = boost::program_options ;

    po::options_description opde ;
    {
        opde.add_options()
            ( "help,h"    ,
              po::value<int>, "display help message" )
            ( "version,v" , "display version information" )
            ;
    }

    po::variables_map vama ;
    po::store( po::parse_command_line( argc, argv, opde ), vama );

    po::notify( vama );
    
#if 0

    barry::pops pops = barry::parse_opts( argc, argv );
    std::cout << "pops == " << pops << std::endl ;

    {
        char const*fargv[2] = { "foo", "bar" };
        int fargc = 2 ;
        std::cout
            << "barry::parse_opts( fargc, fargv ) == "
            << barry::parse_opts( fargc, fargv )
            << std::endl ;
    }

    {
        char const*fargv[2] = { "foo", "--help" };
        int fargc = 2 ;
        std::cout
            << barry::parse_opts( fargc, fargv )
            << std::endl ;
    }

    {
        char const*fargv[2] = { "foo", "--version" };
        int fargc = 2 ;
        std::cout
            << barry::parse_opts( fargc, fargv )
            << std::endl ;
    }

    {
        char*argv[] = { NULL };
        assert( 0 == _len( argv ) );
        barry::pops pops = barry::parse_opts( argv );
        assert( false == pops.version_ );
        assert( false == pops.help_    );
    }
    {
        char*argv[] = { "prog", NULL };
        assert( 1 == _len( argv ) );
        barry::pops pops = barry::parse_opts( argv );
        assert( false == pops.version_ );
        assert( false == pops.help_    );
    }
    {
        char*argv[] = { "prog", "-v", NULL };
        assert( 2 == _len( argv ) );
        barry::pops pops = barry::parse_opts( argv );
        assert( true  == pops.version_ );
        assert( false == pops.help_    );
    }
    {
        char*argv[] = { "prog", "--version", NULL };
        assert( 2 == _len( argv ) );
        barry::pops pops = barry::parse_opts( argv );
        assert( true  == pops.version_ );
        assert( false == pops.help_    );
    }
#endif
    return EXIT_SUCCESS ;
}
