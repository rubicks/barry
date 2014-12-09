/* barry/barry.hh */


#ifndef ___BARRY___BARRY_HH___
#define ___BARRY___BARRY_HH___


#include <iostream>


namespace barry
{
    struct pops
    {
        int version_;
        int help_;
    };

    pops parse_opts( int, char const*[] );

    int main( int, char const*[] );
}

std::ostream&
operator<<( std::ostream&, barry::pops const& );


#endif/* ndef ___BARRY___BARRY_H___ */
