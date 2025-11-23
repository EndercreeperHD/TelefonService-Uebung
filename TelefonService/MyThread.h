#pragma once
#include <iostream>
#include <string>
#include "Thread.h"
#include "Socket.hpp"
#include "Telefonbuch.h"
#include "Eintrag.h"
using namespace std;

class MyThread : public Thread
{
private:
	Socket* work;
	Telefonbuch* daten;
public:
	MyThread(Socket* ini_S, Telefonbuch* ini_TB) { work = ini_S; daten = ini_TB; };
	void run() override {
		string anfrageName = "";
		string antwort;
		cout << "Client verbunden!" << endl;
		while (anfrageName != "exit")
		{
			// 5b) Kommunikation mit read() write()
			anfrageName = work->readLine();
			cout << anfrageName << "\n";
			if (anfrageName.substr(0, 4) == "add ") {
				string zs = anfrageName;
				zs.erase(0, 4);
				daten->eintragEinfuegen(new Eintrag(zs.substr(0, zs.find(" ")), zs.substr(zs.find(" ") + 1, zs.size() - zs.find(" "))));
				antwort = "wurde hinzugefuegt " + zs.substr(0, zs.find(" ")) + " " + zs.substr(zs.find(" ") + 1, zs.size() - zs.find(" "));
				work->write(antwort);
				daten->toString();
			}
			else if (anfrageName.substr(0, 7) == "remove ") {
				string zs = anfrageName;
				zs.erase(0, 7);
				daten->eintragLoeschen(zs);
				antwort = "wurde geloescht " + zs;
				work->write(antwort);
				daten->toString();
			}
			else {
				antwort = daten->nrSuche(anfrageName);
				work->write(antwort);
			}
			antwort.clear();
		}
		work->close();
	};
};