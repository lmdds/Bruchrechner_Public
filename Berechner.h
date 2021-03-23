#ifndef BERECHNER_H
#define BERECHNER_H

#include <vector>
#include <tuple>
#include <utility>
#include <string>

/**
    @brief Entfernt ein Objekt von zahlenstapel und gibt es zurück.
    Die erzeugte Funktion entfernt das letzte Objekt aus dem Vektor zahlenstapel und gibt es zurück.
    @arg T: Datentyp der Zahlen auf zahlenstapel
    @param zahlenstapel: Stapel von Zahlen des Typs T
    @returns Das entferte Objekt
    @pre stapel hält mind. ein Objekt
 */
template <typename T> T getObject( std::vector<T>& stapel ) {
    auto b = stapel.back();
    stapel.pop_back();
    return b;
}

/**
    @brief Verpackt die Auslesefunktion.
    Die Klasse verpackt die allgemeine Funktionstemplate zum auslesen von i+1 eingegebenen Zahlen in den Tuple der Argumente der Rechenoperation.
    @arg T: Speicherdatentyp des zahlenstapels
    @arg i: Index des Vectors bzw. Tuples
    @arg Args: Datentypen der Argumente der Rechenoperation
 */
//Es nach meinem Kenntnisstand notwendig, die Funktionen in Klassen-Templates zu verpacken (ein allgemeines und ein teilweise spezialisiertes),
//da partial specialization für Funktionen nicht erlaubt ist.
template < typename T, int i, typename ... Args>
class Ausleser {
    public:
        /**
            @brief Überträgt i+1 Stellen von zahlenstapel in args.
            Die Funktion liest den Wert von zahlenstapel am Index i in args am selben Index. Dann ruft sie sich rekursiv auf für den Index i = i - 1.
            Zum füllen eines Tuples aus einem Vektor sollte Rekursion begonnen werden mit "Ausleser < T, (sizeOf ... (Args)) - 1, Args ... >::leseTupleAusVektor( zahlenstapel, args )".
            @param zahlenstapel: Vektor mit auszulesenden Objekten
            @param args: zu füllender Tuple
            @pre zahlenstapel und args müssen mindestens i Indizes haben.
         */
        static void leseTupleAusVektor( std::vector<T>& zahlenstapel, std::tuple<Args ...>& args ) {
            std::get<i>( args ) = getObject( zahlenstapel );
            Ausleser < T, i - 1, Args ... >::leseTupleAusVektor( zahlenstapel, args );
        }
};

/**
    @brief Verpackt die Abbruchbedingung.
    Die Klasse verpackt die Abbruchbedinigung der Compiler-Rekursion von Ausleser.
    Diese wird erreicht, wenn der Index i = -1, also nicht mehr auf einen gültigen Index des Vektors zahlenstapel zeigt.
    @arg T: Speicherdatentyp des zahlenstapels
    @arg Args: Datentypen der Argumente der Rechenoperation
 */
template < typename T, typename ...Args>
class Ausleser < T, -1, Args ... > {
    public:
        /**
            @brief Abbruchbedingung des allgemeinen Ausleser::leseTupleAusVektor.
            Die Funktion bricht die Rekursion von leseTupleAusVektor beim Index i = -1 ab.
            @param zahlenstapel: Vektor mit auszulesenden Objekten
            @param args: zu füllender Tuple
        */
        static void leseTupleAusVektor( std::vector<T>& zahlenstapel, std::tuple<Args ...>& args ) {
        }
};


/**
    @brief Berechnet das Ergebnis aus Funktion operation und den obersten Zahlen aus zahlenstapel.
    Die Funktion übernimmt die Berechnung operation, nimmt so viele Zahlen wie nötig aus dem Vektor zahlenstapel, führt die Funktion aus und tut das Ergebnis zurück an das Ende von zahlenstapel.
    @arg T: Datentyp, mit dem gerechnet werden soll
    @arg Args: Datentypen der Parameter von operation
    @param zahlenstapel: Der vektor mit den zu berechnenden Zahlen
    @param operation: Die Berechnung die auf die Zahlen aus den zahlenstapel angewand werden soll
    @pre Alle Parameter Args müssen den Datentyp T haben (bzw. durch ein Gleichzeichen aus ihm überführbar sein)
 */
template <typename T, typename ... Args> void berechneOperation( std::vector<T>& zahlenstapel, T operation( const Args& ... ) ) {
    constexpr int anzahlArgs = sizeof ...( Args );
    if( anzahlArgs > zahlenstapel.size() )
        throw std::runtime_error( "Es sind nicht genug Zahlen für diese Berechnung mit " + std::to_string( anzahlArgs ) + " Stellen." );
    std::tuple<Args ...> args;
    Ausleser < T, anzahlArgs - 1, Args ... >::leseTupleAusVektor( zahlenstapel, args );
    T b = std::apply( operation, args );
    zahlenstapel.push_back( b );
}

///Templates für Grundrechenarten
/**
    @brief Addiert zwei Zahlen.
    Proxyfunktion zur Addition von zwei Summanden gleichen Typs.
    @arg T: Datentyp der Zahlen
    @param summandaA: Erster Summand
    @param summandaB: Zweiter Summand
    @pre Der Operator + (T, T) muss definiert sein.
 */
template <typename T> T add( const T& summandA, const T& summandB ) {
    return summandA + summandB;
}
/**
    @brief Subtrahiert zwei Zahlen.
    Proxyfunktion zur Subtraktion von zwei Zahlen gleichen Typs.
    @arg T: Datentyp der Zahlen
    @param minuend: Minuend
    @param dubtrahend: Subtrahend
    @pre Der Operator - (T, T) muss definiert sein.
 */
template <typename T> T sub( const T& minuend, const T& subtrahend ) {
    return minuend - subtrahend;
}
/**
    @brief Multipliziert zwei Zahlen.
    Proxyfunktion zur Multiplikation von zwei Zahlen gleichen Typs.
    @arg T: Datentyp der Zahlen
    @param faktorA: Erster Faktor
    @param faktorB: Zweiter Faktor
    @pre Der Operator * (T, T) muss definiert sein.
 */
template <typename T> T mul( const T& faktorA, const T& faktorB ) {
    return faktorA * faktorB;
}
/**
    @brief Dividiert zwei Zahlen.
    Proxyfunktion zur Division von zwei Zahlen gleichen Typs.
    @arg T: Datentyp der Zahlen
    @param divident: Divident
    @param divisor: Divisor
    @pre Der Operator / (T, T) muss definiert sein.
 */
template <typename T> T div( const T& divident, const T& divisor ) {
    return divident / divisor;
}

#endif // BERECHNER_H
