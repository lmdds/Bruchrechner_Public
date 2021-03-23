#ifndef BRUCHBERECHNER_H
#define BRUCHBERECHNER_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

#include "Bruch.h"
#include "Berechner.h"

/**
    @brief Testet, ob die nächste Zeichenkette eine Zahl ist.
    Die Funktion gibt True zurück, wenn das nächste Zeichen eine Ziffer ist oder ein Minus und direkt danach eine Ziffer folgt. Whitespace chars werden nicht ignoriert.
    @param Der Stream, der auf Zahlen getestet werden soll
    @returns True, wenn Zahl gefunden
    @pre Es muss ein Zeichen im Eingabestrom vorhanden sein
 */
bool naechsteIstZahl( std::istream& );

/**
    @brief Entfernt alle whitespace chars bis zum ersten Zeichen.
    Die Funktion löscht alle whitespce chars bis zum ersten regulären Zeichen aus dem Eingabestrom und gibt true zurück, wenn der Eingangsstrom dann nicht leer ist.
    @param Der Eingangsstrom, aus dem die chars entfernt werden sollen
    @returns True, wenn im Eingangsstrom nicht-whitespace chars enthalten sind
 */
bool clearWhitespacesCharFound( std::istream& );

/**
    @brief Gibt einen Bruch aus.
    Der Operator gibt den Bruch b über den Ausgabestrom os aus. Wenn möglich, wird der Bruch als Ganzzahl ausgegeben.
    @arg T: Speicherdatentyp von Zähler und Nenner von b
    @param os: Der Ausgabestrom
    @param b: Der auszugebende Bruch
    @returns Den zusammengefügten Ausgabestrom
 */
template <typename T> std::ostream& operator << ( std::ostream& os, const Bruch<T>& b ) {
    os << b.getZaehler();
    ///Sollte der Nenner 1 sein, ist seine Ausgabe überflüssig. Der Bruch wird dann als Ganzzahl ausgegeben.
    if( b.getNenner() != 1 )
        os << "/" << b.getNenner();
    return os;
}

/**
    @brief Einlesen eines Bruchs.
    Der Operator liest einen Bruch des Typs T aus dem Eingabestrom is ein.
    Dabei werden alle whitespace chars vor dem Bruch aus is gelöscht.
    Sollte direkt nach dem Nenner kein Bruchstrich ("/") kommen, wird die Zahl als Ganzzahl interpretiert und 1 in den Nenner geschrieben.
    @arg T: Datentyp von Zähler und Nenner des Bruchs
    @param is: Eingabestrom aus dem der Bruch gelesen wird
    @param b: Bruch, in den Zähler und Nenner geschrieben werden
    @pre Die Nächste Zeichenkette ist ein Bruch mit dem Format "[Zähler]/[Nenner]" oder "[Zähler]"
 */
template <typename T> void operator >> ( std::istream& is, Bruch<T>& b ) {
    if( !clearWhitespacesCharFound( is ) )
        throw std::logic_error( "Der gegebene Inputstream ist leer." );
    if( !naechsteIstZahl( is ) )
        throw std::logic_error( "Der Ausdruck beginnt nicht mit einer Zahl, obwohl ein Bruch erwartet wird." );
    ///Auslesen des Zaehlers
    T zaehler;
    is >> zaehler;
    ///Auslesen des Bruchstrichs oder anderen nächsten Zeichens
    char c;
    if( is.get( c ) ) {
        ///Falls auf den Zähler ein Bruchstrich folgt, wird der Nenner ausgelesen. Ansonsten wird die Zahl als Ganze Zahl interpretiert.
        if( c == '/' ) {
            ///Auslesen des Nenners
            if( !naechsteIstZahl( is ) )
                throw std::runtime_error( "Der Ausdruck besitzt direkt nach einem Bruchstrich keine Zahl, obwohl ein Nenner erwartet wird." );
            T nenner;
            is >> nenner;
            b = Bruch<T>( nenner, zaehler );
        } else {
            is.putback( c );
            b = Bruch<T>( zaehler );
        }
    } else
        b = Bruch<T>( zaehler );
}

/**
    @brief Berechnet das Ergebnis von term.
    Die Funktion liest den Term aus dem Eingangsstrom term und berechnet das Ergebnis.
    Die Zahlen des Terms werden als Brüche interpretiert. Der Term muss in Postfixnotation übergeben werden.
    Das Endergebnis wird vollständig gekürzt zurückgegeben.
    @arg T: Datentyp von Zähler und Nenner
    @param term: der zu berechnende Term
    @returns Das errechnete Endergebnis
    @pre term ist ein gültiger Term in Postfixnotation
 */
template<typename T> Bruch<T> berechneNaechstenTerm( std::istream& term ) {
    std::vector<Bruch<T>> zahlenstapel;
    char c;
    ///Liest die Brüche aus term aus und führt die Rechenzeichen aus bis kein (nicht-leerer) char in term verblieben ist.
    while( clearWhitespacesCharFound( term ) ) {
        if( naechsteIstZahl( term ) ) {
            ///Einlesen und Abspeichern des Bruchs
            Bruch<T> b;
            term >> b;
            zahlenstapel.push_back( b );
        } else {
            ///Einlesen und auswerten des Rechenzeichens
            term >> c;
            switch( c ) {
                case '+': {
                        berechneOperation( zahlenstapel, add<Bruch<T>> );
                        break;
                    }
                case '-': {
                        berechneOperation( zahlenstapel, sub<Bruch<T>> );
                        break;
                    }
                case '*': {
                        berechneOperation( zahlenstapel, mul<Bruch<T>> );
                        break;
                    }
                case '/': {
                        berechneOperation( zahlenstapel, div<Bruch<T>> );
                        break;
                    }
                case 'k': {
                        berechneOperation( zahlenstapel, kuerzeBruch<T> );
                        break;
                    }
                default:
                    throw std::runtime_error( "Es wurde ein unbekanntes Zeichen eingegeben: " + std::string( 1, c ) );
            }
        }
    }
    ///Falls nicht genau ein Bruch am Ende des Terms verblieben ist, wird eine entsprechende Exception geworfen.
    if( 1 < zahlenstapel.size() )
        throw std::runtime_error( "Es sind nicht genug Operatoren für diese Berechnung." );
    if( 0 == zahlenstapel.size() )
        //Alternative: Werfen eines entsprechenden Fehlers
        //throw std::runtime_error( "Es wurde keine Zahl eingegeben." );
        return Bruch<T>( 0 );
    Bruch<T> b = zahlenstapel.front();
    b.kuerzeBruch();
    return b;
}

#endif // BRUCHBERECHNER_H
