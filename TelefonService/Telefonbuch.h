#pragma once
#include <string>
#include "List.h"
using namespace std;

class Eintrag;

// 2.2 Aufgabe
class Telefonbuch
{
private:
	int maxAnzahlEintraege;
	List <Eintrag*>telefonbuchEintraege; 
	int anzahlEintraege;
	

public:
	void eintragEinfuegen(Eintrag*);
	void eintragLoeschen(string);
	string nrSuche(string);
	List<Eintrag*>& getTelefonbuchEintraege();
	void sortierenNachNamen();
	void toString();
	Telefonbuch();
	Telefonbuch(int);
	~Telefonbuch();
};