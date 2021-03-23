#include "Bruch.h"

//Der Algorithmus ist dem GdP Seminar Aufgabe 5.4 entnommen.
unsigned long int ggt( const unsigned long int& a, const unsigned long int& b ) {
    if( a < b )
        return ggt( b, a );
    else if( ( a % b ) == 0 )
        return b;
    else
        return ggt( b, a % b );
}
