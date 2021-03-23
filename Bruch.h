#ifndef BRUCH_H
#define BRUCH_H

#include <type_traits>
#include <stdexcept>

/**
        @brief Gibt größten gemeinsamen Teiler der Zahlen zurück.
        Die Funktion bestimmt rekursiv den ggT der natürlichen Zahlen a und b.
        @param a: Zahl a
        @param b: Zahl b
        @returns Größten gemeinsamen Teiler
 */
unsigned long int ggt( const unsigned long int& a, const unsigned long int& b );

/**
        @brief Speichert eine rationale Zahl als Bruch.
        Die Zahl wird als Zähler und Nenner gespeichert, wobei beide Variabeln den Datentyp T haben.
        @arg T: Speicherklasse von Zähler und Nenner
 */
template <typename T>
class Bruch {
    public:
        /**
            @brief Konstruktor: Initialisiert den Bruch.
            Der Konstruktor initialisiert den Bruch mit zaehler/nenner. Falls der nenner = 0 ist, wird ein runtime-error geworfen, da eine Division durch 0 nicht erlaubt wird.
            @param n: Nenner des Bruchs
            @param z: Zähler des Bruchs
         */
        Bruch( const T& n, const T& z )
            :  zaehler( z ), nenner( n ) {
            if( nenner == 0 )
                throw std::runtime_error( "Eine Division durch Null (bzw. eine Null im Nenner) ist nicht möglich." );
        }

        /**
            @brief Standardkonstruktor: Initialisiert den Bruch.
            Der Konstruktor initialisiert den Bruch mit zaehler/1. Falls kein Zähler übergeben wird, wird der Bruch mit 0/1 (= 0) inititalisiert.
            @param z: zaehler des Bruchs, default = 0
         */
        Bruch( const T& z = 0 )
            :  zaehler( z ), nenner( 1 ) {
        }

        /**
            @brief Kürzt den Bruch auf die einfachste Schreibweise.
            Zum kürzen des Bruchs
            - werden Zähler und Nenner durch den größten gemeinsamen Teiler geteilt.
            - werden beide Zahlen mit -1 multipliziert, falls beide Zahlen negativ sind.
            Ist der Bruch 0/x (mit x != 0) lässt er sich am simpelsten durch 0/1 darstellen. Ansonsten lässt er sich nicht sinnvoll kürzen.
         */
        void kuerzeBruch() {
            if( zaehler == 0 )
                nenner = 1;
            else {
                ///Der angewandte Algorithmus funktioniert für natürliche Zahlen.
                ///Da die Bruchklasse auch negative Zahlen behandeln kann, wird für eine negative Zahl der ggT der entsprechenden positiven Zahl ermittelt.
                T betragZaehler = zaehler;
                T betragNenner = nenner;
                if( betragZaehler < 0 )
                    betragZaehler *= -1;
                if( betragZaehler < 0 )
                    betragZaehler *= -1;
                T ggTeiler = ggt( betragZaehler, betragNenner );
                nenner /= ggTeiler;
                zaehler /= ggTeiler;
                ///Falls Nenner und Zähler negativ sind, lässt sich der Bruch am simpelsten durch die entsprechenden positiven Zahlen darstellen.
                ///Falls nur der Nenner negativ ist wird das Minus in den Zähler gebracht.
                if( nenner < 0 ) {
                    nenner *= -1;
                    zaehler *= -1;
                }
            }
        }

        /**
            @brief Gibt den Zähler des Bruchs zurück.
            @returns Zähler
         */
        T getZaehler() const {
            return zaehler;
        }


        /**
            @brief Gibt den Nenner des Bruchs zurück.
            @returns Nenner
         */
        T getNenner() const {
            return nenner;
        }

    private:
        T zaehler;
        T nenner;
};

/**
        @brief Gibt Kehrwert des Bruchs zurück.
        Die Funktion erzeugt einen Neuen Bruch mit dem Zähler von b als Nenner und dem Nenner von b als Zähler.
        @arg T: Speicherklasse von Zähler und Nenner
        @param b: ursprünglicher Bruch
        @returns Kehrwert des Bruchs
 */
template <typename T> Bruch<T> kehrwert( const Bruch<T>& b ) {
    return Bruch<T>( b.getZaehler(), b.getNenner() );
}

/**
        @brief Gibt den gekürzten Bruch zurück.
        @arg T: Speicherklasse von Zähler und Nenner
        @param b: ursprünglicher Bruch
        @returns Den gekürzten Bruch
 */
template <typename T> Bruch<T> kuerzeBruch( const Bruch<T>& b ) {
    //Den Parameter als Referenz zu nehmen und dann 'manuell' zu kopieren ist nötig, damit b eine const Referenz sein kann
    //und die Parameter der Operation damit zu den Anforderungen von berechneOperation passt.
    Bruch<T> a = b;
    a.kuerzeBruch();
    return a;
}

///Addition
/**
        @brief Addiert die Brüche.
        @arg A: Speicherklasse von Zähler und Nenner von SummandA
        @arg B: Speicherklasse von Zähler und Nenner von SummandB
        @param summandA: der erste Summand
        @param summandB: der zweite Summand
        @returns Die Summe
 */
