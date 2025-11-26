#include <iostream>
#include "List.h"
#include "Telefonbuch.h"
#include "Eintrag.h"

using namespace std;

// 2.2 Aufgabe
Telefonbuch::Telefonbuch()
{
	anzahlEintraege = 0;
	maxAnzahlEintraege = 10;

	// Standardeinträge
	Eintrag* tmp0 = new Eintrag("Betty", "123");
	eintragEinfuegen(tmp0);
	Eintrag* tmp1 = new Eintrag("Anton", "456");
	eintragEinfuegen(tmp1);
	Eintrag* tmp2 = new Eintrag("Cesar", "789");
	eintragEinfuegen(tmp2);

}

Telefonbuch::Telefonbuch(int anzahl)
{
	maxAnzahlEintraege = anzahl;
	anzahlEintraege = 0;

	// Standardeinträge
	Eintrag* tmp0 = new Eintrag("Betty", "123");
	eintragEinfuegen(tmp0);
	Eintrag* tmp1 = new Eintrag("Anton", "456");
	eintragEinfuegen(tmp1);
	Eintrag* tmp2 = new Eintrag("Cesar", "789");
	eintragEinfuegen(tmp2);
}

Telefonbuch::~Telefonbuch()
{
	telefonbuchEintraege.~List();
}

string Telefonbuch::nrSuche(string such)
{
	// ToDo
	//for (Eintrag* e : telefonbuchEintraege) {
	int i = 0;
	for (Eintrag* e = telefonbuchEintraege.get(i);e != nullptr; e = telefonbuchEintraege.get(i)) {
		if (e->getName() == such) return e->getNr();
		i++;
	}
	return "UNKNOWN";
}

List<Eintrag*>& Telefonbuch::getTelefonbuchEintraege()
{
	return telefonbuchEintraege;
}

void Telefonbuch::sortierenNachNamen()
{
	// ToDo
	// 
		// Hinweis >> Die add(index: int, obj : T) Methode funktioniert etwas anders als der Ringtausch!
		// Die Methode fügt das Objekt obj vom Typ T an der Position index in die Liste ein.Alle nachfolgenden Objekte werden um eine Position verschoben.
		//	Beispiel:
		//           11; 12; 13; 14;
		//           11; 12; 55; 13; 14;		
}

void Telefonbuch::toString()
{
	cout << "-----Telefonbucheintraege--------" << endl;
	int i = 0;
	for (Eintrag* e = telefonbuchEintraege.get(0); e != nullptr; e = telefonbuchEintraege.get(i)) {
		cout << e->getName() << " " << e->getNr() << "\n";
		i++;
	}
	cout << "---------------------------------" << endl;
}


void Telefonbuch::eintragLoeschen(string loesch)
{
	int i = 0;
	for (Eintrag* e = telefonbuchEintraege.get(0); e != nullptr; e = telefonbuchEintraege.get(i)) {
		if (e->getName() == loesch) {
			telefonbuchEintraege.remove(e);
			anzahlEintraege--;
			return;
		}
		i++;
	}
}


void Telefonbuch::eintragEinfuegen(Eintrag* einf)
{
	// ToDo für Aufgabe 1 notwendig!
	telefonbuchEintraege.add(einf);
	anzahlEintraege++;
}




