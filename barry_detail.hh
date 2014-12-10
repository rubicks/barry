/* barry/barry.hh */


#ifndef ___BARRY___BARRY_DETAIL_HH___
#define ___BARRY___BARRY_DETAIL_HH___


#include <iostream>


namespace barry
{
    namespace detail
    {
        boost::program_options::options_description
        optdes( void );

        boost::program_options::variables_map
        varmap( int ac, char const*av[] );
    }
}


#endif/* ndef ___BARRY___BARRY_DETAIL_HH___ */