template <typename A, typename B> auto operator + ( const Bruch<A>& summandA, const Bruch<B>& summandB ) {
    auto zaehler = ( summandA.getZaehler() * summandB.getNenner() ) + ( summandB.getZaehler() * summandA.getNenner() );
    auto nenner = summandA.getNenner() * summandB.getNenner();
    return Bruch( nenner, zaehler );
}
/**
        @brief Addiert einen Bruch mit einer Zahl.
        @arg A: Speicherklasse von Zähler und Nenner von SummandA
        @arg B: Typ vom zweiten Summand
        @param summandA: der erste Summand
        @param summandB: der zweite Summand
        @returns Die Summe
 */
template <typename A, typename B> auto operator + ( const Bruch<A>& summandA, const B& summandB ) {
    return summandA + Bruch<B>( summandB );
}
/**
        @brief Addiert einen Bruch mit einer Zahl.
        @arg A: Typ vom ersten Summand
        @arg B: Speicherklasse von Zähler und Nenner von SummandB
        @param summandA: der erste Summand
        @param summandB: der zweite Summand
        @returns Die Summe
 */
template <typename A, typename B> auto operator + ( const A& summandA, const Bruch<B>& summandB ) {
    return Bruch<A>( summandA ) + summandB;
}

///Subtraktion
/**
        @brief Sutrahiert die Brüche.
        @arg A: Speicherklasse von Zähler und Nenner von minuend
        @arg B: Speicherklasse von Zähler und Nenner von subtrahend
        @param minuend: der Minuend
        @param subtrahend: der Subtrahend
        @returns Die Differenz
 */
template <typename A, typename B> auto operator - ( const Bruch<A>& minuend, const Bruch<B>& subtrahend ) {
    return minuend + ( subtrahend * -1 );
}
/**
        @brief Sutrahiert die Brüche.
        @arg A: Speicherklasse von Zähler und Nenner von minuend
        @arg B: Typ vom subtrahend
        @param minuend: der Minuend
        @param subtrahend: der Subtrahend
        @returns Die Differenz
 */
template <typename A, typename B> auto operator - ( const Bruch<A>& minuend, const B& subtrahend ) {
    return minuend - Bruch<B>( subtrahend );
}
/**
        @brief Sutrahiert die Brüche.
        @arg A: Typ vom minuend
        @arg B: Speicherklasse von Zähler und Nenner von subtrahend
        @param minuend: der Minuend
        @param subtrahend: der Subtrahend
        @returns Die Differenz
 */
template <typename A, typename B> auto operator - ( const A& minuend, const Bruch<B>& subtrahend ) {
    return Bruch<A>( minuend ) - subtrahend;
}

///Multiplikation
/**
        @brief Multipliziert die Brüche.
        @arg A: Speicherklasse von Zähler und Nenner von faktorA
        @arg B: Speicherklasse von Zähler und Nenner von faktorB
        @param faktorA: der erste Faktor
        @param faktorB: der zweite Faktor
        @returns Das Produkt
 */
template <typename A, typename B> auto operator * ( const Bruch<A>& faktorA, const Bruch<B>& faktorB ) {
    return Bruch( faktorA.getNenner() * faktorB.getNenner(), faktorA.getZaehler() * faktorB.getZaehler() );
}
/**
        @brief Multipliziert die Brüche.
        @arg A: Speicherklasse von Zähler und Nenner von faktorA
        @arg B: Typ von faktorB
        @param faktorA: der erste Faktor
        @param faktorB: der zweite Faktor
        @returns Das Produkt
 */
template <typename A, typename B> auto operator * ( const Bruch<A>& faktorA, const B& faktorB ) {
    return faktorA * Bruch<B>( faktorB );
}
/**
        @brief Multipliziert die Brüche.
        @arg A: Typ von faktorA
        @arg B: Speicherklasse von Zähler und Nenner von faktorB
        @param faktorA: der erste Faktor
        @param faktorB: der zweite Faktor
        @returns Das Produkt
 */
template <typename A, typename B> auto operator * ( const A& faktorA, const Bruch<B>& faktorB ) {
    return Bruch<A>( faktorA ) * faktorB;
}

///Division
/**
        @brief Dividiert die Brüche.
        @arg A: Speicherklasse von Zähler und Nenner von divident
        @arg B: Speicherklasse von Zähler und Nenner von divisor
        @param divident: der Divident
        @param divisor: der Divisor
        @returns Der Quotient
 */
template <typename A, typename B> auto operator / ( const Bruch<A>& divident, const Bruch<B>& divisor ) {
    return divident * kehrwert( divisor );
}
/**
        @brief Dividiert die Brüche.
        @arg A: Speicherklasse von Zähler und Nenner von divident
        @arg B: Typ von divisor
        @param divident: der Divident
        @param divisor: der Divisor
        @returns Der Quotient
 */
template <typename A, typename B> auto operator / ( const Bruch<A>& divident, const B& divisor ) {
    return divident / Bruch<B>( divisor );
}
/**
        @brief Dividiert die Brüche.
        @arg A: Typ von divident
        @arg B: Speicherklasse von Zähler und Nenner von divisor
        @param divident: der Divident
        @param divisor: der Divisor
        @returns Der Quotient
 */
template <typename A, typename B> auto operator / ( const A& divident, const Bruch<B>& divisor ) {
    return Bruch<A>( divident ) / divisor;
}


#endif // BRUCH_H
