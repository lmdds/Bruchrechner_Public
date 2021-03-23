Aufgabe 2: Datentyp Bruch
Autor: Finn Mergenthal

Ein ausführlicher Test der drei Module findet sich in mainTest.cpp. Die Quelltextkommentare erklären das Ziel des jeweiligen Tests.

Kommentierung des Quellcode:
    - DoxyGen-artige Kommentare für die allgemeine Beschreibung des Programms
    - "//" für sonstige Bemerkungen
Funktionsparameter habe ich mit dem Tag "@param" kommentiert, Templateparameter mit dem Tag "@arg".

Was noch zu verbessern wäre:
    - Das Modul Bruchberechner allgemeiner schreiben, so dass es Terme jeglicher Datentypen berechnen kann und die entsprechnenden Rechenoperationen mit den Zeichen als Parameter übernimmt
    - Prüfen, ob die übergebenen Typen für Zähler und Nenner der Klasse Bruch zulässig sind und ggf. saubere Fehlermeldung beim Kompilieren ausgeben
    - In Berechner die Nutzung von Operatoren auf unterschiedliche Datentypen, die aus dem Datentyp des jeweiligen zahlenstapels gecastet werden können, vereinfachen. Dazu müsste der Zuweisungsoperator '=' überladen werden, so dass er bspw. einen Bruch in eine natürliche Zahl überführt (falls der Bruch die entsprechenden Bedingungen erfüllt) und damit ein Operator summeAus(const unsigend int& von, usw ... ) übergeben werden kann, der die entsprechenden Vorraussetzungen für die Berechnung über den Datentyp definieren kann.
