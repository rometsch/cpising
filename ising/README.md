## Ising Model

# Ausführung

Das Programm muss mit dem Pfad des config-files als erstes Argument aufgerufen werden.

# Struktur

Die Klasse `Rng` ist ein Wrapper zur std::random Klasse und stellt Funktionen für Zufallszahlen zur Verfügung.

Die Klasse `lattice` implementiert das Ising Modell und die Multihit und Wärmebad Algorithmen.

In der Klasse `Logger` werden die Simulationen gesteuert und die Messgrößen aufgezeichnet.

`main.cpp` ließt die Parameter aus dem config-file und ruft ein Objekt der `Logger` Klasse auf.
