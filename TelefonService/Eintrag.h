#pragma once

class Eintrag
{
private:
	string name;
	string telefonnr;
public:
	string getNr ();
	string getName ();
	void setNr (string);
	void setName (string);
	Eintrag(string, string);
	~Eintrag();
};