/**
    @author Finn Mergenthal <finn.mergenthal@stud.htwk-leipzig.de>
 */

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "Bruchberechner.h"

///Prototypes
int summeUeber( const int&, const int&, const int& );
int siebzehn();
template <typename T> void operator << ( std::ostream&, std::vector<T> );

/**
    @brief Testet die Funktionen des Bruchrechners.
    Zum testen werden die einzelnen Module getrennt abgefragt und deren Funktionalität nach Möglchkeit ausgereizt.
 */
int main() {
    try {
        ///
        ///Test Bruch
        std::cout << "Test des Moduls Bruch:\n";
        static const std::string termeBruch[] = {
            "-1/-19 k",                             ///Wenn Zähler und Nenner negativ sind, werden beide beim Kürzen mit -1 multipliziert.
            "0/-16 k",                              ///Eine Zahl mit 0 im Zähler wird auf 0/1 gekürzt.
            "1/0",                                  ///Fehler: Division durch 0
        };
        for( auto str : termeBruch ) {
            try {
                std::cout << str << " = ";
                std::istringstream term( str );
                auto i = berechneNaechstenTerm<int>( term );
                std::cout << i << "\n";
            } catch( const std::runtime_error& e ) {
                std::cout << "\nBei der Berechnung ist ein Fehler aufgetreten:\n";
                std::cout << "\"" << e.what() << "\"\n" << std::endl;
            }
        }
        ///
        static const std::string str1 = "0.5/1 0.5/2 +";                            ///Aufgrund der allgemeinen beschreibung der Klasse Bruch können auch andere Zahlentypen als Speicher für Zähler und Nenner dienen
        std::cout << str1 << " = ";                                                 //Denkbar wäre auch die Implementierung von Zähler und Nenner als unterschiedliche Datentypen.
        std::istringstream term1( str1 );                                           //Dies erscheint mir in diesem Fall aber nicht als Sinnvoll.
        std::cout << berechneNaechstenTerm<double>( term1 ) << "\n";
        ///
        static const std::string str2 = "5 5/2 -";
        std::cout << str2 << " = ";
        std::istringstream term2( str2 );
        std::cout << berechneNaechstenTerm<long unsigned int>( term2 ) << "\n";     ///Dieser Bruchberechner erlaubt bspw. nur natüliche Zahlen als Zähler und Nenner
        ///
        static const std::string str3 = "5.7/2";
        std::cout << str3 << " = ";
        std::istringstream term3( str3 );
        try {
            std::cout << berechneNaechstenTerm<int>( term3 ) << "\n";               ///Falls keine Kommazahlen eingegeben werden dürfen, wird der Punkt richtig als unbekanntes Zeichen identifiziert.
        } catch( const std::runtime_error& e ) {
            std::cout << "\nBei der Berechnung ist ein Fehler aufgetreten:\n";
            std::cout << "\"" << e.what() << "\"\n" << std::endl;
        }
        ///
        ///Test Berechner
        std::cout << "\n\nTest des Moduls Berechner: \n";
        static const int zahlen[] = {17, 19, -5};
        std::vector<int> zahlenstapel( zahlen, zahlen + sizeof( zahlen ) / sizeof( zahlen[0] ) );   //Quelle: User Yacoby von stackoverflow.com - https://stackoverflow.com/a/2236227
        std::cout << "Beispielaufgabe: (Summe von k = 17 bis 19 über -5 * k) + Siebzehn. \n";       ///Möglicher Eingabeweg (nicht implementiert!): 17 19 -5 sum siebzehn +
        std::cout << "Rechenschritte: \n";
        std::cout << "zahlenstapel vor der Berechnung: \n" << zahlenstapel;
        berechneOperation( zahlenstapel, summeUeber );                                              ///Das Modul ermöglicht die unkomplizierte Einführung neuer Operatoren mit beliebig vielen Parametern.
        std::cout << "zahlenstapel nach der Summenbildung: \n" << zahlenstapel;                     ///Zudem ist das Rechnen mit Beliebigen Datentypen möglich (hier int, im Hauptprogramm Bruch<long int>)
        berechneOperation( zahlenstapel, siebzehn );                                                ///Auch Nullstellige Operatoren (Konstanten) sind möglich.
        std::cout << "zahlenstapel nach dem hinzufügen der Konstante: \n" << zahlenstapel;
        berechneOperation( zahlenstapel, add<int> );                                                ///Die Grundrechenarten sind durch das Modul vordefiniert.
        std::cout << "zahlenstapel nach der Addition: \n" << zahlenstapel;
        std::cout << "Endergebnis: " << zahlenstapel.back() << "\n\n";
        ///
        ///Test Bruchberechner
        std::cout << "\n\nTest des Moduls Bruchberechner:\n";
        static const std::string termeBruchberechner[] = {
            "2/4 1/2 1/4 + * 1/8 * k",      ///Testeingabe.
            "2/4 1/2 1/4 + * 1/8 *",        ///Der Bruch wird automatisch nach der Berechnung gekürzt.
            "",                             ///Eine leere Eingabe ist die Zahl null
            "1 5/4 +",                      ///Der Nenner kann weggelassen werden, wenn er 1 ist.
            "    1 5/4  +     ",            ///Leerzeichen zwischen den Zahlen und Operatoren werden ebenfalls ignoriert.
            "-1 7 *",                       ///Negative Zahlen können genutzt werden.
            "1/-1 7 *",                     ///Das Minus negativer Zahlen kann auch im Nenner stehen.
            "9/5 1/5 +",                    ///Eine Zahl mit 1 im Nenner wird als Ganzzahl ohne Nenner ausgegeben.
            "A",                            ///Fehler: Unbekanntes Zeichen
            "1 1",                          ///Fehler: zu wenig Operatoren (bzw. zu viele Zahlen)
            "1 + +",                        ///Fehler: zu viele Operatoren (bzw. zu wenig Zahlen)
            "1/",                           ///Fehler: Nenner wird erwartet
            "1/1 0/1 /",                    ///Fehler: Division durch 0
        };
        for( auto str : termeBruchberechner ) {
            try {
                std::cout << str << " = ";
                std::istringstream term( str );
                auto i = berechneNaechstenTerm<int>( term );
                std::cout << i << "\n";
            } catch( const std::runtime_error& e ) {
                std::cout << "\nBei der Berechnung ist ein Fehler aufgetreten:\n";
                std::cout << "\"" << e.what() << "\"\n" << std::endl;
            }
        }
    } catch( const std::exception& e ) {
        std::cout << "\nBei der Berechnung ist ein unerwarteter Fehler aufgetreten:\n";
        std::cout <<  "\"" << e.what() << "\"\n" << std::endl;
    }
}

///Testfunktion Summe von k = a bis b über c * k
int summeUeber( const int& a, const int& b, const int& c ) {
    int ergebnis = 0;
    for( int k = a; k <= b; k++ )
        ergebnis += k * c;
    return ergebnis;
};
///Testkonstante 17
int siebzehn() {
    return 17;
}
/**
    @brief Gibt einen Vektor über os aus.
    @param os: Der Ausgabestrom
    @param v: Der Vektor
 */
template <typename T> void operator << ( std::ostream& os, std::vector<T> v ) {
    for( auto i : v )
        std::cout << i << std::endl;
}

