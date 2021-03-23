/**
    @author Finn Mergenthal <finn.mergenthal@stud.htwk-leipzig.de>
 */

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "Bruchberechner.h"

/**
    @brief Errechnet das Ergebnis aus der Eingabe.
    Die Main-Funktion liest die, durch den*die Nutzer*in eingegebenen Terme zeilenweise ein, errechnet das Ergebnis und gibt es über die Konsole aus.
    Im Fall einer Exception wird der Fehler ausgegeben und der*die Nutzer*in kann eine erneute Eingabe tätigen.
 */
int main() {
    while( std::cin ) {
        std::string str;
        try {
            std::getline( std::cin, str );
            std::istringstream term( str );
            auto i = berechneNaechstenTerm<long int>( term );
            std::cout << i << "\n" << std::endl;
        } catch( const std::runtime_error& e ) {
            std::cout << "Bei der Berechnung ist ein Fehler aufgetreten:\n";
            std::cout << "\"" << e.what() << "\"\n" << std::endl;
        } catch( const std::exception& e ) {
            std::cout << "Bei der Berechnung ist ein unerwarteter Fehler aufgetreten:\n";
            std::cout <<  "\"" << e.what() << "\"\n" << std::endl;
        }
    }
}


