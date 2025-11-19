#include <string>
using namespace std;

#include "Eintrag.h"


Eintrag::Eintrag(string n_init, string nr_init)
{
	name = n_init;
	telefonnr = nr_init;
}

Eintrag::~Eintrag()
{
}

string Eintrag::getNr()
{
	return telefonnr;
}

string Eintrag::getName()
{
	return name;
}

void Eintrag::setNr(string tmp)
{
	telefonnr = tmp;
}

void Eintrag::setName(string tmp)
{
	name = tmp;
}
