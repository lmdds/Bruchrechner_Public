#include "Bruchberechner.h"

bool naechsteIstZahl( std::istream& is ) {
    char c;
    if( is.get( c ) ) {
        ///Prüft, ob die nächste Zeichenkette eine Zahl ist oder nicht
        if( ( c >= '0' ) && ( c <= '9' ) ) {
            ///Falls das nächste nicht-leere Zeichen eine Ziffer ist, ist die nächste Zeichenkette eine Zahl.
            is.putback( c );
            return true;
        } else if( ( c == '-' ) && is ) {
            ///Falls das nächste nicht-leere Zeichen ein '-' ist, prüft die Funktion das übernächste Zeichen
            if( ( is.peek() >= '0' ) && ( is.peek() <= '9' ) ) {
                is.putback( c );
                return true;
            } else {
                is.putback( c );
                return false;
            }
        } else {
            is.putback( c );
            return false;
        }
    } else
        return false;
}

bool clearWhitespacesCharFound( std::istream& is ) {
    char c;
    if( is >> c ) {
        is.putback( c );
        return true;
    } else
        return false;
}
